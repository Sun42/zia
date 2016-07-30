/// \file

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "PluginManager.h"
#include "SessionPlugin.h"
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
  delete PluginManager::_instance;
  PluginManager::_instance = 0;
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

bool	PluginManager::pluginExist(Plugin const * const newPlugin)
{
  boost::mutex::scoped_lock     lock(this->_mutexPlugins);

  std::list<Plugin *>::const_iterator	itBegin = this->_plugins.begin();
  std::list<Plugin *>::const_iterator	itEnd = this->_plugins.end();
  for (; itBegin != itEnd; ++itBegin)
    {
      if (*(*itBegin) == *newPlugin)
	{
	  return (true);
	}
    }
  return (false);
}

/*********************************************************************/

void		PluginManager::loadPlugins(std::string const & directory)
{
  boost::filesystem::directory_iterator dir_itr_end;
  if (boost::filesystem::is_directory(boost::filesystem::path(directory)))
    {
      for (boost::filesystem::directory_iterator dir_itr((directory)); dir_itr != dir_itr_end; ++dir_itr)
	{
	  this->loadPlugin(dir_itr->path().string());
	}
    }
}



unsigned char	PluginManager::loadPlugin(std::string const & path)
{
#ifdef _WIN32
  std::string ext(".dll");
#else
  std::string ext(".so");
#endif
  boost::filesystem::path	pathLib(boost::filesystem::system_complete(boost::filesystem::path(path)));
  pathLib.normalize();
  if (boost::filesystem::extension(pathLib) == ext)
    {
#ifdef _WIN32
      WLoaderLib    loader;
#else
      ULLoaderLib   loader;
#endif
      Plugin*	newPlugin = 0;

      try
	{
	  newPlugin = new Plugin(loader.loadingLibrary(pathLib.string()), pathLib.string());
	}
      catch (const ExceptionLoaderLib& e)
	{
	  std::cerr << e.what() << std::endl;
	  delete newPlugin;
	  return (SessionPlugin::LIB_FAIL);
	}

      if (false == this->pluginExist(newPlugin))
	{
	  //	  std::cout << "Chargement en memoire du plugin reussi\n";
	  newPlugin->createPoolFilter();
	  this->_mutexPlugins.lock();
	  this->_plugins.push_back(newPlugin);
	  this->_mutexPlugins.unlock();
	  return (SessionPlugin::SUCCESS);
	}
      //      std::cerr << "Le plugin est deja charge !!!" << std::endl;
      return (SessionPlugin::LIB_LOADED);
    }
  return (SessionPlugin::PATH_FAIL);
}

bool	PluginManager::unloadPlugin(std::string const & path)
{
  bool	unloadSucceded = false;
  bool	canDelete = false;

  this->_mutexPlugins.lock();
  std::list<Plugin *>::const_iterator	itBegin = this->_plugins.begin();
  std::list<Plugin *>::const_iterator	itEnd = this->_plugins.end();
  boost::filesystem::path	pathLib(boost::filesystem::system_complete(boost::filesystem::path(path)));
  pathLib.normalize();

  for (; itBegin != itEnd; ++itBegin)
    {
      if (*(*itBegin) == pathLib.string())
	{
	  //	  std::cout << "Le plugin a ete trouve , on ferme les pool" << std::endl;
	  canDelete = (*itBegin)->closeAccessToPool();
	  unloadSucceded = true;
	  break;
	}
    }

  if (itBegin != itEnd)
    {
      Plugin* temp = *itBegin;
      this->_plugins.remove(temp);
      if (true == canDelete)
	delete temp;
    }
  this->_mutexPlugins.unlock();
  return (unloadSucceded);
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

void	PluginManager::unloadAllPlugins()
{
  this->_mutexPlugins.lock();
  std::list<Plugin *>::const_iterator	itBegin = this->_plugins.begin();
  std::list<Plugin *>::const_iterator	itEnd = this->_plugins.end();
  for (; itBegin != itEnd; ++itBegin)
    {
      if (true == (*itBegin)->closeAccessToPool())
	delete *itBegin;
    }
  this->_plugins.clear();
  this->_mutexPlugins.unlock();
}
