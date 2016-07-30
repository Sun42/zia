/// \file

#include <iostream>
#include <sstream>
#include <ctime>

#include "Utils.h"
#include "TypeToString.hpp"
#include "StringToType.hpp"
#include "filterTrace.h"

filterTrace::filterTrace(zia::IConfiguration* conf) : _configuration(conf)
{
}

filterTrace::~filterTrace(void)
{
}

/*********************************************************************/

inline std::size_t	filterTrace::getObjectSize(void) const
{
  return (sizeof(*this));
}

inline void		filterTrace::constructObject(void* storage) const
{
  new (storage) filterTrace(this->_configuration);
}

inline int		filterTrace::getPriority(void) const
{
  return (5);
}

/*********************************************************************/

void	filterTrace::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

/*********************************************************************/

size_t		filterTrace::fillBodyResponse(const zia::http::IRequestHeader& rh,
					      std::istream& isRequestBody,
					      std::ostream& osResponseBody) const
{
  std::string	tempBody(rh.getMethod() + " " + rh.getPath() + " HTTP/" + typeToString(rh.getVMajor()) + "." + typeToString(rh.getVMinor()) + "\r\n");

  const std::map<std::string, std::string>		headersRequest = rh.entities().getContent();
  std::map<std::string, std::string>::const_iterator	it = headersRequest.begin();
  std::map<std::string, std::string>::const_iterator	itEnd = headersRequest.end();
  for (; it != itEnd; ++it)
    {
      tempBody += (*it).first;
      tempBody += ":";
      tempBody += (*it).second;
      tempBody +="\r\n";
    }
  const zia::IDictionnary&	headerRequest = rh.entities();
  const std::string temp = headerRequest.get("Content-Length");
  osResponseBody << tempBody << "\r\n" << isRequestBody.rdbuf();
  return (tempBody.size() + stringToType<size_t>(temp) + 2);
}


size_t		filterTrace::fillBodyResponse(const zia::http::IRequestHeader& rh,
					      std::ostream& osResponseBody) const
{
  std::string	tempBody(rh.getMethod() + " " + rh.getPath() + " HTTP/" + typeToString(rh.getVMajor()) + "." + typeToString(rh.getVMinor()) + "\r\n");

  const std::map<std::string, std::string>		headersRequest = rh.entities().getContent();
  std::map<std::string, std::string>::const_iterator	it = headersRequest.begin();
  std::map<std::string, std::string>::const_iterator	itEnd = headersRequest.end();
  for (; it != itEnd; ++it)
    {
      tempBody += (*it).first;
      tempBody += ":";
      tempBody += (*it).second;
      tempBody +="\r\n";
    }
  osResponseBody << tempBody << "\r\n";
  return (tempBody.size() + 2);
}

/*********************************************************************/

void	filterTrace::fillHeaderResponse(const zia::http::IRequestHeader& rh,
					zia::http::IResponseHeader& rr,
					std::size_t sizeBody) const
{
  rr.setVMajor(rh.getVMajor());
  rr.setVMinor(rh.getVMinor());
  rr.setCode(200);
  rr.setMsg("OK");
  zia::IDictionnary& headerResponse = rr.entities();
  headerResponse.set("Content-Type", "message/http");
  headerResponse.set("Date", Utils::getDate());
  headerResponse.set("Content-Length", typeToString<std::size_t>(sizeBody));
  rr.readyToSend();
}

/*********************************************************************/

void		filterTrace::fillResponse(const zia::http::IRequestHeader& rh,
					  zia::http::IResponseHeader& rr,
					  std::istream& isRequestBody,
					  std::ostream& osResponseBody,
					  struct zia::filter::Status & status) const
{
  const zia::IDictionnary&	headerRequest = rh.entities();
  int				realBodySize = 0;
  realBodySize = stringToType<int>(headerRequest.get("Content-Length"));

  if (realBodySize == (isRequestBody.rdbuf())->in_avail())
    {
      std::cerr << "Je traite la requete trace" << std::endl;
      status.persistence = zia::filter::Status::REMOVEME;
      size_t	sizeBody = this->fillBodyResponse(rh, isRequestBody, osResponseBody);
      this->fillHeaderResponse(rh, rr,  sizeBody);
    }
  else
    {
      std::cerr << "Je n'ai pas encore toute les donnees pour te renvoyer une reponse." << std::endl;
      status.persistence = zia::filter::Status::ALIVE;
    }
}

void		filterTrace::fillResponse(const zia::http::IRequestHeader& rh,
					  zia::http::IResponseHeader& rr,
					  std::ostream& osResponseBody) const

{
  const size_t	sizeBody = this->fillBodyResponse(rh, osResponseBody);
  this->fillHeaderResponse(rh, rr, sizeBody);
}

/*********************************************************************/

zia::filter::Status	filterTrace::processBody(const zia::network::IConnection&,
						 zia::http::IRequestHeader& rh,
						 zia::http::IResponseHeader& rr,
						 std::istream& isRequestBody,
						 std::ostream& osResponseBody)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl << "filterTrace::processBody " << std::endl;
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;

  if (rh.getMethod() == "TRACE")
    {
      status.translation = zia::filter::Status::TAKEOVER;
      this->fillResponse(rh, rr, isRequestBody, osResponseBody, status);
    }
  else
    {
      std::cerr << "ce n est pas un requete trace je n en m occupe pas"<< std::endl;
      status.translation = zia::filter::Status::DECLINE;
      status.persistence = zia::filter::Status::REMOVEME;
    }
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  return (status);
}

zia::filter::Status	filterTrace::processBodyEnding(const zia::network::IConnection&,
						       zia::http::IRequestHeader& rh,
						       zia::http::IResponseHeader& rr,
						       std::ostream& osResponseBody)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl << "filterTrace::processBodyEnding" << std::endl;
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;

  if (rh.getMethod() == "TRACE")
    {
      std::cerr << "Je traite la requete trace" << std::endl;
      status.translation = zia::filter::Status::TAKEOVER;
      this->fillResponse(rh, rr, osResponseBody);
    }
  else
    status.translation = zia::filter::Status::DECLINE;
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  return (status);
}
