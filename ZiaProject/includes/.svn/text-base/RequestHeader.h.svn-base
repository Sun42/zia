/// \file

#ifndef REQUEST_HEADER_H_
#define REQUEST_HEADER_H_

#include "zia_api/http/IRequestHeader.h"

#include "Dictionnary.h"

/*! \class RequestHeader
 * \brief Implementation de IRequestHeader.
 *
 * Cette classe est contenue par HTTPRequest.
 */


class	RequestHeader : public zia::http::IRequestHeader
{
 public:
  RequestHeader(void);
  ~RequestHeader(void);

  void				clear(void);
  void				setMethod(const std::string&);
  const std::string&		getMethod(void) const;
  void				setPath(const std::string&);
  const std::string&		getPath(void) const;
  void				setVMajor(unsigned);
  unsigned int			getVMajor(void) const;
  void				setVMinor(unsigned);
  unsigned int			getVMinor(void) const;

  const zia::IDictionnary&	entities(void) const;
  zia::IDictionnary&		entities(void);

 private:
  std::string		_method;
  std::string		_path;
  unsigned int		_majorVersion;
  unsigned int		_minorVersion;
  Dictionnary		_dictionnary;
};

#endif
