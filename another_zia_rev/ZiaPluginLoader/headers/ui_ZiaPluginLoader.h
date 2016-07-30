/********************************************************************************
** Form generated from reading ui file 'ZiaPluginLoader.ui'
**
** Created: Mon Sep 21 14:41:34 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ZIAPLUGINLOADER_H
#define UI_ZIAPLUGINLOADER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZiaPluginLoader
{
public:
    QAction *actionConnect;
    QAction *actionLoad;
    QAction *actionUnload;
    QAction *actionDisconnect;
    QAction *actionAboutQt;
    QAction *actionPreferences;
    QAction *actionQuit;
    QAction *actionReload;
    QAction *actionLogin;
    QAction *actionRefresh;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuPlugins;
    QMenu *menuAbout;
    QMenu *menuOptions;
    QMenu *menuAccount;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ZiaPluginLoader)
    {
        if (ZiaPluginLoader->objectName().isEmpty())
            ZiaPluginLoader->setObjectName(QString::fromUtf8("ZiaPluginLoader"));
        ZiaPluginLoader->resize(434, 268);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/images/zia_plugin_loader.png")), QIcon::Normal, QIcon::Off);
        ZiaPluginLoader->setWindowIcon(icon);
        actionConnect = new QAction(ZiaPluginLoader);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/images/connect.png")), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon1);
        actionLoad = new QAction(ZiaPluginLoader);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionLoad->setEnabled(false);
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/images/plugin_add.png")), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon2);
        actionUnload = new QAction(ZiaPluginLoader);
        actionUnload->setObjectName(QString::fromUtf8("actionUnload"));
        actionUnload->setEnabled(false);
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/images/plugin_delete.png")), QIcon::Normal, QIcon::Off);
        actionUnload->setIcon(icon3);
        actionDisconnect = new QAction(ZiaPluginLoader);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionDisconnect->setEnabled(false);
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/images/disconnect.png")), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon4);
        actionAboutQt = new QAction(ZiaPluginLoader);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        actionPreferences = new QAction(ZiaPluginLoader);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/images/options.png")), QIcon::Normal, QIcon::Off);
        actionPreferences->setIcon(icon5);
        actionQuit = new QAction(ZiaPluginLoader);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/images/quit.png")), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon6);
        actionReload = new QAction(ZiaPluginLoader);
        actionReload->setObjectName(QString::fromUtf8("actionReload"));
        actionReload->setEnabled(false);
        QIcon icon7;
        icon7.addPixmap(QPixmap(QString::fromUtf8(":/images/refresh.png")), QIcon::Normal, QIcon::Off);
        actionReload->setIcon(icon7);
        actionLogin = new QAction(ZiaPluginLoader);
        actionLogin->setObjectName(QString::fromUtf8("actionLogin"));
        actionLogin->setEnabled(false);
        actionRefresh = new QAction(ZiaPluginLoader);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        actionRefresh->setEnabled(false);
        actionRefresh->setIcon(icon7);
        centralwidget = new QWidget(ZiaPluginLoader);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeWidget = new QTreeWidget(centralwidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setEnabled(false);
        treeWidget->setSortingEnabled(true);
        treeWidget->setAnimated(true);
        treeWidget->setHeaderHidden(false);
        treeWidget->header()->setVisible(true);
        treeWidget->header()->setHighlightSections(false);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        ZiaPluginLoader->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ZiaPluginLoader);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 434, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuPlugins = new QMenu(menubar);
        menuPlugins->setObjectName(QString::fromUtf8("menuPlugins"));
        menuPlugins->setEnabled(true);
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuAccount = new QMenu(menubar);
        menuAccount->setObjectName(QString::fromUtf8("menuAccount"));
        ZiaPluginLoader->setMenuBar(menubar);
        statusbar = new QStatusBar(ZiaPluginLoader);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ZiaPluginLoader->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAccount->menuAction());
        menubar->addAction(menuPlugins->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionConnect);
        menuFile->addAction(actionDisconnect);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuPlugins->addAction(actionLoad);
        menuPlugins->addAction(actionUnload);
        menuPlugins->addAction(actionReload);
        menuPlugins->addAction(actionRefresh);
        menuAbout->addAction(actionAboutQt);
        menuOptions->addAction(actionPreferences);
        menuAccount->addAction(actionLogin);

        retranslateUi(ZiaPluginLoader);

        QMetaObject::connectSlotsByName(ZiaPluginLoader);
    } // setupUi

    void retranslateUi(QMainWindow *ZiaPluginLoader)
    {
        ZiaPluginLoader->setWindowTitle(QApplication::translate("ZiaPluginLoader", "ZiaPluginLoader", 0, QApplication::UnicodeUTF8));
        actionConnect->setText(QApplication::translate("ZiaPluginLoader", "&Connect", 0, QApplication::UnicodeUTF8));
        actionConnect->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("ZiaPluginLoader", "&Load plugin", 0, QApplication::UnicodeUTF8));
        actionLoad->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionUnload->setText(QApplication::translate("ZiaPluginLoader", "&Unload selected plugin", 0, QApplication::UnicodeUTF8));
        actionUnload->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+U", 0, QApplication::UnicodeUTF8));
        actionDisconnect->setText(QApplication::translate("ZiaPluginLoader", "&Disconnect", 0, QApplication::UnicodeUTF8));
        actionDisconnect->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+D", 0, QApplication::UnicodeUTF8));
        actionAboutQt->setText(QApplication::translate("ZiaPluginLoader", "&About Qt", 0, QApplication::UnicodeUTF8));
        actionAboutQt->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionPreferences->setText(QApplication::translate("ZiaPluginLoader", "&Preferences", 0, QApplication::UnicodeUTF8));
        actionPreferences->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("ZiaPluginLoader", "&Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionReload->setText(QApplication::translate("ZiaPluginLoader", "&Reload selected plugin", 0, QApplication::UnicodeUTF8));
        actionReload->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        actionLogin->setText(QApplication::translate("ZiaPluginLoader", "&Login", 0, QApplication::UnicodeUTF8));
        actionLogin->setShortcut(QApplication::translate("ZiaPluginLoader", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionRefresh->setText(QApplication::translate("ZiaPluginLoader", "&Refresh list", 0, QApplication::UnicodeUTF8));
        actionRefresh->setShortcut(QApplication::translate("ZiaPluginLoader", "F5", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("ZiaPluginLoader", "Path", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("ZiaPluginLoader", "Version", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("ZiaPluginLoader", "Name", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("ZiaPluginLoader", "&File", 0, QApplication::UnicodeUTF8));
        menuPlugins->setTitle(QApplication::translate("ZiaPluginLoader", "&Plugins", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("ZiaPluginLoader", "&About", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("ZiaPluginLoader", "&Options", 0, QApplication::UnicodeUTF8));
        menuAccount->setTitle(QApplication::translate("ZiaPluginLoader", "&Account", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ZiaPluginLoader: public Ui_ZiaPluginLoader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZIAPLUGINLOADER_H
