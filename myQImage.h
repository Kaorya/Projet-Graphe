#ifndef MyQImage_h
#define MyQImage_h

#include <QImage>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QString>
#include <QVector>
#include "noeud.h"
#include "lien.h"

class MyQImage: public QWidget
{
public:
        QImage *image;
        QImage imageSave;
        int maxX;
        int maxY;
        int minX;
        int minY;

        Q_OBJECT
public:
        MyQImage(int width, int height, QImage::Format format, QWidget* parent = 0);
        QSize sizeHint() const;
        virtual ~MyQImage();
        void dessineRect(int x, int y, int width, int height, QColor cBordure, QColor cFond);
        void dessineLigne(int x1, int y1, int x2, int y2, QColor c);
        void dessineTexte(int x, int y, QString s, int width, int height, QColor c);
        void dessineNoeud(Noeud n);
        void dessineLien(Lien l, int x1, int x2, int y1, int y2);
        void dessineTexteLien(Lien l, int x1, int x2, int y1, int y2);
        QImage* getImage() const;
        MyQImage();
        void setImage(QImage i);


signals:
    void envoieCoord(int x, int y);
    void envoieClicDroit(int x, int y);
    void mouvementSouris(int x, int y);
    void doubleClic(int x, int y);

private slots:

protected:

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void resizeEvent (QResizeEvent *e);

};

#endif
