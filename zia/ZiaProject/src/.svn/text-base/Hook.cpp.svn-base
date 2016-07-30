/// \file

#include "Hook.h"
#include "PluginManager.h"

Hook::Hook(void)
{
}

Hook::~Hook(void)
{
}

PoolFilter*	Hook::createPoolFilter(const zia::filter::IFilter* filter, Plugin* plugin)
{
  PoolFilter*	poolf = new PoolFilter(filter, plugin);
  this->_mutexPoolsfilters.lock();
  this->_poolsFilters.push_back(poolf);
  this->_mutexPoolsfilters.unlock();
  return (poolf);
}


void	Hook::getListFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters)
{
  this->_mutexPoolsfilters.lock();
  std::list<PoolFilter*>::iterator	itBegin = this->_poolsFilters.begin();
  std::list<PoolFilter*>::iterator	itEnd = this->_poolsFilters.end();
  for (; itBegin != itEnd; ++itBegin)
    {
      (*itBegin)->getInstanceFilter(filters);
    }
  this->_mutexPoolsfilters.unlock();
}

void		Hook::clearListFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters)
{
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	itBegin = filters.begin();
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	itEnd = filters.end();
  for (; itBegin != itEnd; ++itBegin)
    {
      this->clearFilter(*itBegin);
    }
  filters.clear();
}

void	Hook::clearFilter(std::pair< PoolFilter* const, zia::filter::IFilter *> const & filter)
{
  switch (filter.first->releaseInstance(filter.second))
    {
    case PoolFilter::UNLOAD_PLUGIN:
      PluginManager::getInstance()->removePlugin(filter.first->getPlugin());
    case PoolFilter::DEL_POOL:
      this->removePoolFilter(filter.first);
      break;
    case PoolFilter::DO_NOTHING:
    default: ;
    }
}

void	Hook::removePoolFilter(PoolFilter * const poolf)
{
  this->_mutexPoolsfilters.lock();
  this->_poolsFilters.remove(poolf);
  delete poolf;
  this->_mutexPoolsfilters.unlock();
}
