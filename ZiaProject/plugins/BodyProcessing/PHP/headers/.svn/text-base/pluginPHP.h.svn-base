/// \file

#ifndef PLUGIN_PHP_H_
#define PLUGIN_PHP_H_

#include "zia_api/IPlugin.h"
#include "zia_api/IConfiguration.h"

class	filterPHP;

class	pluginPHP : public zia::IPlugin
{
 public:
  pluginPHP(void);
  virtual ~pluginPHP(void);

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void	setConfigurator(zia::IConfiguration* configurator);

 private:
  filterPHP*					_phpFilter;
  std::vector<const zia::filter::IFilter*>	_filters;
  zia::ILogger*					_logger;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&getInstance();
}
#endif

#endif // PLUGIN_PHP_H_
