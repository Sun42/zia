/// \file

#include "Logger.h"

Logger::Logger(std::string const & LoggerPath):
  _file(LoggerPath.c_str(), std::ios_base::app)
{
}

Logger::~Logger()
{
  if (true == this->_file.is_open())
    this->_file.close();
}

// rajouter la date
void    Logger::log(zia::log::Priority prio, const std::string& msg)
{
  this->_mutexLogger.lock();
  if (this->_file.is_open())
    this->_file << "Log Priority : " << prio << "\tMessage : " << msg << std::endl;
  this->_mutexLogger.unlock();
}

zia::ILogger::Message	Logger::log(zia::log::Priority p)
{
  return (Message(*this, p));
}
