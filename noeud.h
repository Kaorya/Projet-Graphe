#ifndef noeud_h
#define noeud_h

#include <iostream>
#include <string>
#include <QColor>
#include <QPainter>
#include "position.h"

class Noeud
{
    std::string m_nom;
    Position m_position;
    QColor m_couleurFond;
    QColor m_couleurPolice;
    QColor m_couleurBordure;
    int m_style; // 0 1 mettre une enum plus tard
    int m_indice;
    int m_widthRect;
    int m_heigth;
    //bool estdansleNoeud;


public :
        Noeud(std::string nom, int indice);
        Noeud(std::string nom, int x, int y, int indice, int width, int heigth);
        Noeud(std::string nom, Position const &p, int indice);
        
        std::string getNom() const;
        const Position getPosition() const;
        QColor getCouleurFond() const;
        QColor getCouleurPolice() const;
        QColor getCouleurBordure() const;
        int getWidth() const;
        int getHeight() const;
        int getStyle() const;

        int getIndice() const;
        void setNom(std::string nom);
        void setPosition(int x, int y);
        void setCouleurFond(QColor couleurFond);
        void setCouleurPolice(QColor couleurPolice);
        void setCouleurBordure(QColor couleurBordure);
        void setWidth(int w);
        void setHeigth(int h);
        void setIndice(int i);
        void setStyle(int s);
   
};

#endif
