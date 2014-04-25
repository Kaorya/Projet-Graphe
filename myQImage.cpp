#include "myQImage.h"
#include <string>
#include <QDebug>

MyQImage::MyQImage(int width, int height, QImage::Format format, QWidget* parent):QWidget(parent), maxX(0), maxY(0), minX(4000), minY(4000)

{
  image = new QImage(width, height, format);

}

MyQImage::~MyQImage(){
}

QSize MyQImage::sizeHint() const
{
  return QSize(4000,4000);
}

void MyQImage::mousePressEvent(QMouseEvent * e)
{
  emit envoieCoord(e->x(),e->y());
}
void MyQImage::mouseMoveEvent(QMouseEvent * e)
{
  emit mouvementSouris(e->x(), e->y());
}

void MyQImage::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0,0,*image);
}

void MyQImage::dessineRect(int x, int y, int width, int height)
{
  QPainter painter(image);
  
  painter.fillRect(x - width/2 - 5, y - height/2, width + 10, height + 5, Qt::white);
  painter.setPen(Qt::blue);
  painter.drawRect(x - width/2 - 5, y - height/2, width + 10, height + 5);

  if(x + width/2 + 10 > maxX)
    maxX = x + width/2 + 10;
  if(y + height/2 + 5 > maxY)
    maxY = y + height/2 + 5;
  if(x - width/2 - 5 < minX)
    minX = x - width/2 -5 ;
  if(y - height/2 < minY)
    minY = y - height/2;

  qDebug() << "min : (" << minX << "," << minY << ") max : (" << maxX << "," << maxY << ")";

  repaint();
}

void MyQImage::dessineLigne(int x1, int y1, int x2, int y2)
{
  QPainter painter(image);
 
  painter.setPen(Qt::red);
  painter.drawLine(x1, y1, x2, y2);


  repaint();

}

void MyQImage::dessineTexte(int x, int y, QString s, int width, int height)
{
  QPainter painter(image);
  painter.setPen(Qt::blue);
  painter.drawText(x - width/2, y + height/2, s);
  repaint();

}

void  MyQImage::dessineNoeud(Noeud n)
{
  QString s = QString::fromStdString(n.getNom());
  dessineRect(n.getPosition().getX(), n.getPosition().getY(), n.getWidth(), n.getHeight());
  dessineTexte(n.getPosition().getX(), n.getPosition().getY(), s, n.getWidth(), n.getHeight());
}
void  MyQImage::dessineLien(Lien l)
{
  dessineLigne(l.getNoeudSource().getPosition().getX(), l.getNoeudSource().getPosition().getY(),
        l.getNoeudCible().getPosition().getX(), l.getNoeudCible().getPosition().getY());
}
void  MyQImage::dessineTexteLien(Lien l)
{
  int x1 = l.getNoeudSource().getPosition().getX();
  int x2 = l.getNoeudCible().getPosition().getX();
  int y1 = l.getNoeudSource().getPosition().getY();
  int y2 = l.getNoeudCible().getPosition().getY();
  QString s = QString::fromStdString(l.getNom());
  QPainter painter(image);
  QFontMetrics fontMetrics(painter.font());

  painter.fillRect((x1 + x2)/2 - (fontMetrics.width(s))/2, ((y1 + y2)/2) - fontMetrics.height(), fontMetrics.width(s), fontMetrics.height() + 5, Qt::white);
  painter.drawText((x1 + x2)/2 - (fontMetrics.width(s))/2, ((y1 + y2)/2), s); 
}

void MyQImage::dessinerCadre()
{
  QPainter painter(image);

  painter.setPen(Qt::black);
  painter.drawRect(0,0,image->width()-1,image->height()-1);

  repaint();

}


QImage* MyQImage::getImage() const
{
    return image;
}