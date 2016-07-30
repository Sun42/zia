#ifndef PLUGINTRACE_H_
#define PLUGINTRACE_H_

#include "zia_api/IPlugin.h"

#include "filterTrace.h"

class	pluginTrace : public zia::IPlugin
{
 public:
  pluginTrace(void);
  ~pluginTrace(void);

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void							setConfigurator(zia::IConfiguration* configurator);

 private:
  std::vector<const zia::filter::IFilter*>	_filters;
  filterTrace*					_filter;

  zia::ILogger*					_logger;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&	getInstance();
}
#endif

#endif // PLUGINTRACE_H_
