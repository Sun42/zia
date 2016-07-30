/// \file

#include <list>
#include <sstream>
#include <iostream>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "Utils.h"
#include "TypeToString.hpp"
#include "filterAccessRights.h"

const char*	RIGHTS_FILENAME = ".private";

filterAccessRights::filterAccessRights(zia::IConfiguration* conf) : _configuration(conf)
{
}

filterAccessRights::~filterAccessRights(void)
{
}


inline std::size_t	filterAccessRights::getObjectSize(void) const
{
  return (sizeof(*this));
}

inline void	filterAccessRights::constructObject(void* storage) const
{
  new (storage) filterAccessRights(this->_configuration);
}

inline int	filterAccessRights::getPriority(void) const
{
  return (15);
}

void	filterAccessRights::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

void	filterAccessRights::fillResponse(std::ostream& osResponseBody,
						 zia::IDictionnary& headerResponse,
						 bool methodHead) const
{
  const std::string	body = "<html><body>403: Forbidden Access !</body></html>";

  headerResponse.set("Date", Utils::getDate());
  headerResponse.set("Content-Type", "text/html");
  headerResponse.set("Content-Length", typeToString<std::size_t>(body.length()));

  if (false == methodHead)
    osResponseBody << body;
}

zia::filter::Status	filterAccessRights::processBody(const zia::network::IConnection& con,
							     zia::http::IRequestHeader& rh,
							     zia::http::IResponseHeader& rr,
							     std::istream& /*isRequestBody*/,
							     std::ostream& osResponseBody)
{
  return (processBodyEnding(con, rh, rr, osResponseBody));
}

zia::filter::Status	filterAccessRights::processBodyEnding(const zia::network::IConnection& /*con*/,
								   zia::http::IRequestHeader& rh,
								   zia::http::IResponseHeader& rr,
								   std::ostream& osResponseBody)
{
  zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;
  status.translation = zia::filter::Status::DECLINE;

  const zia::IDictionnary&	dictionnary = this->_configuration->getHive("Main");

  boost::filesystem::path	uri =
    Utils::getRealPath(dictionnary.get("RootDirectory"), rh.getPath());

  if (!boost::filesystem::is_directory(uri))
    {
      uri.remove_filename();
    }
  uri /= RIGHTS_FILENAME;

  std::cerr << "RIGHTS PATH => " << uri << std::endl;
  if (boost::filesystem::exists(uri))
    {
      // rights file exists: access is forbidden.
      status.translation = zia::filter::Status::TAKEOVER;
      //status.authorization = zia::filter::Status::DENY;
      rr.setVMajor(1);
      rr.setVMinor(1);
      rr.setCode(403);
      rr.setMsg("Forbidden");
      zia::IDictionnary&	headerResponse = rr.entities();

      bool	methodHead = rh.getMethod() == "HEAD";
      fillResponse(osResponseBody, headerResponse, methodHead);
      rr.readyToSend();
    }
  return (status);
}
