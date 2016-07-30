/// \file

#ifndef LOGGER_H_
# define LOGGER_H_

#include <fstream>

#define WIN32_LEAN_AND_MEAN
#include <boost/thread.hpp>

#include "zia_api/ILogger.h"

class	Logger : public zia::ILogger
{
 public:
  Logger(std::string const & LoggerPath);
  ~Logger();

  virtual void			log(zia::log::Priority p, const std::string& msg);
  virtual zia::ILogger::Message	log(zia::log::Priority p);

 private:
  Logger(Logger const &);
  Logger&	operator=(Logger const &);

private:
  boost::mutex			_mutexLogger;
  std::ofstream			_file;
};

#endif
