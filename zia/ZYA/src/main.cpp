#include <iostream>
#include <cstdlib>
#include <signal.h>

#include "Server.h"

void	stopServer(int)
{
  std::cout << "Stopping server" << std::endl;
  Server::getInstance()->stop();
  //exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
  signal(SIGINT, stopServer);
  if (argc == 2)
    {
      Server	*server = Server::getInstance(::atoi(argv[1]));
      server->run();
    }
  else
    {
      std::cerr << "./zia port"<< std::endl;
    }
  return (EXIT_SUCCESS);
}
