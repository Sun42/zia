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
  ConnectionHttp(boost::asio::io_service&, const zia::network::IEndPoint&);
  ~ConnectionHttp();

  boost::asio::ip::tcp::socket&		getSocket();
  Session&				getSession();

  void					stop();
  void					receive();
  void					sendResponse(HttpResponse * const);
  void					shutDown();
 private:
  ConnectionHttp(ConnectionHttp const &);
  ConnectionHttp&				operator=(ConnectionHttp const &);

  void						sendBody(HttpResponse * const);
  void						handleReceive(const boost::system::error_code&, size_t);
  void						handleSendHeader(const boost::system::error_code&, size_t, HttpResponse * const, std::string * const);
  void						handleSendBody(const boost::system::error_code&, size_t, HttpResponse * const, char *);
 private:
  boost::asio::ip::tcp::socket	_socket;
  boost::array<char, 4096>	_receiveBuffer;
  bool				_shutDown;
  Session			_session;
};

typedef boost::shared_ptr<ConnectionHttp> ptrHttpConnection;

#endif // CONNECTIONHTTP_H_
