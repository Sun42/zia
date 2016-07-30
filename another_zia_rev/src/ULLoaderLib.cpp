/// \file

#include <dlfcn.h>

#include "ULLoaderLib.h"
#include "ExceptionLoaderLib.h"

/*********************************************************************/

ULLoaderLib::ULLoaderLib()
{
}

ULLoaderLib::~ULLoaderLib()
{
}

/*********************************************************************/

HANDLELIB		ULLoaderLib::loadingLibrary(std::string const & path)
{
  HANDLELIB handlelib = ::dlopen(path.c_str(), RTLD_LAZY);
  if (0 == handlelib)
    {
      throw (ExceptionLoaderLib(dlerror()));
    }
  return (handlelib);
}

PTRSYMBOL		ULLoaderLib::getSymbol(HANDLELIB handlelib, std::string  const & symbol)
{
  ::dlerror();
  PTRSYMBOL		ptrfunc = ::dlsym(handlelib, symbol.c_str());
  char const *error = ::dlerror();
  if (0 != error)
    {
      throw (ExceptionLoaderLib(error));
    }
  return (ptrfunc);
}

void			ULLoaderLib::unloadLibrary(HANDLELIB handlelib)
{
  if (0 != ::dlclose(handlelib))
    {
      throw (ExceptionLoaderLib(dlerror()));
    }
}
