/// \file

#include "WLoaderLib.h"
#include "ExceptionLoaderLib.h"

/*********************************************************************/

WLoaderLib::WLoaderLib()
{
}

WLoaderLib::~WLoaderLib()
{
}

/*********************************************************************/

HANDLELIB	WLoaderLib::loadingLibrary(std::string const & path)
{
  HMODULE	handlelib = ::LoadLibrary(LPCSTR(path.c_str()));
  if (0 == handlelib)
    {
      throw (ExceptionLoaderLib::ExceptionLoaderLib("Cannot load library."));
    }
  return (handlelib);
}

PTRSYMBOL	WLoaderLib::getSymbol(HANDLELIB handlelib, std::string const & symbolname)
{
  FARPROC	ptrfunc = (PTRSYMBOL)GetProcAddress(handlelib, symbolname.c_str());

  if (0 == ptrfunc)
    {
      throw (ExceptionLoaderLib("Symbol not found."));
    }
  return (ptrfunc);
}

void	WLoaderLib::unloadLibrary(HANDLELIB handlelib)
{
  if (0 == ::FreeLibrary(handlelib))
    {
      throw (ExceptionLoaderLib("Cannot close the dll."));
    }
}
