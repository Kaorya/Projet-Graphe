#include "commandCreerLien.h"

CommandCreerLien::CommandCreerLien(ZoneDessin* zone, int i):indice(i)
{
	m_zone = zone;
}

void CommandCreerLien::undo()
{
	m_zone->tabRectLine[indice]->setActive(false);
	m_zone->tabTxtLine[indice]->setActive(false);
	m_zone->tabLine[indice]->setActive(false);
	m_zone->tabRectLine[indice]->hide();
	m_zone->tabTxtLine[indice]->hide();
	m_zone->tabLine[indice]->hide();
	m_zone->g.m_tabLien[indice].setVisible(false);
}
void CommandCreerLien::redo()
{
	m_zone->tabRectLine[indice]->setActive(true);
	m_zone->tabTxtLine[indice]->setActive(true);
	m_zone->tabLine[indice]->setActive(true);
	m_zone->tabRectLine[indice]->show();
	m_zone->tabTxtLine[indice]->show();
	m_zone->tabLine[indice]->show();
	m_zone->g.m_tabLien[indice].setVisible(true);

}