/// \file

#include "PoolFilter.h"

PoolFilter::PoolFilter(const zia::filter::IFilter* filter, Plugin* plugin) :
  _plugin(plugin), _filter(filter), _access(true), _counter(0), _pool(filter->getObjectSize())
{
}

PoolFilter::~PoolFilter(void)
{
}

Plugin*	PoolFilter::getPlugin() const
{
  return (this->_plugin);
}

void	PoolFilter::getInstanceFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters)
{
  this->_mutexAccess.lock();
  if (this->_access)
    {
      this->_mutexCounterPool.lock();
      void* storage = this->_pool.malloc();
      if (storage != 0)
	{
	  this->_filter->constructObject(storage);
	  std::pair<PoolFilter * const, zia::filter::IFilter *> pair(this, static_cast<zia::filter::IFilter*>(storage));
	  filters.push_back(pair);
	  ++this->_counter;
	}
      this->_mutexCounterPool.unlock();
    }
  this->_mutexAccess.unlock();
}

PoolFilter::ActionOnPool	PoolFilter::releaseInstance(zia::filter::IFilter* filter)
{
  ActionOnPool	delPool = DO_NOTHING;
  this->_mutexCounterPool.lock();
  this->_pool.free(static_cast<void *>(filter));
  --this->_counter;
  this->_mutexAccess.lock();
  if (this->_access == false && this->_counter == 0)
    {
      delPool = DEL_POOL;
      if (this->_plugin->removeFilter(this))
	delPool = UNLOAD_PLUGIN;
    }
  this->_mutexAccess.unlock();
  this->_mutexCounterPool.unlock();
  return (delPool);
}

void	PoolFilter::closeAccess()
{
  this->_mutexAccess.lock();
  this->_access = false;
  this->_mutexAccess.unlock();
}
