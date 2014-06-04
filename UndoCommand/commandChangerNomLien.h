#ifndef commandChangerNomLien_h
#define commandChangerNomLien_h

#include <vector>
#include <QtCore>
#include <Qt/QtGui>
#include "../zoneDessin.h"
#include <QUndoCommand>

class ZoneDessin;

class CommandChangerNomLien: public QUndoCommand
{

    int indice;
    ZoneDessin  *m_zone;
    QString ancienNom;
    QString nouveauNom;

public:
    CommandChangerNomLien(ZoneDessin* zone, int i, QString vieuxNom, QString newNom);

//public slots:
    virtual void undo();
    virtual void redo();

};


#endif

/*
  Liste des event



*/