/// \file

#include "pluginCore.h"

const std::string	pluginName = "ZiaCore";
const unsigned int	currentVersion = 2;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginCore()));
  }
}

pluginCore::pluginCore(void)
{
  this->_fileExistFilter = new filterFileExist();
  this->_filters.push_back(this->_fileExistFilter);

  this->_checkMethodFilter = new filterCheckMethod();
  this->_filters.push_back(this->_checkMethodFilter);

  this->_genericTypeFilter = new filterGenericType();
  this->_filters.push_back(this->_genericTypeFilter);

  this->_accessRightsFilter = new filterAccessRights();
  this->_filters.push_back(this->_accessRightsFilter);
}

pluginCore::~pluginCore(void)
{
  const int	size = this->_filters.size();
  for (int i = 0; i < size; ++i)
    {
      delete this->_filters[i];
    }
}

inline unsigned int		pluginCore::getVersion(void) const
{
  return (currentVersion);
}

inline const std::string&	pluginCore::getName(void) const
{
  return (pluginName);
}

inline const std::vector<const zia::filter::IFilter*>& pluginCore::getFilters() const
{
  return (this->_filters);
}

void	pluginCore::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginCore::setConfigurator(zia::IConfiguration* configurator)
{
  this->_fileExistFilter->setConfigurator(configurator);
  this->_checkMethodFilter->setConfigurator(configurator);
  this->_genericTypeFilter->setConfigurator(configurator);
  this->_accessRightsFilter->setConfigurator(configurator);
}
