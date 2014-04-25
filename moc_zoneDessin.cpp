/****************************************************************************
** Meta object code from reading C++ file 'zoneDessin.h'
**
** Created: Fri Apr 25 15:05:07 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "zoneDessin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zoneDessin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ZoneDessin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      30,   28,   11,   11, 0x0a,
      68,   64,   11,   11, 0x0a,
      95,   64,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ZoneDessin[] = {
    "ZoneDessin\0\0nouveauGraphe()\0s\0"
    "recuperationNomNoeud(std::string)\0x,y\0"
    "recuperationCoord(int,int)\0"
    "mouvementNoeud(int,int)\0"
};

void ZoneDessin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ZoneDessin *_t = static_cast<ZoneDessin *>(_o);
        switch (_id) {
        case 0: _t->nouveauGraphe(); break;
        case 1: _t->recuperationNomNoeud((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->recuperationCoord((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->mouvementNoeud((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ZoneDessin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ZoneDessin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ZoneDessin,
      qt_meta_data_ZoneDessin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ZoneDessin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ZoneDessin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ZoneDessin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ZoneDessin))
        return static_cast<void*>(const_cast< ZoneDessin*>(this));
    return QWidget::qt_metacast(_clname);
}

int ZoneDessin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
