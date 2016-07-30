/// \file

#include "ConnectionHttp.h"
#include "Server.h"

/*********************************************************************/

ConnectionHttp::ConnectionHttp(boost::asio::io_service& ioServive, const zia::network::IEndPoint& serverEndpoint) :
  Connection(serverEndpoint), _socket(ioServive),  _shutDown(false), _session(*this)
{
}

ConnectionHttp::~ConnectionHttp()
{
}

/*********************************************************************/

boost::asio::ip::tcp::socket&	ConnectionHttp::getSocket()
{
  return (this->_socket);
}

Session&	ConnectionHttp::getSession()
{
  return (this->_session);
}

/*********************************************************************/

void	ConnectionHttp::stop()
{
  this->_socket.close();
}

void	ConnectionHttp::receive()
{
  boost::system::error_code		error;
  size_t				nbBytes;
  int					res;
  res = 1;
  while (!this->_shutDown)
    {
      nbBytes = this->_socket.read_some(boost::asio::buffer(this->_receiveBuffer, 4096),  error);
      if (!error)
	{
	  res = this->_session.treatBuffer(this->_receiveBuffer, nbBytes);
	  std::cerr <<"Return of Session = " << res << std::endl;
	   if (res == 3 || res == 4)
	     {
	       this->sendResponse(this->_session.getResponse());
	       this->_session.clear();
	     }
	}
      else
	{
	  this->stop();
	  Server::getInstance()->removeConnexion(shared_from_this());
	  break;;
	}
    }
}

void		ConnectionHttp::handleReceive(const boost::system::error_code& error, size_t nbBytes)
{
  if (!error)
    {
      int res = this->_session.treatBuffer(this->_receiveBuffer, nbBytes);
      std::cerr <<"Return of Session = " << res << std::endl;
      if (res == 1)
	this->receive();
      if (res == 3)
	this->sendResponse(this->_session.getResponse());
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

void                    ConnectionHttp::sendResponse(HttpResponse * const resp)
{
   std::string * headers = new std::string(resp->getHeader().getFullHeader() + "\r\n");
   boost::asio::async_write(this->_socket, boost::asio::buffer(*headers),
                           boost::bind(&ConnectionHttp::handleSendHeader, shared_from_this(),
                                       boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, resp, headers));
}

void                    ConnectionHttp::handleSendHeader(const boost::system::error_code& error, size_t , HttpResponse * const res, std::string * const headers)
{
  if (!error)
    {
			delete headers;
      this->sendBody(res);
    }
  else
    delete res;
}

void                    ConnectionHttp::sendBody(HttpResponse * const res)
{
  char *buf = new char[50000];
  std::stringstream & b = res->getBody();
  std::streamsize s;
  if ((s = b.readsome(buf, 50000)) > 0)
    {
      boost::asio::async_write(this->_socket, boost::asio::buffer(buf, s),
			       boost::bind(&ConnectionHttp::handleSendBody, shared_from_this(),
					   boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, res, buf));

    }
  else
    {
      if (true == this->_shutDown)
	{
	  this->stop();
	  Server::getInstance()->removeConnexion(shared_from_this());
	}
      delete res;
    }
}

void                    ConnectionHttp::handleSendBody(const boost::system::error_code& error, size_t, HttpResponse * const res, char * buf)
{
  delete []buf;
  if (!error)
    this->sendBody(res);
  else
    delete res;
}

void	ConnectionHttp::shutDown()
{
  std::cerr << "=> ConnectionHttp::shutDown" << std::endl;
  this->_shutDown = true;
}
