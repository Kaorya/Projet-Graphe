#include "noeud.h"

Noeud::Noeud(std::string nom):m_nom(nom)
{
	std::cout << "Noeud cree" << std::endl;
}

Noeud::Noeud(std::string nom, int x, int y):m_nom(nom), m_position(x,y)
{
	std::cout << "Noeud avec x y cree" << std::endl;
}
Noeud::Noeud(std::string nom, Position const &p):m_nom(nom),m_position(p)
{
	std::cout << "Noeud avec position cree" << std::endl;
}
std::string Noeud::getNom() const
{
	return m_nom;
}
const Position Noeud::getPosition() const
{
	return m_position;
}
