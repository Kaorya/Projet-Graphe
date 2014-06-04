#include "graphe.h"

Graphe::Graphe()
{
}

Graphe::~Graphe()
{
}
/*
void Graphe::supprimerNoeud(int i)
{
	for(unsigned int j = 0; j < m_tabLien.size(); j++)
	{
		//qDebug() << "for des liens a delete";
		if(m_tabLien[j].getNoeudSource() == i || m_tabLien[j].getNoeudCible() == i)
		{
			m_tabLien.erase(m_tabLien.begin()+j);
			j--;

			for(unsigned int k = j+1; k < m_tabLien.size(); k++)
			{
				m_tabLien[k].setIndice(m_tabLien[k].getIndice()-1);
			}
		}
	}

	for(unsigned int j = 0; j < m_tabLien.size(); j++)
	{

		if(m_tabLien[j].getNoeudSource() > i)
		{
			m_tabLien[j].setNoeudSource(m_tabLien[j].getNoeudSource()-1);
		}
		if(m_tabLien[j].getNoeudCible() > i)
		{
			m_tabLien[j].setNoeudCible(m_tabLien[j].getNoeudCible()-1);
		}
	}
	

		//qDebug() << " apres le for des liens a delete";

		m_tabNoeud.erase(m_tabNoeud.begin()+i);

		for(unsigned int j = i; j < m_tabNoeud.size(); j++)
		{
			m_tabNoeud[j].setIndice(m_tabNoeud[j].getIndice()-1);
			//qDebug() << "Indice du noeud " << j << " : " << g.m_tabNoeud[j].getIndice();
		}
	
}
void Graphe::supprimerLien(int i)
{
	m_tabLien.erase(m_tabLien.begin()+i);

	for(unsigned int k = i; k < m_tabLien.size(); k++)
	{
		m_tabLien[k].setIndice(m_tabLien[k].getIndice()-1);
	}	
}
*/