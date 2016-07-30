/// \file

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

SessionPlugin::SessionPlugin(SessionPlugin const & rhs) :
  _mapPtFunc(rhs._mapPtFunc)
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
}

/*********************************************************************/

void	SessionPlugin::exec(Packet& receivedPacket, Packet& packetToSend)
{
  std::map<char, ptfunc_t>::iterator itFind = this->_mapPtFunc.find(receivedPacket.getCmd());
  if (itFind != this->_mapPtFunc.end())
    {
      packetToSend << static_cast<unsigned char>(itFind->first);
      (this->*(itFind->second))(receivedPacket, packetToSend);
    }
  else // erreur mauvaise commande
    packetToSend << static_cast<unsigned char>('L') << SessionPlugin::LIB_FAIL;
}

/*********************************************************************/

void	SessionPlugin::authentification(Packet& receivedPacket, Packet& packetToSend)
{
  std::string	params;
  receivedPacket >> params;

  size_t	delimitPos = params.find_first_of(" ");
  if (std::string::npos == delimitPos)
    packetToSend << SessionPlugin::LOGIN_FAIL;
  else
    {
      std::string	name = params.substr(0, delimitPos);
      params.erase(0, delimitPos + 1); // +1 pour eraser l espace
      if ("root" == name && "root" == params)
	{
	  packetToSend << SessionPlugin::SUCCESS;
	  this->_logged = true;
	}
      else
	packetToSend << SessionPlugin::LOGIN_FAIL;
    }
}

void	SessionPlugin::loadPlugin(Packet& receivedPacket, Packet& packetToSend)
{
  if (true == this->_logged)
    {
      std::string	path;
      receivedPacket >> path;
      packetToSend << PluginManager::getInstance()->loadPlugin(path) << path;
    }
  else
    packetToSend << SessionPlugin::LOGIN_NEED;
}

void	SessionPlugin::unloadPlugin(Packet& receivedPacket, Packet& packetToSend)
{
  if (true == this->_logged)
    {
      std::string	path;
      receivedPacket >> path;
      if (PluginManager::getInstance()->unloadPlugin(path))
	packetToSend <<  SessionPlugin::SUCCESS;
      else
	packetToSend << SessionPlugin::LIB_FAIL;
      packetToSend << path;
    }
  else
    packetToSend << SessionPlugin::LOGIN_NEED;
}

void	SessionPlugin::reloadPlugin(Packet& receivedPacket, Packet& packetToSend)
{
  if (true == this->_logged)
    {
      std::string	path;
      receivedPacket >> path;
      PluginManager*	pgm = PluginManager::getInstance();
      if (true == pgm->unloadPlugin(path))
	{
	  if (pgm->loadPlugin(path))
	    packetToSend <<  SessionPlugin::SUCCESS;
	  else
	    packetToSend << SessionPlugin::LIB_FAIL;
	}
      else
	packetToSend << SessionPlugin::LIB_FAIL;
      packetToSend << path;
    }
  else
    packetToSend << SessionPlugin::LOGIN_NEED;
}

void	SessionPlugin::listPlugins(Packet&, Packet& packetToSend)
{
  if (true == this->_logged)
    {
      std::string list;
      PluginManager::getInstance()->listPlugins(list);
      packetToSend << list;
    }
  else
    packetToSend << SessionPlugin::LOGIN_NEED;
}
