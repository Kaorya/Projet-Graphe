#include "myQView.h"
#include <string>
#include <QDebug>
#include <qmath.h>
#include <QGraphicsItem>

MyQView::MyQView(QGraphicsScene *scene, QWidget *parent):QGraphicsView(scene,parent)
{
  //image = NULL;
  verticalScrollBar()->installEventFilter(this);
  horizontalScrollBar()->installEventFilter(this);

}
MyQView::MyQView()
{
}
MyQView::~MyQView(){
}

QSize MyQView::sizeHint() const
{
  return QSize(4000,4000);
}

void MyQView::mousePressEvent(QMouseEvent * e)
{
  //qDebug() << "clic sur la scene ! (" << e->x() << "," << e->y() << ")";
  if(e->button() == Qt::LeftButton)
  {
    emit envoieCoord(e->x() + horizontalScrollBar()->sliderPosition(),e->y() + verticalScrollBar()->sliderPosition());
  }
  else if(e->button() == Qt::RightButton)
  {
    emit envoieClicDroit(e->x() + horizontalScrollBar()->sliderPosition(),e->y() + verticalScrollBar()->sliderPosition());
  }
}
void MyQView::mouseMoveEvent(QMouseEvent * e)
{
  emit mouvementSouris(e->x() + horizontalScrollBar()->sliderPosition(),e->y() + verticalScrollBar()->sliderPosition());
}

void MyQView::mouseDoubleClickEvent(QMouseEvent *e)
{
  emit doubleClic(e->x() + horizontalScrollBar()->sliderPosition(),e->y() + verticalScrollBar()->sliderPosition());
}
void  MyQView::mouseReleaseEvent(QMouseEvent *e)
{
  emit relachement(e->x() + horizontalScrollBar()->sliderPosition(),e->y() + verticalScrollBar()->sliderPosition());
}

bool MyQView::eventFilter(QObject * obj, QEvent * event)
{
  if(event->type() == QEvent::Wheel)
  {
    // faire le zoom plus tard
    //this->setSceneRect();
    //centerOn(event->type().x(), event->type().y());
    return true;
  }
  else
  {
    return QGraphicsView::eventFilter(obj, event);
  }
}
void MyQView::wheelEvent(QWheelEvent* event)
{
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    int horizontalPosition = horizontalScrollBar()->sliderPosition();
    int verticalPosition = verticalScrollBar()->sliderPosition();

 
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
        qDebug() << "Ancienne position horizontal scrollBar : " << horizontalPosition;
        qDebug() << "Nouvelle position horizontal scrollBar : " << horizontalScrollBar()->sliderPosition();
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    emit wheelAction(horizontalPosition, verticalPosition);
/*
   QTransform t = transform();
   QList<QGraphicsItem *> list = scene()->items();
   for(int i = 0; i < list.size(); i++)
   {
    list[i]->setTransform(t);
   }
   */
}

