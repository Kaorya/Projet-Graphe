#ifndef commandCreerNoeud_h
#define commandCreerNoeud_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandCreerNoeud: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;

public:
    CommandCreerNoeud(ZoneDessin* zone, int i);

//public slots:
    virtual void undo();
    virtual void redo();

};


#endif

/*
  Liste des event

  eventDeleteLien
  eventDeleteSelection

  eventCreationLien

  eventChangementNomNoeud
  eventChangementNomLien

  eventChangementPositionNoeud
  eventChangementPositionTexteLien

  eventChangementStyleNoeud
  eventChangementStyleLien

*/