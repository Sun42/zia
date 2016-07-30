/// \file

#ifndef FILTER_PYTHON_H_
#define FILTER_PYTHON_H_

#include <iostream>
#include <boost/process/pistream.hpp>

#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"

class	filterPython : public zia::filter::IBodyProcessing
{
 public:
  filterPython(zia::IConfiguration* conf = 0);
  ~filterPython(void);

  virtual inline std::size_t	getObjectSize(void) const;
  virtual inline void		constructObject(void* storage) const;
  virtual inline int		getPriority(void) const;

  void				setConfigurator(zia::IConfiguration* conf);

  virtual zia::filter::Status	processBody(const zia::network::IConnection& con,
					    zia::http::IRequestHeader& rh,
					    zia::http::IResponseHeader& rr,
					    std::istream& isRequestBody,
					    std::ostream& osResponseBody);

  virtual zia::filter::Status	processBodyEnding(const zia::network::IConnection& con,
						  zia::http::IRequestHeader& rh,
						  zia::http::IResponseHeader& rr,
						  std::ostream& osResponseBody);
 private:
  void			configureFilter(void);
  bool			parsePython(const std::string& filename,
				    std::ostream& osResponseBody,
				    zia::IDictionnary& responseHeader,
				    bool methodHead);
  void			fillHeader(zia::IDictionnary& responseHeader,
				   std::size_t contentSize);
  std::size_t		fillBody(std::ostream& osResponseBody,
				 boost::process::pistream& is,
				 bool methodHead);

  std::string		_pythonPath;
  zia::IConfiguration*	_configuration;
};

#endif // FILTER_PERL_H_
