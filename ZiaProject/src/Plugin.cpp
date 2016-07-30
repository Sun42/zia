/// \file

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "Plugin.h"
#include "HookManager.h"
#include "ExceptionLoaderLib.h"
#include "XmlParser.h"
#include "Server.h"

#ifdef _WIN32
#include "WLoaderLib.h"
#else
#include "ULLoaderLib.h"
#endif // _WIN32

/*********************************************************************/

Plugin::Plugin(HANDLELIB handle, std::string const & path) :
  _handlelib(handle), _path(path), _plugin(0), _confPlugin(0), _logger(new Logger)
{
#ifdef _WIN32
  WLoaderLib    loader;
#else
  ULLoaderLib   loader;
#endif
  zia::getPlugin_t  ptrCtor;

  try
    {
      ptrCtor = (zia::getPlugin_t)(loader.getSymbol(this->_handlelib, "getInstance"));
      this->_plugin = &(ptrCtor());
    }
  catch (const ExceptionLoaderLib& e)
    {
      std::cerr << e.what() << std::endl;
    }

  XmlParser			parser;
  // change l extension du fichier pour loader le xml qui va avec le plugin
  boost::filesystem::path	xmlPath = boost::filesystem::change_extension(boost::filesystem::path(path), ".xml");

  Configuration*	confPlugin = new Configuration();
  parser.read(xmlPath.string(), *confPlugin);
  confPlugin->addHive("Main", Server::getInstance()->getDefaultConf());
  this->_confPlugin = confPlugin;

  this->_plugin->setConfigurator(this->_confPlugin);
  this->_plugin->setLogger(this->_logger);
}

Plugin::~Plugin()
{
  std::cout << "Plugin::~Plugin" << std::endl << "Personne n utilise le plugin : " << this->_path << std::endl;
  delete this->_plugin;
  delete this->_confPlugin;
  delete this->_logger;

  std::list<PoolFilter*>::const_iterator	it = this->_poolsFilters.begin();
  std::list<PoolFilter*>::const_iterator	itEnd = this->_poolsFilters.end();
  for (; it != itEnd; ++it)
    {
      delete *it;
    }

#ifdef _WIN32
  WLoaderLib    loader;
#else
  ULLoaderLib   loader;
#endif

  try
    {
      loader.unloadLibrary(this->_handlelib);
    }
  catch (const ExceptionLoaderLib& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

/*********************************************************************/

bool	Plugin::operator==(std::string const & path) const
{
  return (this->_path == path);
}

bool	Plugin::operator==(Plugin const & rhs) const
{
  return (this->_path == rhs._path || this->_plugin->getName() == rhs._plugin->getName());
}

/*********************************************************************/

std::string	Plugin::getId() const
{
  std::ostringstream	os;
  os << this->_plugin->getVersion();
  return (this->_plugin->getName() + ":" + os.str() + ":" + this->_path + "\r\n");
}

/*********************************************************************/

void	Plugin::createPoolFilter()
{
  const std::vector< const zia::filter::IFilter *>		filters = this->_plugin->getFilters();
  std::vector< const zia::filter::IFilter *>::const_iterator	itBegin = filters.begin();
  std::vector< const zia::filter::IFilter *>::const_iterator	itEnd = filters.end();

  HookManager*	hkm = HookManager::getInstance();
  std::cout << "\nLe plugin --->" << this->_path <<  " <--- contient  : " << filters.size() << " filtres" << std::endl;
  for (; itBegin != itEnd; ++itBegin)
    hkm->createPoolFilter(*itBegin, this, this->_poolsFilters);
}

bool	Plugin::removeFilter(PoolFilter* pool)
{
  boost::mutex::scoped_lock     lock(this->_mutexPoolsFilters);
  this->_poolsFilters.remove(pool);
  return (this->_poolsFilters.size() == 0);
}

bool	Plugin::closeAccessToPool()
{
  HookManager*	hkm = HookManager::getInstance();
  bool		canDelete = true;

  this->_mutexPoolsFilters.lock();

  std::list<PoolFilter *>::const_iterator	it = this->_poolsFilters.begin();
  std::list<PoolFilter *>::const_iterator	itEnd = this->_poolsFilters.end();
  for (;  it != itEnd; ++it)
    {
      if (hkm->removePoolFilter(*it, (*it)->getHookType()) == false)
	canDelete = false;
    }

  this->_mutexPoolsFilters.unlock();
  return (canDelete);
}
