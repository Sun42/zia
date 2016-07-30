/// \file

#ifndef PARSERLOADER_H_
#define PARSERLOADER_H_

#include <map>
#include <QObject>
#include <QStringList>
#include "Packet.h"

/*! \class ParserLoader
 * \brief Parseur de protocole ZiaPluginLoader.
 *
 * ParserLoader interprete des paquets de donnees
 * et emet des signaux lorsqu'ils sont interpretes correctement.
 */
class	ParserLoader : public QObject
{
	Q_OBJECT

public:
  ParserLoader();
  ~ParserLoader();

  void		exec(Packet&);

signals:
  void	loginState(bool success);
  void	pluginLoadState(bool success, const QString& explanation = "");
  void	unloadPluginState(bool success, const QString& explanation = "");
  void	reloadPluginState(bool success, const QString& explanation = "");
  void	sendPluginList(const QStringList&);

 private:
  void	authentification(Packet&);
  void	loadPlugin(Packet&);
  void	unloadPlugin(Packet&);
  void	reloadPlugin(Packet&);
  void	listPlugins(Packet&);

 private:
  typedef void (ParserLoader::*ptfunc_t)(Packet&);
  std::map<char, ptfunc_t>		_mapPtFunc;
};

#endif //! PARSERLOADER_H_
