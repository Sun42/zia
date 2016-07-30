/// \file

#ifndef FILTER_FILE_EXIST_H_
#define FILTER_FILE_EXIST_H_

#include "zia_api/IConfiguration.h"
#include "zia_api/filter/IBodyProcessing.h"

class	filterFileExist : public zia::filter::IBodyProcessing
{
 public:
  filterFileExist(zia::IConfiguration* conf = 0);
  ~filterFileExist(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

  void				setConfigurator(zia::IConfiguration* conf);

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
  void				fillResponse(std::ostream& osResponseBody,
					     zia::IDictionnary& headerResponse,
					     bool methodHead);

  zia::IConfiguration*		_configuration;
};

#endif // FILTER_FILE_EXIST_H_
