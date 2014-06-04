#ifndef commandChangerPositionNoeud_h
#define commandChangerPositionNoeud_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandChangerPositionNoeud: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;
    QPoint anciennePos;
    QPoint nouvellePos;
    bool premierRedo;

public:
    CommandChangerPositionNoeud(ZoneDessin* zone, int i, QPoint viellePos, QPoint newPos);

//public slots:
    virtual void undo();
    virtual void redo();

};


#endif

/*
  Liste des event



*/