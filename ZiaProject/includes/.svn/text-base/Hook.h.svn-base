/// \file

#ifndef HOOK_H_
#define HOOK_H_

#include <list>

#include "PoolFilter.h"

/*! \class Hook
 * \brief Conteneur de pool
 *
 * Un hook contient une liste de pool correspondant a ses filtres.
 */
class	Hook
{
 public:
  Hook(void);
  ~Hook(void);


  /*!
   *   \fn   PoolFilter*	Hook::createPoolFilter(const zia::filter::IFilter* filter, Plugin* plugin)
   * \brief Permet de creer un nouveau Pool d'objets  IFilter dans le hook.
   * \param filter : Pointeur sur IFilter
   * \param plugin : Pointeur sur Plugin
   * \return un pointeur sur le PoolFilter construit.
   */
  PoolFilter*	createPoolFilter(const zia::filter::IFilter* filter, Plugin* plugin, HookType numHook);
  bool		removePoolFilter(PoolFilter *);
  /*!
   * \fn   void		getListFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters)
   * \brief  Remplit la liste de Filters passee en parametre par une instance
   *  prise dans chaque poolFilters du hook
   * \param filters : reference sur une liste de pair(PoolFilter *, IFilter*)
   * \return void
   */
  void		getListFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >& filters);

  void		clearListFilter(std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >&); /*!< Libere les instances dans leur pool respectif*/
  void		clearFilter(std::pair< PoolFilter* const, zia::filter::IFilter *> const &); /*!< Libere l'instance du filtre dans son pool*/
  void		deletePoolFilter(PoolFilter * const); /*!< Detruit un pool du hook */

 private:
  Hook(Hook const &);
  Hook&		operator=(Hook const &);

  boost::mutex			_mutexPoolsfilters; /*!< Mutex sur la liste */
  std::list<PoolFilter*>	_poolsFilters; /*!< Liste des pools de filtres */
};

#endif
