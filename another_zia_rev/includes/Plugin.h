/// \file

#ifndef PLUGIN_H_
#define PLUGIN_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/thread.hpp>

#include "zia_api/IPlugin.h"

#include "ILoaderLib.h"

class PoolFilter;

/*! \class Plugin
 * \brief A REMPLIR
 *
 */

class	Plugin
{
 public:
  Plugin(HANDLELIB, std::string const &);
  ~Plugin();
  Plugin(Plugin const &);

  Plugin&	operator=(Plugin const &);
  bool		operator==(std::string const &) const;
  bool		operator==(Plugin const &) const;

  std::string	getId() const;

  void		createPoolFilter();
  bool		closeAccessToPool(); // retourne vrai si aucun pool fiters n est utilise, le plugin est ensuite delete de la memoire
  bool		removeFilter(PoolFilter *);

 private:
  HANDLELIB			_handlelib;
  std::string			_path;
  zia::IPlugin*			_plugin;
  zia::IConfiguration*		_confPlugin;
  zia::ILogger*			_logger;
  boost::mutex			_mutexPoolsFilters;
  std::list<PoolFilter*>	_poolsFilters;
};

#endif // PLUGIN_H_
