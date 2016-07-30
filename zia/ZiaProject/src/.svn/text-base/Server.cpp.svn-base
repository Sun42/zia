/// \file

#include "Server.h"
#include "PluginManager.h" // --> a remove juste pour les test

/*********************************************************************/
Server* Server::_instance = 0;
/*********************************************************************/

Server*	Server::getInstance()
{
  if (Server::_instance == 0)
    {
      Server::_instance = new Server();
    }
  return (Server::_instance);
}

void	Server::destroyInstance()
{
  if (Server::_instance != 0)
    {
      delete Server::_instance;
      Server::_instance = 0;
    }
}

/*********************************************************************/

Server::Server()
  : _ioService(),
    _acceptorHttp(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 80)),
    _acceptorSSL(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 443)),
    _acceptorPlugin(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 42000))
{
  std::cerr << "avant  le load du premier plugin\n";
  //PluginManager::getInstance()->loadPlugin("../plugins/BodyProcessing/DirectoryBrowsing/build/lib/libpluginDirectoryBrowsing.so");
  PluginManager::getInstance()->loadPlugin("../plugins/BodyProcessing/DirectoryBrowsing/test.so");
  std::cerr << "apres le load du premier plugin\n";
  std::string list;
  PluginManager::getInstance()->listPlugins(list);
  std::cout << list << std::endl;
}

Server::~Server()
{
  std::cout << "Server::~Server" << std::endl;
}

/*********************************************************************/

void	Server::run()
{
  std::cout << "Server running\n";
  this->acceptHttp();
  this->acceptPlugin();
  this->_ioService.run();
}

void	Server::acceptHttp()
{
  boost::asio::ip::tcp::endpoint	endpoint = this->_acceptorHttp.local_endpoint();
  ptrHttpConnection			newConnection(new ConnectionHttp(this->_ioService, endpoint));

  this->_acceptorHttp.async_accept(newConnection->getSocket(),
				   boost::bind(&Server::handleAcceptHttp, this, newConnection,
					       boost::asio::placeholders::error));
}

void	Server::acceptPlugin()
{
  ptrPluginConnection			newConnection(new ConnectionPlugin(this->_ioService));

  this->_acceptorPlugin.async_accept(newConnection->getSocket(),
				     boost::bind(&Server::handleAcceptPlugin, this, newConnection,
						 boost::asio::placeholders::error));
}


void		Server::handleAcceptHttp(ptrHttpConnection newConnection,
					 const boost::system::error_code& error)
{
  if (!error)
    {
      // hookmanager faire le NEW_CONNECTION
      this->_mutexConnectionsHttp.lock();
      this->_connectionsHttp.push_back(newConnection);
      this->_mutexConnectionsHttp.unlock();
      boost::asio::ip::tcp::endpoint endpoint = newConnection->getSocket().remote_endpoint();
      newConnection->setClient(endpoint);
      std::cerr << "New connection from : " << endpoint << std::endl;
      newConnection->receive();
      this->acceptHttp();
    }
  else if (error.value() != 125)
    std::cerr << "Error : Value -->" << error.value() << " --> Sig:" << error.message() << std::endl;
}

void		Server::handleAcceptPlugin(ptrPluginConnection newConnection,
					   const boost::system::error_code& error)
{
  if (!error)
    {
      std::cout <<  "new connection Plugin" << std::endl;
      this->_mutexConnectionsPlugin.lock();
      this->_connectionsPlugin.push_back(newConnection);
      this->_mutexConnectionsPlugin.unlock();
      newConnection->receive();
      this->acceptPlugin();
    }
  else if (error.value() != 125)
    std::cerr << "Error : Value -->" << error.value() << " --> Sig:" << error.message() << std::endl;
}

void	Server::stop()
{
  std::cout << "Server::stop\n" << std::endl;
  this->_ioService.post(boost::bind(&Server::handleStop, this));
}

void		Server::handleStop()
{
  std::cout << "Server::handleStop" << std::endl;
  this->_acceptorHttp.close();
  this->_acceptorPlugin.close();
  this->_acceptorSSL.close();

  this->_mutexConnectionsHttp.lock();
  std::for_each(this->_connectionsHttp.begin(), this->_connectionsHttp.end(), boost::bind(&Connection::stop, _1));
  this->_connectionsHttp.clear();
  this->_mutexConnectionsHttp.unlock();

  this->_mutexConnectionsPlugin.lock();
  std::for_each(this->_connectionsPlugin.begin(), this->_connectionsPlugin.end(), boost::bind(&Connection::stop, _1));
  this->_connectionsPlugin.clear();
  this->_mutexConnectionsPlugin.unlock();
}

template<>
void		Server::removeConnexion<ptrHttpConnection>(ptrHttpConnection connection)
{
  this->_mutexConnectionsHttp.lock();
  this->_connectionsHttp.remove(connection);
  this->_mutexConnectionsHttp.unlock();
}

template<>
void		Server::removeConnexion<ptrPluginConnection>(ptrPluginConnection connection)
{
  this->_mutexConnectionsPlugin.lock();
  this->_connectionsPlugin.remove(connection);
  this->_mutexConnectionsPlugin.unlock();
}
