#include <sstream>
#include <iostream>

#include "filterAllow.h"

filterAllow::filterAllow(zia::IConfiguration* conf) :
  _configuration(conf)
{
}

filterAllow::~filterAllow(void)
{
  std::cerr << "filterAllow::~filterAllow\n";
}

std::size_t	filterAllow::getObjectSize() const
{
  return (sizeof(*this));
}

void	filterAllow::constructObject(void* storage) const
{
  new (storage) filterAllow(this->_configuration);
}

int	filterAllow::getPriority() const
{
  return (1000000);
}

void	filterAllow::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}


bool			filterAllow::isEqual(const unsigned char ip[4], const unsigned char ip2[4]) const
{
  return (ip[0] == ip2[0] && ip[1] == ip2[1] && ip[2] == ip2[2] && ip[3] == ip2[3]);
}

void			filterAllow::fillByteIP(unsigned char& byte, std::string& banIP) const
{
  byte = 0;
  size_t		pos = banIP.find_first_of(".");
  std::istringstream	value(banIP.substr(0, pos));
  unsigned int temp;
  value >> temp;
  byte = static_cast<unsigned char>(temp);
  banIP.erase(0, pos + 1);
}

void			filterAllow::fillIP(unsigned char byte[4], std::string& banIP) const
{
  this->fillByteIP(byte[0], banIP);
  this->fillByteIP(byte[1], banIP);
  this->fillByteIP(byte[2], banIP);
  this->fillByteIP(byte[3], banIP);
}

zia::filter::Status	filterAllow::newConnection(zia::network::IConnection& con)
{
  std::cerr << "filterAllow::newConnection\n";
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.persistence = zia::filter::Status::REMOVEME;

  if (0 != this->_configuration)
    {
      const zia::IDictionnary&		confPlugin = this->_configuration->getHive("PluginAllow");
      std::string			banIP = confPlugin.get("DirectIP");
      if ("" != banIP)
	{
	  const zia::network::IAddress&	addrClient = con.getClient().getAddress();
	  if (true == addrClient.isV4())
	    {
	      const zia::network::IPv4Address&	v4addr = addrClient.getV4();
	      unsigned char			ip[4];
	      this->fillIP(ip, banIP);
// 	      std::cerr << "IP of the con : "<< std::endl << (unsigned)v4addr.bytes[0] << "." << (unsigned)v4addr.bytes[1] <<  "." << (unsigned)v4addr.bytes[2] << "." <<  (unsigned)v4addr.bytes[3 ]<< std::endl;
// 	      std::cerr << "IP of the file : " << (unsigned)ip[0] << "." << (unsigned)ip[1] <<  "." << (unsigned)ip[2] << "." <<  (unsigned)ip[3 ]<< std::endl;
	      if (true == this->isEqual(v4addr.bytes, ip))
		{
		  std::cerr << "c alex je le bloque lol\n";
		  status.authorization = zia::filter::Status::DENY;
		  status.translation = zia::filter::Status::TAKEOVER;
		  return (status);
		}
	    }
	}
    }
  status.authorization = zia::filter::Status::ACCEPT;
  status.translation = zia::filter::Status::DECLINE;
  return (status);
}
