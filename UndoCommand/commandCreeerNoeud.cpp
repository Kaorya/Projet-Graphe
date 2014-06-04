#include "commandCreerNoeud.h"

CommandCreerNoeud::CommandCreerNoeud(ZoneDessin* zone, int i):indice(i)
{
	m_zone = zone;
}

void CommandCreerNoeud::undo()
{
	m_zone->tabRect[indice]->setActive(false);
	m_zone->tabTxtRect[indice]->setActive(false);
	m_zone->tabRect[indice]->hide();
	m_zone->tabTxtRect[indice]->hide();
	m_zone->g.m_tabNoeud[indice].setVisible(false);
}
void CommandCreerNoeud::redo()
{
	m_zone->tabRect[indice]->setActive(true);
	m_zone->tabTxtRect[indice]->setActive(true);
	m_zone->tabRect[indice]->show();
	m_zone->tabTxtRect[indice]->show();
	m_zone->g.m_tabNoeud[indice].setVisible(true);

}