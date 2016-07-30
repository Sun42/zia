/// \file

#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#include <sstream>

#include "RequestHeader.h"

/*! \class HttpRequest
 * \brief Classe permettant la creation et reception de requete HTTP.
 *
 * HTTP request contient un header (RequestHeader) ainsi qu'un body stocke dans un ostringstream.
 */

class	HttpRequest
{
 public:
  HttpRequest(void);
  ~HttpRequest(void);
  HttpRequest(const HttpRequest&);
  HttpRequest&	operator=(const HttpRequest&);

  void			clear(void);
  void			setHeaderMethod(const std::string&);
  void			setHeaderRequestUri(const std::string&);
  void			setHeaderVMinor(const std::string&);
  void			setHeaderVMajor(const std::string&);
  void			insertMessageHeader(const std::string&);

  RequestHeader&	getHeader(void);
  const std::ostream&	getBody(void) const;
  void			appendBodyData(const char* data);

 private:
  RequestHeader		_header;
  std::ostringstream	_body;
};

#endif
