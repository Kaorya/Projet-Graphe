#ifndef lien_h
#define lien_h

#include <vector>
#include "noeud.h"

class Lien
{
    std::string m_nom;
    int m_noeudSource;
    int m_noeudCible;
    Position m_positionNomLien;
    int m_width;
    int m_height;
    int m_fleche; // 0 1 2
    QColor m_couleurLien;
    QColor m_couleurPoliceLien;
    int m_indice;
    

public :
    std::vector<Position> m_tabCassure;
    Lien(std::string nom, int S, int C, int indice);
   
   	std::string getNom() const;
   	int getNoeudSource() const;
   	int getNoeudCible() const;
   	const Position getPosition() const;
    int getWidth() const;
    int getHeight() const;
    QColor getCouleurLien() const;
    QColor getCouleurPoliceLien() const;
    int getFleche() const;
    int getIndice() const;
   	std::vector<Position> getTabCassure() const;
   	void setNom(std::string nom);
    void setNoeudSource(int i);
    void setNoeudCible(int i);
   	void setPositionNomLien(int x, int y);
    void setWidth(int w);
    void setHeight(int h);
    void setCouleurLien(QColor c);
    void setCouleurPoliceLien(QColor c);
    void setFleche(int f);
    void setIndice(int i);

};
//test modification pour git

#endif
