#include "myQImage.h"
#include <string>
#include <QDebug>

MyQImage::MyQImage(int width, int height, QImage::Format format, QWidget* parent):QWidget(parent), maxX(0), maxY(0), minX(4000), minY(4000)

{
  image = new QImage(width, height, format);
  //image = NULL;

}
MyQImage::MyQImage():maxX(0),maxY(0),minX(0),minY(0)
{
  image = new QImage();

}
MyQImage::~MyQImage(){
}

QSize MyQImage::sizeHint() const
{
  return QSize(4000,4000);
}

void MyQImage::mousePressEvent(QMouseEvent * e)
{
  if(e->button() == Qt::LeftButton)
  {
    emit envoieCoord(e->x(),e->y());
  }
  else if(e->button() == Qt::RightButton)
  {
    emit envoieClicDroit(e->x(), e->y());
  }
}
void MyQImage::mouseMoveEvent(QMouseEvent * e)
{
  emit mouvementSouris(e->x(), e->y());
}

void MyQImage::mouseDoubleClickEvent(QMouseEvent *e)
{
  emit doubleClic(e->x(), e->y());
}

void MyQImage::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0,0,*image);
}

void MyQImage::resizeEvent(QResizeEvent *e)
{
  if (image != NULL)
  {
    if (image->height() < e->size().height() || image->width() < e->size().width())
    {
      qDebug() << "On resize l'image ";

      int width = (e->size().width() > image->width() ? e->size().width() : image->width());
      int height = (e->size().height() > image->height() ? e->size().height() : image->height());
      QImage * tmp = new QImage(width, height, QImage::Format_ARGB4444_Premultiplied);
      tmp->fill(Qt::white);
      QPainter p(tmp);
      p.drawImage(0,0, *image);
      //QImage * tmp = new QImage(m_bitmap->copy(0,0, width, height));

      delete image;
      image = tmp;
    }
  }
  else
  {
    image = new QImage(e->size(), QImage::Format_ARGB4444_Premultiplied);
    image->fill(Qt::white);
    qDebug() << "On créer la bitmap";
  }
}

void MyQImage::dessineRect(int x, int y, int width, int height, QColor cBordure, QColor cFond)
{
  QPainter painter(image);
  
  painter.fillRect(x - width/2 , y - height/2, width, height, cFond);
  painter.setPen(cBordure);
  painter.drawRect(x - width/2 , y - height/2, width, height);

  if(x + width/2 + 10 > maxX)
    maxX = x + width/2 + 10;
  if(y + height/2 + 5 > maxY)
    maxY = y + height/2 + 5;
  if(x - width/2 - 5 < minX)
    minX = x - width/2 -5 ;
  if(y - height/2 < minY)
    minY = y - height/2;

  //qDebug() << "min : (" << minX << "," << minY << ") max : (" << maxX << "," << maxY << ")";

  repaint();
}

void MyQImage::dessineLigne(int x1, int y1, int x2, int y2, QColor c)
{
  QPainter painter(image);
 
  painter.setPen(c);
  painter.drawLine(x1, y1, x2, y2);


  repaint();

}

void MyQImage::dessineTexte(int x, int y, QString s, int width, int height, QColor c)
{
  QPainter painter(image);
  painter.setPen(c);
  QRect rect(x - width/2,y - height/2,width,height);
  painter.drawText(rect, Qt::AlignCenter, s, NULL);
  repaint();

}

void  MyQImage::dessineNoeud(Noeud n)
{
  QString s = QString::fromStdString(n.getNom());
  dessineRect(n.getPosition().getX(), n.getPosition().getY(), n.getWidth(), n.getHeight(), n.getCouleurBordure(), n.getCouleurFond());
  dessineTexte(n.getPosition().getX(), n.getPosition().getY(), s, n.getWidth(), n.getHeight(), n.getCouleurPolice());
}
void  MyQImage::dessineLien(Lien l, int x1, int x2, int y1, int y2)
{
  dessineLigne(x1, y1, x2, y2, l.getCouleurLien());
}
void  MyQImage::dessineTexteLien(Lien l, int x1 , int x2 , int y1, int y2)
{
  QString s = QString::fromStdString(l.getNom());
  QPainter painter(image);
  QFontMetrics fontMetrics(painter.font());

  painter.fillRect((x1 + x2)/2 - (fontMetrics.width(s))/2, ((y1 + y2)/2) - fontMetrics.height(), fontMetrics.width(s), fontMetrics.height() + 5, Qt::white);
  //painter.drawRect((x1 + x2)/2 - (fontMetrics.width(s))/2, ((y1 + y2)/2) - fontMetrics.height(), fontMetrics.width(s), fontMetrics.height() + 5);
  painter.setPen(l.getCouleurPoliceLien());
  painter.drawText((x1 + x2)/2 - (fontMetrics.width(s))/2, ((y1 + y2)/2), s); 
}


QImage* MyQImage::getImage() const
{
    return image;
}
void MyQImage::setImage(QImage i)
{
  *image = i;
}