#include <sstream>
#include <iostream>

#include "filterAllow.h"

filterAllow::filterAllow(zia::IConfiguration* conf, zia::ILogger* logger) :
  _configuration(conf), _logger(logger)
{
}

filterAllow::~filterAllow(void)
{
}

/*********************************************************************/

std::size_t	filterAllow::getObjectSize() const
{
  return (sizeof(*this));
}

void	filterAllow::constructObject(void* storage) const
{
  new (storage) filterAllow(this->_configuration, this->_logger);
}

int	filterAllow::getPriority() const
{
  return (1000000);
}

/*********************************************************************/

void	filterAllow::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

void	filterAllow::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

/*********************************************************************/

std::string&	filterAllow::trim(std::string& str) const
{
  return (str = str.substr(str.find_first_not_of(" \t\f\v\n\r"),
			   str.find_last_not_of(" \t\f\v\n\r") - str.find_first_not_of(" \t\f\v\n\r") + 1));
}

template<class T, long unsigned int N>
void	filterAllow::fillArray(boost::array<T, N>& temp, unsigned char const * bytes)
{
  for (unsigned int i = 0; i < N; ++i)
    temp[i] = bytes[i];
}

/*********************************************************************/

bool	filterAllow::checkBannedList(boost::asio::ip::address const & addrClient, std::string & listBannedIP, std::string & ipClient)
{
  ipClient = addrClient.to_string();
  size_t	pos;
  std::string	tempAddr;

  //listBannedIP = listBannedIP.substr(listBannedIP.find_first_of("\n") + 1);
  while ((pos = listBannedIP.find_first_of("\n")) != std::string::npos)
    {
      tempAddr = listBannedIP.substr(0, pos);
      if (tempAddr != "")
	{
	  if (addrClient == boost::asio::ip::address::from_string(trim(tempAddr)))
	    return (true);
	}
      listBannedIP = listBannedIP.substr(pos + 1);
    }
  return (false);
}

/*********************************************************************/

zia::filter::Status	filterAllow::newConnection(zia::network::IConnection& con)
{
  zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.persistence = zia::filter::Status::REMOVEME;

  if (0 != this->_configuration)
    {
      const zia::IDictionnary&		confPlugin = this->_configuration->getHive("PluginAllow");
      std::string			listBannedIP = confPlugin.get("DirectIP");
      if ("" != listBannedIP)
	{
	  const zia::network::IAddress& addrClient = con.getClient().getAddress();
	  bool				isBan;
	  std::string			ipClient;
	  if (true == addrClient.isV4())
	    {
	      boost::array<unsigned char, 4>	temp;
	      this->fillArray<unsigned char,4>(temp, addrClient.getV4().bytes);
	      isBan = this->checkBannedList(boost::asio::ip::address_v4(temp), trim(listBannedIP), ipClient);
	    }
	  else
	    {
	      boost::array<unsigned char, 16>	temp;
	      this->fillArray<unsigned char, 16>(temp, addrClient.getV6().bytes);
	      isBan = this->checkBannedList(boost::asio::ip::address_v6(temp), listBannedIP, ipClient);
	    }

	  if (true == isBan)
	    {
	      if (0 != this->_logger)
		this->_logger->log(zia::log::ZIA_INFO, "Connection Refused for : " + ipClient);
	      status.authorization = zia::filter::Status::DENY;
	      status.translation = zia::filter::Status::TAKEOVER;
	      return (status);
	    }
	  if (0 != this->_logger)
	    this->_logger->log(zia::log::ZIA_INFO, "Connection Accepted for : " + ipClient);
	}
    }
  status.authorization = zia::filter::Status::ACCEPT;
  status.translation = zia::filter::Status::DECLINE;
  return (status);
}
