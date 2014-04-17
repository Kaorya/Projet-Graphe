#ifndef lien_h
#define lien_h

#include <vector>
#include "noeud.h"

class Lien
{
    std::string m_nom;
    Noeud m_noeudSource;
    Noeud m_noeudCible;
    std::vector<Position> m_tabCassure;

public :
    Lien(std::string nom, Noeud noeudSource, Noeud noeudCible);
   
   	std::string getNom() const;
   	const Noeud getNoeudSource() const;
   	const Noeud getNoeudCible() const; 
};

#endif
