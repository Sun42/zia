/// \file

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "zia_api/IConfiguration.h"

#include "Dictionnary.h"

/*! \class Configuration
 * \brief Fichier de configuration de plugin.
 *
 * Implementation de IConfiguration.
 */

class	Configuration : public zia::IConfiguration
{
 public:
  Configuration(void);
  ~Configuration(void);

  const zia::IDictionnary&	getHive(const std::string& section);
  bool				hiveExists(const std::string& section) const;
  void				addData(const std::string& section, const std::string& key, const std::string& value);
  void				addHive(std::string const & sectionName, const Dictionnary& hive);
  void				checkZiaConfiguration();

 private:
  zia::IDictionnary &		getOrSetDictionnary(const std::string& section,
					    const std::string& key,
					    const std::string& value);
  void				checkZiaInfo(zia::IDictionnary & theDictionnary, std::string const & key, std::string const & value);

 private:
  std::map<std::string, Dictionnary>	_sections;
};

#endif
