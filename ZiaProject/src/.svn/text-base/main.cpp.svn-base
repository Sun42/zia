/// \file

#include <iostream>
#include <cstdlib>
#include <csignal>

#include "Server.h"
#include "PluginManager.h"
#include "Configuration.h"
#include "XmlParser.h"
#include "IDictionnary.h"
#include "StringToType.hpp"

#if 0

#include "XmlParser.h"

int	main(void)
{
   XmlParser	myParser;
   Configuration	conf;

   if (true == myParser.read("ZiaConf.xml", conf))
     {
       const Dictionnary&	plugin = static_cast<const Dictionnary&>(conf.getHive("Plugins"));
       const Dictionnary&	items = static_cast<const Dictionnary&>(conf.getHive("Main"));

       std::map<std::string, std::string>	pluginMap = plugin.getContent();
       std::map<std::string, std::string>	itemsMap = items.getContent();

       std::map<std::string, std::string>::iterator	it;
       std::map<std::string, std::string>::iterator	end;

       std::cerr << "file mapper:" << std::endl;
       for (it = pluginMap.begin(), end = pluginMap.end(); it != end; ++it)
 	{
 	  std::cerr << "Key: " << it->first << std::endl;
 	  std::cerr << "Value: " << it->second << std::endl;
 	}
       std::cerr << "ssl:" << std::endl;
       for (it = itemsMap.begin(), end = itemsMap.end(); it != end; ++it)
 	{
 	  std::cerr << "Key: " << it->first << std::endl;
 	  std::cerr << "Value: " << it->second << std::endl;
 	}
     }
   return (0);
}

#else

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
  std::cerr << "DEBUG ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CA TERMINE PROPREMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  Server::destroyInstance();
  return (EXIT_SUCCESS);
}

#endif
