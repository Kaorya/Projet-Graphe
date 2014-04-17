#include "dialogSave.h"


DialogSave::DialogSave(QString message ,QWidget * parent) : QDialog(parent) {

	//******************************************************//
    //       Déclarations des Widgets et Layouts
    //******************************************************//

	vboxPrincipale = new QVBoxLayout(this);
	hboxBoutons = new QHBoxLayout();
	texte = new QLabel(message);
	bOui = new QPushButton("Oui");
	bNon = new QPushButton("Non");


	//******************************************************//
    //       Ajout des widget/layout à l'affichage
    //******************************************************//

	hboxBoutons->addStretch(5);
	hboxBoutons->addWidget(bOui);
	hboxBoutons->addWidget(bNon);
	vboxPrincipale->addWidget(texte);
	vboxPrincipale->addLayout(hboxBoutons);

}

QPushButton* DialogSave::getBOui()
{
	return bOui;
}
QPushButton* DialogSave::getBNon()
{
	return bNon;
}