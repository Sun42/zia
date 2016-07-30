/****************************************************************************
** Meta object code from reading C++ file 'ParserLoader.h'
**
** Created: Mon Sep 21 14:41:51 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headers/ParserLoader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParserLoader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParserLoader[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x05,
      59,   39,   13,   13, 0x05,
      89,   14,   13,   13, 0x25,
     111,   39,   13,   13, 0x05,
     143,   14,   13,   13, 0x25,
     167,   39,   13,   13, 0x05,
     199,   14,   13,   13, 0x25,
     223,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ParserLoader[] = {
    "ParserLoader\0\0success\0loginState(bool)\0"
    "success,explanation\0pluginLoadState(bool,QString)\0"
    "pluginLoadState(bool)\0"
    "unloadPluginState(bool,QString)\0"
    "unloadPluginState(bool)\0"
    "reloadPluginState(bool,QString)\0"
    "reloadPluginState(bool)\0"
    "sendPluginList(QStringList)\0"
};

const QMetaObject ParserLoader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ParserLoader,
      qt_meta_data_ParserLoader, 0 }
};

const QMetaObject *ParserLoader::metaObject() const
{
    return &staticMetaObject;
}

void *ParserLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParserLoader))
        return static_cast<void*>(const_cast< ParserLoader*>(this));
    return QObject::qt_metacast(_clname);
}

int ParserLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loginState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: pluginLoadState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: pluginLoadState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: unloadPluginState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: unloadPluginState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: reloadPluginState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: reloadPluginState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: sendPluginList((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ParserLoader::loginState(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ParserLoader::pluginLoadState(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, 2, _a);
}

// SIGNAL 3
void ParserLoader::unloadPluginState(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, 4, _a);
}

// SIGNAL 5
void ParserLoader::reloadPluginState(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, 6, _a);
}

// SIGNAL 7
void ParserLoader::sendPluginList(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
