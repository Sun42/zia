/// \file

#ifndef HOOKMANAGER_H_
#define HOOKMANAGER_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/array.hpp>

#include "zia_api/filter/IFilter.h"

#include "Hook.h"
#include "HookType.h"

/*! \class HookManager
 * \brief Gestion des hooks.
 *
 *
 */

class	HookManager
{
 public:
  static HookManager*	getInstance();
  static void		destroyInstance();

  void			createPoolFilter(const zia::filter::IFilter*, Plugin* const, std::list<PoolFilter*>&); /*!< Choisis le bon Hook dans lequel ajouter le Pool */
  bool			removePoolFilter(PoolFilter * const, HookType);

  bool			getHook(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >&, HookType);
  void			clearHook(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >&, HookType);
  void			clearFilter(std::pair< PoolFilter* const, zia::filter::IFilter *> const &, HookType) ;

 private:
  HookManager();
  ~HookManager();
  HookManager(HookManager const &);
  HookManager&		operator=(HookManager const &);

 private:
  static HookManager*				_instance;
  boost::array<Hook, CLOSED_CONNECTION + 1>	_hooks; /*!< Tableau de tous les hooks disponibles*/
};

#endif // HOOKMANAGER_H_
