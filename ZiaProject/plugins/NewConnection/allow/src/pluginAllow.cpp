#include "pluginAllow.h"
#include "filterAllow.h"

const std::string	pluginName = "pluginAllow";
const unsigned int	currentVersion = 1;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginAllow()));
  }
}

pluginAllow::pluginAllow(void)
{
  this->_filter = new filterAllow;
  this->_filters.push_back(this->_filter);
}

pluginAllow::~pluginAllow(void)
{
  delete this->_filter;
}

unsigned int		pluginAllow::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginAllow::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginAllow::getFilters() const
{
  return (this->_filters);
}

void	pluginAllow::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginAllow::setConfigurator(zia::IConfiguration* configurator)
{
  this->_filter->setConfigurator(configurator);
}
