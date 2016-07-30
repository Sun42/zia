/// \file

#include "Connection.h"
#include "EndPoint.h"

/*********************************************************************/

Connection::Connection(const zia::network::IEndPoint& serverEndPoint) :
  _clientEndPoint(0), _serverEndPoint(serverEndPoint)
{
}

Connection::~Connection()
{
  delete this->_clientEndPoint;
}

/*********************************************************************/

void		Connection::setClient(boost::asio::ip::tcp::endpoint& clientEndPoint)
{
  if (0 == this->_clientEndPoint)
    this->_clientEndPoint = new EndPoint(clientEndPoint);
}

const zia::network::IEndPoint& Connection::getClient() const
{
  return (*this->_clientEndPoint);
}

const zia::network::IEndPoint& Connection::getServer() const
{
  return (this->_serverEndPoint);
}
