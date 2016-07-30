/// \file

#include <iostream>

#include <boost/bind.hpp>

#include "Connection.h"
#include "EndPoint.h"

/*********************************************************************/

Connection::Connection() :
  _clientEndPoint(0), _serverEndPoint(0)
{
}

Connection::Connection(boost::asio::ip::tcp::endpoint& serverEndPoint) :
  _clientEndPoint(0), _serverEndPoint(new EndPoint(serverEndPoint))
{
  this->_serverEndPoint->setHostName(boost::asio::ip::host_name());
}

Connection::~Connection()
{
  delete this->_clientEndPoint;
  delete this->_serverEndPoint;
}

/*********************************************************************/

void		Connection::setClient(boost::asio::ip::tcp::endpoint& clientEndPoint)
{
  if (!this->_clientEndPoint)
    this->_clientEndPoint = new EndPoint(clientEndPoint);
}

const zia::network::IEndPoint& Connection::getClient() const
{
  return (*this->_clientEndPoint);
}

const zia::network::IEndPoint& Connection::getServer() const
{
  return (*this->_serverEndPoint);
}
