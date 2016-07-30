#ifndef FILTERGZIP_H_
# define FILTERGZIP_H_

#include <iostream>

#include "zia_api/filter/IBodyEncoder.h"
#include "zia_api/IConfiguration.h"

class	filterGzip : public zia::filter::IBodyEncoder
{
 public:
  filterGzip(zia::IConfiguration* conf = 0);
  ~filterGzip(void);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

  void				setConfigurator(zia::IConfiguration*);
  void				configureFilter(void);

  virtual zia::filter::Status	bodyEncode(
					  const zia::network::IConnection& con,
					  const zia::http::IRequestHeader& rh,
					  const zia::http::IResponseHeader& rr,
					  std::istream& isPlainBody,
					  std::ostream& osEncodeBody
				   );

  virtual zia::filter::Status	bodyEncodeEnding(
					 const zia::network::IConnection& con,					 const zia::http::IRequestHeader& rh,
					 const zia::http::IResponseHeader& rr,
					 std::ostream& osEncodeBody
					 );

 private:
  zia::IConfiguration*		_configuration;
  std::string			_gzipPath;
  unsigned int			_sizeLimit;
};

#endif // FILTERGZIP_H_
