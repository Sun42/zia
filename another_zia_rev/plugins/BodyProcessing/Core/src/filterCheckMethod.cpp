/// \file

#include <iostream>

#include "Utils.h"
#include "filterCheckMethod.h"
#include "zia_api/IDictionnary.h"

filterCheckMethod::filterCheckMethod(zia::ILogger* logger) : _logger(logger)
{
}

filterCheckMethod::~filterCheckMethod(void)
{
}

inline std::size_t	filterCheckMethod::getObjectSize() const
{
  return (sizeof(*this));
}

inline void		filterCheckMethod::constructObject(void* storage) const
{
  new (storage) filterCheckMethod;
}

inline int		filterCheckMethod::getPriority() const
{
  return (20);
}

void	filterCheckMethod::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

zia::filter::Status	filterCheckMethod::processBody(const zia::network::IConnection& con,
						       zia::http::IRequestHeader& rh,
						       zia::http::IResponseHeader& rr,
						       std::istream& /*isRequestBody*/,
						       std::ostream& osResponseBody)
{
  return (this->processBodyEnding(con, rh, rr, osResponseBody));
}

zia::filter::Status	filterCheckMethod::processBodyEnding(const zia::network::IConnection&,
						       zia::http::IRequestHeader& rh,
							   zia::http::IResponseHeader& rr,
							   std::ostream& osResponseBody)
{
  //std::cerr<< "processBodyEnding: "<<std::endl;
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;
  status.translation = zia::filter::Status::DECLINE;
  std::string method = rh.getMethod();

  if (!this->isValidMethod(method))
    {
      status.translation = zia::filter::Status::TAKEOVER;
      rr.setVMajor(1);
      rr.setVMinor(1);
      rr.setCode(405);
      rr.setMsg("Method Not Allowed");
      zia::IDictionnary& headerResponse = rr.entities();
      const std::string rep = "Bad Request";
      headerResponse.set("Content-Type", "text/plain");
      headerResponse.set("Content-Length", "11");
      osResponseBody << rep;
      rr.readyToSend();
    }
  else if (!this->isImplementedMethod(method))
    {
      status.translation = zia::filter::Status::TAKEOVER;
      rr.setVMajor(1);
      rr.setVMinor(1);
      rr.setCode(501);
      rr.setMsg("Not Implemented");
      zia::IDictionnary& headerResponse = rr.entities();
      headerResponse.set("Content-Type", "text/plain");
      headerResponse.set("Content-Length", "18");
      osResponseBody << "Not Implemen...ted";
      rr.readyToSend();
    }
  return (status);
}



bool filterCheckMethod::isImplementedMethod(const std::string& method) const
{
  return (!(method == "PUT" || method == "OPTION" || method == "DELETE"));
}

bool	filterCheckMethod::isValidMethod(const std::string& method) const
{
  if (method != "TRACE" && method  != "GET" && method != "POST" && method != "PUT" && method != "DELETE" && method != "HEAD" && method != "CONNECT" && method != "OPTION")
    return false;
  return true;
}
