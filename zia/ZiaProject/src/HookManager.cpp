/// \file

#include "HookManager.h"

#include "zia_api/filter/IBodyDecoder.h"
#include "zia_api/filter/IBodyEncoder.h"
#include "zia_api/filter/IBodyProcessing.h"
#include "zia_api/filter/IClosedConnection.h"
#include "zia_api/filter/IInputDecoder.h"
#include "zia_api/filter/INewConnection.h"
#include "zia_api/filter/IOutputEncoder.h"

/*********************************************************************/
HookManager*	HookManager::_instance = 0;
/*********************************************************************/

HookManager*	HookManager::getInstance()
{
  if (HookManager::_instance == 0)
      HookManager::_instance = new HookManager();
  return (HookManager::_instance);
}

void	HookManager::destroyInstance()
{
  if (HookManager::_instance != 0)
    {
      delete HookManager::_instance;
      HookManager::_instance = 0;
    }
}

/*********************************************************************/

HookManager::HookManager()
{
  for (int i = 0; i < CLOSED_CONNECTION + 1; i++)
    {
      this->_hooks[i] = new Hook();
    }
}

HookManager::~HookManager()
{
}

/*********************************************************************/

PoolFilter*	HookManager::createPoolFilter(const zia::filter::IFilter* filter, Plugin* plugin)
{
  if (dynamic_cast<const zia::filter::INewConnection *>(filter) != 0)
    {
      return (this->_hooks[NEW_CONNECTION]->createPoolFilter(filter, plugin));
    }
  else if (dynamic_cast<const zia::filter::IInputDecoder *>(filter) != 0)
    {
      return (this->_hooks[INPUT_DECODER]->createPoolFilter(filter, plugin));
    }
  else if(dynamic_cast<const zia::filter::IBodyDecoder *>(filter) != 0)
    {
      return (this->_hooks[BODY_DECODER]->createPoolFilter(filter, plugin));
    }
  else if(dynamic_cast<const zia::filter::IBodyProcessing *>(filter) != 0)
    {
      return (this->_hooks[BODY_PROCESSING]->createPoolFilter(filter, plugin));
    }
  else if(dynamic_cast<const zia::filter::IBodyEncoder *>(filter) != 0)
    {
      return (this->_hooks[BODY_ENCODER]->createPoolFilter(filter, plugin));
    }
  else if(dynamic_cast<const zia::filter::IOutputEncoder *>(filter) != 0)
    {
      return (this->_hooks[OUTPUT_ENCODER]->createPoolFilter(filter, plugin));
    }
  else if(dynamic_cast<const zia::filter::IClosedConnection *>(filter) != 0)
    {
      return (this->_hooks[CLOSED_CONNECTION]->createPoolFilter(filter, plugin));
    }
  return (0);
}

bool	HookManager::getHook(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters, hookType currentHook)
{
  if (currentHook >= NEW_CONNECTION && currentHook <= CLOSED_CONNECTION)
    {
      this->_hooks[currentHook]->getListFilter(filters);
      return (true);
    }
  return (false);
}

void	HookManager::clearHook(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters, hookType currentHook)
{
  if (currentHook >= NEW_CONNECTION && currentHook <= CLOSED_CONNECTION)
      this->_hooks[currentHook]->clearListFilter(filters);
  else
    std::cerr << "HookManager::clearHook bad currentHook" << std::endl;
}

void	HookManager::clearFilter(std::pair< PoolFilter* const, zia::filter::IFilter *> const & filter, hookType currentHook)
{
  if (currentHook >= NEW_CONNECTION && currentHook <= CLOSED_CONNECTION)
    this->_hooks[currentHook]->clearFilter(filter);
  else
    std::cerr << "HookManager::clearFilter bad currentHook" << std::endl;
}
