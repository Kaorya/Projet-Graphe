#include "noeud.h"

Noeud::Noeud(std::string nom, int indice):m_nom(nom),m_indice(indice)
{
	//std::cout << "Noeud cree" << std::endl;
}

Noeud::Noeud(std::string nom, int x, int y, int indice, int width, int heigth):m_nom(nom), m_position(x,y), m_indice(indice), m_widthRect(width), m_heigth(heigth)
{
	//std::cout << "Noeud avec x y cree" << std::endl;
	m_couleurFond = Qt::white;
	m_couleurPolice = Qt::black;
	m_couleurBordure = Qt::black;
	//m_style = 0;
	m_visible = true;
}
Noeud::Noeud(std::string nom, Position const &p, int indice):m_nom(nom),m_position(p), m_indice(indice)
{
	//std::cout << "Noeud avec position cree" << std::endl;
	m_visible = true;
}
Noeud::Noeud(const Noeud &n):m_nom(n.m_nom),m_position(n.m_position),m_widthRect(n.m_widthRect),m_heigth(n.m_heigth),m_couleurFond(n.m_couleurFond),m_couleurPolice(n.m_couleurPolice),m_couleurBordure(n.m_couleurBordure),m_indice(n.m_indice)
{
 //std::cout << "noeud par recopie cree";
	m_visible = true;
}

std::string Noeud::getNom() const
{
	return m_nom;
}
const Position Noeud::getPosition() const
{
	return m_position;
}
QColor Noeud::getCouleurFond() const
{
	return m_couleurFond;
}
QColor Noeud::getCouleurPolice() const
{
	return m_couleurPolice;
}
QColor Noeud::getCouleurBordure() const
{
	return m_couleurBordure;
}
int Noeud::getIndice() const
{
	return m_indice;
}
int Noeud::getWidth() const
{
	return m_widthRect;
}
int Noeud::getHeight() const
{
	return m_heigth;
}

bool Noeud::isVisible() const
{
	return m_visible;
}

void Noeud::setNom(std::string nom)
{
	m_nom = nom;
}
void Noeud::setPosition(int x , int y)
{
	m_position.setX(x);
	m_position.setY(y);
}
void Noeud::setCouleurFond(QColor couleurFond)
{
	m_couleurFond = couleurFond;
}
void Noeud::setCouleurPolice(QColor couleurPolice)
{
	m_couleurPolice = couleurPolice;
}
void Noeud::setCouleurBordure(QColor couleurBordure)
{
	m_couleurBordure = couleurBordure;
}
void Noeud::setIndice(int indice)
{
	m_indice = indice;
}

void Noeud::setWidth(int w)
{
	m_widthRect = w;
}
void Noeud::setHeigth(int h)
{
	m_heigth = h;
}

void Noeud::setVisible(bool b)
{
	m_visible = b;
}