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

	//std::vector<Noeud> getTabNoeud() const;
	//std::vector<Lien> getTabLien() const;
};

#endif