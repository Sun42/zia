#ifndef CONNECTION_H_
# define CONNECTION_H_

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>

class	Connection : public boost::enable_shared_from_this<Connection>
{
 public:
  Connection(boost::asio::io_service&);
  ~Connection();
  boost::asio::ip::tcp::socket&	getSocket();
  void				receive();
  void				send();
  void				stop();

 private:
  Connection(Connection const &);
  Connection&			operator=(Connection const &);

  void				handleReceive(const boost::system::error_code&, size_t);
  void				handleSend(const boost::system::error_code& , size_t, std::string*);

 private:
  boost::asio::ip::tcp::socket	_socket;
  boost::array<char, 4096>	_receiveBuffer;
};

typedef boost::shared_ptr<Connection> ptrConnection;

#endif // CONNECTION_H_
