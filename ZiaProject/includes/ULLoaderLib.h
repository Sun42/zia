/// \file

#ifndef ULLOADERLIB_H_
# define ULLOADERLIB_H_

#include "ILoaderLib.h"

/*! \class ULLoaderLib
 * \brief Abstraction Lunix de ILoaderLib.
 *
 * Implementation de l'abstraction Linux de ILoaderLib.
 */

class ULLoaderLib : public ILoaderLib
{
 public:
  ULLoaderLib();
  ~ULLoaderLib();

  virtual HANDLELIB	loadingLibrary(std::string const &);
  virtual PTRSYMBOL	getSymbol(HANDLELIB, std::string  const &);
  virtual void		unloadLibrary(HANDLELIB);

 private:
  ULLoaderLib(ULLoaderLib const &);
  ULLoaderLib&		operator=(ULLoaderLib const &);
};

#endif // ULLOADERLIB_H_
