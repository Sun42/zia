#include <iostream>
#include <QDir>
#include <QSettings>
#include <QFileDialog>
#include "ZiaPluginLoader.h"

ZiaPluginLoader::ZiaPluginLoader(QWidget* parent)
 :	QMainWindow(parent),
	_loadedPlugins(0),
	_network(0),
	_preferences(new Preferences(this)),
	_fileDialog(0),
	_contextMenu(0)
{
	setupUi(this);
	connectActions();
	createContextMenu();
	readSettings();
}

ZiaPluginLoader::~ZiaPluginLoader(void)
{
	writeSettings();
}

QTreeWidgetItem*	ZiaPluginLoader::find(const QString& data, const int& column) const
{
	QList<QTreeWidgetItem*>	found(this->treeWidget->findItems(data, Qt::MatchExactly, column));
	if (found.size())
	{
		return (found.at(0));
	}
	return (0);
}

void	ZiaPluginLoader::addItem(const QString& pluginName, const QString& version, const QString& path) const
{
	if (0 == find(pluginName))
	{
		QStringList			fields(pluginName);
		fields << version;
		fields << path;
		QTreeWidgetItem*	item = new QTreeWidgetItem(fields);
		this->treeWidget->addTopLevelItem(item);
	}
}

void	ZiaPluginLoader::removeItem(const int& column, const QString& data) const
{
	QTreeWidgetItem*	childToRemove = find(data, column);
	if (childToRemove != 0)
	{
		QTreeWidgetItem*	root = this->treeWidget->invisibleRootItem();
		root->removeChild(childToRemove);
		delete childToRemove;
	}
}

void	ZiaPluginLoader::removeAllItems(void)
{
	this->treeWidget->clear();
}

void	ZiaPluginLoader::connect(void)
{
	if (0 == this->_network)
	{
		this->_network = new NetworkThread(this->_preferences->lineEditIp->text().toStdString(),
										   this->_preferences->lineEditPort->text().toUShort());
		QObject::connect(this->_network, SIGNAL(sendToStatusBar(const QString&)), SLOT(displayInStatusBar(const QString&)));
		QObject::connect(this->_network, SIGNAL(stateChanged(const int&)), SLOT(updateActions(const int&)));
		QObject::connect(this->_network, SIGNAL(error(const char*)), SLOT(processNetworkErrors(const char*)));
		connectParserSignals();
		this->_network->start();
	}
}

void	ZiaPluginLoader::disconnect(void)
{
	if (this->_network != 0)
	{
		this->_network->stop();
		delete this->_network;
		this->_network = 0;
		this->removeAllItems();
		this->statusBar()->showMessage(tr("You are now disconnected."), 3000);
		this->updateActions(DISCONNECTED);
	}
}

void	ZiaPluginLoader::loadPlugin(void)
{
	if (0 == this->_network)
	{
		std::cerr << "loadPlugin called but network is not created yet." << std::endl;
		return;
	}

	if (0 == this->_fileDialog)
		this->_fileDialog = new QFileDialog(this, tr("Open plugin"), QDir::currentPath(), tr("Plugins (*.dll *.so *.dylib)"));

	QStringList fileNames;
	if (this->_fileDialog->exec())
		fileNames = this->_fileDialog->selectedFiles();

	for (int i = 0; i < fileNames.count(); ++i)
	{
		this->_network->send('L', fileNames.at(i).toStdString());
	}
}

void	ZiaPluginLoader::unloadPlugin(void)
{
	const QTreeWidgetItem*	currentItem = this->treeWidget->currentItem();

	if (currentItem != 0)
	{
		if (tr("Loaded Plugins") != currentItem->text(0))
		{
			if (this->_network != 0 && false == currentItem->text(2).isEmpty())
				this->_network->send('U', currentItem->text(2).toStdString());
		}
	}
}

void	ZiaPluginLoader::reloadPlugin(void)
{
	const QTreeWidgetItem*	currentItem = this->treeWidget->currentItem();

	if (currentItem != 0)
	{
		if (tr("Loaded Plugins") != currentItem->text(0))
		{
			if (this->_network != 0)
			{
				this->_network->send('R', currentItem->text(0).toStdString());
			}
		}
	}
}

void	ZiaPluginLoader::refreshList(void)
{
	if (this->_network != 0)
	{
		this->_network->send('l');
	}
}

void	ZiaPluginLoader::login(void)
{
	if (this->_network != 0)
	{
		this->_network->login(this->_preferences->lineEditLogin->text(), this->_preferences->lineEditPassword->text());
	}
}

void	ZiaPluginLoader::updateActions(const int& status)
{
	if (CONNECTED == status)
	{
		this->actionConnect->setEnabled(false);
		this->actionDisconnect->setEnabled(true);
		this->actionLogin->setEnabled(true);
		this->statusBar()->showMessage(tr("You are now connected."), 3000);
		if (this->_preferences->isAutoConnectChecked())
			login();
	}
	else if (LOGGED_IN == status)
	{
		this->actionLoad->setEnabled(true);
		this->actionUnload->setEnabled(true);
		this->actionReload->setEnabled(true);
		this->actionRefresh->setEnabled(true);
		this->treeWidget->setEnabled(true);
		this->actionLogin->setEnabled(false);
	}
	else if (DISCONNECTED == status)
	{
		this->actionConnect->setEnabled(true);
		this->actionDisconnect->setEnabled(false);
		this->actionLoad->setEnabled(false);
		this->actionUnload->setEnabled(false);
		this->actionReload->setEnabled(false);
		this->actionRefresh->setEnabled(false);
		this->treeWidget->setEnabled(false);
		this->actionLogin->setEnabled(false);
		this->statusBar()->showMessage(tr("You are now disconnected."), 3000);
	}
}

