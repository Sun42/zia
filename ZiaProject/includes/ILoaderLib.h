/// \file

#ifndef ILOADER_LIB_H_
# define ILOADER_LIB_H_

#include <iostream>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>
typedef HMODULE	HANDLELIB;
typedef FARPROC	PTRSYMBOL;
#else
# include <dlfcn.h>
typedef void*	HANDLELIB;
typedef void*	PTRSYMBOL;
#endif // _WIN32

/*! \class ILLoaderLib
 * \brief Abstraction Windows/Lunix.
 *
 * Se referer a ULoaderLib et WLoaderLib.
 */
class	ILoaderLib
{
 public:
  virtual ~ILoaderLib(){}
  virtual HANDLELIB		loadingLibrary(std::string const &) = 0;
  virtual PTRSYMBOL		getSymbol(HANDLELIB, std::string  const &) = 0;
  virtual void			unloadLibrary(HANDLELIB) = 0;
};

#endif // ILOADER_LIB_H_
