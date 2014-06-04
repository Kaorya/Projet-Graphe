#include "commandChangerCouleurNoeud.h"

CommandChangerCouleurNoeud::CommandChangerCouleurNoeud(ZoneDessin* zone, int i, QColor aBordure, QColor aTexte, QColor aFond, QColor nBordure, QColor nTexte, QColor nFond):indice(i),ancienneCouleurBordure(aBordure),ancienneCouleurTexte(aTexte),ancienneCouleurFond(aFond),nouvelleCouleurBordure(nBordure),nouvelleCouleurTexte(nTexte),nouvelleCouleurFond(nFond)
{
	m_zone = zone;
}

void CommandChangerCouleurNoeud::undo()
{
  m_zone->g.m_tabNoeud[indice].setCouleurPolice(ancienneCouleurTexte);
  m_zone->g.m_tabNoeud[indice].setCouleurFond(ancienneCouleurFond);
  m_zone->g.m_tabNoeud[indice].setCouleurBordure(ancienneCouleurBordure);

  m_zone->tabRect[indice]->setPen(m_zone->g.m_tabNoeud[indice].getCouleurBordure());
  m_zone->tabRect[indice]->setBrush(m_zone->g.m_tabNoeud[indice].getCouleurFond());
  m_zone->tabTxtRect[indice]->setDefaultTextColor(m_zone->g.m_tabNoeud[indice].getCouleurPolice());
}
void CommandChangerCouleurNoeud::redo()
{
  m_zone->g.m_tabNoeud[indice].setCouleurPolice(nouvelleCouleurTexte);
  m_zone->g.m_tabNoeud[indice].setCouleurFond(nouvelleCouleurFond);
  m_zone->g.m_tabNoeud[indice].setCouleurBordure(nouvelleCouleurBordure);

  m_zone->tabRect[indice]->setPen(m_zone->g.m_tabNoeud[indice].getCouleurBordure());
  m_zone->tabRect[indice]->setBrush(m_zone->g.m_tabNoeud[indice].getCouleurFond());
  m_zone->tabTxtRect[indice]->setDefaultTextColor(m_zone->g.m_tabNoeud[indice].getCouleurPolice());
}