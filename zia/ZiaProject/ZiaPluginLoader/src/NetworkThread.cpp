#include <iostream>
#include <boost/thread.hpp>
#include "ZiaPluginLoader.h"
#include "NetworkThread.h"

NetworkThread::NetworkThread(const std::string& ip, unsigned short port)
	: _ios(),
	_resolver(this->_ios),
	_socket(this->_ios),
	_packetReceive()
{
	QObject::connect(this, SIGNAL(error(const char*)), SLOT(stop()));
	this->_endPoint.address(boost::asio::ip::address::from_string(ip.c_str()));
	this->_endPoint.port(port);
}

NetworkThread::~NetworkThread(void)
{
}

void	NetworkThread::loadPlugin(const QString& path)
{
	this->send('L', path.toStdString());
}

void	NetworkThread::runIos(void)
{
	try
	{
		this->_ios.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	NetworkThread::start(void)
{
	this->_socket.async_connect(this->_endPoint,
								boost::bind(&NetworkThread::handleConnect, this,
								boost::asio::placeholders::error));
	boost::thread	threadRunning(boost::bind(&NetworkThread::runIos, this));
}

void	NetworkThread::login(const QString& login, const QString& password)
{
	this->send('A', login.toStdString() + ' ' + password.toStdString());
}

void	NetworkThread::getPluginList(void)
{
	this->send('l', "");
}

void    NetworkThread::handleConnect(const boost::system::error_code& err)
{
	if (!err)
	{
		std::cerr << "handle_connect OK" << std::endl;
		this->readLoop();
		emit stateChanged(ZiaPluginLoader::CONNECTED);
	}
	else
	{
		std::cerr << "handle_connect ERROR" << std::endl;
		emit error(err.message().c_str());
	}
}

void	NetworkThread::readLoop(void)
{
	std::cerr << "readLoop" << std::endl;
	this->_socket.async_read_some(boost::asio::buffer(this->_rBuffer),
								  boost::bind(&NetworkThread::handleRead, this,
											  boost::asio::placeholders::error,
											  boost::asio::placeholders::bytes_transferred));
}

void	NetworkThread::handleRead(const boost::system::error_code& err, size_t nbBytes)
{
  if (!err)
	{
		this->_packetReceive.add(this->_rBuffer, static_cast<unsigned int>(nbBytes));
		if (this->_packetReceive.checkLen())
		{
		std::cout << "exec du packet";
		this->_parser.exec(this->_packetReceive);
		this->_packetReceive.reset();
		}
		this->readLoop();
	}
	else
	{
		std::cerr << "handle_read ERROR" << std::endl;
		emit error(err.message().c_str());
	}
}

ParserLoader&	NetworkThread::getParser(void)
{
	return (this->_parser);
}

void	NetworkThread::send(const Packet& data)
{
	std::vector<unsigned char>    *bufToSend = data.getData();
	boost::asio::async_write(this->_socket, boost::asio::buffer(*bufToSend),
							 boost::bind(&NetworkThread::handleWrite,
										 this,
										 boost::asio::placeholders::error,
										 boost::asio::placeholders::bytes_transferred,
										 bufToSend));
}

void    NetworkThread::send(unsigned char packetId, const std::string& message)
{
	Packet	packet;

	packet << packetId;
	if (message.size() != 0)
		packet << message;
	packet.addHead();
	this->send(packet);
}

void    NetworkThread::handleWrite(const boost::system::error_code& err, size_t, std::vector<unsigned char>* bufferSent)
{
	if (!err)
	{
		delete bufferSent;
	}
	else
	{
		std::cerr << "handle_write ERROR" << std::endl;
		emit error(err.message().c_str());
	}
}

void	NetworkThread::stop(void)
{
	if (true == this->_socket.is_open())
	{
		std::cerr << "Closing socket..." << std::endl;
		this->_socket.close();
	}
}
