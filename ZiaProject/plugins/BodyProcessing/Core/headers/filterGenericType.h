#ifndef FILTERGENERICTYPE_H_
# define FILTERGENERICTYPE_H_

#include <iostream>
#include <boost/filesystem/path.hpp>

#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"


class	filterGenericType : public zia::filter::IBodyProcessing
{
 public:
  filterGenericType(zia::IConfiguration* conf = 0);
  ~filterGenericType(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

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
  void	completeResponse(zia::http::IRequestHeader& rh,
			 zia::http::IResponseHeader& rr,
			 std::ostream& osResponseBody,
			 const std::string& path);
  void	fillMimeType(zia::http::IResponseHeader& rr,
		     const std::string &path);

  zia::IConfiguration*	_configuration;
};

#endif // FILTERGENERICTYPE_H_
