/// \file

#include <string>
#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "Utils.h"
#include "filterPython.h"
#include "Dictionnary.h"
#include "TypeToString.hpp"

static const std::string	PYTHON_SECTION = "PythonPlugin";

filterPython::filterPython(zia::IConfiguration* conf) : _configuration(conf)
{
  configureFilter();
}

filterPython::~filterPython(void)
{
}

std::size_t	filterPython::getObjectSize() const
{
  return (sizeof(*this));
}

void		filterPython::constructObject(void* storage) const
{
  new (storage) filterPython(this->_configuration);
}

int		filterPython::getPriority() const
{
  return (9);
}

void		filterPython::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

zia::filter::Status	filterPython::processBody(const zia::network::IConnection& con,
					       zia::http::IRequestHeader& rh,
					       zia::http::IResponseHeader& rr,
					       std::istream& /*isRequestBody*/,
					       std::ostream& osResponseBody)
{
  return (processBodyEnding(con, rh, rr, osResponseBody));
}

zia::filter::Status	filterPython::processBodyEnding(const zia::network::IConnection&,
						     zia::http::IRequestHeader& rh,
						     zia::http::IResponseHeader& rr,
						     std::ostream& osResponseBody)
{
  struct zia::filter::Status    status;
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
	  ".py" == boost::filesystem::extension(uri) &&
	  false == Utils::isDirectory(uri))
        {
          bool			headMethod = (rh.getMethod() == "HEAD");
	  zia::IDictionnary&	headerResponse = rr.entities();
          if (true == parsePython(uri, osResponseBody, headerResponse, headMethod))
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

void		filterPython::configureFilter(void)
{
  if (0 == this->_configuration)
    return;

  if (this->_configuration->hiveExists(PYTHON_SECTION))
    {
      const zia::IDictionnary&  mainHive = this->_configuration->getHive(PYTHON_SECTION);
      this->_pythonPath = mainHive.get("binary path");
    }
}

bool	filterPython::parsePython(const std::string& filename,
				  std::ostream& osResponseBody,
				  zia::IDictionnary& responseHeader,
				  bool methodHead)
{
  bool	result = false;

  boost::process::command_line cl(this->_pythonPath);
  cl.argument(filename);

  boost::process::launcher l;
  l.set_stdout_behavior(boost::process::redirect_stream);
  l.set_merge_out_err(true);

  boost::process::child c = l.start(cl);
  boost::process::pistream& is = c.get_stdout();
  boost::process::status s = c.wait();

  if (s.exited() && s.exit_status() == EXIT_SUCCESS)
    {
      result = true;

      const std::size_t contentSize = fillBody(osResponseBody, is, methodHead);
      fillHeader(responseHeader, contentSize);
      std::cerr << "Parsing de Python succeed :) !" << std::endl;
    }
  else
    {
      std::cerr << "Parsing de Python failed :( !" << std::endl;
    }
  return (result);
}

void	filterPython::fillHeader(zia::IDictionnary& responseHeader,
				 std::size_t contentSize)
{
  responseHeader.set("Date", Utils::getDate());
  responseHeader.set("Content-Type", "text/plain");
  responseHeader.set("Content-Length", typeToString<std::size_t>(contentSize));
}

std::size_t	filterPython::fillBody(std::ostream& osResponseBody,
			       boost::process::pistream& is,
			       bool methodHead)
{
  std::string   result;
  std::string   buffer;

  while (std::getline(is, buffer))
    {
      result += buffer + '\n';
    }
  std::size_t   contentSize = result.size();
  if (contentSize > 0)
    {
      --contentSize;
      result.erase(contentSize);
      if (false == methodHead)
        {
          osResponseBody << result;
        }
    }
  std::cerr << "fillBody @ filterPython BODY result =>" << std::endl << result << std::endl;
  return (contentSize);
}
