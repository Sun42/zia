/// \file

#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "ParserLoader.h"

/*! \class NetworkThread
 * \brief Connexion multithreadee
 *
 * Permet la connexion via le port d'administration du serveur,
 * la reception ainsi que l'emission de paquets de donnees.
 */
class	NetworkThread : public QObject
{
	Q_OBJECT

public:
	NetworkThread(const std::string& ip, unsigned short port);
	~NetworkThread(void);

	void			run(void);
	void			runIos(void);
	void			login(const QString& login, const QString& password);
	void			getPluginList(void);
	void			send(const Packet&);
	void			send(unsigned char packetId, const std::string& message = "");
	void			start(void);
	void			loadPlugin(const QString&);
	void			readLoop(void);
	void			handleConnect(const boost::system::error_code& err);
	void			handleWrite(const boost::system::error_code& err, size_t, std::vector<unsigned char>* bufferSent);
	void			handleRead(const boost::system::error_code& err, size_t nb_read);
	ParserLoader&	getParser(void);

signals:
	void    sendToStatusBar(const QString&);
	void    stateChanged(int);
	void    error(const char* error);

public slots:
	void	stop(void);

private:
	boost::array<unsigned char, 4096>	_rBuffer;
	boost::asio::streambuf				_wBuffer;
	boost::asio::io_service				_ios;
	boost::asio::ip::tcp::resolver		_resolver;
	boost::asio::ip::tcp::socket		_socket;
	boost::asio::ip::tcp::endpoint		_endPoint;
	boost::thread*						_iosRunThread;
	Packet								_packetReceive;
	ParserLoader						_parser;
};

#endif // NETWORKTHREAD_H
