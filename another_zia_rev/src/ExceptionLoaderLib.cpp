/// \file

#include "ExceptionLoaderLib.h"

ExceptionLoaderLib::ExceptionLoaderLib(const char *message)  throw()
  : _message(message)
{
}

ExceptionLoaderLib::~ExceptionLoaderLib() throw()
{
}

char const *	ExceptionLoaderLib::what() const throw()
{
  return (this->_message);
}
