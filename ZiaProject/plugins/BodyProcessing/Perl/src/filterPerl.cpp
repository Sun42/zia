/// \file

#include <string>
#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "Utils.h"
#include "filterPerl.h"
#include "Dictionnary.h"
#include "TypeToString.hpp"

static const std::string	PERL_SECTION = "PerlPlugin";

filterPerl::filterPerl(zia::IConfiguration* conf) : _configuration(conf)
{
  configureFilter();
}

filterPerl::~filterPerl(void)
{
}

std::size_t	filterPerl::getObjectSize() const
{
  return (sizeof(*this));
}

void		filterPerl::constructObject(void* storage) const
{
  new (storage) filterPerl(this->_configuration);
}

int		filterPerl::getPriority() const
{
  return (11);
}

void			filterPerl::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

void			filterPerl::configureFilter(void)
{
  if (0 == this->_configuration)
    return;

  if (this->_configuration->hiveExists(PERL_SECTION))
    {
      const zia::IDictionnary&  mainHive = this->_configuration->getHive(PERL_SECTION);
      this->_perlPath = mainHive.get("binary path");
    }
}

zia::filter::Status	filterPerl::processBody(const zia::network::IConnection& /*con*/,
					       zia::http::IRequestHeader& rh,
					       zia::http::IResponseHeader& rr,
					       std::istream& /*isRequestBody*/,
					       std::ostream& osResponseBody)
{
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;
  status.translation = zia::filter::Status::DECLINE;

  if (this->_configuration != 0)
    {
      bool			ok = true;
      std::string		uri = rh.getPath();
      const zia::IDictionnary&	dictionnary = this->_configuration->getHive("Main");

      Utils::uriCat(uri, dictionnary.get("RootDirectory"), uri);
      std::cerr << "Uri: " << uri << std::endl;
      ok = Utils::existPath(uri);
      if (true == ok)
        {
          bool			headMethod = (rh.getMethod() == "HEAD");
	  zia::IDictionnary&	headerResponse = rr.entities();
	  if (true == parsePerl(uri, osResponseBody, headerResponse, headMethod))
            {
              rr.setVMajor(rh.getVMajor());
              rr.setVMinor(rh.getVMinor());
              rr.setCode(200);
              rr.setMsg("OK");
              status.translation = zia::filter::Status::TAKEOVER;
              rr.readyToSend();
            }
	}
    }
  return (status);
}

zia::filter::Status	filterPerl::processBodyEnding(const zia::network::IConnection& /*con*/,
						      zia::http::IRequestHeader& rh,
						      zia::http::IResponseHeader& rr,
						      std::ostream& osResponseBody)
{
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;
  status.translation = zia::filter::Status::DECLINE;

  if (this->_configuration != 0)
    {
      std::string		uri = rh.getPath();
      const zia::IDictionnary&	dictionnary = this->_configuration->getHive("Main");

      Utils::uriCat(uri, dictionnary.get("RootDirectory"), uri);
      std::cerr << "Uri: " << uri << std::endl;
      if (Utils::existPath(uri) &&
	  ".pl" == boost::filesystem::extension(uri) &&
	  false == Utils::isDirectory(uri))
        {
          bool			headMethod = (rh.getMethod() == "HEAD");
	  zia::IDictionnary&	headerResponse = rr.entities();
	  if (true == parsePerl(uri, osResponseBody, headerResponse, headMethod))
            {
              rr.setVMajor(rh.getVMajor());
              rr.setVMinor(rh.getVMinor());
              rr.setCode(200);
              rr.setMsg("OK");
              status.translation = zia::filter::Status::TAKEOVER;
              rr.readyToSend();
            }
	}
    }
  return (status);
}

bool	filterPerl::parsePerl(const std::string& filename,
			      std::ostream& osResponseBody,
			      zia::IDictionnary& responseHeader,
			      bool methodHead)
{
  if (this->_perlPath.empty())
    {
      std::cerr << "PerlPlugin warning: binary path has not been set. Aborting..." << std::endl;
      return (false);
    }
  if (false == Utils::existPath(this->_perlPath))
    {
      std::cerr << "Perl Plugin warning: " << this->_perlPath;
      std::cerr << " does not exist. Aborting..." << std::endl;
      return (false);
    }
  bool	result = false;

  boost::process::command_line cl(this->_perlPath);
  cl.argument(filename);

  boost::process::launcher l;
  l.set_stdout_behavior(boost::process::redirect_stream);
  l.set_merge_out_err(true);
  //l.set_work_directory(".");

  boost::process::child c = l.start(cl);
  boost::process::pistream& is = c.get_stdout();
  boost::process::status s = c.wait();

  if (s.exited() && s.exit_status() == EXIT_SUCCESS)
    {
      result = true;
      const std::size_t contentSize = fillBody(osResponseBody, is, methodHead);
      fillHeader(responseHeader, contentSize);
      std::cerr << "Parsing de Perl succeed :) !" << std::endl;
    }
  else
    {
      std::cerr << "Parsing de Perl failed :( !" << std::endl;
    }
  return (result);
}

void	filterPerl::fillHeader(zia::IDictionnary& responseHeader,
			       std::size_t contentSize)
{
  responseHeader.set("Date", Utils::getDate());
  responseHeader.set("Content-Type", "text/plain");
  responseHeader.set("Content-Length", typeToString<std::size_t>(contentSize));
}

std::size_t	filterPerl::fillBody(std::ostream& osResponseBody,
				     boost::process::pistream& is,
				     bool methodHead)
{
  std::string	result;
  std::string	buffer;

  while (std::getline(is, buffer))
    {
      result += buffer + '\n';
    }
  std::size_t	contentSize = result.size();
  if (contentSize > 0)
    {
      --contentSize;
      result.erase(contentSize);
      if (false == methodHead)
        {
          osResponseBody << result;
        }
    }
  std::cerr << "fillBody @ filterPerl BODY result =>" << std::endl << result << std::endl;
  return (contentSize);
}
