/// \file

#include <iostream>

#include <boost/bind.hpp>

#include "Connection.h"
#include "EndPoint.h"

/*********************************************************************/

Connection::Connection(boost::asio::io_service& ioService) :
  _socket(ioService), _clientEndPoint(0), _serverEndPoint(0)
{}

Connection::Connection(boost::asio::io_service& ioService, boost::asio::ip::tcp::endpoint& serverEndPoint) :
  _socket(ioService), _clientEndPoint(0), _serverEndPoint(new EndPoint(serverEndPoint))
{
}

Connection::~Connection()
{
  if (this->_clientEndPoint != 0)
    delete this->_clientEndPoint;
  if (this->_serverEndPoint != 0)
    delete this->_serverEndPoint;
}

/*********************************************************************/

boost::asio::ip::tcp::socket&	Connection::getSocket()
{
  return (this->_socket);
}

/*********************************************************************/

void	Connection::receive()
{
  this->_socket.async_read_some(boost::asio::buffer(this->_receiveBuffer /*this->_session.getReceiver()*/, 4096),
				boost::bind(&Connection::handleReceive, this,
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
}

void	Connection::stop()
{
  this->_socket.close();
}

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
