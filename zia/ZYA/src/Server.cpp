#include "Server.h"


/*********************************************************************/
Server* Server::_instance = 0;
/*********************************************************************/

Server*	Server::getInstance(short int port)
{
  if (Server::_instance == 0)
    {
      //std::cout << "Creation du serveur\n";
      Server::_instance = new Server(port);
    }
  return (Server::_instance);
}

Server*	Server::getInstance()
{
  return (Server::_instance);
}

/*********************************************************************/

Server::Server(short int port)
  : _ioService(), _acceptor(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

Server::~Server()
{
}

/*********************************************************************/

void	Server::run()
{
  this->accept();
  this->_ioService.run();
}


void	Server::accept()
{
  ptrConnection	newConnection(new Connection(this->_ioService));
  this->_acceptor.async_accept(newConnection->getSocket(),
			       boost::bind(&Server::handleAccept, this, newConnection,
			       boost::asio::placeholders::error));
}

void		Server::handleAccept(ptrConnection newConnection,
				     const boost::system::error_code& error)
{
  if (!error)
    {
      this->_mutexConnections.lock();
      this->_connections.push_back(newConnection);
      this->_mutexConnections.unlock();
      newConnection->receive();
      this->accept();
    }
  else
    std::cerr <<"Error accept" << std::endl;
}

void	Server::stop()
{
  std::cout << "stop ask\n" << std::endl;
  this->_ioService.post(boost::bind(&Server::handleStop, this));
}

void		Server::handleStop()
{
  std::cout << "handleStop" << std::endl;
  this->_acceptor.close();
  this->_mutexConnections.lock();
  std::for_each(this->_connections.begin(), this->_connections.end(), boost::bind(&Connection::stop, _1));
  this->_mutexConnections.unlock();
}

void		Server::removeConnexion(ptrConnection connection)
{
  this->_mutexConnections.lock();
  this->_connections.remove(connection);
  this->_mutexConnections.unlock();
}
