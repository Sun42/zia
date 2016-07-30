/// \file

#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include <sstream>
#include "ResponseHeader.h"

/*! \class HttpRequest
 * \brief Classe permettant la creation et revoie de requete HTTP.
 *
 * HTTP response contient un header (ResponseHeader) ainsi qu'un body stocke dans un ostringstream.
 */
class	HttpResponse
{
 public:
  HttpResponse(void);
  ~HttpResponse(void);
  HttpResponse(const HttpResponse&);
  HttpResponse&	operator=(const HttpResponse&);

  ResponseHeader&	getHeader(void);
  const ResponseHeader&	getConstHeader(void) const;
  std::stringstream&		getBody(void);
  const std::ostream&	getConstBody(void) const;

 private:
  ResponseHeader	_header;
  std::stringstream	_body;
};

std::ostream&	operator<<(std::ostream& os, HttpResponse & response);

#endif
