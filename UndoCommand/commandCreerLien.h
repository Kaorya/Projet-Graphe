#ifndef commandCreerLien_h
#define commandCreerLien_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandCreerLien: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;

public:
    CommandCreerLien(ZoneDessin* zone, int i);

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