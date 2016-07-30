/// \file

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

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
  if (key != "")
    {
      if (this->hiveExists(section))
	this->checkZiaInfo(theDictionnary, key, value);
      else
	this->addData(section, key, value);
    }
  return (theDictionnary);
}
void	Configuration::checkDirectoryValidity()
{
  zia::IDictionnary & dic = this->getOrSetDictionnary("Main", "", "");
  boost::filesystem::path	path(boost::filesystem::system_complete(boost::filesystem::path(dic.get("RootDirectory"))));
  path.normalize();
  if (false == boost::filesystem::is_directory(path))
    {
#ifdef _WIN32
      dic.set("RootDirectory", "C:/");
#else
      dic.set("RootDirectory", "/");
#endif
    }
  else
    {
      std::string tempPath = path.string();
      if ('.' == tempPath[tempPath.size() - 1])
	tempPath.erase(tempPath.size() - 1);
      dic.set("RootDirectory", tempPath);
    }

  path = boost::filesystem::system_complete(boost::filesystem::path(dic.get("LogsDirectory")));
  path.normalize();

  if (false == boost::filesystem::is_directory(path))
    {
#ifdef _WIN32
      dic.set("LogsDirectory", "logs/");
#else
      dic.set("LogsDirectory", "logs/");
#endif
    }
  else
    {
      std::string tempPath = path.string();
      if ('.' == tempPath[tempPath.size() - 1])
	tempPath.erase(tempPath.size() - 1);
      dic.set("LogsDirectory", tempPath);
    }
}

void	Configuration::checkZiaConfiguration()
{
  zia::IDictionnary & portDictionnary = this->getOrSetDictionnary("Ports", "SSL", "443");
  this->checkZiaInfo(portDictionnary, "Http", "80");
  this->checkZiaInfo(portDictionnary, "PluginLoader", "42000");

  zia::IDictionnary &	paramsDictionnary = this->getOrSetDictionnary("Main", "RootDirectory", "www/");
  this->checkZiaInfo(paramsDictionnary, "ServerAdmin", "youa@your.address");
  this->checkZiaInfo(paramsDictionnary, "ServerName", "ZiaServer");
  this->checkZiaInfo(paramsDictionnary, "LogsDirectory", "logs/");
  this->checkZiaInfo(paramsDictionnary, "MaxKeepAlive", "300");
  this->checkZiaInfo(paramsDictionnary, "KeepAlive", "On");
  this->getOrSetDictionnary("Plugins", "LoadDirectory", "libs/");
  this->checkDirectoryValidity();
}
