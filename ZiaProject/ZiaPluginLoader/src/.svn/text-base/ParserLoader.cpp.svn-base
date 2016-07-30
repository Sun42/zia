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
	{
		std::cerr << "Unknown Command" << std::endl;
	}
}

/*********************************************************************/

void	ParserLoader::authentification(Packet& receivedPacket)
{
	unsigned char	responseState;
	receivedPacket >> responseState;

	if (responseState == '1')
	{
		emit loginState(true);
	}
	else if (responseState == '2')
	{
		emit loginState(false);
	}
}

void	ParserLoader::loadPlugin(Packet& receivedPacket)
{
	unsigned char	responseState;

	receivedPacket >> responseState;
  if ('1' == responseState)
  {
	  emit pluginLoadState(true);
  }
  else if ('3' == responseState)
  {
	  emit pluginLoadState(false, tr("Incorrect path..."));
  }
  else if ('4' == responseState)
  {
	  emit pluginLoadState(false, tr("Invalid plugin..."));
  }
  else if ('6' == responseState)
  {
	  emit pluginLoadState(false, tr("Plugin already loaded..."));
  }
}

void	ParserLoader::unloadPlugin(Packet& receivedPacket)
{
	unsigned char	responseState;
	std::string		path;

	receivedPacket >> responseState;
	receivedPacket >> path;
	if ('1' == responseState)
	{
		emit unloadPluginState(true, path.c_str());
	}
	else if ('3' == responseState)
	{
		emit unloadPluginState(false, tr("Incorrect path..."));
	}
	else if ('4' == responseState)
	{
		emit unloadPluginState(false, tr("Invalid plugin..."));
	}
}

void	ParserLoader::reloadPlugin(Packet& receivedPacket)
{
	unsigned char	responseState;
	receivedPacket >> responseState;
	if (responseState == '1')
	{
		emit reloadPluginState(true);
	}
	else if ('3' == responseState)
	{
		emit reloadPluginState(false, tr("Incorrect path..."));
	}
	else if ('4' == responseState)
	{
		emit reloadPluginState(false, tr("Invalid plugin..."));
	}
}

void	ParserLoader::listPlugins(Packet& receivedPacket)
{
	std::string list;
	receivedPacket >> list;
	QStringList	plugins = QString(list.c_str()).split("\r\n", QString::SkipEmptyParts);
	emit sendPluginList(plugins);
}
