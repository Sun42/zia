#ifndef FILTERTRACE_H_
# define FILTERTRACE_H_

#include "zia_api/ILogger.h"
#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"


class	filterDelete : public zia::filter::IBodyProcessing
{
 public:
  filterDelete(zia::IConfiguration* conf = 0, zia::ILogger* log = 0);
  ~filterDelete(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

  void				setConfigurator(zia::IConfiguration* conf);
  void				setLogger(zia::ILogger* logger);

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
  bool				deleteURI(std::string const &) const;
  void				fillHeaderResponse(const zia::http::IRequestHeader&, zia::http::IResponseHeader&, unsigned int, std::string const &) const;
  void				fillResponse(const zia::http::IRequestHeader& rh, zia::http::IResponseHeader& rr) const;

  zia::ILogger*			_logger;
  zia::IConfiguration*		_configuration;
};

#endif // FILTERTRACE_H_
