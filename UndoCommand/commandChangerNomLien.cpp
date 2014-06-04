#include "commandChangerNomLien.h"

CommandChangerNomLien::CommandChangerNomLien(ZoneDessin* zone, int i, QString vieuxNom, QString newNom):indice(i),ancienNom(vieuxNom), nouveauNom(newNom)
{
	m_zone = zone;
}

void CommandChangerNomLien::undo()
{
    m_zone->g.m_tabLien[indice].setNom(ancienNom.toStdString());

    QFontMetrics fontMetrics(m_zone->scene->font());
    m_zone->g.m_tabLien[indice].setWidth(fontMetrics.width(ancienNom));
    QRectF rect(2, 5, m_zone->g.m_tabLien[indice].getWidth()+4, m_zone->g.m_tabLien[indice].getHeight());

    m_zone->tabRectLine[indice]->setRect(rect);
    m_zone->tabTxtLine[indice]->setPlainText(QString::fromStdString(m_zone->g.m_tabLien[indice].getNom()));

    m_zone->tabRectLine[indice]->setPos(m_zone->g.m_tabLien[indice].getPosition().getX()
     - m_zone->tabRectLine[indice]->rect().width()/2, 
     m_zone->g.m_tabLien[indice].getPosition().getY()
     - m_zone->tabRectLine[indice]->rect().height());

    m_zone->tabTxtLine[indice]->setPos(m_zone->g.m_tabLien[indice].getPosition().getX()
     - m_zone->tabRectLine[indice]->rect().width()/2,
    m_zone->g.m_tabLien[indice].getPosition().getY() 
     - m_zone->tabRectLine[indice]->rect().height());

}
void CommandChangerNomLien::redo()
{
    m_zone->g.m_tabLien[indice].setNom(nouveauNom.toStdString());

    QFontMetrics fontMetrics(m_zone->scene->font());
    m_zone->g.m_tabLien[indice].setWidth(fontMetrics.width(nouveauNom));
    QRectF rect(2, 5, m_zone->g.m_tabLien[indice].getWidth()+4, m_zone->g.m_tabLien[indice].getHeight());

    m_zone->tabRectLine[indice]->setRect(rect);
    m_zone->tabTxtLine[indice]->setPlainText(QString::fromStdString(m_zone->g.m_tabLien[indice].getNom()));

    m_zone->tabRectLine[indice]->setPos(m_zone->g.m_tabLien[indice].getPosition().getX()
     - m_zone->tabRectLine[indice]->rect().width()/2, 
     m_zone->g.m_tabLien[indice].getPosition().getY()
     - m_zone->tabRectLine[indice]->rect().height());

    m_zone->tabTxtLine[indice]->setPos(m_zone->g.m_tabLien[indice].getPosition().getX()
     - m_zone->tabRectLine[indice]->rect().width()/2,
    m_zone->g.m_tabLien[indice].getPosition().getY() 
     - m_zone->tabRectLine[indice]->rect().height());

}