/// \file

#ifndef ADDRESS_H_
# define ADDRESS_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>

#include "zia_api/network/IAddress.h"

/*! \class Address
 * \brief Implementation de IAddress.
 *
 * Cette classe permet une abstraction de l'adresse qu'elle soit de type Ipv4 ou Ipv6.
 */

class Address : public zia::network::IAddress
{
 public:
  Address(boost::asio::ip::tcp::endpoint& bEndpoint);
  ~Address();

  virtual bool isV4() const;
  virtual bool isV6() const;
  virtual bool isV4Compatible() const;
  virtual const zia::network::IPv4Address& getV4() const;
  virtual const zia::network::IPv6Address& getV6() const;

 private:
  bool				_isV4;
  bool				_isV6;
  bool				_isV4Compatible;
  zia::network::IPv4Address	_iPv4Address;
  zia::network::IPv6Address	_iPv6Address;
};

#endif //!ADDRESS_H_
