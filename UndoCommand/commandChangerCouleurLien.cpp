#include "commandChangerCouleurLien.h"

CommandChangerCouleurLien::CommandChangerCouleurLien(ZoneDessin* zone, int i, QColor aLigne, QColor aTexte, QColor nLigne, QColor nTexte):indice(i),ancienneCouleurLigne(aLigne),ancienneCouleurTexte(aTexte),nouvelleCouleurLigne(nLigne),nouvelleCouleurTexte(nTexte)
{
	m_zone = zone;
}

void CommandChangerCouleurLien::undo()
{
  m_zone->g.m_tabLien[indice].setCouleurPoliceLien(ancienneCouleurTexte);
  m_zone->g.m_tabLien[indice].setCouleurLien(ancienneCouleurLigne);

  m_zone->tabLine[indice]->setPen(m_zone->g.m_tabLien[indice].getCouleurLien());
  m_zone->tabTxtLine[indice]->setDefaultTextColor(m_zone->g.m_tabLien[indice].getCouleurPoliceLien());
  //redessiner seulement le lien;
}
void CommandChangerCouleurLien::redo()
{
  m_zone->g.m_tabLien[indice].setCouleurPoliceLien(nouvelleCouleurTexte);
  m_zone->g.m_tabLien[indice].setCouleurLien(nouvelleCouleurLigne);

  m_zone->tabLine[indice]->setPen(m_zone->g.m_tabLien[indice].getCouleurLien());
  m_zone->tabTxtLine[indice]->setDefaultTextColor(m_zone->g.m_tabLien[indice].getCouleurPoliceLien());
  //redessiner seulement le lien;

}