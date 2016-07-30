/// \file

#include "PluginManager.h"
#include "ExceptionLoaderLib.h"

#ifdef _WIN32
# include "WLoaderLib.h"
#else
# include "ULLoaderLib.h"
#endif // _WIN32

/*********************************************************************/
PluginManager*	PluginManager::_instance = 0;
/*********************************************************************/

PluginManager*	PluginManager::getInstance()
{
  if (PluginManager::_instance == 0)
    PluginManager::_instance = new PluginManager();
  return (PluginManager::_instance);
}

void	PluginManager::destroyInstance()
{
  if (PluginManager::_instance != 0)
    {
      delete PluginManager::_instance;
      PluginManager::_instance = 0;
    }
}

/*********************************************************************/

PluginManager::PluginManager()
  : _plugins()
{
}

PluginManager::~PluginManager()
{
}

/*********************************************************************/

bool	PluginManager::loadPlugin(std::string const & path)
{
  std::cout << "PluginManager::loadPlugin\n";
#ifdef _WIN32
  WLoaderLib    loader;
#else
  ULLoaderLib   loader;
#endif
  Plugin*	newPlugin = 0;

  try
    {
      newPlugin = new Plugin(loader.loadingLibrary(path), path);
    }
  catch (const ExceptionLoaderLib& e)
    {
      std::cerr << e.what() << std::endl;
      if (newPlugin != 0)
	delete newPlugin;
      return (false);
    }
  std::cout << "fin load\navant createPoolFilter\n";
  newPlugin->createPoolFilter();
  std::cout << "fin createPoolFilter\n";
  this->_mutexPlugins.lock();
  std::cout << "fin PluginManager::loadPlugin\n";
  this->_plugins.push_back(newPlugin);
  this->_mutexPlugins.unlock();
  std::cout << "fin PluginManager::loadPlugin\n";
  return (true);
}

bool	PluginManager::unloadPlugin(std::string const & path)
{
  this->_mutexPlugins.lock();
  bool	unloadSucceded = false;
  std::list<Plugin *>::iterator	itBegin = this->_plugins.begin();
  std::list<Plugin *>::iterator	itEnd = this->_plugins.end();
  for (; itBegin != itEnd; ++itBegin)
    {
      if (*(*itBegin) == path)
	{
	  (*itBegin)->closeAccessToPool();
	  unloadSucceded = true;
	  break;
	}
    }
  this->_mutexPlugins.unlock();
  return (unloadSucceded);
}

void	PluginManager::removePlugin(Plugin * plugin)
{
  this->_mutexPlugins.lock();
  std::list<Plugin *>::iterator		itSearch = std::find(this->_plugins.begin(), this->_plugins.end(), plugin);
  if (itSearch != this->_plugins.end())
    {
      this->_plugins.remove(plugin);
      delete plugin;
    }
  this->_mutexPlugins.unlock();
}

void	PluginManager::listPlugins(std::string & list)
{
  this->_mutexPlugins.lock();
  std::list<Plugin *>::const_iterator	it = this->_plugins.begin();
  std::list<Plugin *>::const_iterator	itEnd = this->_plugins.end();
  for (; it != itEnd; ++it)
    {
      list += (*it)->getId();
    }
  this->_mutexPlugins.unlock();
}
