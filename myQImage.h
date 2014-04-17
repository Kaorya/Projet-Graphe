#ifndef MyQImage_h
#define MyQImage_h

#include <QImage>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QString>
#include <QVector>

class MyQImage: public QWidget
{
public:
        QImage *image;
        QImage imageSave;
        QVector<QRect> tabRect;
        int maxX;
        int maxY;
        int minX;
        int minY;

        Q_OBJECT
public:
        MyQImage(int width, int height, QImage::Format format, QWidget* parent = 0);
        QSize sizeHint() const;
        virtual ~MyQImage();
        void dessineRect(int x, int y, QString s);
        void dessineLigne(int x1, int y1, int x2, int y2, QString s);
        void dessineTexte(int x, int y, QString s);
        void dessinerCadre();
        QImage* getImage() const;

signals:
    void envoieCoord(int x, int y, QVector<QRect> tab);


private slots:

protected:

    virtual void mousePressEvent(QMouseEvent * e);
    virtual void paintEvent(QPaintEvent *e);


};

#endif
