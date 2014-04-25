#include "graphe.h"

Graphe::Graphe()
{
}

Graphe::~Graphe()
{
}

std::vector<Noeud> Graphe::getTabNoeud() const
{
	return m_tabNoeud;
}
std::vector<Lien> Graphe::getTabLien() const
{
	return m_tabLien;
}