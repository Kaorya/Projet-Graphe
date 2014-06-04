#ifndef commandChangerNomNoeud_h
#define commandChangerNomNoeud_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandChangerNomNoeud: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;
    QString ancienNom;
    QString nouveauNom;

public:
    CommandChangerNomNoeud(ZoneDessin* zone, int i, QString vieuxNom, QString newNom);

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