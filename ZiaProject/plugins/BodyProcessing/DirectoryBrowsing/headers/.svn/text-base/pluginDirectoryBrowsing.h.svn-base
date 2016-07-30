#ifndef PLUGINDIRECTORYBROWSING_H_
# define PLUGINDIRECTORYBROWSING_H_

#include "zia_api/IPlugin.h"

#include "filterDirectoryBrowsing.h"

class	pluginDirectoryBrowsing : public zia::IPlugin
{
 public:
  pluginDirectoryBrowsing();
  ~pluginDirectoryBrowsing();

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void							setConfigurator(zia::IConfiguration* configurator);

 private:
  std::vector<const zia::filter::IFilter*>	_filters;
  filterDirectoryBrowsing*			_filter;

  zia::ILogger*					_logger;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&	getInstance();
}
#endif

#endif // PLUGINDIRECTORYBROWSING_H_
