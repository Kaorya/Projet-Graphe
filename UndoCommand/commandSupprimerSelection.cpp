#include "commandSupprimerSelection.h"

CommandSupprimerSelection::CommandSupprimerSelection(ZoneDessin* zone, std::vector<int> tabN, std::vector<int> tabL)
{
	m_zone = zone;
	tabIndiceNoeud = tabN;
	tabIndiceLien = tabL;
}

void CommandSupprimerSelection::undo()
{
	for(int i = 0; i < tabIndiceNoeud.size(); i++)
	{
		for(unsigned int j = 0; j < m_zone->g.m_tabLien.size(); j++)
		{
			if(m_zone->g.m_tabLien[j].getNoeudSource() == tabIndiceNoeud[i]-i || m_zone->g.m_tabLien[j].getNoeudCible() == tabIndiceNoeud[i]-i)
			{
				if(!m_zone->g.m_tabLien[j].isVisible())
				{
					m_zone->g.m_tabLien[j].setVisible(true);

					m_zone->tabLine[j]->setActive(true);
					m_zone->tabRectLine[j]->setActive(true);
					m_zone->tabTxtLine[j]->setActive(true);
				
					m_zone->tabLine[j]->show();
					m_zone->tabRectLine[j]->show();
					m_zone->tabTxtLine[j]->show();
				}
			}
		}

		m_zone->tabRect[tabIndiceNoeud[i]]->setActive(true);
		m_zone->tabTxtRect[tabIndiceNoeud[i]]->setActive(true);
		m_zone->tabRect[tabIndiceNoeud[i]]->show();
		m_zone->tabTxtRect[tabIndiceNoeud[i]]->show();
		m_zone->g.m_tabNoeud[tabIndiceNoeud[i]].setVisible(true);
	}

	for(unsigned int i = 0; i < tabIndiceLien.size(); i++)
	{
		//qDebug() << "for des liens a delete";

		m_zone->g.m_tabLien[tabIndiceLien[i]].setVisible(true);
		m_zone->tabRectLine[tabIndiceLien[i]]->setActive(true);
		m_zone->tabLine[tabIndiceLien[i]]->setActive(true);
		m_zone->tabTxtLine[tabIndiceLien[i]]->setActive(true);

		m_zone->tabRectLine[tabIndiceLien[i]]->show();
		m_zone->tabLine[tabIndiceLien[i]]->show();
		m_zone->tabTxtLine[tabIndiceLien[i]]->show();

	}

}
void CommandSupprimerSelection::redo()
{
	for(int i = 0; i < tabIndiceNoeud.size(); i++)
	{
		for(unsigned int j = 0; j < m_zone->g.m_tabLien.size(); j++)
		{
			if(m_zone->g.m_tabLien[j].getNoeudSource() == tabIndiceNoeud[i]-i || m_zone->g.m_tabLien[j].getNoeudCible() == tabIndiceNoeud[i]-i)
			{
				if(m_zone->g.m_tabLien[j].isVisible())
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

		m_zone->tabRect[tabIndiceNoeud[i]]->setActive(false);
		m_zone->tabTxtRect[tabIndiceNoeud[i]]->setActive(false);
		m_zone->tabRect[tabIndiceNoeud[i]]->hide();
		m_zone->tabTxtRect[tabIndiceNoeud[i]]->hide();
		m_zone->g.m_tabNoeud[tabIndiceNoeud[i]].setVisible(false);
	}

	for(unsigned int i = 0; i < tabIndiceLien.size(); i++)
	{
		//qDebug() << "for des liens a delete";

		m_zone->g.m_tabLien[tabIndiceLien[i]].setVisible(false);
		m_zone->tabRectLine[tabIndiceLien[i]]->setActive(false);
		m_zone->tabLine[tabIndiceLien[i]]->setActive(false);
		m_zone->tabTxtLine[tabIndiceLien[i]]->setActive(false);

		m_zone->tabRectLine[tabIndiceLien[i]]->hide();
		m_zone->tabLine[tabIndiceLien[i]]->hide();
		m_zone->tabTxtLine[tabIndiceLien[i]]->hide();

	}

}