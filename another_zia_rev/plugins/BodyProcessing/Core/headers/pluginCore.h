/// \file

#ifndef PLUGIN_CORE_H_
#define PLUGIN_CORE_H_

#include "zia_api/IPlugin.h"

#include "filterFileExist.h"
#include "filterCheckMethod.h"
#include "filterGenericType.h"
#include "filterAccessRights.h"

class	pluginCore : public zia::IPlugin
{
 public:
  pluginCore(void);
  ~pluginCore(void);

  virtual unsigned int						getVersion(void) const;
  virtual const std::string&					getName(void) const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters(void) const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void							setConfigurator(zia::IConfiguration* configurator);

 private:
  zia::ILogger*					_logger;

  filterFileExist*				_fileExistFilter;
  filterCheckMethod*				_checkMethodFilter;
  filterGenericType*				_genericTypeFilter;
  filterAccessRights*				_accessRightsFilter;

  std::vector<const zia::filter::IFilter*>	_filters;
};

#ifdef _WIN32
extern "C"
{
  __declspec(dllexport) zia::IPlugin&getInstance();
}
#endif

#endif // PLUGIN_ACCESS_RIGHTS_H_
