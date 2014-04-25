#include "lien.h"

Lien::Lien(std::string nom, Noeud const & noeudSource, Noeud const & noeudCible):m_nom(nom),m_noeudSource(noeudSource),m_noeudCible(noeudCible),fleche(0)
{
	std::cout << "Lien cree" << std::endl;
}

std::string Lien::getNom() const
{
	return m_nom;
}
const Noeud Lien::getNoeudSource() const
{
	return m_noeudSource;
}
const Noeud Lien::getNoeudCible() const
{
	return m_noeudCible;
}
const Position Lien::getPosition() const
{
	return m_positionNomLien;
}
std::vector<Position> Lien::getTabCassure() const
{
	return m_tabCassure;
}
void Lien::setNom(std::string nom)
{
	m_nom = nom;
}
void Lien::setPositionNomLien(int x, int y)
{
	m_positionNomLien.setX(x);
	m_positionNomLien.setY(y);
}