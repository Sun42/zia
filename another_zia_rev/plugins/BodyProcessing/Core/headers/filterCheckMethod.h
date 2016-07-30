/// \file

#ifndef FILTER_CHECK_METHOD_H_
#define FILTER_CHECK_METHOD_H_

#include <iostream>

#include "zia_api/ILogger.h"
#include "zia_api/filter/IBodyProcessing.h"


class	filterCheckMethod : public zia::filter::IBodyProcessing
{
 public:
  filterCheckMethod(zia::ILogger* logger = 0);
  ~filterCheckMethod(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

  void				setLogger(zia::ILogger* logger);

  virtual zia::filter::Status	processBody(const zia::network::IConnection& con,
					    zia::http::IRequestHeader& rh,
					    zia::http::IResponseHeader& rr,
					    std::istream& isRequestBody,
					    std::ostream& osResponseBody
					    );

  virtual zia::filter::Status	processBodyEnding(const zia::network::IConnection& con,
						  zia::http::IRequestHeader& rh,
						  zia::http::IResponseHeader& rr,
						  std::ostream& osResponseBody);
 private:
  bool		isImplementedMethod(const std::string& method) const;
  bool		isValidMethod(const std::string& method) const;

  zia::ILogger*	_logger;
};

#endif // FILTER_CHECK_METHOD_H_
