/// \file

#ifndef PLUGINMANAGER_H_
# define PLUGINMANAGER_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/thread.hpp>

#include "Plugin.h"

/*! \class PluginManager
 * \brief Gestionnaire de plugins
 *
 * Cette classe permet la gestion des plugins. C'est a dire l'ajout, la suppression de plugin a chaud.
 */

class	PluginManager
{
 public:
  static PluginManager*	getInstance();
  static void		destroyInstance();

  unsigned char		loadPlugin(std::string const &); // load the dll/so at the specific path
  void			loadPlugins(std::string const &); // load the dll/so at the specific directory
  bool			unloadPlugin(std::string const &);
  void			unloadAllPlugins();
  void			listPlugins(std::string &);
  bool			pluginExist(Plugin const * const);

 private:
  PluginManager();
  ~PluginManager();
  PluginManager(PluginManager const &);

  PluginManager&	operator=(PluginManager const &);

 private:
  static PluginManager*	_instance;
  boost::mutex		_mutexPlugins;
  std::list<Plugin *>	_plugins;
};

#endif // PLUGINMANAGER_H_
