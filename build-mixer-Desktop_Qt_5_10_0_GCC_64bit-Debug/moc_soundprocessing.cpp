/****************************************************************************
** Meta object code from reading C++ file 'soundprocessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mixer/soundprocessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'soundprocessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SoundProcessing_t {
    QByteArrayData data[29];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SoundProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SoundProcessing_t qt_meta_stringdata_SoundProcessing = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SoundProcessing"
QT_MOC_LITERAL(1, 16, 11), // "lowEQChange"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "value"
QT_MOC_LITERAL(4, 35, 11), // "medEQChange"
QT_MOC_LITERAL(5, 47, 12), // "highEQChange"
QT_MOC_LITERAL(6, 60, 12), // "lowEQChange2"
QT_MOC_LITERAL(7, 73, 12), // "medEQChange2"
QT_MOC_LITERAL(8, 86, 13), // "highEQChange2"
QT_MOC_LITERAL(9, 100, 11), // "crossChange"
QT_MOC_LITERAL(10, 112, 12), // "crossChange2"
QT_MOC_LITERAL(11, 125, 13), // "startDownload"
QT_MOC_LITERAL(12, 139, 8), // "filename"
QT_MOC_LITERAL(13, 148, 13), // "downloadReady"
QT_MOC_LITERAL(14, 162, 4), // "play"
QT_MOC_LITERAL(15, 167, 8), // "download"
QT_MOC_LITERAL(16, 176, 7), // "Actions"
QT_MOC_LITERAL(17, 184, 7), // "WN_true"
QT_MOC_LITERAL(18, 192, 8), // "WN_false"
QT_MOC_LITERAL(19, 201, 3), // "low"
QT_MOC_LITERAL(20, 205, 3), // "med"
QT_MOC_LITERAL(21, 209, 4), // "high"
QT_MOC_LITERAL(22, 214, 5), // "cross"
QT_MOC_LITERAL(23, 220, 8), // "WN2_true"
QT_MOC_LITERAL(24, 229, 9), // "WN2_false"
QT_MOC_LITERAL(25, 239, 4), // "low2"
QT_MOC_LITERAL(26, 244, 4), // "med2"
QT_MOC_LITERAL(27, 249, 5), // "high2"
QT_MOC_LITERAL(28, 255, 6) // "cross2"

    },
    "SoundProcessing\0lowEQChange\0\0value\0"
    "medEQChange\0highEQChange\0lowEQChange2\0"
    "medEQChange2\0highEQChange2\0crossChange\0"
    "crossChange2\0startDownload\0filename\0"
    "downloadReady\0play\0download\0Actions\0"
    "WN_true\0WN_false\0low\0med\0high\0cross\0"
    "WN2_true\0WN2_false\0low2\0med2\0high2\0"
    "cross2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SoundProcessing[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       1,  106, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       5,    1,   80,    2, 0x06 /* Public */,
       6,    1,   83,    2, 0x06 /* Public */,
       7,    1,   86,    2, 0x06 /* Public */,
       8,    1,   89,    2, 0x06 /* Public */,
       9,    1,   92,    2, 0x06 /* Public */,
      10,    1,   95,    2, 0x06 /* Public */,
      11,    1,   98,    2, 0x06 /* Public */,
      13,    0,  101,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  102,    2, 0x0a /* Public */,
      15,    1,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,

 // enums: name, flags, count, data
      16, 0x0,   12,  110,

 // enum data: key, value
      17, uint(SoundProcessing::WN_true),
      18, uint(SoundProcessing::WN_false),
      19, uint(SoundProcessing::low),
      20, uint(SoundProcessing::med),
      21, uint(SoundProcessing::high),
      22, uint(SoundProcessing::cross),
      23, uint(SoundProcessing::WN2_true),
      24, uint(SoundProcessing::WN2_false),
      25, uint(SoundProcessing::low2),
      26, uint(SoundProcessing::med2),
      27, uint(SoundProcessing::high2),
      28, uint(SoundProcessing::cross2),

       0        // eod
};

void SoundProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SoundProcessing *_t = static_cast<SoundProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lowEQChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->medEQChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->highEQChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->lowEQChange2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->medEQChange2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->highEQChange2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->crossChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->crossChange2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->startDownload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->downloadReady(); break;
        case 10: _t->play(); break;
        case 11: _t->download((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::lowEQChange)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::medEQChange)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::highEQChange)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::lowEQChange2)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::medEQChange2)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::highEQChange2)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::crossChange)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::crossChange2)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::startDownload)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (SoundProcessing::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SoundProcessing::downloadReady)) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject SoundProcessing::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SoundProcessing.data,
      qt_meta_data_SoundProcessing,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SoundProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SoundProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SoundProcessing.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SoundProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SoundProcessing::lowEQChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SoundProcessing::medEQChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SoundProcessing::highEQChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SoundProcessing::lowEQChange2(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SoundProcessing::medEQChange2(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SoundProcessing::highEQChange2(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SoundProcessing::crossChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SoundProcessing::crossChange2(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SoundProcessing::startDownload(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SoundProcessing::downloadReady()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
