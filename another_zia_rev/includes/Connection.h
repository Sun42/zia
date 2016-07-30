/// \file

#ifndef CONNECTION_H_
# define CONNECTION_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>

#include "zia_api/network/IConnection.h"

/*! \class Connection
 * \brief Gestion des connections entre le serveur et ses clients.
 *
 * Permet de wrapper une socket pour en faciliter son utilisation.
 */

class	Connection : public zia::network::IConnection
{
 public:
  Connection(const zia::network::IEndPoint&);
  ~Connection();

  virtual void					setClient(boost::asio::ip::tcp::endpoint&);
  virtual const zia::network::IEndPoint&	getClient() const;
  virtual const zia::network::IEndPoint&	getServer() const;

 private:
  Connection(Connection const &);
  Connection&				operator=(Connection const &);

 protected:
  zia::network::IEndPoint*		_clientEndPoint;
  const zia::network::IEndPoint&	_serverEndPoint;
};

#endif // CONNECTION_H_
