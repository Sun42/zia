/// \file

#include "pluginPython.h"
#include "filterPython.h"

const std::string	pluginName = "Python-plugin";
const unsigned int	currentVersion = 0;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginPython()));
  }
}

pluginPython::pluginPython(void)
{
  this->_pythonFilter = new filterPython();
  this->_filters.push_back(this->_pythonFilter);
}

pluginPython::~pluginPython(void)
{
  delete this->_pythonFilter;
}

unsigned int		pluginPython::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginPython::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginPython::getFilters() const
{
  return (this->_filters);
}

void	pluginPython::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginPython::setConfigurator(zia::IConfiguration* configurator)
{
  this->_pythonFilter->setConfigurator(configurator);
}
