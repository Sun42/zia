/// \file

#include "pluginDelete.h"
#include "filterDelete.h"

const std::string	pluginName = "pluginDelete";
const unsigned int	currentVersion = 1;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginDelete()));
  }
}

pluginDelete::pluginDelete(void)
{
  this->_filterDelete = new filterDelete;
  this->_filters.push_back(this->_filterDelete);
}

pluginDelete::~pluginDelete(void)
{
  delete this->_filterDelete;
}

inline unsigned int		pluginDelete::getVersion(void) const
{
  return (currentVersion);
}

inline const std::string&	pluginDelete::getName(void) const
{
  return (pluginName);
}

inline const std::vector<const zia::filter::IFilter*>& pluginDelete::getFilters() const
{
  return (this->_filters);
}

void	pluginDelete::setLogger(zia::ILogger* logger)
{
  this->_filterDelete->setLogger(logger);
}

void	pluginDelete::setConfigurator(zia::IConfiguration* conf)
{
  this->_filterDelete->setConfigurator(conf);
}
