#ifndef SERVER_H_
# define SERVER_H_

#include <list>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Connection.h"

class	Server
{
 public:
  static Server*	getInstance(short int);
  static Server*	getInstance();
  void			run();
  void			stop();
  void			removeConnexion(ptrConnection);

 private:
  Server(short int);
  ~Server();
  Server(Server const &);
  Server&	operator=(Server const &);

  void		accept();
  void		handleAccept(ptrConnection, const boost::system::error_code&);
  void		handleStop();

 private:
  static Server*			_instance;
  boost::asio::io_service		_ioService;
  boost::asio::ip::tcp::acceptor	_acceptor;
  boost::mutex				_mutexConnections;
  std::list<ptrConnection>		_connections;
};

#endif // SERVER_H_
