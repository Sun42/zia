/// \file

#ifndef FILTER_PHPCGI_H_
#define FILTER_PHPCGI_H_

#include <vector>
#include <iostream>
#include <string>
#include <boost/process/pistream.hpp>

#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"
#include "zia_api/http/IRequestHeader.h"
#include "zia_api/http/IResponseHeader.h"
#include "zia_api/IDictionnary.h"
#include "zia_api/network/IConnection.h"

#include "pluginPHPCGI.h"

class	filterPHPCGI : public zia::filter::IBodyProcessing
{
 public:
  filterPHPCGI(zia::IConfiguration* conf = 0);
  ~filterPHPCGI(void);

  void				setConfigurator(zia::IConfiguration*);
  void				configureFilter(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;


  bool				takeOverRequest(std::string& result, std::string uri, const std::string& rootDir);
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
/*   bool				parsePHP(const std::string& filename, */
/* 					 std::ostream& osResponseBody); */
  bool				isValidPath(std::string& result, std::string uri,
					    const std::string& rootFile) const;

  bool				parsePHPCGI(const zia::network::IConnection& con,
					    zia::http::IRequestHeader& rh,
					    zia::http::IResponseHeader& rr,
					    std::istream& isRequestBody,
					    std::ostream& osResponseBody,
					    const std::string& filename,
					    const zia::IDictionnary& ziaConf
					    );

  void				fillBody(const zia::network::IConnection& con,
					 zia::http::IRequestHeader& rh,
					 zia::http::IResponseHeader& rr,
					 std::istream& isRequestBody,
					 std::ostream& osResponseBody,
					 boost::process::pistream& is);

  

  std::string			_phpPath;
  std::vector<std::string>	_rootFiles;
  zia::IConfiguration*		_configuration;
};

#endif // FILTER_PHPCGI_H_
