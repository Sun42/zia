/// \file

#ifndef FILTER_PHP_H_
#define FILTER_PHP_H_

#include <vector>
#include <iostream>
#include <boost/process/pistream.hpp>

#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"

#include "pluginPHP.h"

class	filterPHP : public zia::filter::IBodyProcessing
{
 public:
  filterPHP(zia::IConfiguration* conf = 0);
  ~filterPHP(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

  void				setConfigurator(zia::IConfiguration*);

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
  bool				parsePHP(const std::string& filename,
					 std::ostream& osResponseBody,
					 zia::IDictionnary& responseHeader,
					 bool methodHead);
  std::size_t			fillBody(std::ostream& osResponseBody,
					 boost::process::pistream& is,
					 bool methodHead);
  void				fillHeader(zia::IDictionnary& responseHeader,
					   std::size_t contentSize);
  void				configureFilter(void);
  bool				takeOverRequest(std::string& result, const std::string& uri);
  bool				isValidPath(std::string& result, std::string uri,
					    const std::string& rootDir) const;

  std::string			_phpPath;
  std::vector<std::string>	_rootFiles;
  zia::IConfiguration*		_configuration;
};

#endif // FILTER_PHP_H_
