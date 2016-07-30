/// \file

#include <string>
#include <iostream>
#include <vector>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>

#include "filterPHPCGI.h"
#include "Dictionnary.h"
#include "Utils.h"

static const std::string	PHPCGI_SECTION = "PHPCGI-Plugin";

filterPHPCGI::filterPHPCGI(zia::IConfiguration* conf) : _configuration(conf)
{
  configureFilter();
}

filterPHPCGI::~filterPHPCGI(void)
{
}

std::size_t	filterPHPCGI::getObjectSize() const
{
  return (sizeof(*this));
}

bool	filterPHPCGI::isValidPath(std::string& result, std::string uri,
			       const std::string& rootFile) const
{
  Utils::uriCat(uri, uri, rootFile);
  if (Utils::existPath(uri))
    {
      result = uri;
      return (true);
    }
  else
      return (false);
}

void		filterPHPCGI::constructObject(void* storage) const
{
  new (storage) filterPHPCGI(this->_configuration);
}

int		filterPHPCGI::getPriority() const
{
  return (13);
}

zia::filter::Status	filterPHPCGI::processBody(const zia::network::IConnection& con,
					       zia::http::IRequestHeader& rh,
					       zia::http::IResponseHeader& rr,
					       std::istream& isRequestBody,
					       std::ostream& osResponseBody)
{
  std::cerr<< "filterPHPCGI::ProcessBody" <<std::endl;
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;

  std::cout<< "processBody->hostName" << con.getClient().getHostName() << std::endl;
  if (this->_configuration != 0)
    {
      bool		ok = true;
      std::string	uri = rh.getPath();
      const zia::IDictionnary&	ziaConf = this->_configuration->getHive("Main");

      std::cerr << "BEFORE: " << uri << std::endl;
      if (!Utils::isDirectory(uri))
	{
	  Utils::uriCat(uri, uri, ziaConf.get("RootDirectory"));
	}
      else
	{
#warning "Verifier le retour de takeOverRequest."
	  takeOverRequest(uri, ziaConf.get("RootDirectory"), uri);
	}
      std::cerr << "AFTER: " << uri << std::endl;
      zia::IDictionnary&	headerResponse = rr.entities();
      rr.setVMajor(rh.getVMajor());
      rr.setVMinor(rh.getVMinor());
      rr.setCode(200);
      rr.setMsg("OK");
      headerResponse.set("Date", Utils::getDate());
      headerResponse.set("Content-Type", "text/html");
      ok = parsePHPCGI(con, rh, rr, isRequestBody,
		       osResponseBody, uri, ziaConf);
      //ok = parsePHP(uri, osResponseBody);
      if (true == ok)
	{
	  rr.readyToSend();
	  status.translation = zia::filter::Status::TAKEOVER;
	  return (status);
	}
    }
  status.translation = zia::filter::Status::DECLINE;
  return (status);
}

zia::filter::Status	filterPHPCGI::processBodyEnding(const zia::network::IConnection&,
						     zia::http::IRequestHeader&,
						     zia::http::IResponseHeader&,
						     std::ostream&)
{
  std::cerr<< "filterPHPCGI::ProcessBodyEnding" <<std::endl;
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

      // Its a directory: index.html or index.php is seeked.
      uri = Utils::getRealPath(dictionnary.get("RootDirectory"), uri);
      std::cerr << "Uri: " << uri << std::endl;
      if (true == Utils::isDirectory(uri))
	{
	  ok = takeOverRequest(uri, uri);
	}
      else
	{
	  //std::cerr << "EXTENSION == " << boost::filesystem::extension(uri) << std::endl;
	  if (".php" == boost::filesystem::extension(uri))
	    ok = Utils::existPath(uri);
	  else
	    ok = false;
	}
      if (true == ok)
	{
	  bool			headMethod = (rh.getMethod() == "HEAD");
	  zia::IDictionnary&	headerResponse = rr.entities();

	  if (true == parsePHPCGI(uri, osResponseBody, headerResponse, headMethod))
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

bool	filterPHPCGI::takeOverRequest(std::string& result, std::string uri, const std::string& rootDir)
{
  std::cerr << "DEBUG URI @ TAKE OVER REQUEST: " << uri << std::endl;
  const int	size = this->_rootFiles.size();
  for (int i = 0; i < size; ++i)
    {
      if (this->isValidPath(result, uri, this->_rootFiles[i]))
	{
	  return (true);
	}
    }
  return (false);
}



void	filterPHPCGI::configureFilter(void)
{
  if (0 == this->_configuration)
    return;

  if (this->_configuration->hiveExists(PHPCGI_SECTION))
    {
      const zia::IDictionnary&  mainHive = this->_configuration->getHive(PHPCGI_SECTION);
      this->_phpPath = mainHive.get("binary path");

      std::string	list = mainHive.get("root files");
      if (list.size() > 0)
	{
	  boost::char_separator<char>				separators(" \n\t\f\v\r");
	  boost::tokenizer<boost::char_separator<char> >	tok(list, separators);

	  for(boost::tokenizer<boost::char_separator<char> >::iterator beg=tok.begin();
	      beg != tok.end(); ++beg)
	    {
	      this->_rootFiles.push_back(*beg);
	    }
	}
      else
	{
	  this->_rootFiles.push_back("index.php");
	  this->_rootFiles.push_back("index.html");
	}
    }
}

void	filterPHPCGI::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}
