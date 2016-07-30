/// \file

#include "PoolFilter.h"
#include "PluginManager.h"

PoolFilter::PoolFilter(zia::filter::IFilter const * const filter, Plugin* const plugin, HookType num) :
  _plugin(plugin), _filter(filter), _numHook(num), _counter(0), _pool(filter->getObjectSize())
{
}

PoolFilter::~PoolFilter(void)
{
}

/*********************************************************************/

Plugin*	PoolFilter::getPlugin() const
{
  return (this->_plugin);
}

HookType	PoolFilter::getHookType() const
{
  return (this->_numHook);
}

int		PoolFilter::getPriority() const
{
  return (this->_filter->getPriority());
}

bool		PoolFilter::isUsed()
{
  boost::mutex::scoped_lock     lock(this->_mutexCounterPool);
  return (this->_counter > 0);
}


/*********************************************************************/

void	PoolFilter::getInstanceFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters)
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

PoolFilter::ActionOnPool	PoolFilter::releaseInstance(zia::filter::IFilter* const filter)
{
  ActionOnPool	delPool = DO_NOTHING;
  this->_mutexCounterPool.lock();
  filter->~IFilter();
  this->_pool.free(static_cast<void *>(filter));
  --this->_counter;
  if (this->_counter == 0 && PluginManager::getInstance()->pluginExist(this->_plugin) == false)
    {
      delPool = DEL_POOL;
      if (true == this->_plugin->removeFilter(this))
	delPool = UNLOAD_PLUGIN;
    }
  this->_mutexCounterPool.unlock();
  return (delPool);
}
