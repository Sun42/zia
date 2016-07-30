/// \file

#include <sstream>

#include "ResponseHeader.h"

ResponseHeader::ResponseHeader(void)
  : _major(0), _minor(0), _code(0), _sent(false)
{
}

ResponseHeader::~ResponseHeader(void)
{
}

// HTTP/major.minor code message\r\n
std::string	ResponseHeader::getFullHeader(void) const
{
  std::ostringstream	os("HTTP/");

  os << "HTTP/" << this->_major << '.' << this->_minor << " " << this->_code << ' ' << this->_message << "\r\n";
  os << "Server: ZiaMaster \r\n";
  std::map<std::string, std::string> dic = this->entities().getContent();
  std::map<std::string, std::string>::const_iterator		it = dic.begin();
  std::map<std::string, std::string>::const_iterator		ite = dic.end();
  for (;it != ite ;++it)
    os << it->first << ": " << it->second << "\r\n";
  return (os.str());
}

unsigned int	ResponseHeader::getVMajor(void) const
{
  return (this->_major);
}

void	ResponseHeader::setVMajor(unsigned int major)
{
  this->_major = major;
}

unsigned int	ResponseHeader::getVMinor(void) const
{
  return (this->_minor);
}

void	ResponseHeader::setVMinor(unsigned int minor)
{
  this->_minor = minor;
}

void	ResponseHeader::setCode(unsigned int code)
{
  this->_code = code;
}

unsigned int	ResponseHeader::getCode(void) const
{
  return (this->_code);
}

void	ResponseHeader::setMsg(const std::string& message)
{
  this->_message = message;
}

const std::string&	ResponseHeader::getMsg(void) const
{
  return (this->_message);
}

void	ResponseHeader::readyToSend(void)
{
  this->_sent = true;
}

bool	ResponseHeader::sent(void) const
{
  return (this->_sent);
}

const zia::IDictionnary&	ResponseHeader::entities(void) const
{
  return (this->_dictionnary);
}

zia::IDictionnary&	ResponseHeader::entities(void)
{
  return (this->_dictionnary);
}
