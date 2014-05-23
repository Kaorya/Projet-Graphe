#include "myQView.h"
#include <string>
#include <QDebug>

MyQView::MyQView(QGraphicsScene *scene, QWidget *parent):QGraphicsView(scene,parent)
{
  //image = NULL;

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
