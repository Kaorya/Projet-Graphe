#ifndef commandSupprimerLien_h
#define commandSupprimerLien_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandSupprimerLien: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;

public:
    CommandSupprimerLien(ZoneDessin* zone, int i);

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