/// \file

#ifndef PLUGIN_TRACE_H_
#define PLUGIN_TRACE_H_

#include "zia_api/IPlugin.h"

class	filterDelete;

class	pluginDelete : public zia::IPlugin
{
 public:
  pluginDelete(void);
  ~pluginDelete(void);

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void							setConfigurator(zia::IConfiguration* configurator);

 private:
  filterDelete*					_filterDelete;
  std::vector<const zia::filter::IFilter*>	_filters;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&	getInstance();
}
#endif

#endif // PLUGIN_TRACE_H_
