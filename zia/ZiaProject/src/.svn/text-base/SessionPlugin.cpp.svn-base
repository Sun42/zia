#include <fstream>
#include <string>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "SessionPlugin.h"
#include "PluginManager.h"

SessionPlugin::SessionPlugin() :
  _logged(false)
{
  this->_mapPtFunc['A'] = &SessionPlugin::authentification;
  this->_mapPtFunc['L'] = &SessionPlugin::loadPlugin;
  this->_mapPtFunc['U'] = &SessionPlugin::unloadPlugin;
  this->_mapPtFunc['R'] = &SessionPlugin::reloadPlugin;
  this->_mapPtFunc['l'] = &SessionPlugin::listPlugins;
}

SessionPlugin::SessionPlugin(SessionPlugin const & rhs): _mapPtFunc(rhs._mapPtFunc)
{
}

SessionPlugin &	SessionPlugin::operator=(SessionPlugin const & rhs)
{
  if (this != &rhs)
    {
      this->_mapPtFunc = rhs._mapPtFunc;
    }
  return (*this);
}

SessionPlugin::~SessionPlugin()
{
  this->_mapPtFunc.clear();
}

/*********************************************************************/

void	SessionPlugin::exec(Packet& receivedPacket, Packet& packetToSend)
{
  std::map<char, ptfunc_t>::iterator itFind = this->_mapPtFunc.find(receivedPacket.getCmd());
  if (itFind != this->_mapPtFunc.end())
    {
      ptfunc_t	ptFunc = itFind->second;
      packetToSend << static_cast<unsigned char>(itFind->first);
      (this->*ptFunc)(receivedPacket, packetToSend);
    }
  else
    {
      std::cerr << "Unknown Command" << std::endl;
      packetToSend << static_cast<unsigned char>('L');
      packetToSend << static_cast<unsigned char>('4');
    }
}

/*********************************************************************/

void	SessionPlugin::authentification(Packet& receivedPacket, Packet& packetToSend)
{
  std::cout << "SessionPlugin::authentification" << std::endl;
  std::string	params;
  receivedPacket >> params;

  size_t	delimitPos = params.find_first_of(" ");
  if (delimitPos == std::string::npos)
    packetToSend << static_cast<unsigned char>('2');
  else
    {
      std::string	name = params.substr(0, delimitPos);
      params.erase(0, delimitPos + 1); // +1 pour eraser l espace
      if (name == "root" && params == "root")
	{
	  packetToSend << static_cast<unsigned char>('1');
	  this->_logged = true;
	}
      else
	packetToSend << static_cast<unsigned char>('2');
    }
}

void	SessionPlugin::loadPlugin(Packet& receivedPacket, Packet& packetToSend)
{
  std::cout << "SessionPlugin::loadPlugin" << std::endl;
  if (this->_logged)
    {
      std::string	path;
      receivedPacket >> path;

      boost::filesystem::path       mypath(path);
#ifdef _WIN32
      std::string ext(".dll");
#else
      std::string ext(".so");
#endif

      if (boost::filesystem::extension(mypath) != ext)
	packetToSend << static_cast<unsigned char>('3');
      else
	packetToSend << (PluginManager::getInstance()->loadPlugin(path) ? static_cast<unsigned char>('1') : static_cast<unsigned char>('4'));
    }
  else
    packetToSend << static_cast<unsigned char>('5');
}

void	SessionPlugin::unloadPlugin(Packet& receivedPacket, Packet& packetToSend)
{
  if (this->_logged)
    {
  std::cout << "SessionPlugin::unloadPlugin" << std::endl;
  std::string	path;
  receivedPacket >> path;

  boost::filesystem::path       mypath(path);
#ifdef _WIN32
  std::string ext(".dll");
#else
  std::string ext(".so");
#endif

  if (boost::filesystem::extension(mypath) != ext)
    packetToSend << static_cast<unsigned char>('3');
  else
    packetToSend << (PluginManager::getInstance()->unloadPlugin(path) ? static_cast<unsigned char>('1') : static_cast<unsigned char>('4'));
    }
  else
    packetToSend << static_cast<unsigned char>('5');
}

void	SessionPlugin::reloadPlugin(Packet& receivedPacket, Packet& packetToSend)
{
  if (this->_logged)
    {
      std::cout << "SessionPlugin::reloadPlugin" << std::endl;
      std::string	path;
      receivedPacket >> path;

      boost::filesystem::path       mypath(path);
#ifdef _WIN32
      std::string ext(".dll");
#else
      std::string ext(".so");
#endif

      if (boost::filesystem::extension(mypath) != ext)
	packetToSend << static_cast<unsigned char>('3');
      else
	{
	  PluginManager*	pl = PluginManager::getInstance();
	  if (pl->unloadPlugin(path))
	    packetToSend << (pl->unloadPlugin(path) ? static_cast<unsigned char>('1') : static_cast<unsigned char>('4'));
	  else
	    packetToSend << static_cast<unsigned char>('4');
	}
    }
  else
    packetToSend << static_cast<unsigned char>('5');
}

void	SessionPlugin::listPlugins(Packet&, Packet& packetToSend)
{
  if (this->_logged)
    {
      std::cout << "SessionPlugin::listPlugins" << std::endl;
      std::string list;
      PluginManager::getInstance()->listPlugins(list);
      packetToSend << list;
    }
  else
    packetToSend << static_cast<unsigned char>('5');
}
