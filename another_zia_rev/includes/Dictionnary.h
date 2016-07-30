/// \file

#ifndef DICTIONNARY_H_
#define DICTIONNARY_H_

#include "zia_api/IDictionnary.h"

/*! \class Dictionnary
 * \brief Conteneur officiel de l'API.
 *
 * Implementation de IDictionnary.
 */

class	Dictionnary : public zia::IDictionnary
{
 public:
  Dictionnary(void);
  ~Dictionnary(void);

  void			clear(void);
  void			set(const std::string& key, const std::string& value);
  std::string		get(const std::string& key) const;
  void			unset(const std::string& key);
  bool			exists(const std::string& key) const;

  size_t		getSize(void) const;
  bool			isEmpty(void) const;

  std::map<std::string, std::string>	getContent() const;

 private:
  mutable std::map<std::string, std::string>	_entities;
};

#endif
