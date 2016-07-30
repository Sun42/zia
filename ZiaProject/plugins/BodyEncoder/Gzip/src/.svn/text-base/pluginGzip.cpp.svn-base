#include "pluginGzip.h"
#include "filterGzip.h"

const std::string	pluginName = "pluginGzip";
const unsigned int	currentVersion = 1;

extern "C"
{
  zia::IPlugin&	getInstance()
  {
    return (*(new pluginGzip()));
  }
}

pluginGzip::pluginGzip(void)
{
  this->_encode = new filterGzip();
  this->_filters.push_back(this->_encode);
}

pluginGzip::~pluginGzip(void)
{
}

unsigned int		pluginGzip::getVersion(void) const
{
  return (currentVersion);
}

const std::string&	pluginGzip::getName(void) const
{
  return (pluginName);
}

const std::vector<const zia::filter::IFilter*>& pluginGzip::getFilters() const
{
  return (this->_filters);
}

void	pluginGzip::setLogger(zia::ILogger* logger)
{
  this->_logger = logger;
}

void	pluginGzip::setConfigurator(zia::IConfiguration* conf)
{
   this->_encode->setConfigurator(conf);
}
