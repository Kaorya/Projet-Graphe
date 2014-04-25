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
        void dessineRect(int x, int y, int width, int height);
        void dessineLigne(int x1, int y1, int x2, int y2);
        void dessineTexte(int x, int y, QString s, int width, int height);
        void dessineNoeud(Noeud n);
        void dessineLien(Lien l);
        void dessineTexteLien(Lien l);
        void dessinerCadre();
        QImage* getImage() const;

signals:
    void envoieCoord(int x, int y);
    void mouvementSouris(int x, int y);

private slots:

protected:

    virtual void mousePressEvent(QMouseEvent * e);
    virtual void paintEvent(QPaintEvent *e);
    virtual void mouseMoveEvent(QMouseEvent * e);


};

#endif
