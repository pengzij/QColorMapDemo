/****************************************************************************
** Meta object code from reading C++ file 'udpconnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../udpconnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpconnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UDP_t {
    QByteArrayData data[15];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UDP_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UDP_t qt_meta_stringdata_UDP = {
    {
QT_MOC_LITERAL(0, 0, 3), // "UDP"
QT_MOC_LITERAL(1, 4, 13), // "sendWriteAble"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 18), // "sendWriteAble_wave"
QT_MOC_LITERAL(4, 38, 17), // "sendUpdataHeatmap"
QT_MOC_LITERAL(5, 56, 10), // "sendReinit"
QT_MOC_LITERAL(6, 67, 8), // "sendExit"
QT_MOC_LITERAL(7, 76, 14), // "readWLDataSlot"
QT_MOC_LITERAL(8, 91, 14), // "readSPDataSlot"
QT_MOC_LITERAL(9, 106, 13), // "restoreSPData"
QT_MOC_LITERAL(10, 120, 13), // "restoreWLData"
QT_MOC_LITERAL(11, 134, 13), // "flashFileName"
QT_MOC_LITERAL(12, 148, 18), // "flashFileName_wave"
QT_MOC_LITERAL(13, 167, 6), // "reSend"
QT_MOC_LITERAL(14, 174, 4) // "exit"

    },
    "UDP\0sendWriteAble\0\0sendWriteAble_wave\0"
    "sendUpdataHeatmap\0sendReinit\0sendExit\0"
    "readWLDataSlot\0readSPDataSlot\0"
    "restoreSPData\0restoreWLData\0flashFileName\0"
    "flashFileName_wave\0reSend\0exit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UDP[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UDP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UDP *_t = static_cast<UDP *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendWriteAble(); break;
        case 1: _t->sendWriteAble_wave(); break;
        case 2: _t->sendUpdataHeatmap(); break;
        case 3: _t->sendReinit(); break;
        case 4: _t->sendExit(); break;
        case 5: _t->readWLDataSlot(); break;
        case 6: _t->readSPDataSlot(); break;
        case 7: _t->restoreSPData(); break;
        case 8: _t->restoreWLData(); break;
        case 9: _t->flashFileName(); break;
        case 10: _t->flashFileName_wave(); break;
        case 11: _t->reSend(); break;
        case 12: _t->exit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UDP::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UDP::sendWriteAble)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UDP::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UDP::sendWriteAble_wave)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (UDP::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UDP::sendUpdataHeatmap)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (UDP::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UDP::sendReinit)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (UDP::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UDP::sendExit)) {
                *result = 4;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UDP::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UDP.data,
      qt_meta_data_UDP,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UDP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UDP::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UDP.stringdata0))
        return static_cast<void*>(const_cast< UDP*>(this));
    return QObject::qt_metacast(_clname);
}

int UDP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void UDP::sendWriteAble()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void UDP::sendWriteAble_wave()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void UDP::sendUpdataHeatmap()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void UDP::sendReinit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void UDP::sendExit()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
