/// \file

#ifndef RESPONSE_HEADER_H_
#define RESPONSE_HEADER_H_

#include <string>
#include "Dictionnary.h"
#include "zia_api/http/IResponseHeader.h"

/*! \class ResponseHeader
 * \brief Implementation de IResponseHeader.
 *
 * Cette classe est contenue par ResponseHTTP.
 */

class	ResponseHeader : public zia::http::IResponseHeader
{
 public:
  ResponseHeader(void);
  ~ResponseHeader(void);

  std::string			getFullHeader(void) const;

  unsigned int			getVMajor(void) const;
  void				setVMajor(unsigned int major);
  unsigned int			getVMinor(void) const;
  void				setVMinor(unsigned int minor);

  void				setCode(unsigned int code);
  unsigned int			getCode(void) const;
  void				setMsg(const std::string& msg);
  const std::string&		getMsg(void) const;

  void				readyToSend(void);
  bool				sent(void) const;

  const zia::IDictionnary&	entities(void) const;
  zia::IDictionnary&		entities(void);

 private:
  unsigned int			_major;
  unsigned int			_minor;
  unsigned int			_code;
  std::string			_message;
  bool				_sent;
  Dictionnary			_dictionnary;
};

#endif
