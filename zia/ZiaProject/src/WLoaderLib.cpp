/// \file
//#warning "enlever se ifdef"
#ifdef _WIN32
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
  if (handlelib == NULL)
    {
      throw (ExceptionLoaderLib::ExceptionLoaderLib("Cannot load library."));
    }
  return (handlelib);
}

PTRSYMBOL	WLoaderLib::getSymbol(HANDLELIB handlelib, std::string const & symbolname)
{
  FARPROC	ptrfunc = (PTRSYMBOL)GetProcAddress(handlelib, symbolname.c_str());

  if (ptrfunc == NULL)
    {
      throw (ExceptionLoaderLib("Symbol not found."));
    }
  return (ptrfunc);
}

void	WLoaderLib::unloadLibrary(HANDLELIB handlelib)
{
  std::cout << "Unload de -->" << handlelib << std::endl;
  if (::FreeLibrary(handlelib) == 0)
    {
      throw (ExceptionLoaderLib("Cannot close the dll."));
    }
}
#endif
