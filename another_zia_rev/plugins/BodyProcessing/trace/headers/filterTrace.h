/// \file

#ifndef FILTER_TRACE_H_
#define FILTER_TRACE_H_

#include "zia_api/filter/IBodyProcessing.h"
#include "zia_api/IConfiguration.h"

class	filterTrace : public zia::filter::IBodyProcessing
{
 public:
  filterTrace(zia::IConfiguration* conf = 0);
  ~filterTrace(void);

  virtual std::size_t		getObjectSize(void) const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority(void) const;

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
  void		fillHeaderResponse(const zia::http::IRequestHeader&, zia::http::IResponseHeader&, std::size_t) const;
  std::size_t	fillBodyResponse(const zia::http::IRequestHeader&, std::istream&, std::ostream&) const;
  std::size_t	fillBodyResponse(const zia::http::IRequestHeader& rh, std::ostream& osResponseBody) const;

  void		fillResponse(const zia::http::IRequestHeader&, zia::http::IResponseHeader&, std::istream&, std::ostream&, struct zia::filter::Status &) const;
  void		fillResponse(const zia::http::IRequestHeader& rh,  zia::http::IResponseHeader& rr, std::ostream& osResponseBody) const;

 private:
  zia::IConfiguration*		_configuration;
};

#endif // FILTER_TRACE_H_
