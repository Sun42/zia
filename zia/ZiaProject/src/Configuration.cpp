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

bool	Configuration::hiveExists(const std::string& section)
{
  std::map<std::string, Dictionnary>::iterator	it;

  it = this->_sections.find(section);
  return (it != this->_sections.end());
}

void	Configuration::addData(const std::string& section,
			       const std::string& key,
			       const std::string& value)
{
  this->_sections[section].set(key, value);
}
