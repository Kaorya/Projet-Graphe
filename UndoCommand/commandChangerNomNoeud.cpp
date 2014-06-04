#include "commandChangerNomNoeud.h"

CommandChangerNomNoeud::CommandChangerNomNoeud(ZoneDessin* zone, int i, QString vieuxNom, QString newNom):indice(i),ancienNom(vieuxNom), nouveauNom(newNom)
{
	m_zone = zone;
}

void CommandChangerNomNoeud::undo()
{
    m_zone->g.m_tabNoeud[indice].setNom(ancienNom.toStdString());

    QFontMetrics fontMetrics(m_zone->scene->font());
    m_zone->g.m_tabNoeud[indice].setWidth(fontMetrics.width(ancienNom) + 10);
    QRectF rect(0 ,0, m_zone->g.m_tabNoeud[indice].getWidth() - 3, m_zone->g.m_tabNoeud[indice].getHeight() - 3);
    
    m_zone->tabRect[indice]->setRect(rect);
    m_zone->tabTxtRect[indice]->setPlainText(QString::fromStdString(m_zone->g.m_tabNoeud[indice].getNom()));

    m_zone->tabRect[indice]->setPos(m_zone->g.m_tabNoeud[indice].getPosition().getX()
     - m_zone->g.m_tabNoeud[indice].getWidth()/2,
     m_zone->g.m_tabNoeud[indice].getPosition().getY()
     - m_zone->g.m_tabNoeud[indice].getHeight()/2);

    m_zone->tabTxtRect[indice]->setPos(m_zone->g.m_tabNoeud[indice].getPosition().getX()
     - m_zone->g.m_tabNoeud[indice].getWidth()/2,
    m_zone->g.m_tabNoeud[indice].getPosition().getY()
     - m_zone->g.m_tabNoeud[indice].getHeight()/2);
}
void CommandChangerNomNoeud::redo()
{
    ///////////////////////////////
    m_zone->g.m_tabNoeud[indice].setNom(nouveauNom.toStdString());

    QFontMetrics fontMetrics(m_zone->scene->font());
    m_zone->g.m_tabNoeud[indice].setWidth(fontMetrics.width(nouveauNom) + 10);
    QRectF rect(0 ,0, m_zone->g.m_tabNoeud[indice].getWidth() - 3, m_zone->g.m_tabNoeud[indice].getHeight() - 3);
    
    m_zone->tabRect[indice]->setRect(rect);
    m_zone->tabTxtRect[indice]->setPlainText(QString::fromStdString(m_zone->g.m_tabNoeud[indice].getNom()));

    m_zone->tabRect[indice]->setPos(m_zone->g.m_tabNoeud[indice].getPosition().getX()
     - m_zone->g.m_tabNoeud[indice].getWidth()/2,
     m_zone->g.m_tabNoeud[indice].getPosition().getY()
     - m_zone->g.m_tabNoeud[indice].getHeight()/2);

    m_zone->tabTxtRect[indice]->setPos(m_zone->g.m_tabNoeud[indice].getPosition().getX()
     - m_zone->g.m_tabNoeud[indice].getWidth()/2,
    m_zone->g.m_tabNoeud[indice].getPosition().getY()
     - m_zone->g.m_tabNoeud[indice].getHeight()/2);


}