/****************************************************************************
** Meta object code from reading C++ file 'MyMainWindows.h'
**
** Created: Wed Jun 4 21:07:28 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyMainWindows.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyMainWindows.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyMainWindows[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      48,   15,   14,   14, 0x05,
      74,   15,   14,   14, 0x05,
     100,   15,   14,   14, 0x05,
     125,   15,   14,   14, 0x05,
     155,   15,   14,   14, 0x05,
     184,   15,   14,   14, 0x05,
     208,   15,   14,   14, 0x05,
     253,  236,   14,   14, 0x05,
     307,  305,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     335,   15,   14,   14, 0x08,
     362,   14,   14,   14, 0x08,
     384,   14,   14,   14, 0x08,
     401,   14,   14,   14, 0x08,
     418,   14,   14,   14, 0x08,
     434,   14,   14,   14, 0x08,
     453,   14,   14,   14, 0x08,
     471,   14,   14,   14, 0x08,
     486,   14,   14,   14, 0x08,
     505,   14,   14,   14, 0x08,
     518,   14,   14,   14, 0x08,
     530,   14,   14,   14, 0x08,
     562,   14,   14,   14, 0x08,
     589,   14,   14,   14, 0x08,
     610,   14,   14,   14, 0x08,
     628,   14,   14,   14, 0x08,
     654,   14,   14,   14, 0x08,
     675,   14,   14,   14, 0x08,
     692,   14,   14,   14, 0x08,
     706,   14,   14,   14, 0x08,
     722,   14,   14,   14, 0x08,
     739,  735,   14,   14, 0x08,
     762,  735,   14,   14, 0x08,
     789,   14,   14,   14, 0x08,
     809,   14,   14,   14, 0x08,
     828,  735,   14,   14, 0x08,
     853,  735,   14,   14, 0x08,
     877,   14,   14,   14, 0x08,
     890,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyMainWindows[] = {
    "MyMainWindows\0\0d\0signalDNouveauGraphe(QDialog*)\0"
    "signalDImporter(QDialog*)\0"
    "signalDExporter(QDialog*)\0"
    "signalDQuitter(QDialog*)\0"
    "signalDNouveauNoeud(QDialog*)\0"
    "signalDNouveauLien(QDialog*)\0"
    "signalDChange(QDialog*)\0"
    "signalDChangeLien(QDialog*)\0"
    "tabNoeud,tabLien\0"
    "signalSupression(std::vector<int>,std::vector<int>)\0"
    "s\0envoieNomNoeud(std::string)\0"
    "apparitionDialog(QDialog*)\0"
    "appelDNouveauGraphe()\0appelDImporter()\0"
    "appelDExporter()\0appelDQuitter()\0"
    "appelDCreerNoeud()\0appelDCreerLien()\0"
    "appelDChange()\0appelDChangeLien()\0"
    "ajoutNoeud()\0ajoutLien()\0"
    "appelDSaveBeforeNouveauGraphe()\0"
    "appelDSaveBeforeImporter()\0"
    "appelDSaveExporter()\0appelDSaveImage()\0"
    "appelDSaveBeforeQuitter()\0"
    "appelDOpenImporter()\0emissionSignal()\0"
    "enSelection()\0enDeplacement()\0"
    "annulation()\0x,y\0affichageMenu(int,int)\0"
    "affichageMenuLien(int,int)\0"
    "changerStyleNoeud()\0changerStyleLien()\0"
    "changerNomNoeud(int,int)\0"
    "changerNomLien(int,int)\0changerNom()\0"
    "suppression()\0"
};

void MyMainWindows::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyMainWindows *_t = static_cast<MyMainWindows *>(_o);
        switch (_id) {
        case 0: _t->signalDNouveauGraphe((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 1: _t->signalDImporter((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 2: _t->signalDExporter((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 3: _t->signalDQuitter((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 4: _t->signalDNouveauNoeud((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 5: _t->signalDNouveauLien((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 6: _t->signalDChange((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 7: _t->signalDChangeLien((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 8: _t->signalSupression((*reinterpret_cast< std::vector<int>(*)>(_a[1])),(*reinterpret_cast< std::vector<int>(*)>(_a[2]))); break;
        case 9: _t->envoieNomNoeud((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 10: _t->apparitionDialog((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 11: _t->appelDNouveauGraphe(); break;
        case 12: _t->appelDImporter(); break;
        case 13: _t->appelDExporter(); break;
        case 14: _t->appelDQuitter(); break;
        case 15: _t->appelDCreerNoeud(); break;
        case 16: _t->appelDCreerLien(); break;
        case 17: _t->appelDChange(); break;
        case 18: _t->appelDChangeLien(); break;
        case 19: _t->ajoutNoeud(); break;
        case 20: _t->ajoutLien(); break;
        case 21: _t->appelDSaveBeforeNouveauGraphe(); break;
        case 22: _t->appelDSaveBeforeImporter(); break;
        case 23: _t->appelDSaveExporter(); break;
        case 24: _t->appelDSaveImage(); break;
        case 25: _t->appelDSaveBeforeQuitter(); break;
        case 26: _t->appelDOpenImporter(); break;
        case 27: _t->emissionSignal(); break;
        case 28: _t->enSelection(); break;
        case 29: _t->enDeplacement(); break;
        case 30: _t->annulation(); break;
        case 31: _t->affichageMenu((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 32: _t->affichageMenuLien((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 33: _t->changerStyleNoeud(); break;
        case 34: _t->changerStyleLien(); break;
        case 35: _t->changerNomNoeud((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 36: _t->changerNomLien((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 37: _t->changerNom(); break;
        case 38: _t->suppression(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyMainWindows::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyMainWindows::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyMainWindows,
      qt_meta_data_MyMainWindows, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyMainWindows::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyMainWindows::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyMainWindows::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyMainWindows))
        return static_cast<void*>(const_cast< MyMainWindows*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyMainWindows::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    return _id;
}

// SIGNAL 0
void MyMainWindows::signalDNouveauGraphe(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyMainWindows::signalDImporter(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyMainWindows::signalDExporter(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyMainWindows::signalDQuitter(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyMainWindows::signalDNouveauNoeud(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyMainWindows::signalDNouveauLien(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MyMainWindows::signalDChange(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MyMainWindows::signalDChangeLien(QDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MyMainWindows::signalSupression(std::vector<int> _t1, std::vector<int> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MyMainWindows::envoieNomNoeud(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
