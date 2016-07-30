#include <string>
#include <fstream>
#include <iostream>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "ParserLoader.h"

ParserLoader::ParserLoader()
{
  this->_mapPtFunc['A'] = &ParserLoader::authentification;
  this->_mapPtFunc['L'] = &ParserLoader::loadPlugin;
  this->_mapPtFunc['U'] = &ParserLoader::unloadPlugin;
  this->_mapPtFunc['R'] = &ParserLoader::reloadPlugin;
  this->_mapPtFunc['l'] = &ParserLoader::listPlugins;
}

ParserLoader::~ParserLoader()
{
  this->_mapPtFunc.clear();
}

/*********************************************************************/

void	ParserLoader::exec(Packet& receivedPacket)
{
  std::map<char, ptfunc_t>::iterator itFind = this->_mapPtFunc.find(receivedPacket.getCmd());
  if (itFind != this->_mapPtFunc.end())
	{
	  ptfunc_t	ptFunc = itFind->second;
	  (this->*ptFunc)(receivedPacket);
	}
  else
	std::cerr << "Unknown Command" << std::endl;
}

/*********************************************************************/

void	ParserLoader::authentification(Packet& receivedPacket)
{
  std::cout << "ParserLoader::authentification" << std::endl;
  unsigned char	responseState;
  receivedPacket >> responseState;

  if (responseState == '1')
  {
	  std::cerr << "SUCCESS" << std::endl;
	  emit loginState(true);
  }
  else if (responseState == '2')
  {
	  std::cerr << "FAILED." << std::endl;
	  emit loginState(false);
  }
}

void	ParserLoader::loadPlugin(Packet& receivedPacket)
{
  std::cout << "ParserLoader::loadPlugin" << std::endl;
  unsigned char	responseState;
  receivedPacket >> responseState;
  if (responseState == '1')
  {
	  emit pluginLoadState(true);
  }
  else if (responseState == '3')
  {
	  emit pluginLoadState(false, tr("Incorrect Path..."));
  }
  else if (responseState == '4')
  {
	  emit pluginLoadState(false, tr("Invalid DLL..."));
  }
}

void	ParserLoader::unloadPlugin(Packet& receivedPacket)
{
	std::cout << "ParserLoader::unloadPlugin" << std::endl;
	unsigned char	responseState;
	receivedPacket >> responseState;
	if (responseState == '1')
	{
		emit unloadPluginState(true);
	}
	else if (responseState == '3')
	{
		emit unloadPluginState(false, tr("Incorrect Path..."));
	}
	else if (responseState == '4')
	{
		emit unloadPluginState(false, tr("Incorrect DLL..."));
	}
}

void	ParserLoader::reloadPlugin(Packet& receivedPacket)
{
	std::cout << "ParserLoader::reloadPlugin" << std::endl;
	unsigned char	responseState;
	receivedPacket >> responseState;
	if (responseState == '1')
	{
		emit reloadPluginState(true);
	}
	else if (responseState == '3')
	{
		emit reloadPluginState(false, tr("Incorrect Path..."));
	}
	else if (responseState == '4')
	{
		emit reloadPluginState(false, tr("Incorrect DLL..."));
	}
}

void	ParserLoader::listPlugins(Packet& receivedPacket)
{
  std::cout << "ParserLoader::listPlugins" << std::endl;
  std::string list;
  receivedPacket >> list;
  QStringList	plugins = QString(list.c_str()).split("\r\n", QString::SkipEmptyParts);
  emit sendPluginList(plugins);
}
