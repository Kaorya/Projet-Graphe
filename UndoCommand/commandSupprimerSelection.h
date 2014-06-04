#ifndef commandSupprimerSelection_h
#define commandSupprimerSelection_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandSupprimerSelection: public QUndoCommand
{

    std::vector<int> tabIndiceNoeud;
    std::vector<int> tabIndiceLien;

    ZoneDessin  *m_zone;

public:
    CommandSupprimerSelection(ZoneDessin* zone, std::vector<int> tabN, std::vector<int> tabL);

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