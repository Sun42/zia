/// \file

#include "pluginPerl.h"
#include "filterPerl.h"

const std::string	pluginName = "Perl-plugin";
const unsigned int	currentVersion = 2;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginPerl()));
  }
}

pluginPerl::pluginPerl(void)
{
  this->_perlFilter = new filterPerl;
  this->_filters.push_back(this->_perlFilter);
}

pluginPerl::~pluginPerl(void)
{
  delete this->_perlFilter;
}

unsigned int		pluginPerl::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginPerl::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginPerl::getFilters() const
{
  return (this->_filters);
}

void	pluginPerl::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginPerl::setConfigurator(zia::IConfiguration* configurator)
{
  this->_perlFilter->setConfigurator(configurator);
}
