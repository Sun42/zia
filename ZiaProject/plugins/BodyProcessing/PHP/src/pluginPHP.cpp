/// \file

#include "pluginPHP.h"
#include "filterPHP.h"

const std::string	pluginName = "PHP-plugin";
const unsigned int	currentVersion = 3;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginPHP()));
  }
}

pluginPHP::pluginPHP(void)
{
  this->_phpFilter = new filterPHP();
  this->_filters.push_back(this->_phpFilter);
}

pluginPHP::~pluginPHP(void)
{
  delete this->_phpFilter;
}

unsigned int		pluginPHP::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginPHP::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginPHP::getFilters() const
{
  return (this->_filters);
}

void	pluginPHP::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginPHP::setConfigurator(zia::IConfiguration* configurator)
{
  this->_phpFilter->setConfigurator(configurator);
}
