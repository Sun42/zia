/// \file

#include "Dictionnary.h"

Dictionnary::Dictionnary(void)
{
}

Dictionnary::~Dictionnary(void)
{
}

/*!
 * Supprimme toutes les entites du conteneur.
 */
void	Dictionnary::clear(void)
{
  this->_entities.clear();
}

/*!
 * Affecte une valeur a une clef.
 */
void	Dictionnary::set(const std::string& key, const std::string& value)
{
  this->_entities[key] = value;
}

std::string	Dictionnary::get(const std::string& key) const
{
  return (this->_entities[key]);
}

void	Dictionnary::unset(const std::string& key)
{
  std::map<std::string, std::string>::iterator	it;

  it = this->_entities.find(key);
  if (it != this->_entities.end())
    this->_entities.erase(it);
}

bool	Dictionnary::exists(const std::string& key) const
{
  std::map<std::string, std::string>::const_iterator	it;

  it = this->_entities.find(key);
  return (it != this->_entities.end());
}

size_t	Dictionnary::getSize(void) const
{
  return (this->_entities.size());
}

bool	Dictionnary::isEmpty(void) const
{
  return (this->_entities.empty());
}

std::map<std::string, std::string>	Dictionnary::getContent(void) const
{
  return (this->_entities);
}
