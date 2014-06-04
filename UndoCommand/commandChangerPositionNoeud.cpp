#include "commandChangerPositionNoeud.h"

CommandChangerPositionNoeud::CommandChangerPositionNoeud(ZoneDessin* zone, int i, QPoint viellePos, QPoint newPos):indice(i),anciennePos(viellePos), nouvellePos(newPos)
{
	m_zone = zone;
	premierRedo = false;
}

void CommandChangerPositionNoeud::undo()
{
	int x = anciennePos.x();
	int y = anciennePos.y();

	if(x<0)
		x = 0;
	else if(x > m_zone->scene->width())
		x = m_zone->scene->width();
	if(y<0)
		y = 0;
	else if(y > m_zone->scene->height())
		y = m_zone->scene->height();
		if(indice < m_zone->g.m_tabNoeud.size())
		{ 
			m_zone->g.m_tabNoeud[indice].setPosition(x,y);
			
			for(unsigned int i = 0; i < m_zone->g.m_tabLien.size(); i++)
			{//vérifier que le lien contienne le noeud en mouvement en cible ou en source
				if(m_zone->g.m_tabLien[i].getNoeudSource() == indice || m_zone->g.m_tabLien[i].getNoeudCible() == indice)
				{
			  		int x1 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudSource()].getPosition().getX();
		 			int x2 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudCible()].getPosition().getX();
		 			int y1 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudSource()].getPosition().getY();
		 			int y2 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudCible()].getPosition().getY();
		 			int x3 = (x1 + x2)/2;
		 			int y3 = (y1 + y2)/2;
					m_zone->g.m_tabLien[i].setPositionNomLien(x3,y3);
					m_zone->tabLine[i]->setLine(x1,y1,x2,y2);

					m_zone->tabRectLine[i]->setPos(x3 - m_zone->tabRectLine[i]->rect().width()/2, y3 - m_zone->tabRectLine[i]->rect().height()/2);
					m_zone->tabTxtLine[i]->setPos(x3 - m_zone->tabRectLine[i]->rect().width()/2, y3 - m_zone->tabRectLine[i]->rect().height()/2);
					
					m_zone->tabRectLine[i]->setZValue(2.5);
					m_zone->tabTxtLine[i]->setZValue(2.5);
				}
			}
			
			m_zone->tabRect[indice]->setPos(x - m_zone->g.m_tabNoeud[indice].getWidth()/2,y - m_zone->g.m_tabNoeud[indice].getHeight()/2);
			m_zone->tabTxtRect[indice]->setPos(x - m_zone->g.m_tabNoeud[indice].getWidth()/2,y - m_zone->g.m_tabNoeud[indice].getHeight()/2);
		}
}
void CommandChangerPositionNoeud::redo()
{
	if(premierRedo)
	{
		int x = nouvellePos.x();
		int y = nouvellePos.y();

		if(x<0)
			x = 0;
		else if(x > m_zone->scene->width())
			x = m_zone->scene->width();
		if(y<0)
			y = 0;
		else if(y > m_zone->scene->height())
			y = m_zone->scene->height();
		if(indice < m_zone->g.m_tabNoeud.size())
		{ 
			m_zone->g.m_tabNoeud[indice].setPosition(x,y);
			
			for(unsigned int i = 0; i < m_zone->g.m_tabLien.size(); i++)
			{//vérifier que le lien contienne le noeud en mouvement en cible ou en source
				if(m_zone->g.m_tabLien[i].getNoeudSource() == indice || m_zone->g.m_tabLien[i].getNoeudCible() == indice)
				{
			  		int x1 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudSource()].getPosition().getX();
		 			int x2 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudCible()].getPosition().getX();
		 			int y1 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudSource()].getPosition().getY();
		 			int y2 = m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[i].getNoeudCible()].getPosition().getY();
		 			int x3 = (x1 + x2)/2;
		 			int y3 = (y1 + y2)/2;
					m_zone->g.m_tabLien[i].setPositionNomLien(x3,y3);
					m_zone->tabLine[i]->setLine(x1,y1,x2,y2);

					m_zone->tabRectLine[i]->setPos(x3 - m_zone->tabRectLine[i]->rect().width()/2, y3 - m_zone->tabRectLine[i]->rect().height()/2);
					m_zone->tabTxtLine[i]->setPos(x3 - m_zone->tabRectLine[i]->rect().width()/2, y3 - m_zone->tabRectLine[i]->rect().height()/2);
					
					m_zone->tabRectLine[i]->setZValue(2.5);
					m_zone->tabTxtLine[i]->setZValue(2.5);
				}
			}
			
			m_zone->tabRect[indice]->setPos(x - m_zone->g.m_tabNoeud[indice].getWidth()/2,y - m_zone->g.m_tabNoeud[indice].getHeight()/2);
			m_zone->tabTxtRect[indice]->setPos(x - m_zone->g.m_tabNoeud[indice].getWidth()/2,y - m_zone->g.m_tabNoeud[indice].getHeight()/2);

		}
	}
	if(!premierRedo)
		premierRedo = true;
}