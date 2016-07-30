/// \file

#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <QFile>
#include <QIODevice>
#include <QXmlStreamReader>

#include "Configuration.h"

/*! \class XmlParser
 * \brief zconf parseur
 *
 * Parse les fichiers de configuration zconf.
 */

class	XmlParser : public QXmlStreamReader
{
 public:
  XmlParser(void);
  ~XmlParser(void);

  bool	read(const std::string& filename, Configuration& conf);

 private:
  void	readHives(Configuration&);
  void	readHive(Configuration&, const std::string&);
  void	readUnknownElement(void);

 private:
  QFile*	_file;
};

#endif
