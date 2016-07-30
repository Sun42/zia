#ifndef PLUGINALLOW_H_
# define PLUGINALLOW_H_

#include "zia_api/IPlugin.h"

#include "filterAllow.h"

class	pluginAllow : public zia::IPlugin
{
 public:
  pluginAllow();
  ~pluginAllow();

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void							setConfigurator(zia::IConfiguration* configurator);

 private:
  std::vector<const zia::filter::IFilter*>	_filters;
  filterAllow*					_filter;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&	getInstance();
}
#endif

#endif // PLUGINALLOW_H_
