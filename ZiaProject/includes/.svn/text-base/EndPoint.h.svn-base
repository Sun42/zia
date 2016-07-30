/// \file

#ifndef ENDPOINT_H_
# define ENDPOINT_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>

#include "zia_api/network/IEndPoint.h"

/*! \class EndPoint
 * \brief Implementation de IEndPoint.
 *
 * EndPoint est une classe qui contient des informations de connexion.
 */

class	EndPoint : public zia::network::IEndPoint
{
 public:
  EndPoint(boost::asio::ip::tcp::endpoint& bEndpoint);
  ~EndPoint();
  virtual const std::string& getHostName() const;
  virtual unsigned short getPort() const;
  virtual const zia::network::IAddress& getAddress() const;
  virtual void setHostName(const std::string& hname);

 private:
  std::string			_hostName;
  unsigned short		_port;
  zia::network::IAddress*	_address;
};

#endif //! ENDPOINT_H_
