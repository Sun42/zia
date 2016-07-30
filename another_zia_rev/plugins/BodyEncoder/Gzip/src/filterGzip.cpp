#include <sstream>
#include <ctime>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <boost/process.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "filterGzip.h"
#include "StringToType.hpp"
#include "TypeToString.hpp"

filterGzip::filterGzip(zia::IConfiguration* conf) : _configuration(conf)
{
  configureFilter();
}

filterGzip::~filterGzip(void)
{
}

std::size_t	filterGzip::getObjectSize() const
{
  return (sizeof(*this));
}

void		filterGzip::constructObject(void* storage) const
{
  new (storage) filterGzip(this->_configuration);
}

int		filterGzip::getPriority() const
{
  return (1);
}

void		filterGzip::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

void		filterGzip::configureFilter(void)
{
  if (!this->_configuration)
    return ;
  if (this->_configuration->hiveExists("GZIP-Plugin"))
    {
      const zia::IDictionnary&  gHive = this->_configuration->getHive("GZIP-Plugin");
      this->_gzipPath = gHive.get("binary-path");
      if (!boost::filesystem::exists(this->_gzipPath))
	this->_gzipPath = "/bin/gzip";
      std::cout << "=============== " << gHive.get("size-limit")<< std::endl;
      this->_sizeLimit = stringToType<int>(gHive.get("size-limit"));
      if (this->_sizeLimit < 1)
	this->_sizeLimit = 1024;
    }
}

zia::filter::Status	filterGzip::bodyEncode(
					       const zia::network::IConnection&,
					       const zia::http::IRequestHeader& rq,
					       const zia::http::IResponseHeader& rh,
					       std::istream& isPlainBody,
					       std::ostream& osEncodeBody)
{
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.translation = zia::filter::Status::DECLINE;
  status.persistence = zia::filter::Status::REMOVEME;
  //  std::cout << "************************************* " << rq.entities().get("Accept-Encoding") << std::endl;
  if (isPlainBody.rdbuf()->in_avail() > static_cast<int>(this->_sizeLimit) && rq.entities().get("Accept-Encoding").find("gzip") != std::string::npos)
    {
  std::cout << "************************************* " << rq.entities().get("Accept-Encoding") << std::endl;
      std::string filename;
      {
	std::ofstream tmp;
	filename = typeToString<int>((int)this);
	tmp.open(filename.c_str(), std::ofstream::trunc);
	tmp << isPlainBody.rdbuf();
	tmp.close();
      }
      boost::process::command_line cl(this->_gzipPath);
      cl.argument(filename);
      boost::process::launcher l;
      l.set_stdout_behavior(boost::process::redirect_stream);
      l.set_merge_out_err(true);
      boost::process::child c = l.start(cl);
      //      boost::process::pistream& is = c.get_stdout();
      boost::process::status s = c.wait();

      if (s.exited() && EXIT_SUCCESS == s.exit_status())
	{
	  std::fstream tmp;
	  std::string  resp = filename + ".gz";
	  tmp.open(resp.c_str());
	  osEncodeBody << tmp.rdbuf();
	  tmp.close();
	  remove(resp.c_str());
	  //	  osEncodeBody << is.rdbuf();
	  std::stringstream f;
	  f << (((std::stringstream &)osEncodeBody).str().size() );
	  (const_cast<zia::IDictionnary &>(rh.entities())).set("Content-Encoding", "gzip");
	  (const_cast<zia::IDictionnary &>(rh.entities())).set("Content-length", f.str());
	}
      else
	{
	  osEncodeBody << isPlainBody.rdbuf();
	  remove(filename.c_str());
	}
    }
  else
    {
      osEncodeBody << isPlainBody.rdbuf();
    }
  return (status);
}

zia::filter::Status	filterGzip::bodyEncodeEnding(
					       const zia::network::IConnection& co,
					       const zia::http::IRequestHeader& req,
					       const zia::http::IResponseHeader& res,
					       std::ostream& o)
{
  std::istream in(o.rdbuf());
  //  in << o.rdbuf();
  return (this->bodyEncode(co, req, res,  in, o));
}
