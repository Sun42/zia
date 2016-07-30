/// \file

#include "EndPoint.h"
#include "Address.h"

EndPoint::EndPoint(boost::asio::ip::tcp::endpoint& bEndpoint):
  _hostName(), _port(static_cast<unsigned short>(bEndpoint.port())), _address(new Address(bEndpoint))
{
}

EndPoint::EndPoint(boost::asio::ip::tcp::endpoint& bEndpoint, std::string const & hostName):
  _hostName(hostName), _port(static_cast<unsigned short>(bEndpoint.port())), _address(new Address(bEndpoint))
{
}

EndPoint::~EndPoint()
{
  if (this->_address != 0)
    delete this->_address;
}

const std::string&	EndPoint::getHostName() const
{
  return (this->_hostName);
}

unsigned short	EndPoint::getPort() const
{
  return (this->_port);
}

const	zia::network::IAddress&	EndPoint::getAddress() const
{
  return (*this->_address);
}

void	EndPoint::setHostName(const std::string& hname)
{
  this->_hostName = hname;
}
