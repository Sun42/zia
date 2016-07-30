/// \file

#include "Address.h"

Address::Address(boost::asio::ip::tcp::endpoint& bEndpoint):
  _isV4(bEndpoint.address().is_v4()), _isV6(bEndpoint.address().is_v6()), _isV4Compatible(false), _iPv4Address(), _iPv6Address()
{
  if (this->_isV4)
    {
      this->_iPv4Address.bytes[0] = bEndpoint.address().to_v4().to_bytes()[0];
      this->_iPv4Address.bytes[1] = bEndpoint.address().to_v4().to_bytes()[1];
      this->_iPv4Address.bytes[2] = bEndpoint.address().to_v4().to_bytes()[2];
      this->_iPv4Address.bytes[3] = bEndpoint.address().to_v4().to_bytes()[3];
    }
  else if (this->_isV6)
    {
      this->_iPv6Address.bytes[0] = bEndpoint.address().to_v6().to_bytes()[0];
      this->_iPv6Address.bytes[1] = bEndpoint.address().to_v6().to_bytes()[1];
      this->_iPv6Address.bytes[2] = bEndpoint.address().to_v6().to_bytes()[2];
      this->_iPv6Address.bytes[3] = bEndpoint.address().to_v6().to_bytes()[3];
    }
}

Address::~Address()
{
}

bool	Address::isV4() const
{
  return (this->_isV4);
}

bool	Address::isV6() const
{
  return (this->_isV6);
}

bool	Address::isV4Compatible() const
{
  return (this->_isV4Compatible);
}

const zia::network::IPv4Address& Address::getV4() const
{
	return (this->_iPv4Address);
}
const zia::network::IPv6Address& Address::getV6() const
{
  return (this->_iPv6Address);
}
