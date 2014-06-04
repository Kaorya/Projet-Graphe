#ifndef MyQScene_h
#define MyQScene_h

#include <QImage>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QString>
#include <QVector>
#include "noeud.h"
#include "lien.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRectF>
#include <QtGui/QScrollBar> 

class MyQView: public QGraphicsView
{


        Q_OBJECT

public:

        MyQView(QGraphicsScene *scene, QWidget* parent = 0);
        MyQView();
        QSize sizeHint() const;
        virtual ~MyQView();



signals:
    void envoieCoord(int x, int y);
    void envoieClicDroit(int x, int y);
    void mouvementSouris(int x, int y);
    void doubleClic(int x, int y);
    void relachement(int x, int y);
    void wheelAction(int hori, int verti);


protected:

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

    bool eventFilter(QObject * obj, QEvent * event);
    virtual void wheelEvent(QWheelEvent* event);
};

#endif
