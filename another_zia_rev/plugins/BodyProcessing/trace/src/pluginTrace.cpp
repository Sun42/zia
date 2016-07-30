#include "pluginTrace.h"
#include "filterTrace.h"

const std::string	pluginName = "pluginTrace";
const unsigned int	currentVersion = 1;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginTrace()));
  }
}

pluginTrace::pluginTrace(void)
{
  this->_filter = new filterTrace;
  this->_filters.push_back(this->_filter);
}

pluginTrace::~pluginTrace(void)
{
  delete this->_filter;
}

unsigned int		pluginTrace::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginTrace::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginTrace::getFilters() const
{
  return (this->_filters);
}

void	pluginTrace::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginTrace::setConfigurator(zia::IConfiguration* conf)
{
  this->_filter->setConfigurator(conf);
}
