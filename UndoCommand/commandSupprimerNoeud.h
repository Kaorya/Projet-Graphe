#ifndef commandSupprimerNoeud_h
#define commandSupprimerNoeud_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandSupprimerNoeud: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;

public:
    CommandSupprimerNoeud(ZoneDessin* zone, int i);

//public slots:
    virtual void undo();
    virtual void redo();

};


#endif

/*
  Liste des event

  eventDeleteSelection

  eventChangementNomNoeud
  eventChangementNomLien

  eventChangementPositionNoeud
  eventChangementPositionTexteLien

  eventChangementStyleNoeud
  eventChangementStyleLien

*/