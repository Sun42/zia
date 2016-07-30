/// \file

#include "HttpResponse.h"

HttpResponse::HttpResponse(void)
{
}

HttpResponse::~HttpResponse(void)
{
}

HttpResponse::HttpResponse(const HttpResponse& copy)
{
  this->_header = copy._header;
  this->_body << copy._body;
}

HttpResponse&	HttpResponse::operator=(const HttpResponse& copy)
{
  this->_header = copy._header;
  this->_body << copy._body;
  return (*this);
}

ResponseHeader&	HttpResponse::getHeader(void)
{
  return (this->_header);
}

const ResponseHeader&	HttpResponse::getConstHeader(void) const
{
  return (this->_header);
}

std::stringstream&	HttpResponse::getBody(void)
{
  return (this->_body);
}

const std::ostream&	HttpResponse::getConstBody(void) const
{
  return (this->_body);
}

std::ostream&	operator<<(std::ostream& os, HttpResponse & response)
{
  return (os << "HTTP RESPONSE Sended:\n" << response.getHeader().getFullHeader() << "\r\n" << response.getBody().str());
}
