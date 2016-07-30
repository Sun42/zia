/// \file

#ifndef PLUGIN_PYTHON_H_
#define PLUGIN_PYTHON_H_

#include "zia_api/IPlugin.h"
#include "zia_api/IConfiguration.h"

class	filterPython;

class	pluginPython : public zia::IPlugin
{
 public:
  pluginPython(void);
  ~pluginPython(void);

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void	setConfigurator(zia::IConfiguration* configurator);

 private:
  filterPython*					_pythonFilter;
  std::vector<const zia::filter::IFilter*>	_filters;
  zia::ILogger*					_logger;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&getInstance();
}
#endif

#endif // PLUGIN_PYTHON_H_
