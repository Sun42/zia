/// \file

#ifndef PLUGIN_PERL_H_
#define PLUGIN_PERL_H_

#include "zia_api/IPlugin.h"
#include "zia_api/IConfiguration.h"

class	filterPerl;

class	pluginPerl : public zia::IPlugin
{
 public:
  pluginPerl(void);
  ~pluginPerl(void);

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void	setConfigurator(zia::IConfiguration* configurator);

 private:
  filterPerl*					_perlFilter;
  std::vector<const zia::filter::IFilter*>	_filters;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&getInstance();
}
#endif

#endif // PLUGIN_PERL_H_
