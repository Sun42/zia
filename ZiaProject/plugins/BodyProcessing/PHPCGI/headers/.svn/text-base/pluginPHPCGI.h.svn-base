/// \file

#ifndef PLUGIN_PHPCGI_H_
#define PLUGIN_PHPCGI_H_

#include "zia_api/IPlugin.h"
#include "zia_api/IConfiguration.h"

class	filterPHPCGI;

class	pluginPHPCGI : public zia::IPlugin
{
 public:
  pluginPHPCGI(void);
  virtual ~pluginPHPCGI(void);

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void	setConfigurator(zia::IConfiguration* configurator);

 private:
  filterPHPCGI*					_phpFilter;
  std::vector<const zia::filter::IFilter*>	_filters;

  zia::ILogger*					_logger;
  zia::IConfiguration*				_configurator;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&getInstance();
}
#endif

#endif // PLUGIN_PHPCGI_H_
