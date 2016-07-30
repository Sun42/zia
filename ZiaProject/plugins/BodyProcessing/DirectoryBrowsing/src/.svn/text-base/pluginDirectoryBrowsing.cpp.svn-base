#include <iostream>

#include "pluginDirectoryBrowsing.h"
#include "filterDirectoryBrowsing.h"

const std::string	pluginName = "pluginDirectoryBrowsing";
const unsigned int	currentVersion = 5;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginDirectoryBrowsing()));
  }
}

pluginDirectoryBrowsing::pluginDirectoryBrowsing(void)
{
  this->_filter = new filterDirectoryBrowsing;
  this->_filters.push_back(this->_filter);
}

pluginDirectoryBrowsing::~pluginDirectoryBrowsing(void)
{
  delete this->_filter;
}

unsigned int		pluginDirectoryBrowsing::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginDirectoryBrowsing::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginDirectoryBrowsing::getFilters() const
{
  return (this->_filters);
}

void	pluginDirectoryBrowsing::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginDirectoryBrowsing::setConfigurator(zia::IConfiguration* conf)
{
  this->_filter->setConfigurator(conf);
}
