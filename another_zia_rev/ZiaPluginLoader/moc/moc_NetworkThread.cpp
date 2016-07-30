/****************************************************************************
** Meta object code from reading C++ file 'NetworkThread.h'
**
** Created: Mon Sep 21 14:41:47 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headers/NetworkThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetworkThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetworkThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      40,   14,   14,   14, 0x05,
      64,   58,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NetworkThread[] = {
    "NetworkThread\0\0sendToStatusBar(QString)\0"
    "stateChanged(int)\0error\0error(const char*)\0"
    "stop()\0"
};

const QMetaObject NetworkThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetworkThread,
      qt_meta_data_NetworkThread, 0 }
};

const QMetaObject *NetworkThread::metaObject() const
{
    return &staticMetaObject;
}

void *NetworkThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkThread))
        return static_cast<void*>(const_cast< NetworkThread*>(this));
    return QObject::qt_metacast(_clname);
}

int NetworkThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendToStatusBar((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: error((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 3: stop(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NetworkThread::sendToStatusBar(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetworkThread::stateChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetworkThread::error(const char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
