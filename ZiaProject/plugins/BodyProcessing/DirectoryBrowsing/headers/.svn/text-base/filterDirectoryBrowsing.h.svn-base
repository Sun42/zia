#ifndef FILTERDIRECTORYBROWSING_H_
#define FILTERDIRECTORYBROWSING_H_

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "zia_api/filter/IBodyProcessing.h"
#include "zia_api/IConfiguration.h"

class filterDirectoryBrowsing : public zia::filter::IBodyProcessing
{
 public:
  filterDirectoryBrowsing(zia::IConfiguration* conf = 0);
  ~filterDirectoryBrowsing();

  void				setConfigurator(zia::IConfiguration* conf);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

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
  void				uriCat(std::string& result, const std::string& rootDir, std::string uri) const;
  std::string			getDayTimeToString() const;

  size_t			fillListFiles(boost::filesystem::path const & path, std::string const &, std::ostream& osResponseBody, bool) const;
  void				fillHeaderResponse(const zia::http::IRequestHeader& rh, zia::http::IResponseHeader& rr, size_t) const;
  size_t			fillBodyResponse(const zia::network::IConnection&, boost::filesystem::path const &, std::string const &, std::ostream&, std::string const &, bool) const;
  void				fillResponse(const zia::network::IConnection&, const zia::http::IRequestHeader&, zia::http::IResponseHeader&, std::ostream&) const;

 private:
  zia::IConfiguration*		_configuration;
};

#endif // FILTERDIRECTORYBROWSING_H_
