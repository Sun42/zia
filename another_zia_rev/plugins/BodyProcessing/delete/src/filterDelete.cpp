#include <cstdio>
#include <iostream>

#include "Utils.h"
#include "TypeToString.hpp"
#include "StringToType.hpp"
#include "filterDelete.h"

filterDelete::filterDelete(zia::IConfiguration* conf, zia::ILogger* logger)
  : _logger(logger), _configuration(conf)
{
}

filterDelete::~filterDelete(void)
{
}

/*********************************************************************/

std::size_t	filterDelete::getObjectSize() const
{
  return (sizeof(*this));
}

void		filterDelete::constructObject(void* storage) const
{
  new (storage) filterDelete(this->_configuration, this->_logger);
}

int		filterDelete::getPriority() const
{
  return (1);
}

/*********************************************************************/

void	filterDelete::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

void	filterDelete::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

/*********************************************************************/

bool	filterDelete::deleteURI(std::string const &/*uriTodelete*/) const
{
  //   return (remove(uriTodelete.c_str()) == 0);
  return (true);
}

/*********************************************************************/

void	filterDelete::fillHeaderResponse(const zia::http::IRequestHeader& rh,
					 zia::http::IResponseHeader& rr,
					 unsigned int code,
					 std::string const & message) const
{
  rr.setVMajor(rh.getVMajor());
  rr.setVMinor(rh.getVMinor());
  rr.setCode(code);
  rr.setMsg(message);
  zia::IDictionnary& headerResponse = rr.entities();
  headerResponse.set("Date", Utils::getDate());
  headerResponse.set("Content-Length", "0");
  rr.readyToSend();
}

void	filterDelete::fillResponse(const zia::http::IRequestHeader& rh, zia::http::IResponseHeader& rr) const
{
  std::string			messageLog;
  zia::log::Priority		pLog;
  const zia::IDictionnary&	dictionnary = this->_configuration->getHive("Main");
  std::string			rootDirectory = dictionnary.get("RootDirectory");
  std::string			URI = Utils::getRealPath(rootDirectory , rh.getPath());

  std::string			isEnacted("OFF");

  if (this->_configuration != 0)
    {
      const zia::IDictionnary&	confPlugin = this->_configuration->getHive("PluginDelete");
      isEnacted = confPlugin.get("Enacted");
      if (isEnacted == "" || (isEnacted != "OFF" && isEnacted != "ON"))
	isEnacted = "ON";
    }
  std::cerr << "isEnacted ? " << std::boolalpha << isEnacted << std::endl;
  if (isEnacted == "ON")
    {
      this->fillHeaderResponse(rh, rr, 202, "Accepted");
      pLog = zia::log::ZIA_INFO;
      messageLog = "Demande de suppression pour l'URI suivante --> Path : " + URI;
    }
  else
    if (true == this->deleteURI(URI))
      {
	this->fillHeaderResponse(rh, rr, 204, "No Content");
	pLog = zia::log::ZIA_WARN;
	messageLog = "L'URI suivante a ete supprime avec success --> Path : " + URI;
      }
    else
      {
	this->fillHeaderResponse(rh, rr, 500, "Internal Server Error");
	pLog = zia::log::ZIA_ERROR;
	messageLog = "Echec lors de la suppression de l'URI suivante --> Path : " + URI;
      }

  if (0 != this->_logger)
    {
      this->_logger->log(pLog, messageLog);
    }
}


/*********************************************************************/

zia::filter::Status	filterDelete::processBody(const zia::network::IConnection&,
						  zia::http::IRequestHeader& rh,
						  zia::http::IResponseHeader& rr,
						  std::istream&,
						  std::ostream&)
{
  std::cerr << "filterDelete::processBody" << std::endl;
  zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;

  if ("DELETE" == rh.getMethod())
    {
      status.translation = zia::filter::Status::TAKEOVER;
      this->fillResponse(rh, rr);
    }
  else
    {
      status.translation = zia::filter::Status::DECLINE;
    }
  return (status);
}

zia::filter::Status	filterDelete::processBodyEnding(const zia::network::IConnection&,
							zia::http::IRequestHeader& rh,
							zia::http::IResponseHeader& rr,
							std::ostream&)
{
  std::cerr << "filterDelete::processBodyEnding" << std::endl;
  zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;

  if ("DELETE" == rh.getMethod())
    {
      status.translation = zia::filter::Status::TAKEOVER;
      this->fillResponse(rh, rr);
    }
  else
    {
      status.translation = zia::filter::Status::DECLINE;
    }
  return (status);
}
