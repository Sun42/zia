/// \file

#ifndef LOGGER_H_
# define LOGGER_H_

#include "zia_api/ILogger.h"

class	Logger : public zia::ILogger
{
 public:
  Logger();
  ~Logger();

  virtual void			log(zia::log::Priority p, const std::string& msg);
  virtual zia::ILogger::Message	log(zia::log::Priority p);

 private:
  Logger(Logger const &);
  Logger&	operator=(Logger const &);
};

#endif
