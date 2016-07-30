/// \file

#include "Configuration.h"

Configuration::Configuration(void)
{
}

Configuration::~Configuration(void)
{
}

const zia::IDictionnary&	Configuration::getHive(const std::string& section)
{
  return (this->_sections[section]);
}

bool	Configuration::hiveExists(const std::string& section) const
{
  std::map<std::string, Dictionnary>::const_iterator	it;

  it = this->_sections.find(section);
  return (it != this->_sections.end());
}

void	Configuration::addData(const std::string& section,
			       const std::string& key,
			       const std::string& value)
{
  this->_sections[section].set(key, value);
}

void	Configuration::addHive(const std::string& sectionName, const Dictionnary& hive)
{
  this->_sections[sectionName] = hive;
}

void	Configuration::checkZiaInfo(zia::IDictionnary & theDictionnary,
				    std::string const & key,
				    std::string const & value)
{
  if (theDictionnary.exists(key))
    {
      if (theDictionnary.get(key) == "")
	theDictionnary.set(key, value);
    }
  else
    theDictionnary.set(key, value);
}

zia::IDictionnary &	Configuration::getOrSetDictionnary(const std::string& section,
							   const std::string& key,
							   const std::string& value)
{
  zia::IDictionnary &	theDictionnary = this->_sections[section];
  if (this->hiveExists(section))
    this->checkZiaInfo(theDictionnary, key, value);
  else
    this->addData(section, key, value);
  return (theDictionnary);
}

void	Configuration::checkZiaConfiguration()
{
  zia::IDictionnary &	portDictionnary = this->getOrSetDictionnary("Ports", "SSL", "443");
  this->checkZiaInfo(portDictionnary, "Http", "80");
  this->checkZiaInfo(portDictionnary, "PluginLoader", "42000");

  zia::IDictionnary &	paramsDictionnary = this->getOrSetDictionnary("Main", "RootDirectory", "www/");
  this->checkZiaInfo(paramsDictionnary, "ServerAdmin", "youa@your.address");
  this->checkZiaInfo(paramsDictionnary, "ServerName", "www.example.com");
  this->checkZiaInfo(paramsDictionnary, "LogsDirectory", "logs/");
  this->checkZiaInfo(paramsDictionnary, "MaxKeepAlive", "300");
  this->checkZiaInfo(paramsDictionnary, "KeepAlive", "On");

  this->getOrSetDictionnary("Plugins", "LoadDirectory", "libs/");
}

