/// \file

#ifndef FILTER_ACCESS_RIGHTS_H_
#define FILTER_ACCESS_RIGHTS_H_

#include "zia_api/ILogger.h"
#include "zia_api/IDictionnary.h"
#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"

class filterAccessRights : public zia::filter::IBodyProcessing
{
 public:
  filterAccessRights(zia::IConfiguration* conf = 0, zia::ILogger* logger = 0);
  ~filterAccessRights();

  virtual std::size_t		getObjectSize(void) const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority(void) const;

  void				setLogger(zia::ILogger* logger);
  void				setConfigurator(zia::IConfiguration* configurator);

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
  void				fillResponse(std::ostream& osResponseBody,
					     zia::IDictionnary& headerResponse,
					     bool methodHead) const;
  zia::ILogger*			_logger;
  zia::IConfiguration*		_configuration;
};

#endif // FILTER_ACCESS_RIGHTS_H_
