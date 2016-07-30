#include <iostream>
#include <cstdlib>
#include <csignal>

#include "Server.h"

#if 0

#include "XmlParser.h"

int	main(void)
{
  XmlParser	myParser;
  Configuration	conf;

  if (true == myParser.read("config.xml", conf))
    {
      const Dictionnary&	plugin = static_cast<const Dictionnary&>(conf.getHive("Plugin"));
      const Dictionnary&	items = static_cast<const Dictionnary&>(conf.getHive("Items"));

      std::map<std::string, std::string>	pluginMap = plugin.getContent();
      std::map<std::string, std::string>	itemsMap = items.getContent();

      std::map<std::string, std::string>::iterator	it;
      std::map<std::string, std::string>::iterator	end;

      std::cerr << "Plugin" << std::endl;
      for (it = pluginMap.begin(), end = pluginMap.end(); it != end; ++it)
	{
	  std::cerr << "Key: " << it->first << std::endl;
	  std::cerr << "Value: " << it->second << std::endl;
	}
      std::cerr << "Items" << std::endl;
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
}

int	main(void)
{
  signal(SIGINT, stopServer);
  Server	*server = Server::getInstance();
  server->run();
  Server::destroyInstance();
  return (EXIT_SUCCESS);
}

#endif
