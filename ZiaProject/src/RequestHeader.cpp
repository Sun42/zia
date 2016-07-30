/// \file
#include <iostream>

#include "RequestHeader.h"
#include <iostream>

RequestHeader::RequestHeader(void)
  : _majorVersion(0), _minorVersion(0)
{
}

RequestHeader::~RequestHeader(void)
{
}

void	RequestHeader::clear(void)
{
  this->_method.clear();
  this->_path.clear();
  this->_majorVersion = 0;
  this->_minorVersion = 0;
  this->_dictionnary.clear();
}

void	RequestHeader::setMethod(const std::string& method)
{
  this->_method = method;
}

const std::string&	RequestHeader::getMethod(void) const
{
  return (this->_method);
}

void	RequestHeader::setPath(const std::string& path)
{
  this->_path = path;
}

const std::string&	RequestHeader::getPath(void) const
{
  return (this->_path);
}

void	RequestHeader::setVMajor(unsigned int majorVersion)
{
  this->_majorVersion = majorVersion;
}

unsigned int	RequestHeader::getVMajor(void) const
{
  return (this->_majorVersion);
}

void	RequestHeader::setVMinor(unsigned int minorVersion)
{
  this->_minorVersion = minorVersion;
}

unsigned int	RequestHeader::getVMinor(void) const
{
  return (this->_minorVersion);
}

const zia::IDictionnary&	RequestHeader::entities(void) const
{
  return (this->_dictionnary);
}

zia::IDictionnary&	RequestHeader::entities(void)
{
  return (this->_dictionnary);
}
