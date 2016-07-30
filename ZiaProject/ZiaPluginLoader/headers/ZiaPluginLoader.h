/// \file

#ifndef ZIA_PLUGIN_LOADER_H
#define ZIA_PLUGIN_LOADER_H

#include <QString>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include "NetworkThread.h"
#include "Preferences.h"
#include "ui_ZiaPluginLoader.h"

class	Preferences;
class	QFileDialog;

/*! \class ZiaPluginLoader
 * \brief Fenetre principale du client.
 *
 * Widget principal ou sont affiches les plugins charges.
 */
class	ZiaPluginLoader : public QMainWindow, public Ui_ZiaPluginLoader
{
  Q_OBJECT

public:
  ZiaPluginLoader(QWidget* parent = 0);
  ~ZiaPluginLoader(void);

  enum	Status
  {
	  CONNECTED,
	  DISCONNECTED,
	  LOGGED_IN
  };

  QTreeWidgetItem*	find(const QString& data, const int& column = 0) const;
  void	addItem(const QString& pluginName, const QString& version, const QString& path) const;
  void	removeItem(const int& column, const QString& pluginName) const;
  void	removeItemByPath(const QString& path) const;
  void	removeAllItems(void);

  private slots:
  void	connect(void);
  void	disconnect(void);
  void	loadPlugin(void);
  void	unloadPlugin(void);
  void	reloadPlugin(void);
  void	refreshList(void);
  void	login(void);
  void	updateActions(const int&);
  void	openPreferencesDialog(void);
  void  processNetworkErrors(const char*);
  void	displayInStatusBar(const QString&);
  void	openContextMenu(const QPoint&);

  void	processLoginState(bool success);
  void	processPluginLoadState(bool success, const QString&);
  void	processUnloadPluginState(bool success, const QString&);
  void	processReloadPluginState(bool success, const QString&);
  void	receivePluginList(const QStringList&);

 private:
  bool	setRootChildren(void);
  void	connectActions(void);
  void	createContextMenu(void);
  void	readSettings(void);
  void	writeSettings(void);
  void	connectParserSignals(void);

  QTreeWidgetItem*	_loadedPlugins;
  NetworkThread*	_network;
  Preferences*		_preferences;
  QFileDialog*		_fileDialog;
  QMenu*			_contextMenu;
};

#endif // ZIA_PLUGIN_LOADER_H
