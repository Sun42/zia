/// \file

#include "HttpRequest.h"

HttpRequest::HttpRequest(void)
{
}

HttpRequest::~HttpRequest(void)
{
}

HttpRequest::HttpRequest(const HttpRequest& copy)
{
  this->_header = copy._header;
  this->_body << copy._body;
}

HttpRequest&	HttpRequest::operator=(const HttpRequest& copy)
{
  this->_header = copy._header;
  this->_body << copy._body;
  return (*this);
}

void	HttpRequest::clear(void)
{
  this->_header.clear();
  this->_body.clear();
}

void	HttpRequest::setHeaderMethod(const std::string& method)
{
  this->_header.setMethod(method);
}

void	HttpRequest::setHeaderRequestUri(const std::string& uri)
{
  this->_header.setPath(uri);
}

void	HttpRequest::setHeaderVMinor(const std::string& minor)
{
  this->_header.setVMinor(stringToType<unsigned int>(minor));
}

void	HttpRequest::setHeaderVMajor(const std::string& major)
{
  this->_header.setVMajor(stringToType<unsigned int>(major));
}

// A verifier.
void	HttpRequest::insertMessageHeader(const std::string& messageHeader)
{
  Dictionnary&	dictionnary = static_cast<Dictionnary&>(this->_header.entities());
  const size_t	sep = messageHeader.find(':');

  dictionnary.set(messageHeader.substr(0, sep), messageHeader.substr(sep +1));
}

RequestHeader&	HttpRequest::getHeader(void)
{
  return (this->_header);
}

const std::ostream&	HttpRequest::getBody(void) const
{
  return (this->_body);
}

void	HttpRequest::appendBodyData(const char* data)
{
  this->_body << data;
}

template<typename T>
T	HttpRequest::stringToType(const std::string& input)
{
  T			output;
  std::istringstream	iss(input);

  iss >> output;
  return (output);
}
