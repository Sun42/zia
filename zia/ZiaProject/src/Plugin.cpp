/// \file

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "Plugin.h"
#include "HookManager.h"
#include "ExceptionLoaderLib.h"
#include "XmlParser.h"

#ifdef _WIN32
#include "WLoaderLib.h"
#else
#include "ULLoaderLib.h"
#endif

/*********************************************************************/

Plugin::Plugin(HANDLELIB handle, std::string const & path)
  : _handlelib(handle), _path(path)
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
      std::cout << "Value du ptr " << this->_plugin << std::endl;
    }
  catch (const ExceptionLoaderLib& e)
    {
      std::cerr << e.what() << std::endl;
    }

  XmlParser			parser;
  // change l extension du fichier pour loader le xml qui va avec le plugin
  boost::filesystem::path	xmlPath = boost::filesystem::change_extension(boost::filesystem::path(path), ".xml");
  parser.read(xmlPath.string(), this->_confPlugin);
}

Plugin::~Plugin()
{
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

bool	Plugin::operator==(std::string const & path) const
{
  return (this->_path == path);
}

/*********************************************************************/

void	Plugin::createPoolFilter()
{
  std::cout << "avant getFilter " << this->_plugin << std::endl;
  const std::vector< const zia::filter::IFilter *>		filters = this->_plugin->getFilters();
  std::cout << "apres getFilter " << std::endl;
  std::vector< const zia::filter::IFilter *>::const_iterator	itBegin = filters.begin();
  std::vector< const zia::filter::IFilter *>::const_iterator	itEnd = filters.end();
  std::cout << "avant size :" << filters.size() << std::endl;
  HookManager*	hkm = HookManager::getInstance();
  std::cout << "size :" << filters.size() << std::endl;
  for (; itBegin != itEnd; ++itBegin)
    {
      std::cout << "avant push"<< std::endl;
      this->_poolsFilters.push_back(hkm->createPoolFilter(*itBegin, this));
      std::cout << "apres push"<< std::endl;
    }
}

bool	Plugin::removeFilter(PoolFilter* pool)
{
  boost::mutex::scoped_lock     lock(this->_mutexPoolsFilters);
  this->_poolsFilters.remove(pool);
  return (this->_poolsFilters.size() == 0);
}

void	Plugin::closeAccessToPool()
{
  this->_mutexPoolsFilters.lock();
  std::for_each(this->_poolsFilters.begin(), this->_poolsFilters.end(), boost::bind(&PoolFilter::closeAccess, _1));
  this->_mutexPoolsFilters.unlock();
}

std::string	Plugin::getId() const
{
  std::ostringstream	os;
  os << this->_plugin->getVersion();
  return (this->_plugin->getName() + ":" + os.str() + ":" + this->_path + "\r\n");
}
