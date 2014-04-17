#ifndef noeud_h
#define noeud_h

#include <iostream>
#include <string>
#include "position.h"

class Noeud
{
    std::string m_nom;
    Position m_position;


public :
        Noeud(std::string nom);
        Noeud(std::string nom, int x, int y);
        Noeud(std::string nom, Position const &p);
        
        std::string getNom() const;
        const Position getPosition() const;
   
};

#endif
