#ifndef commandChangerCouleurNoeud_h
#define commandChangerCouleurNoeud_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandChangerCouleurNoeud: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;
    QColor ancienneCouleurBordure;
    QColor ancienneCouleurTexte;
    QColor ancienneCouleurFond;

    QColor nouvelleCouleurFond;
    QColor nouvelleCouleurBordure;
    QColor nouvelleCouleurTexte;



public:
    CommandChangerCouleurNoeud(ZoneDessin* zone, int i, QColor aBordure, QColor aTexte, QColor aFond, QColor nBordure, QColor nTexte, QColor nFond);

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