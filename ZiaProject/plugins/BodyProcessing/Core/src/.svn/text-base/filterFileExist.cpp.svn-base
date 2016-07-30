/// \file

#include <iostream>

#include "Utils.h"
#include "TypeToString.hpp"
#include "filterFileExist.h"

filterFileExist::filterFileExist(zia::IConfiguration* conf) : _configuration(conf)
{
}

filterFileExist::~filterFileExist(void)
{
}

inline std::size_t	filterFileExist::getObjectSize() const
{
  return (sizeof(*this));
}

inline void	filterFileExist::constructObject(void* storage) const
{
  new (storage) filterFileExist (this->_configuration);
}

inline int	filterFileExist::getPriority() const
{
  return (18);
}

void	filterFileExist::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

void		filterFileExist::fillResponse(std::ostream& osResponseBody,
					      zia::IDictionnary& headerResponse,
					      bool methodHead)
{
  const std::string	error404 = "<?xml version=\"1.0\" encoding=\"utf-8\"?><!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\"><head><title>Erreur 404</title><meta http-equiv=\"Content-Language\" content=\"fr\" /><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /></head><body><h1>404: Page Not Found</h1><hr>The requested URL ??? was not found on this server.</body></html>";
  headerResponse.set("Content-Length", typeToString<std::size_t>(error404.length()));

  if (false == methodHead)
    osResponseBody << error404;
}

zia::filter::Status	filterFileExist::processBody(const zia::network::IConnection& con,
						     zia::http::IRequestHeader& rh,
						     zia::http::IResponseHeader& rr,
						     std::istream& /*isRequestBody*/,
						     std::ostream& osResponseBody)
{
  return (processBodyEnding(con, rh, rr, osResponseBody));
}


zia::filter::Status	filterFileExist::processBodyEnding(const zia::network::IConnection&,
							   zia::http::IRequestHeader& rh,
							   zia::http::IResponseHeader& rr,
							   std::ostream& osResponseBody)
{
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;
  status.translation = zia::filter::Status::DECLINE;

  if (0 == this->_configuration ||
      "TRACE" == rh.getMethod() ||
      "PUT" == rh.getMethod())
    return (status);

  const zia::IDictionnary&	dictionnary = this->_configuration->getHive("Main");

  const std::string	uri =
    Utils::getRealPath(dictionnary.get("RootDirectory"), rh.getPath());

  std::cerr << "FILE EXIST. mapped uri => " << uri << std::endl;
  //TODO : decliner si le header ne necessite pas d'uri
  if (!Utils::existPath(uri))
    {
      status.translation = zia::filter::Status::TAKEOVER;
      rr.setVMajor(1);
      rr.setVMinor(1);
      rr.setCode(404);
      rr.setMsg("Not Found");
      zia::IDictionnary& headerResponse = rr.entities();
      headerResponse.set("Date", Utils::getDate());
      headerResponse.set("Content-Type", "text/html");
      bool	methodHead = "HEAD" == rh.getMethod();
      this->fillResponse(osResponseBody, headerResponse, methodHead);
      rr.readyToSend();
    }
  return (status);
}
