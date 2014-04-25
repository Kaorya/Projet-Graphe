#ifndef lien_h
#define lien_h

#include <vector>
#include "noeud.h"

class Lien
{
    std::string m_nom;
    Noeud m_noeudSource;
    Noeud m_noeudCible;
    Position m_positionNomLien;
    int fleche; // 0 1 2
    std::vector<Position> m_tabCassure;

public :
    Lien(std::string nom, Noeud const & noeudSource, Noeud const & noeudCible);
   
   	std::string getNom() const;
   	const Noeud getNoeudSource() const;
   	const Noeud getNoeudCible() const;
   	const Position getPosition() const;
   	std::vector<Position> getTabCassure() const;
   	void setNom(std::string nom);
   	void setPositionNomLien(int x, int y);

};
//test modification pour git

#endif
