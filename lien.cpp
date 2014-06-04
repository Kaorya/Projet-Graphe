#include "lien.h"

Lien::Lien(std::string nom, int S, int C, int indice):m_nom(nom),m_noeudSource(S),m_noeudCible(C),m_indice(indice)
{
	//std::cout << "Lien cree" << std::endl;
	m_couleurLien = Qt::blue;
	m_couleurPoliceLien = Qt::blue;
	m_visible = true;
}

std::string Lien::getNom() const
{
	return m_nom;
}
int Lien::getNoeudSource() const
{
	return m_noeudSource;
}
int Lien::getNoeudCible() const
{
	return m_noeudCible;
}
const Position Lien::getPosition() const
{
	return m_positionNomLien;
}
QColor Lien::getCouleurLien() const
{
	return m_couleurLien;
}
QColor Lien::getCouleurPoliceLien() const
{
	return m_couleurPoliceLien;
}

int Lien::getWidth() const
{
	return m_width;
}
int Lien::getHeight() const
{
	return m_height;
}
int Lien::getIndice() const
{
	return m_indice;
}
bool Lien::isVisible() const
{
	return m_visible;
}

//setters
void Lien::setNom(std::string nom)
{
	m_nom = nom;
}
void Lien::setNoeudSource(int i)
{
	m_noeudSource = i;
}
void Lien::setNoeudCible(int i)
{
	m_noeudCible = i;
}
void Lien::setPositionNomLien(int x, int y)
{
	m_positionNomLien.setX(x);
	m_positionNomLien.setY(y);
}
void Lien::setWidth(int w)
{
	m_width = w;
}
void Lien::setHeight(int h)
{
	m_height = h;
}
void Lien::setCouleurLien(QColor c)
{
	m_couleurLien = c;
}
 void Lien::setCouleurPoliceLien(QColor c)
 {
 	m_couleurPoliceLien = c;
 }

void Lien::setIndice(int i)
{
	m_indice = i;
}
void Lien::setVisible(bool b)
{
	m_visible = b;
}