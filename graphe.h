#ifndef graphe_h
#define graphe_h

#include <vector>
#include "noeud.h"
#include "lien.h"

class Graphe
{
public:
	std::vector<Noeud> m_tabNoeud;
	std::vector<Lien> m_tabLien;


	Graphe();
	~Graphe();
/*
	void supprimerNoeud(int i);
	void supprimerLien(int i);
*/
};

#endif