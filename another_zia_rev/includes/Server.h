/// \file

#ifndef SERVER_H_
#define SERVER_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "zia_api/network/IEndPoint.h"

#include "ConnectionHttp.h"
#include "ConnectionPlugin.h"

/*! \class Server
 * \brief Gestion du serveur dans sa globalite...
 *
 * Permet de lancer, fermer le serveur.
 */
class	Server
{
public:
  static Server*	getInstance(const Dictionnary& ziaConf, unsigned short portSSL, unsigned short portHttp, unsigned short portAdmin);
  static Server*	getInstance();
  static void		destroyInstance();

  const Dictionnary&	getDefaultConf() const;
  std::string		getPathLog() const;

  void			loadStartingPlugins(const zia::IDictionnary &);
  void			run();
  void			stop();
  void			removeConnexion(ptrHttpConnection);
  void			removeConnexion(ptrPluginConnection);

 private:
  Server(const Dictionnary& ziaConf, unsigned short portSSL, unsigned short portHttp, unsigned short portAdmin);
  ~Server();
  Server(Server const &);

  Server&	operator=(Server const &);

  /*! \fn
   * \brief Accepte les connexions sur le port d'ecoute Http
   * \param
   * \return void
   */
  void		acceptHttp();
  void		handleAcceptHttp(ptrHttpConnection, const boost::system::error_code&);
  void		acceptPlugin();
  void		handleAcceptPlugin(ptrPluginConnection, const boost::system::error_code&);
  void		handleStop();

 private:
  static Server*			_instance;

  boost::asio::io_service		_ioService;

  boost::asio::ip::tcp::acceptor	_acceptorHttp;
  boost::asio::ip::tcp::acceptor	_acceptorSSL;
  boost::asio::ip::tcp::acceptor	_acceptorPlugin;

  boost::mutex				_mutexConnectionsHttp;
  std::list<ptrHttpConnection>		_connectionsHttp;
  boost::mutex				_mutexConnectionsPlugin;
  std::list<ptrPluginConnection>	_connectionsPlugin;

  const Dictionnary&			_defaultConf;
  zia::network::IEndPoint*		_serverEndpoint;
};

#endif // SERVER_H_
