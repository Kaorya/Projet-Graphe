/****************************************************************************
** Meta object code from reading C++ file 'zoneDessin.h'
**
** Created: Thu May 22 23:23:47 2014
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
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      27,   11,   11,   11, 0x05,
      45,   41,   11,   11, 0x05,
      67,   41,   11,   11, 0x05,
      93,   41,   11,   11, 0x05,
     118,   41,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     142,   11,   11,   11, 0x0a,
     160,  158,   11,   11, 0x0a,
     194,   41,   11,   11, 0x0a,
     221,   41,   11,   11, 0x0a,
     245,   41,   11,   11, 0x0a,
     264,   41,   11,   11, 0x0a,
     301,  284,   11,   11, 0x0a,
     348,   41,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ZoneDessin[] = {
    "ZoneDessin\0\0nouveauNoeud()\0nouveauLien()\0"
    "x,y\0afficherMenu(int,int)\0"
    "afficherMenuLien(int,int)\0"
    "changerNomNoeud(int,int)\0"
    "changerNomLien(int,int)\0nouveauGraphe()\0"
    "s\0recuperationNomNoeud(std::string)\0"
    "recuperationCoord(int,int)\0"
    "mouvementNoeud(int,int)\0clicDroit(int,int)\0"
    "doubleClic(int,int)\0tabNoeud,tabLien\0"
    "suppression(std::vector<int>,std::vector<int>)\0"
    "releaseSouris(int,int)\0"
};

void ZoneDessin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ZoneDessin *_t = static_cast<ZoneDessin *>(_o);
        switch (_id) {
        case 0: _t->nouveauNoeud(); break;
        case 1: _t->nouveauLien(); break;
        case 2: _t->afficherMenu((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->afficherMenuLien((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->changerNomNoeud((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->changerNomLien((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->nouveauGraphe(); break;
        case 7: _t->recuperationNomNoeud((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: _t->recuperationCoord((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->mouvementNoeud((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->clicDroit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->doubleClic((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->suppression((*reinterpret_cast< std::vector<int>(*)>(_a[1])),(*reinterpret_cast< std::vector<int>(*)>(_a[2]))); break;
        case 13: _t->releaseSouris((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ZoneDessin::nouveauNoeud()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ZoneDessin::nouveauLien()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ZoneDessin::afficherMenu(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ZoneDessin::afficherMenuLien(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ZoneDessin::changerNomNoeud(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ZoneDessin::changerNomLien(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
