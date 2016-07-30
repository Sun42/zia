/// \file

#ifndef SIZE_FILE_HPP
#define SIZE_FILE_HPP

#include <string>
using std::basic_string;
#include <fstream>
using std::basic_ifstream;

template <class C>
long	SizeFile(const C *s)
{
  // ate signifie at end
  return static_cast<long> (basic_ifstream<C>(s, std::ios::ate).tellg());
}

template <class C>
long	SizeFile(const basic_string<C> &s)
{
  return SizeFile(s.c_str());
}

#endif /* !SIZE_FILE_HPP */
