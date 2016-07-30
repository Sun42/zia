/****************************************************************************
** Meta object code from reading C++ file 'ZiaPluginLoader.h'
**
** Created: Mon Sep 21 14:41:49 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headers/ZiaPluginLoader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZiaPluginLoader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ZiaPluginLoader[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      27,   16,   16,   16, 0x08,
      40,   16,   16,   16, 0x08,
      53,   16,   16,   16, 0x08,
      68,   16,   16,   16, 0x08,
      83,   16,   16,   16, 0x08,
      97,   16,   16,   16, 0x08,
     105,   16,   16,   16, 0x08,
     124,   16,   16,   16, 0x08,
     148,   16,   16,   16, 0x08,
     182,   16,   16,   16, 0x08,
     210,   16,   16,   16, 0x08,
     242,  234,   16,   16, 0x08,
     275,  266,   16,   16, 0x08,
     312,  266,   16,   16, 0x08,
     351,  266,   16,   16, 0x08,
     390,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ZiaPluginLoader[] = {
    "ZiaPluginLoader\0\0connect()\0disconnect()\0"
    "loadPlugin()\0unloadPlugin()\0reloadPlugin()\0"
    "refreshList()\0login()\0updateActions(int)\0"
    "openPreferencesDialog()\0"
    "processNetworkErrors(const char*)\0"
    "displayInStatusBar(QString)\0"
    "openContextMenu(QPoint)\0success\0"
    "processLoginState(bool)\0success,\0"
    "processPluginLoadState(bool,QString)\0"
    "processUnloadPluginState(bool,QString)\0"
    "processReloadPluginState(bool,QString)\0"
    "receivePluginList(QStringList)\0"
};

const QMetaObject ZiaPluginLoader::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ZiaPluginLoader,
      qt_meta_data_ZiaPluginLoader, 0 }
};

const QMetaObject *ZiaPluginLoader::metaObject() const
{
    return &staticMetaObject;
}

void *ZiaPluginLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ZiaPluginLoader))
        return static_cast<void*>(const_cast< ZiaPluginLoader*>(this));
    if (!strcmp(_clname, "Ui_ZiaPluginLoader"))
        return static_cast< Ui_ZiaPluginLoader*>(const_cast< ZiaPluginLoader*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ZiaPluginLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connect(); break;
        case 1: disconnect(); break;
        case 2: loadPlugin(); break;
        case 3: unloadPlugin(); break;
        case 4: reloadPlugin(); break;
        case 5: refreshList(); break;
        case 6: login(); break;
        case 7: updateActions((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: openPreferencesDialog(); break;
        case 9: processNetworkErrors((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 10: displayInStatusBar((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: openContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: processLoginState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: processPluginLoadState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: processUnloadPluginState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: processReloadPluginState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 16: receivePluginList((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
