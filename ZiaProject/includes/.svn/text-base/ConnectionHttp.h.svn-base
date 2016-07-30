/// \file

#ifndef CONNECTIONHTTP_H_
# define CONNECTIONHTTP_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/enable_shared_from_this.hpp>

#include "Connection.h"
#include "Session.h"

/*! \class ConnectionHttp 
 * \brief Gestion des connexions.
 *
 * Cette classe est une specialisation de connection, elle permet un traitement specifique de handleReceive.
 */

class	ConnectionHttp : public Connection, public boost::enable_shared_from_this<ConnectionHttp>
{
 public:
  ConnectionHttp(boost::asio::io_service&, boost::asio::ip::tcp::endpoint&);
  ~ConnectionHttp();

  boost::asio::ip::tcp::socket&		getSocket();

  void					stop();
  void					receive();
  void					sendResponse(HttpResponse *);

 private:
  ConnectionHttp(ConnectionHttp const &);
  ConnectionHttp&				operator=(ConnectionHttp const &);

  void						handleReceive(const boost::system::error_code&, size_t);
  void						handleSend(const boost::system::error_code&, size_t, std::string *);

 private:
  boost::asio::ip::tcp::socket	_socket;
  boost::array<char, 4096>	_receiveBuffer;
  Session			_session;
};

typedef boost::shared_ptr<ConnectionHttp> ptrHttpConnection;

#endif // CONNECTIONHTTP_H_
