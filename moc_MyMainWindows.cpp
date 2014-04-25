/****************************************************************************
** Meta object code from reading C++ file 'MyMainWindows.h'
**
** Created: Fri Apr 25 15:05:05 2014
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
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      48,   15,   14,   14, 0x05,
      74,   15,   14,   14, 0x05,
     100,   15,   14,   14, 0x05,
     125,   15,   14,   14, 0x05,
     155,   15,   14,   14, 0x05,
     186,  184,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     214,   15,   14,   14, 0x08,
     241,   14,   14,   14, 0x08,
     263,   14,   14,   14, 0x08,
     280,   14,   14,   14, 0x08,
     297,   14,   14,   14, 0x08,
     313,   14,   14,   14, 0x08,
     332,   14,   14,   14, 0x08,
     350,   14,   14,   14, 0x08,
     363,   14,   14,   14, 0x08,
     375,   14,   14,   14, 0x08,
     407,   14,   14,   14, 0x08,
     434,   14,   14,   14, 0x08,
     455,   14,   14,   14, 0x08,
     473,   14,   14,   14, 0x08,
     499,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyMainWindows[] = {
    "MyMainWindows\0\0d\0signalDNouveauGraphe(QDialog*)\0"
    "signalDImporter(QDialog*)\0"
    "signalDExporter(QDialog*)\0"
    "signalDQuitter(QDialog*)\0"
    "signalDNouveauNoeud(QDialog*)\0"
    "signalDNouveauLien(QDialog*)\0s\0"
    "envoieNomNoeud(std::string)\0"
    "apparitionDialog(QDialog*)\0"
    "appelDNouveauGraphe()\0appelDImporter()\0"
    "appelDExporter()\0appelDQuitter()\0"
    "appelDCreerNoeud()\0appelDCreerLien()\0"
    "ajoutNoeud()\0ajoutLien()\0"
    "appelDSaveBeforeNouveauGraphe()\0"
    "appelDSaveBeforeImporter()\0"
    "appelDSaveExporter()\0appelDSaveImage()\0"
    "appelDSaveBeforeQuitter()\0"
    "appelDOpenImporter()\0"
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
        case 6: _t->envoieNomNoeud((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 7: _t->apparitionDialog((*reinterpret_cast< QDialog*(*)>(_a[1]))); break;
        case 8: _t->appelDNouveauGraphe(); break;
        case 9: _t->appelDImporter(); break;
        case 10: _t->appelDExporter(); break;
        case 11: _t->appelDQuitter(); break;
        case 12: _t->appelDCreerNoeud(); break;
        case 13: _t->appelDCreerLien(); break;
        case 14: _t->ajoutNoeud(); break;
        case 15: _t->ajoutLien(); break;
        case 16: _t->appelDSaveBeforeNouveauGraphe(); break;
        case 17: _t->appelDSaveBeforeImporter(); break;
        case 18: _t->appelDSaveExporter(); break;
        case 19: _t->appelDSaveImage(); break;
        case 20: _t->appelDSaveBeforeQuitter(); break;
        case 21: _t->appelDOpenImporter(); break;
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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
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
void MyMainWindows::envoieNomNoeud(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
