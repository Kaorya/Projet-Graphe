#include "commandSupprimerNoeud.h"

CommandSupprimerNoeud::CommandSupprimerNoeud(ZoneDessin* zone, int i):indice(i)
{
	m_zone = zone;
}

void CommandSupprimerNoeud::undo()
{
	m_zone->tabRect[indice]->setActive(true);
	m_zone->tabTxtRect[indice]->setActive(true);
	m_zone->tabRect[indice]->show();
	m_zone->tabTxtRect[indice]->show();
	m_zone->g.m_tabNoeud[indice].setVisible(true);

	for(int j=0; j < m_zone->g.m_tabLien.size(); j++)
	{
		if(!m_zone->lienDejaSuppr.contains(m_zone->g.m_tabLien[j].getIndice()))
		{
			if(m_zone->g.m_tabLien[j].getNoeudSource() == indice)
			{	

				if(m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[j].getNoeudCible()].isVisible())
				{
					m_zone->g.m_tabLien[j].setVisible(true);

					m_zone->tabLine[j]->setActive(true);
					m_zone->tabRectLine[j]->setActive(true);
					m_zone->tabTxtLine[j]->setActive(true);
				
					m_zone->tabLine[j]->show();
					if(!QString::fromStdString(m_zone->g.m_tabLien[j].getNom()).isEmpty())
						m_zone->tabRectLine[j]->show();
					m_zone->tabTxtLine[j]->show();
				}
			}

				if(m_zone->g.m_tabLien[j].getNoeudCible() == indice)
				{
					if(m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[j].getNoeudSource()].isVisible())
					{
						m_zone->g.m_tabLien[j].setVisible(true);

						m_zone->tabLine[j]->setActive(true);
						m_zone->tabRectLine[j]->setActive(true);
						m_zone->tabTxtLine[j]->setActive(true);
					
						m_zone->tabLine[j]->show();
						if(!QString::fromStdString(m_zone->g.m_tabLien[j].getNom()).isEmpty())
							m_zone->tabRectLine[j]->show();
						m_zone->tabTxtLine[j]->show();
					}
				}
					
			
		}
	}

}
void CommandSupprimerNoeud::redo()
{

	m_zone->tabRect[indice]->setActive(false);
	m_zone->tabTxtRect[indice]->setActive(false);
	m_zone->tabRect[indice]->hide();
	m_zone->tabTxtRect[indice]->hide();
	m_zone->g.m_tabNoeud[indice].setVisible(false);

	for(int j=0; j < m_zone->g.m_tabLien.size(); j++)
	{
		if(m_zone->g.m_tabLien[j].getNoeudSource() == indice)
		{
			if(m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[j].getNoeudCible()].isVisible())
			{
				m_zone->g.m_tabLien[j].setVisible(false);

				m_zone->tabLine[j]->setActive(false);
				m_zone->tabRectLine[j]->setActive(false);
				m_zone->tabTxtLine[j]->setActive(false);
			
				m_zone->tabLine[j]->hide();
				m_zone->tabRectLine[j]->hide();
				m_zone->tabTxtLine[j]->hide();
			}
		}

		if(m_zone->g.m_tabLien[j].getNoeudCible() == indice)
		{
			if(m_zone->g.m_tabNoeud[m_zone->g.m_tabLien[j].getNoeudSource()].isVisible())
			{
				m_zone->g.m_tabLien[j].setVisible(false);

				m_zone->tabLine[j]->setActive(false);
				m_zone->tabRectLine[j]->setActive(false);
				m_zone->tabTxtLine[j]->setActive(false);
			
				m_zone->tabLine[j]->hide();
				m_zone->tabRectLine[j]->hide();
				m_zone->tabTxtLine[j]->hide();
			}
		}
	}

}