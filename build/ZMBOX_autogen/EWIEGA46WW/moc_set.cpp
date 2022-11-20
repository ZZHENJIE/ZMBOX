/****************************************************************************
** Meta object code from reading C++ file 'set.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../set.h"
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'set.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SET_t {
    const uint offsetsAndSize[16];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SET_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SET_t qt_meta_stringdata_SET = {
    {
QT_MOC_LITERAL(0, 3), // "SET"
QT_MOC_LITERAL(4, 28), // "on_Select_Background_clicked"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 19), // "on_Open_Dir_clicked"
QT_MOC_LITERAL(54, 25), // "on_Log_Pushbutton_clicked"
QT_MOC_LITERAL(80, 19), // "on_Exit_Log_clicked"
QT_MOC_LITERAL(100, 15), // "on_Open_clicked"
QT_MOC_LITERAL(116, 16) // "on_Close_clicked"

    },
    "SET\0on_Select_Background_clicked\0\0"
    "on_Open_Dir_clicked\0on_Log_Pushbutton_clicked\0"
    "on_Exit_Log_clicked\0on_Open_clicked\0"
    "on_Close_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SET[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SET::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SET *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_Select_Background_clicked(); break;
        case 1: _t->on_Open_Dir_clicked(); break;
        case 2: _t->on_Log_Pushbutton_clicked(); break;
        case 3: _t->on_Exit_Log_clicked(); break;
        case 4: _t->on_Open_clicked(); break;
        case 5: _t->on_Close_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject SET::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_SET.offsetsAndSize,
    qt_meta_data_SET,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SET_t
, QtPrivate::TypeAndForceComplete<SET, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *SET::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SET::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SET.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SET::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
