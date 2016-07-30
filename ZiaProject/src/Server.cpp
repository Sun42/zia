/// \file

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "Server.h"
#include "PluginManager.h"

/*********************************************************************/
Server* Server::_instance = 0;
/*********************************************************************/

Server*	Server::getInstance(const Dictionnary& ziaConf, unsigned short portSSL, unsigned short portHttp, unsigned short portAdmin)
{
  if (Server::_instance == 0)
    {
      Server::_instance = new Server(ziaConf, portSSL, portHttp, portAdmin);
    }
  return (Server::_instance);
}

Server*	Server::getInstance()
{
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

Server::Server(const Dictionnary& defaultConf, unsigned short portSSL, unsigned short portHttp, unsigned short portAdmin)
  : _ioService(),
    _acceptorHttp(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portHttp)),
    _acceptorSSL(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portSSL)),
    _acceptorPlugin(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portAdmin)),
    _defaultConf(defaultConf)
{
}

Server::~Server()
{
  std::cout << "Server::~Server" << std::endl;
  HookManager::destroyInstance();
  PluginManager::destroyInstance();
}

/*********************************************************************/

const Dictionnary&	Server::getDefaultConf() const
{
  return (this->_defaultConf);
}

/*********************************************************************/

static std::string&	trim(std::string& str)
{
  return (str = str.substr(str.find_first_not_of(" \t\f\v\n\r"),
			   str.find_last_not_of(" \t\f\v\n\r") - str.find_first_not_of(" \t\f\v\n\r") + 1));
}

void	Server::loadStartingPlugins(zia::IDictionnary const & defaultPlugins)
{
  PluginManager*	pgm = PluginManager::getInstance();

  std::string	listPlugin = defaultPlugins.get("LoadPlugin"), path;
  size_t	pos;

  if (listPlugin != "")
    {
      listPlugin = listPlugin.substr(listPlugin.find_first_of("\n") + 1);
      while ((pos = listPlugin.find_first_of("\n")) != std::string::npos)
	{
	  path = listPlugin.substr(0, pos);
	  if (path != "")
	    pgm->loadPlugin(boost::filesystem::system_complete(boost::filesystem::path(trim(path))).string());
	  listPlugin = listPlugin.substr(pos + 1);
	}
    }

  listPlugin = defaultPlugins.get("LoadDirectory");
  if (listPlugin != "")
    {
      listPlugin = listPlugin.substr(listPlugin.find_first_of("\n") + 1);
      while ((pos = listPlugin.find_first_of("\n")) != std::string::npos)
	{
	  path = listPlugin.substr(0, pos);
	  if (path != "")
	    pgm->loadPlugins(boost::filesystem::system_complete(boost::filesystem::path(trim(path))).string());
	  listPlugin = listPlugin.substr(pos + 1);
	}
    }
}

void	Server::run()
{
  std::cout << "Server Running\nHttp Port\t: " << this->_acceptorHttp.local_endpoint().port() <<
    "\nSSL Port\t: " << this->_acceptorSSL.local_endpoint().port() <<
    "\nAdmin Port\t: " << this->_acceptorPlugin.local_endpoint().port() << std::endl;
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
  std::cout << "Server::stop" << std::endl;
  this->_ioService.post(boost::bind(&Server::handleStop, this));
}

void		Server::handleStop()
{
  std::cout << "\n\n\nServer::handleStop" << std::endl;
  this->_acceptorHttp.close();
  this->_acceptorPlugin.close();
  this->_acceptorSSL.close();

  this->_mutexConnectionsHttp.lock();
  std::for_each(this->_connectionsHttp.begin(), this->_connectionsHttp.end(), boost::bind(&ConnectionHttp::stop, _1));
  this->_connectionsHttp.clear();
  this->_mutexConnectionsHttp.unlock();

  this->_mutexConnectionsPlugin.lock();
  std::for_each(this->_connectionsPlugin.begin(), this->_connectionsPlugin.end(), boost::bind(&ConnectionPlugin::stop, _1));
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
