/// \file

#include "pluginPHPCGI.h"
#include "filterPHPCGI.h"

const std::string	pluginName = "PHPCGI-plugin";
const unsigned int	currentVersion = 0;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginPHPCGI()));
  }
}

pluginPHPCGI::pluginPHPCGI(void)
{
  this->_phpFilter = new filterPHPCGI();
  this->_filters.push_back(this->_phpFilter);
}

pluginPHPCGI::~pluginPHPCGI(void)
{
  delete this->_phpFilter;
}

unsigned int		pluginPHPCGI::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginPHPCGI::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginPHPCGI::getFilters() const
{
  return (this->_filters);
}

void	pluginPHPCGI::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginPHPCGI::setConfigurator(zia::IConfiguration* configurator)
{
  this->_configurator = configurator;
  this->_phpFilter->setConfigurator(configurator);
}
