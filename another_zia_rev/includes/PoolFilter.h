/// \file

#ifndef POOL_FILTER_H_
#define POOL_FILTER_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/pool/pool.hpp>

#include "zia_api/filter/IFilter.h"

#include "Plugin.h"
#include "HookType.h"

/*! \class PoolFilter
 * \brief Pool de filtres
 *
 * Classe s'occupant de la gestion des instances de filtres.
 */

class	PoolFilter
{
 public:
  enum ActionOnPool{
    DO_NOTHING,
    DEL_POOL,
    UNLOAD_PLUGIN};

  PoolFilter(zia::filter::IFilter const * const, Plugin * const , HookType);
  ~PoolFilter(void);

  Plugin*	getPlugin() const; /*!< recupere le plugin duquel provient le filtre */
  HookType	getHookType() const;
  int		getPriority() const;
  bool		isUsed();

  void		getInstanceFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >&); /*!< ajoute une instance du pool dans la liste */
  ActionOnPool	releaseInstance(zia::filter::IFilter* const); /*!< relache l'instance dans le pool */

 private:
  Plugin * const			_plugin; /*!< Plugin d ou provient le filtre */
  zia::filter::IFilter const * const	_filter; /*!< Filtre qui permet de construire les instance du pool*/
  HookType				_numHook;
  boost::mutex				_mutexCounterPool;
  unsigned int				_counter; /*!< Nombre d'instance en cours d'utilisation */
  boost::pool<>				_pool;
};

#endif
