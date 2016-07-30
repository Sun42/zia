/// \file

#ifndef CONNECTIONPLUGIN_H_
# define CONNECTIONPLUGIN_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/enable_shared_from_this.hpp>

#include "Connection.h"
#include "Packet.h"
#include "SessionPlugin.h"

/*! \class ConnectionPlugin
 * \brief  Connection des plugins.
 *
 * Traitement de handleReceve se fait differemment que dans la classe Connection.
 */

class	ConnectionPlugin : public Connection, public boost::enable_shared_from_this<ConnectionPlugin>
{
 public:
  ConnectionPlugin(boost::asio::io_service&);
  ~ConnectionPlugin();

  boost::asio::ip::tcp::socket&		getSocket();

  void					stop();
  void					receive();

 private:
  ConnectionPlugin(ConnectionPlugin const &);
  ConnectionPlugin&	operator=(ConnectionPlugin const &);

  virtual void		handleReceive(const boost::system::error_code&, size_t);
  void			send(Packet const &);
  void			handleSend(const boost::system::error_code& , size_t , std::vector<unsigned char>*);

 private:
  boost::asio::ip::tcp::socket		_socket;
  boost::array<unsigned char, 4096>	_receiveBuffer;
  Packet				_packetReceive;
  SessionPlugin				_parser;
};

typedef boost::shared_ptr<ConnectionPlugin> ptrPluginConnection;

#endif
