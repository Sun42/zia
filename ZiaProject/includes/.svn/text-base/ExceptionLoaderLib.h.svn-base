/// \file

#ifndef EXCEPTIONLOADERLIB_H_
# define EXCEPTIONLOADERLIB_H_

#include <exception>

/*! \class ExceptionLoaderLib
 * \brief Classe d'exception pour le loader de lib.
 *
 * Ce type d'exception est jete lorsqu'une erreur survient dans le module de chargement des bibliotheques dynamiques..
 */

class	ExceptionLoaderLib : public std::exception
{
 public:
  ExceptionLoaderLib(char const *) throw();
  ~ExceptionLoaderLib() throw();
  virtual char const *	what() const throw();

 private:
  char const *	_message;
};

#endif // EXCEPTIONLOADERLIB_H_
