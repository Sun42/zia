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
  std::cout << path << " -- handlelib --> " << handlelib << std::endl;
  if (handlelib == 0)
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
  if (error != NULL)
    {
      throw (ExceptionLoaderLib(error));
    }
  std::cout << "handleLib --> " << handlelib << " --- nom du symbol -->" << symbol << " -- Value -->" << ptrfunc << std::endl;
  return (ptrfunc);
}

void			ULLoaderLib::unloadLibrary(HANDLELIB handlelib)
{
  std::cout << "Unload de -->" << handlelib << std::endl;
  if (::dlclose(handlelib))
    {
      throw (ExceptionLoaderLib(dlerror()));
    }
}
