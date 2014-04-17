#include "lien.h"

Lien::Lien(std::string nom, Noeud noeudSource, Noeud noeudCible):m_nom(nom),m_noeudSource(noeudSource),m_noeudCible(noeudCible)
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