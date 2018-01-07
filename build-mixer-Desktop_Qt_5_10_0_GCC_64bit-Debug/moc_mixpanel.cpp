/****************************************************************************
** Meta object code from reading C++ file 'mixpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mixer/mixpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mixpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MixPanel_t {
    QByteArrayData data[20];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MixPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MixPanel_t qt_meta_stringdata_MixPanel = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MixPanel"
QT_MOC_LITERAL(1, 9, 10), // "timeChange"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "time"
QT_MOC_LITERAL(4, 26, 11), // "writeToFile"
QT_MOC_LITERAL(5, 38, 4), // "type"
QT_MOC_LITERAL(6, 43, 8), // "position"
QT_MOC_LITERAL(7, 52, 5), // "value"
QT_MOC_LITERAL(8, 58, 9), // "fileReady"
QT_MOC_LITERAL(9, 68, 9), // "playPause"
QT_MOC_LITERAL(10, 78, 8), // "playStop"
QT_MOC_LITERAL(11, 87, 9), // "loadAudio"
QT_MOC_LITERAL(12, 97, 8), // "filename"
QT_MOC_LITERAL(13, 106, 10), // "readBuffer"
QT_MOC_LITERAL(14, 117, 14), // "finishDecoding"
QT_MOC_LITERAL(15, 132, 16), // "enableWhiteNoise"
QT_MOC_LITERAL(16, 149, 17), // "disableWhiteNoise"
QT_MOC_LITERAL(17, 167, 5), // "lowEQ"
QT_MOC_LITERAL(18, 173, 5), // "medEQ"
QT_MOC_LITERAL(19, 179, 6) // "highEQ"

    },
    "MixPanel\0timeChange\0\0time\0writeToFile\0"
    "type\0position\0value\0fileReady\0playPause\0"
    "playStop\0loadAudio\0filename\0readBuffer\0"
    "finishDecoding\0enableWhiteNoise\0"
    "disableWhiteNoise\0lowEQ\0medEQ\0highEQ"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MixPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    3,   82,    2, 0x06 /* Public */,
       8,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   90,    2, 0x0a /* Public */,
      10,    0,   91,    2, 0x0a /* Public */,
      11,    1,   92,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,
      16,    0,   98,    2, 0x0a /* Public */,
      17,    1,   99,    2, 0x0a /* Public */,
      18,    1,  102,    2, 0x0a /* Public */,
      19,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong, QMetaType::ULongLong,    5,    6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void MixPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MixPanel *_t = static_cast<MixPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->writeToFile((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3]))); break;
        case 2: _t->fileReady(); break;
        case 3: _t->playPause(); break;
        case 4: _t->playStop(); break;
        case 5: _t->loadAudio((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->readBuffer(); break;
        case 7: _t->finishDecoding(); break;
        case 8: _t->enableWhiteNoise(); break;
        case 9: _t->disableWhiteNoise(); break;
        case 10: _t->lowEQ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->medEQ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->highEQ((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MixPanel::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixPanel::timeChange)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MixPanel::*_t)(quint64 , quint64 , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixPanel::writeToFile)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MixPanel::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixPanel::fileReady)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MixPanel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MixPanel.data,
      qt_meta_data_MixPanel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MixPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MixPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MixPanel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MixPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MixPanel::timeChange(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MixPanel::writeToFile(quint64 _t1, quint64 _t2, quint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MixPanel::fileReady()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
