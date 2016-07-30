#include <cstdio>


#include "TypeToString.hpp"
#include "StringToType.hpp"
#include "filterDelete.h"
#include "Utils.h"

filterDelete::filterDelete(zia::IConfiguration* conf, zia::ILogger* logger) :
  _configuration(conf), _logger(logger)
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

bool	filterDelete::deleteURI(const zia::http::IRequestHeader& /*rh*/) const
{
//   std::string uri = Utils::getRealPath(rh.getPath());
//   return (remove(uri.c_str()) == 0);
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

void	filterDelete::fillResponse(const zia::http::IRequestHeader& rh,
				   zia::http::IResponseHeader& rr) const
{
  std::string		isEnacted = "OFF";
  if (this->_configuration != 0)
    {
      const zia::IDictionnary&	confPlugin = this->_configuration->getHive("PluginDelete");
      isEnacted = confPlugin.get("Enacted");
      if (isEnacted == "" || (isEnacted != "OFF" && isEnacted != "ON"))
	isEnacted = "OFF";
    }

  if (isEnacted == "ON")
    {
      this->fillHeaderResponse(rh, rr, 202, "Accepted");
    }
  else
    {
      if (true == this->deleteURI(rh))
	{
	  this->fillHeaderResponse(rh, rr, 204, "No Content");
	}
      else
	{
	  this->fillHeaderResponse(rh, rr, 500, "Internal Server Error");
	}
    }
}


/*********************************************************************/

zia::filter::Status	filterDelete::processBody(const zia::network::IConnection&,
						 zia::http::IRequestHeader& rh,
						 zia::http::IResponseHeader& rr,
						 std::istream&,
						 std::ostream&)
{
  zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;

  if (rh.getMethod() == "DELETE")
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
