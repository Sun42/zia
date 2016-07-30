/// \file

#include <string>
#include <iostream>
#include <boost/process.hpp>
#include <boost/tokenizer.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "Utils.h"
#include "filterPHP.h"
#include "Dictionnary.h"
#include "TypeToString.hpp"

static const std::string	PHP_SECTION = "PHP-Plugin";

filterPHP::filterPHP(zia::IConfiguration* conf) : _configuration(conf)
{
  configureFilter();
}

filterPHP::~filterPHP(void)
{
}

std::size_t	filterPHP::getObjectSize() const
{
  return (sizeof(*this));
}

void		filterPHP::constructObject(void* storage) const
{
  new (storage) filterPHP(this->_configuration);
}

int		filterPHP::getPriority() const
{
  return (13);
}

void		filterPHP::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

zia::filter::Status	filterPHP::processBody(const zia::network::IConnection& con,
					       zia::http::IRequestHeader& rh,
					       zia::http::IResponseHeader& rr,
					       std::istream& /*isRequestBody*/,
					       std::ostream& osResponseBody)
{
  return (processBodyEnding(con, rh, rr, osResponseBody));
}

std::size_t	fillBody(std::ostream& osResponseBody,
				    boost::process::pistream& is,
				    bool methodHead)
{
  std::string   result;
  std::string   buffer;

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
  std::cerr << "fillBody @ filterPHP BODY result =>" << std::endl << result << std::endl;
  return (contentSize);
}

zia::filter::Status	filterPHP::processBodyEnding(const zia::network::IConnection& /*con*/,
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

	  if (true == parsePHP(uri, osResponseBody, headerResponse, headMethod))
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
std::cerr << "Fin filter php" << std::endl;
  return (status);
}

bool	filterPHP::parsePHP(const std::string& filename,
			    std::ostream& osResponseBody,
			    zia::IDictionnary& responseHeader,
			    bool methodHead)
{
  if (this->_phpPath.empty())
    {
      std::cerr << "PHP Plugin warning: binary path has not been set. Aborting..." << std::endl;
      return (false);
    }
  if (false == Utils::existPath(this->_phpPath))
    {
      std::cerr << "PHP Plugin warning: " << this->_phpPath;
      std::cerr << " does not exist. Aborting..." << std::endl;
      return (false);
    }
  bool	result = false;

  boost::process::command_line cl(this->_phpPath);
  cl.argument(filename);

  boost::process::launcher l;
  l.set_stdout_behavior(boost::process::redirect_stream);
  l.set_merge_out_err(true);

  boost::process::child c = l.start(cl);
  boost::process::pistream& is = c.get_stdout();
  boost::process::status s = c.wait();

  if (s.exited() && EXIT_SUCCESS == s.exit_status())
    {
      result = true;
      const std::size_t	size = fillBody(osResponseBody, is, methodHead);
      fillHeader(responseHeader, size);
      std::cerr << "Parsing de PHP succeed :) !" << std::endl;
    }
  else
    {
      std::cerr << "Parsing de PHP failed :( !" << std::endl;
    }
  return (result);
}

void	filterPHP::fillHeader(zia::IDictionnary& responseHeader, std::size_t contentSize)
{
  responseHeader.set("Date", Utils::getDate());
  responseHeader.set("Content-Type", "text/html");
  responseHeader.set("Content-Length", typeToString<std::size_t>(contentSize));
}

void		filterPHP::configureFilter(void)
{
  if (0 == this->_configuration)
    return;

  if (this->_configuration->hiveExists(PHP_SECTION))
    {
      const zia::IDictionnary&  mainHive = this->_configuration->getHive(PHP_SECTION);
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

bool	filterPHP::takeOverRequest(std::string& result, const std::string& uri)
{
  std::cerr << "DEBUG URI @ TAKE OVER REQUEST: " << uri << std::endl;

  const int	size = this->_rootFiles.size();
  for (int i = 0; i < size; ++i)
    {
      if (isValidPath(result, uri, this->_rootFiles[i]))
	{
	  return (true);
	}
    }
  return (false);
}

bool	filterPHP::isValidPath(std::string& result, std::string uri,
			       const std::string& rootFile) const
{
  Utils::uriCat(uri, uri, rootFile);
  if (Utils::existPath(uri))
    {
      result = uri;
      return (true);
    }
  else
    {
      return (false);
    }
}
