/// \file

#ifndef FILTER_PERL_H_
#define FILTER_PERL_H_

//#include "pluginPerl.h"

#include <iostream>

//#include "temp.h"
//#include <boost/process/pistream.hpp>

#include "zia_api/ILogger.h"
#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"

class	filterPerl : public zia::filter::IBodyProcessing
{
 public:
  filterPerl(zia::IConfiguration* conf = 0, zia::ILogger* log = 0);
  ~filterPerl(void);

  virtual inline std::size_t	getObjectSize(void) const;
  virtual inline void		constructObject(void* storage) const;
  virtual inline int		getPriority(void) const;

  void				setLogger(zia::ILogger* logger);
  void				setConfigurator(zia::IConfiguration* conf);
  void				configureFilter(void);

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
  bool			parsePerl(const std::string& filename,
				  std::ostream& osResponseBody,
				  zia::IDictionnary& responseHeader,
				  bool methodHead);
/*  std::size_t		fillBody(std::ostream& osResponseBody,
				 boost::process::pistream& is,
				 bool methodHead);*/
  void			fillHeader(zia::IDictionnary& responseHeader,
				   std::size_t contentSize);

  std::string		_perlPath;
  zia::ILogger*		_logger;
  zia::IConfiguration*	_configuration;
};

#endif // FILTER_PERL_H_
