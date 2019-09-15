/****************************************************************************
** Meta object code from reading C++ file 'slippymap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../slippymap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slippymap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SlippyMap_t {
    QByteArrayData data[15];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SlippyMap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SlippyMap_t qt_meta_stringdata_SlippyMap = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SlippyMap"
QT_MOC_LITERAL(1, 10, 7), // "updated"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "rect"
QT_MOC_LITERAL(4, 24, 17), // "handleNetworkData"
QT_MOC_LITERAL(5, 42, 14), // "QNetworkReply*"
QT_MOC_LITERAL(6, 57, 5), // "reply"
QT_MOC_LITERAL(7, 63, 8), // "download"
QT_MOC_LITERAL(8, 72, 17), // "tileForCoordinate"
QT_MOC_LITERAL(9, 90, 9), // "CGeoPoint"
QT_MOC_LITERAL(10, 100, 6), // "geoPos"
QT_MOC_LITERAL(11, 107, 4), // "zoom"
QT_MOC_LITERAL(12, 112, 14), // "GeoPosFromTile"
QT_MOC_LITERAL(13, 127, 2), // "tx"
QT_MOC_LITERAL(14, 130, 2) // "ty"

    },
    "SlippyMap\0updated\0\0rect\0handleNetworkData\0"
    "QNetworkReply*\0reply\0download\0"
    "tileForCoordinate\0CGeoPoint\0geoPos\0"
    "zoom\0GeoPosFromTile\0tx\0ty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SlippyMap[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,
       8,    2,   46,    2, 0x08 /* Private */,
      12,    3,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QRect,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::QPointF, 0x80000000 | 9, QMetaType::Int,   10,   11,
    0x80000000 | 9, QMetaType::QReal, QMetaType::QReal, QMetaType::Int,   13,   14,   11,

       0        // eod
};

void SlippyMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SlippyMap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated((*reinterpret_cast< const QRect(*)>(_a[1]))); break;
        case 1: _t->handleNetworkData((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->download(); break;
        case 3: { QPointF _r = _t->tileForCoordinate((*reinterpret_cast< CGeoPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPointF*>(_a[0]) = std::move(_r); }  break;
        case 4: { CGeoPoint _r = _t->GeoPosFromTile((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< CGeoPoint*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SlippyMap::*)(const QRect & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SlippyMap::updated)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SlippyMap::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SlippyMap.data,
    qt_meta_data_SlippyMap,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SlippyMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SlippyMap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SlippyMap.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SlippyMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SlippyMap::updated(const QRect & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
