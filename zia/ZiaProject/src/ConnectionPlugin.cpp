#include <iostream>

#include <boost/bind.hpp>

#include "ConnectionPlugin.h"

#include "Server.h"

ConnectionPlugin::ConnectionPlugin(boost::asio::io_service& ioService) :
  Connection(ioService)
{
}

ConnectionPlugin::~ConnectionPlugin()
{
  std::cout << "ConnectionPlugin::~ConnectionPlugin\n";
}

void		ConnectionPlugin::handleReceive(const boost::system::error_code& error, size_t nbBytes)
{
  std::cout << "ConnectionPlugin::handleReceive\n";
  if (!error)
    {
      std::cout << "Size : " << nbBytes << " - Content : " << this->_receiveBuffer.data() << "<----" << std::endl;
      for (unsigned int i = 0; i < nbBytes; ++i)
	{
	  std::cout << "[" << this->_receiveBuffer[i] << "]";
	}
      std::cout << "add du packet\n";
      this->_packetReceive.add(this->_receiveBuffer, static_cast<unsigned int>(nbBytes));
      std::cout << "check de la len";
      if (this->_packetReceive.checkLen())
	{
	  std::cout << "\nexec du packet";
	  Packet	responsePacket;
	  this->_parser.exec(this->_packetReceive, responsePacket);
	  responsePacket.addHead();
	  this->send(responsePacket);
	  this->_packetReceive.reset();
	}
      this->receive();
    }
  else
    {
      if (error.value() == 2 || error.value() == 104)
	{
	  this->stop();
	  Server::getInstance()->removeConnexion(shared_from_this());
	}
      else
	std::cerr << "Error ConnectionPlugin::handleReceive : Value -->" << error.value() << "--> Message : " << error.message() << std::endl;
    }
}

void	ConnectionPlugin::send(Packet const & data)
{
  std::vector<unsigned char>    *bufToSend = data.getData();

  this->_socket.async_send(boost::asio::buffer(*bufToSend),
			   boost::bind(&ConnectionPlugin::handleSend,
				       shared_from_this(),
				       boost::asio::placeholders::error,
				       boost::asio::placeholders::bytes_transferred,
				       bufToSend));
}

void	ConnectionPlugin::handleSend(const boost::system::error_code& error, size_t, std::vector<unsigned char>* dataSent)
{
  if (!error)
    {
      std::cerr << "jai send un msg" << std::endl;
      delete dataSent;
    }
  else
    std::cerr << "Error ConnectionHttp::handleSend : Value -->" << error.value() << "--> Message : " << error.message() << std::endl;
}
