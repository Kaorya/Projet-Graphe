#ifndef commandChangerCouleurLien_h
#define commandChangerCouleurLien_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandChangerCouleurLien: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;
    QColor ancienneCouleurLigne;
    QColor ancienneCouleurTexte;

    QColor nouvelleCouleurLigne;
    QColor nouvelleCouleurTexte;



public:
    CommandChangerCouleurLien(ZoneDessin* zone, int i, QColor aLigne, QColor aTexte, QColor nLigne, QColor nTexte);

//public slots:
    virtual void undo();
    virtual void redo();

};


#endif

/*
  Liste des event


  eventChangementNomNoeud
  eventChangementNomLien

  eventChangementPositionNoeud
  eventChangementPositionTexteLien

  eventChangementStyleNoeud
  eventChangementStyleLien

*/