void	ZiaPluginLoader::openPreferencesDialog(void)
{
	this->_preferences->update();
	this->_preferences->show();
}

void	ZiaPluginLoader::processNetworkErrors(const char* error)
{
	this->statusBar()->showMessage(QString(error), 3000);
	this->disconnect();
}

void	ZiaPluginLoader::displayInStatusBar(const QString& message)
{
	this->statusBar()->showMessage(message, 3000);
}

void	ZiaPluginLoader::openContextMenu(const QPoint& pos)
{
	QTreeWidgetItem*	pointedItem = this->treeWidget->itemAt(pos);

	if (pointedItem != 0)
	{
		this->_contextMenu->exec(QCursor::pos());
	}
}

void	ZiaPluginLoader::processLoginState(bool success)
{
	if (true == success)
	{
		this->statusBar()->showMessage(tr("You are now logged in."), 3000);
		this->updateActions(ZiaPluginLoader::LOGGED_IN);
		if (this->_network != 0)
		{
			this->_network->send('l');
		}
	}
	else
	{
		this->statusBar()->showMessage(tr("Authentification failed."), 3000);
	}
}

void	ZiaPluginLoader::processPluginLoadState(bool success, const QString& explanation)
{
	if (true == success)
	{
		this->statusBar()->showMessage(tr("Loading completed."), 3000);
		if (this->_network != 0)
		{
			this->_network->send('l');
		}
	}
	else
	{
		this->statusBar()->showMessage(tr("Loading failed: ") + explanation, 3000);
	}
}

void	ZiaPluginLoader::processUnloadPluginState(bool success, const QString& path)
{
	if (true == success)
	{
		this->statusBar()->showMessage(tr("Plugin has been unloaded."), 3000);
		removeItem(2, path);
	}
	else
	{
		this->statusBar()->showMessage(tr("Unloading failed: ") + path, 3000);
	}
}

void	ZiaPluginLoader::processReloadPluginState(bool success, const QString& explanation)
{
	if (true == success)
	{
		this->statusBar()->showMessage(tr("Reloading completed."), 3000);
		if (this->_network != 0)
		{
			this->_network->send('l');
		}
	}
	else
	{
		this->statusBar()->showMessage(tr("Reloading failed: ") + explanation, 3000);
	}
}

void	ZiaPluginLoader::receivePluginList(const QStringList& list)
{
	const int	size = list.size();

	/*
	if (1 == size)
		this->statusBar()->showMessage("1" + tr(" plugin received."), 3000);
	else if (size > 1)
		this->statusBar()->showMessage(QString::number(size) + tr(" plugins received."), 3000);
	*/

	for (int i = 0; i < size; ++i)
	{
		QStringList	fields = QString(list.at(i)).split(':', QString::SkipEmptyParts);
		if (3 == fields.count())
		{
			this->addItem(fields.at(0), fields.at(1), fields.at(2));
		}
		else
		{
			std::cerr << "DEBUG RECEIVE PLUGIN LIST COUNT == " << fields.count() << std::endl;
		}
	}
}

void	ZiaPluginLoader::connectActions(void)
{
	// File
	QObject::connect(this->actionConnect, SIGNAL(triggered()), SLOT(connect()));
	QObject::connect(this->actionDisconnect, SIGNAL(triggered()), SLOT(disconnect()));
	QObject::connect(this->actionQuit, SIGNAL(triggered()), SLOT(close()));
	// Account
	QObject::connect(this->actionLogin, SIGNAL(triggered()), SLOT(login()));
	// Plugins
	QObject::connect(this->actionLoad, SIGNAL(triggered()), SLOT(loadPlugin()));
	QObject::connect(this->actionUnload, SIGNAL(triggered()), SLOT(unloadPlugin()));
	QObject::connect(this->actionReload, SIGNAL(triggered()), SLOT(reloadPlugin()));
	QObject::connect(this->actionRefresh, SIGNAL(triggered()), SLOT(refreshList()));
	// Options
	QObject::connect(this->actionPreferences, SIGNAL(triggered()), SLOT(openPreferencesDialog()));
	// About
	QObject::connect(this->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void	ZiaPluginLoader::createContextMenu(void)
{
	this->_contextMenu = new QMenu(this->treeWidget);
	this->_contextMenu->addAction(actionUnload);
	this->_contextMenu->addAction(actionReload);
	this->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(this->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(openContextMenu(const QPoint&)));
}

void	ZiaPluginLoader::readSettings(void)
{
	QSettings	settings("Epitech", "ZiaPluginLoader");

	settings.beginGroup("MainWindow");
	resize(settings.value("size", QSize(679, 267)).toSize());
	move(settings.value("pos", QPoint(444, 357)).toPoint());
	settings.endGroup();
}

void	ZiaPluginLoader::writeSettings(void)
{
	QSettings	settings("Epitech", "ZiaPluginLoader");

	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.endGroup();
	this->_preferences->writeSettings();
}

void	ZiaPluginLoader::connectParserSignals(void)
{
	if (this->_network != 0)
	{
		ParserLoader&	pl = this->_network->getParser();
		QObject::connect(&pl, SIGNAL(loginState(bool)), SLOT(processLoginState(bool)));
		QObject::connect(&pl, SIGNAL(pluginLoadState(bool, const QString&)), SLOT(processPluginLoadState(bool, const QString&)));
		QObject::connect(&pl, SIGNAL(unloadPluginState(bool, const QString&)), SLOT(processUnloadPluginState(bool, const QString&)));
		QObject::connect(&pl, SIGNAL(reloadPluginState(bool, const QString&)), SLOT(processReloadPluginState(bool, const QString&)));
		QObject::connect(&pl, SIGNAL(sendPluginList(const QStringList&)), SLOT(receivePluginList(const QStringList&)));
	}
}
