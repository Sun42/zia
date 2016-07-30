#include "ConnectionHttp.h"
#include "Server.h"

ConnectionHttp::ConnectionHttp(boost::asio::io_service& ioServive, boost::asio::ip::tcp::endpoint& serverEndpoint) :
  Connection(ioServive, serverEndpoint), _session(*this)
{
}

ConnectionHttp::~ConnectionHttp()
{
}

void		ConnectionHttp::handleReceive(const boost::system::error_code& error, size_t nbBytes)
{
  if (!error)
    {
      std::cout << "Size : " << nbBytes << " - Content : " << this->_receiveBuffer.data() << std::endl;
      int res = this->_session.treatBuffer(this->_receiveBuffer, nbBytes);
      if (res == 2)
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
  std::string * header = new std::string(resp->getHeader().getFullHeader());
  std::cout << "header == " << *header << std::endl;
  *header += "\r\n";
  boost::asio::async_write(this->_socket, boost::asio::buffer(*header),
                           boost::bind(&ConnectionHttp::handleSend, this,
                                       boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, header, resp)
                           );

}

void                    ConnectionHttp::handleSend(const boost::system::error_code& error, size_t nbsend, std::string * msg, HttpResponse * resp)
{
  static int		ind = 0;

  if (!error)
    {
      if (nbsend < msg->size())
	{
	  std::cout << "Not enaught ++"<< std::endl;
	  msg->erase(0, nbsend);
	  boost::asio::async_write(this->_socket, boost::asio::buffer(*msg),
				   boost::bind(&ConnectionHttp::handleSend, this,
					       boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, msg, resp)
				   );
	}
      else if (ind == 0)
	{
	  std::cout << "ind = 0"<< std::endl;
	  delete msg;
	  msg = new std::string(resp->getBody().str());
	  ind = 1;
	  std::cout << "Body == "<< *msg << std::endl;
	  boost::asio::async_write(this->_socket, boost::asio::buffer(*msg),
				   boost::bind(&ConnectionHttp::handleSend, this,
					       boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, msg, resp)
				   );

	}
      else if (ind == 1)
	{
	  std::cout << "ind = 1"<< std::endl;
	  delete msg;
	  delete resp;
	  ind = 0;
	}
    }
}
