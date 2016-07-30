/// \file

#ifndef FILTER_CHECK_METHOD_H_
#define FILTER_CHECK_METHOD_H_

#include <iostream>
#include "zia_api/filter/IBodyProcessing.h"
#include "zia_api/IConfiguration.h"

class	filterCheckMethod : public zia::filter::IBodyProcessing
{
 public:
  filterCheckMethod(void);
  virtual ~filterCheckMethod(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;
  virtual void			setConfigurator(zia::IConfiguration* conf);

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
};

#endif // FILTER_CHECK_METHOD_H_
