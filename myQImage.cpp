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
  emit envoieCoord(e->x(),e->y(), tabRect);

}

void MyQImage::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0,0,*image);
}

void MyQImage::dessineRect(int x, int y, QString s)
{
  QPainter painter(image);
  painter.setPen(Qt::blue);


  QFontMetrics fontMetrics(painter.font());
  QRect rectangle(fontMetrics.boundingRect(s));
  painter.drawRect(x - rectangle.width()/2 - 5, y - rectangle.height()/2, rectangle.width() + 10, rectangle.height() + 5);
  tabRect.push_back(rectangle);

  if(x + rectangle.width()/2 + 10 > maxX)
    maxX = x + rectangle.width()/2 + 10;
  if(y + rectangle.height()/2 + 5 > maxY)
    maxY = y + rectangle.height()/2 + 5;
  if(x - rectangle.width()/2 - 5 < minX)
    minX = x - rectangle.width()/2 -5 ;
  if(y - rectangle.height()/2 < minY)
    minY = y - rectangle.height()/2;

  qDebug() << "min : (" << minX << "," << minY << ") max : (" << maxX << "," << maxY << ")";

  repaint();
}

void MyQImage::dessineLigne(int x1, int y1, int x2, int y2, QString s)
{
  QPainter painter(image);
 

  // A gauche
        if(x1 >= x2){

          // En Haut à gauche
          if(y1 >= y2){

          painter.setPen(Qt::red);
          painter.drawLine(x1 - tabRect[0].width()/2 - 5, y1 - tabRect[0].height()/2 , x2 + tabRect[1].width()/2 + 5 , y2 + tabRect[1].height()/2 + 5);

          painter.drawText((x1 - tabRect[0].width()/2 - 5 + x2 + tabRect[1].width()/2 + 5)/2, ((y1 - tabRect[0].height()/2 + y2 + tabRect[1].height()/2 + 5)/2), s);
          }
      
          
          // En Bas à gauche
          else{  

          painter.setPen(Qt::green);
          painter.drawLine(x1 - tabRect[0].width()/2 - 5, y1 + tabRect[0].height()/2 + 5 , x2 + tabRect[1].width()/2 + 5, y2 - tabRect[1].height()/2);

          painter.drawText((x1 - tabRect[0].width()/2 - 5 + x2 + tabRect[1].width()/2 + 5)/2, (y1 + tabRect[0].height()/2 + 5 + y2 - tabRect[1].height()/2)/2, s);

          }

        }
        // A droite
        else{

          // En Haut à droite
          if(y1 >= y2){

          painter.setPen(Qt::black);
          painter.drawLine(x1 + tabRect[0].width()/2 + 5, y1 - tabRect[0].height()/2, x2 - tabRect[1].width()/2 - 5, y2 + tabRect[1].height()/2 + 5);

          painter.drawText((x1 + tabRect[0].width()/2 + 5 + x2 - tabRect[1].width()/2 - 5)/2, (y1 - tabRect[0].height()/2 + y2 + tabRect[1].height()/2 + 5)/2, s);

          
        }
          // En Bas à droite
          else{  

            painter.setPen(Qt::yellow);
            painter.drawLine(x1 + tabRect[0].width()/2 + 5, y1 + tabRect[0].height()/2 + 5, x2 - tabRect[1].width()/2 - 5, y2 - tabRect[1].height()/2);

            painter.drawText((x1 + tabRect[0].width()/2 + 5 + x2 - tabRect[1].width()/2 - 5)/2, (y1 + tabRect[0].height()/2 + 5 + y2 - tabRect[1].height()/2)/2, s);

          }

        }


  repaint();

}

void MyQImage::dessineTexte(int x, int y, QString s)
{
  QPainter painter(image);
  painter.setPen(Qt::blue);
  painter.drawText(x - tabRect[tabRect.size()-1].width()/2,y + tabRect[tabRect.size()-1].height()/2,s);
  repaint();

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