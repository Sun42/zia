/// \file

#include "Hook.h"
#include "PluginManager.h"

/*********************************************************************/

Hook::Hook(void)
{
}

Hook::~Hook(void)
{
}

/*********************************************************************/

PoolFilter*	Hook::createPoolFilter(zia::filter::IFilter const * const filter, Plugin* const plugin, HookType numHook)
{
  PoolFilter*	poolf = new PoolFilter(filter, plugin, numHook);
  int		priority = filter->getPriority();
  this->_mutexPoolsfilters.lock();
  std::list<PoolFilter*>::iterator	it = this->_poolsFilters.begin();
  std::list<PoolFilter*>::iterator	itEnd = this->_poolsFilters.end();

  for (;it != itEnd && priority <= (*it)->getPriority(); ++it) ;
  this->_poolsFilters.insert(it, poolf);

  this->_mutexPoolsfilters.unlock();
  return (poolf);
}

void	Hook::getListFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters)
{
  this->_mutexPoolsfilters.lock();
  std::list<PoolFilter*>::const_iterator	itBegin = this->_poolsFilters.begin();
  std::list<PoolFilter*>::const_iterator	itEnd = this->_poolsFilters.end();
  for (; itBegin != itEnd; ++itBegin)
    {
      (*itBegin)->getInstanceFilter(filters);
    }
  this->_mutexPoolsfilters.unlock();
}

void		Hook::clearListFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters)
{
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::const_iterator	itBegin = filters.begin();
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::const_iterator	itEnd = filters.end();
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
    case PoolFilter::UNLOAD_PLUGIN :
      delete filter.first->getPlugin();
    case PoolFilter::DEL_POOL:
      this->deletePoolFilter(filter.first);
      break;
    case PoolFilter::DO_NOTHING:
    default: ;
    }
}

void	Hook::deletePoolFilter(PoolFilter * const poolf)
{
  this->_mutexPoolsfilters.lock();
  delete poolf;
  this->_mutexPoolsfilters.unlock();
}

bool	Hook::removePoolFilter(PoolFilter * const poolf)
{
  this->_mutexPoolsfilters.lock();
  this->_poolsFilters.remove(poolf);
  this->_mutexPoolsfilters.unlock();
  return (!poolf->isUsed());
}
