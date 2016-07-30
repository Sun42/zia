/// \file

#include "ConnectionPlugin.h"
#include "Server.h"

/*********************************************************************/

ConnectionPlugin::ConnectionPlugin(boost::asio::io_service& ioService, const zia::network::IEndPoint& serverEndpoint) :
  Connection(serverEndpoint), _socket(ioService)
{
}

ConnectionPlugin::~ConnectionPlugin()
{
}

/*********************************************************************/

boost::asio::ip::tcp::socket&	ConnectionPlugin::getSocket()
{
  return (this->_socket);
}

/*********************************************************************/

void	ConnectionPlugin::stop()
{
  this->_socket.close();
}

void	ConnectionPlugin::receive()
{
  this->_socket.async_read_some(boost::asio::buffer(this->_receiveBuffer, 4096),
				boost::bind(&ConnectionPlugin::handleReceive,
					    shared_from_this(),
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
}

void		ConnectionPlugin::handleReceive(const boost::system::error_code& error, size_t nbBytes)
{
  if (!error)
    {
      this->_packetReceive.add(this->_receiveBuffer, static_cast<unsigned int>(nbBytes));
      if (true == this->_packetReceive.checkLen())
	{
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

void	ConnectionPlugin::handleSend(const boost::system::error_code& error, size_t, std::vector<unsigned char>* const dataSent)
{
  if (!error)
    std::cerr << "ConnectionPlugin::handleSend" << std::endl;
  else
    std::cerr << "Error ConnectionHttp::handleSend : Value -->" << error.value() << "--> Message : " << error.message() << std::endl;
  delete dataSent;
}
