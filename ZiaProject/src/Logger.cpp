/// \file

#include <iostream>

#include "Logger.h"

Logger::Logger()
{
}
Logger::~Logger()
{
}

void    Logger::log(zia::log::Priority, const std::string&)
{
  std::cout << "Not implemented" << std::endl;
}

zia::ILogger::Message Logger::log(zia::log::Priority p)
{
  std::cout << "Not implemented" << std::endl;
  Message m(*this, p);
  return (m);
}
