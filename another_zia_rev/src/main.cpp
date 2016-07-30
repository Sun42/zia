/// \file

#include <iostream>
#include <cstdlib>
#include <csignal>

#include "Server.h"
#include "PluginManager.h"
#include "XmlParser.h"
#include "StringToType.hpp"

static void	stopServer(int)
{
  Server::getInstance()->stop();
  PluginManager::getInstance()->unloadAllPlugins();
}

static void	loadConfiguration(Configuration& ziaConf, unsigned short& portSSL, unsigned short& portHttp, unsigned short& portAdmin)
{
  ziaConf.checkZiaConfiguration();
  zia::IDictionnary const &	portDictionnary = ziaConf.getHive("Ports");
  portSSL = stringToType<unsigned short>(portDictionnary.get("SSL"));
  portHttp = stringToType<unsigned short>(portDictionnary.get("Http"));
  portAdmin = stringToType<unsigned short>(portDictionnary.get("PluginLoader"));
}

int	main(void)
{
  signal(SIGINT, stopServer);
  Server		*server;
  unsigned short	portSSL, portHttp, portAdmin;
  XmlParser		parser;
  Configuration		ziaConf;

  parser.read("ZiaConf.xml", ziaConf);
  loadConfiguration(ziaConf, portSSL, portHttp, portAdmin);
  try
    {
      server = Server::getInstance(static_cast<const Dictionnary &>(ziaConf.getHive("Main")), portSSL, portHttp, portAdmin);
    }
  catch (const std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  server->loadStartingPlugins(ziaConf.getHive("Plugins"));
  server->run();
  //  std::cerr << "DEBUG ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CA TERMINE PROPREMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  Server::destroyInstance();
  return (EXIT_SUCCESS);
}
