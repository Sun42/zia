/// \file

#ifndef WLOADER_LIB_H_
# define WLOADER_LIB_H_

#include "ILoaderLib.h"

/*! \class WLLoaderLib
 * \brief Abstraction Windows de ILoaderLib.
 *
 * Implementation de l'abstraction Windows de ILoaderLib.
 */

class WLoaderLib : public ILoaderLib
{
 public:
  WLoaderLib();
  ~WLoaderLib();

  virtual HANDLELIB	loadingLibrary(std::string const &);
  virtual PTRSYMBOL	getSymbol(HANDLELIB, std::string  const &);
  virtual void		unloadLibrary(HANDLELIB);

 private:
  WLoaderLib(WLoaderLib const &);
  WLoaderLib&		operator=(WLoaderLib const &);
};

#endif // WLOADER_LIB_H_
