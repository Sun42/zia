/// \file

#ifndef	STRINGTOTYPE_H_
# define STRINGTOTYPE_H_

#include <sstream>
#include <string>

template<typename T>
T	stringToType(const std::string& input)
{
  T			output;
  std::istringstream	iss(input);

  iss >> output;
  return (output);
}

#endif //! STRINGTOTYPE_H_
