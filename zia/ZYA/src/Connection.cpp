#include <iostream>

#include <boost/bind.hpp>

#include "Connection.h"
#include "Server.h"

/*********************************************************************/

Connection::Connection(boost::asio::io_service& ioService) :
  _socket(ioService)
{
  //std::cout << "New Connection from : " << this->_socket.remote_endpoint() << std::endl;
}

Connection::~Connection()
{
  std::cout << "Connexion Close" << std::endl;
  Server::getInstance()->removeConnexion(shared_from_this());
}

/*********************************************************************/

boost::asio::ip::tcp::socket&	Connection::getSocket()
{
  return (this->_socket);
}

/*********************************************************************/

void	Connection::receive()
{
  this->_socket.async_read_some(boost::asio::buffer(this->_receiveBuffer, 4096),
				boost::bind(&Connection::handleReceive, shared_from_this(),
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
}

void		Connection::handleReceive(const boost::system::error_code& error, size_t nbByteRecv)
{
  if (!error)
    {
      for (unsigned int i = 0; i < nbByteRecv; ++i)
        {
	  std::cout << this->_receiveBuffer[i];
	}
      this->send();
      this->receive();
    }
}

void	Connection::send()
{
  std::string	*data = new std::string("HTTP/1.1 200 OK\r\nDate: Mon, 23 May 2005 22:38:34 GMT\r\nServer: Apache/1.3.3.7 (Unix)  (Red-Hat/Linux)\r\nLast-Modified: Wed, 08 Jan 2003 23:11:55 GMT\r\nEtag: \"3f80f-1b6-3e1cb03b\"\r\nAccept-Ranges: bytes\r\nContent-Length: 4\r\nConnection: close\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nyann");
  this->_socket.async_write_some(boost::asio::buffer(*data, data->size()),
				 boost::bind(&Connection::handleSend, shared_from_this(),
					     boost::asio::placeholders::error,
					     boost::asio::placeholders::bytes_transferred, data));
}

void	Connection::handleSend(const boost::system::error_code& error, size_t nbByteSend, std::string* data)
{
  if (!error)
    {
      delete data;
    }
}

void	Connection::stop()
{
  this->_socket.close();
}
