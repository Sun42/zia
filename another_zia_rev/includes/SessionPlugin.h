/// \file

#ifndef SESSIONPLUGIN_H_
# define SESSIONPLUGIN_H_

#include <map>

#include "Packet.h"

/*! \class SessionPlugin
 * \brief Gestion des plugins.
 *
 * Permet de charger, decharger et lister les plugins.
 */

class	SessionPlugin
{
 public:
  static const unsigned char SUCCESS = '1'; // OK
  static const unsigned char LOGIN_FAIL = '2'; // Login ou pass invalid
  static const unsigned char PATH_FAIL = '3'; // Path incorrect
  static const unsigned char LIB_FAIL = '4'; // Le symbole n a pas ete trouve -  plugin invalide
  static const unsigned char LOGIN_NEED = '5'; // besoin de se logger
  static const unsigned char LIB_LOADED = '6'; // Plugin deja charge

  SessionPlugin();
  SessionPlugin(SessionPlugin const & rhs);
  ~SessionPlugin();

  SessionPlugin&	operator=(SessionPlugin const & rhs);

  void			exec(Packet&, Packet&);

 private:
  void			authentification(Packet&, Packet&);
  void			loadPlugin(Packet&, Packet&);
  void			unloadPlugin(Packet&, Packet&);
  void			reloadPlugin(Packet&, Packet&); // Couille
  void			listPlugins(Packet&, Packet&);

 private:
  typedef void (SessionPlugin::*ptfunc_t)(Packet&, Packet&);
  std::map<char, ptfunc_t>	_mapPtFunc;
  bool				_logged;
};

#endif //! SESSIONPLUGIN_H_
