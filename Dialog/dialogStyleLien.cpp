#include "dialogStyleLien.h"

DialogStyleLien::DialogStyleLien(QWidget * parent) : QDialog(parent)
{

	//******************************************************//
    //       Déclarations des Widgets et Layouts
    //******************************************************//

	vboxPrincipale = new QVBoxLayout(this);
	hboxPrincipale = new QHBoxLayout();
	vboxTexte = new QVBoxLayout();
	vboxCombo = new QVBoxLayout();
	hboxBoutons = new QHBoxLayout();

	txtCouleurPolice = new QLabel("Couleur de la police : ");
	txtCouleurLien = new QLabel("Couleur du lien : ");
	cCouleurPolice = new QComboBox();
	cCouleurLien = new QComboBox();
	bValider = new QPushButton("Valider");
	bAnnuler = new QPushButton("Annuler");

	//******************************************************//
    //       Ajout des items au ComboBox
    //******************************************************//

    cCouleurPolice->addItem("Rose");
    cCouleurPolice->addItem("Jaune");
    cCouleurPolice->addItem("Orange");
    cCouleurPolice->addItem("Rouge");
    cCouleurPolice->addItem("Violet");
    cCouleurPolice->addItem("Bleu");
    cCouleurPolice->addItem("Vert");
    cCouleurPolice->addItem("Noir");
    cCouleurPolice->addItem("Blanc");

    cCouleurLien->addItem("Rose");
    cCouleurLien->addItem("Jaune");
    cCouleurLien->addItem("Orange");
    cCouleurLien->addItem("Rouge");
    cCouleurLien->addItem("Violet");
    cCouleurLien->addItem("Bleu");
    cCouleurLien->addItem("Vert");
    cCouleurLien->addItem("Noir");
    cCouleurLien->addItem("Blanc");

	//******************************************************//
    //       Ajout des widget/layout à l'affichage
    //******************************************************//

	hboxBoutons->addWidget(bValider);
	hboxBoutons->addWidget(bAnnuler);
	vboxCombo->addWidget(cCouleurPolice);
	vboxCombo->addWidget(cCouleurLien);
	vboxTexte->addWidget(txtCouleurPolice);
	vboxTexte->addWidget(txtCouleurLien);

	hboxPrincipale->addLayout(vboxTexte);
	hboxPrincipale->addLayout(vboxCombo);
	vboxPrincipale->addLayout(hboxPrincipale);
	vboxPrincipale->addLayout(hboxBoutons);

	this->setWindowTitle("Changer le style du lien");

}

QPushButton* DialogStyleLien::getBValider() const
{
	return bValider;
}

QPushButton* DialogStyleLien::getBAnnuler() const
{
	return bAnnuler;
}

QColor DialogStyleLien::getCouleurPolice() const
{
	switch(cCouleurPolice->currentIndex()){
		case 0:{
			QColor c("#FF6699");
			return c;
			break;
		}
		case 1:{
			QColor c("#FFCC00");
			return c;
			break;
		}
		case 2:{
			QColor c("#FF6600");
			return c;
			break;
		}
		case 3:{
			QColor c(Qt::red);
			return c;
			break;
		}
		case 4:{
			QColor c("#660099");
			return c;
			break;
		}
		case 5:{
			QColor c(Qt::blue);
			return c;
			break;
		}
		case 6:{
			QColor c(Qt::green);
			return c;
			break;
		}
		case 7:{
			QColor c(Qt::black);
			return c;
			break;
		}
		case 8:{
			QColor c(Qt::white);
			return c;
			break;
		}
		default:{
			QColor c(Qt::black);
			return c;
			break;
		}
	};
}

QColor DialogStyleLien::getCouleurLien() const
{

	switch(cCouleurLien->currentIndex()){
		case 0:{
			QColor c("#FF6699");
			return c;
			break;
		}
		case 1:{
			QColor c("#FFCC00");
			return c;
			break;
		}
		case 2:{
			QColor c("#FF6600");
			return c;
			break;
		}
		case 3:{
			QColor c(Qt::red);
			return c;
			break;
		}
		case 4:{
			QColor c("#660099");
			return c;
			break;
		}
		case 5:{
			QColor c(Qt::blue);
			return c;
			break;
		}
		case 6:{
			QColor c(Qt::green);
			return c;
			break;
		}
		case 7:{
			QColor c(Qt::black);
			return c;
			break;
		}
		case 8:{
			QColor c(Qt::white);
			return c;
			break;
		}
		default:{
			QColor c(Qt::black);
			return c;
			break;
		}
	};
}

void  DialogStyleLien::setCouleurPolice(QString s)
{
	int i = cCouleurPolice->findText(s, Qt::MatchExactly);
	cCouleurPolice->setCurrentIndex(i);
}
void  DialogStyleLien::setCouleurLien(QString s)
{
	int i = cCouleurLien->findText(s, Qt::MatchExactly);
	cCouleurLien->setCurrentIndex(i);
}