#include "dialogCreerNoeud.h"


DialogCreerNoeud::DialogCreerNoeud(QWidget * parent) : QDialog(parent) {

	//******************************************************//
    //       Déclarations des Widgets et Layouts
    //******************************************************//

	vboxPrincipale = new QVBoxLayout(this);
	hboxBoutons = new QHBoxLayout();
	hboxTexte = new QHBoxLayout();
	texte = new QLabel("Nom : ");
	nomNoeud = new QLineEdit();
	bCreer = new QPushButton("Creer");
	bAnnuler = new QPushButton("Annuler");



	//******************************************************//
    //       Ajout des widget/layout à l'affichage
    //******************************************************//

	hboxBoutons->addStretch(5);
	hboxBoutons->addWidget(bCreer);
	hboxBoutons->addWidget(bAnnuler);
	hboxTexte->addWidget(texte);
	hboxTexte->addWidget(nomNoeud);
	vboxPrincipale->addLayout(hboxTexte);
	vboxPrincipale->addLayout(hboxBoutons);

}

QPushButton* DialogCreerNoeud::getBCreer() const
{
	return bCreer;
}
QPushButton* DialogCreerNoeud::getBAnnuler() const
{
	return bAnnuler;
}
QString DialogCreerNoeud::getNomNoeud() const
{
	return nomNoeud->text();
}
void DialogCreerNoeud::setNomNoeud(QString s)
{
	nomNoeud->setText(s);
}
