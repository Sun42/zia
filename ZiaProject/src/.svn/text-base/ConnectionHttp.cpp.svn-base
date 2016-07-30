/// \file

#include "ConnectionHttp.h"
#include "Server.h"

/*********************************************************************/

ConnectionHttp::ConnectionHttp(boost::asio::io_service& ioServive, boost::asio::ip::tcp::endpoint& serverEndpoint) :
  Connection(serverEndpoint), _socket(ioServive), _session(*this)
{
}

ConnectionHttp::~ConnectionHttp()
{
  std::cout << "ConnectionHttp::~ConnectionHttp" << std::endl;
}

/*********************************************************************/

boost::asio::ip::tcp::socket&	ConnectionHttp::getSocket()
{
  return (this->_socket);
}

/*********************************************************************/

void	ConnectionHttp::stop()
{
  this->_socket.close();
}

void	ConnectionHttp::receive()
{
  this->_socket.async_read_some(boost::asio::buffer(this->_receiveBuffer, 4096),
				boost::bind(&ConnectionHttp::handleReceive, shared_from_this(),

					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
}

void		ConnectionHttp::handleReceive(const boost::system::error_code& error, size_t nbBytes)
{
  if (!error)
    {
      int res = this->_session.treatBuffer(this->_receiveBuffer, nbBytes);
      if (res == 1)
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
	std::cerr << "Error ConnectionHttp::handleReceive : Value -->" << error.value() << "--> Message : " << error.message() << std::endl;
    }
}

void                    ConnectionHttp::sendResponse(HttpResponse * resp)
{
  std::stringstream stst;
  stst << resp->getBody().str().size();
  (resp->getHeader().entities()).set("Content-Length", stst.str());
  std::string * msg = new std::string(resp->getHeader().getFullHeader() + "\r\n" + resp->getBody().str());

  std::cout << *resp << std::endl;
  delete resp;
  boost::asio::async_write(this->_socket, boost::asio::buffer(*msg),
                           boost::bind(&ConnectionHttp::handleSend, this,
                                       boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, msg));

  std::cout<< "end ::sendResponse" << std::endl;
}

void                    ConnectionHttp::handleSend(const boost::system::error_code& error, size_t nbsend, std::string * msg)
{
  if (!error)
    {
      if (nbsend < msg->size())
	{
	  msg->erase(0, nbsend);
	  boost::asio::async_write(this->_socket, boost::asio::buffer(*msg),
				   boost::bind(&ConnectionHttp::handleSend, this,
					       boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, msg));
	}
      else
	delete msg;
    }
  else
    delete msg;
}
