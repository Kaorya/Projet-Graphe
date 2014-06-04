#include "dialogChangeStyle.h"

DialogChangeStyle::DialogChangeStyle(QWidget * parent) : QDialog(parent)
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
	txtCouleurFond = new QLabel("Couleur de fond : ");
	txtCouleurBordure = new QLabel("Couleur de la bordure : ");
	cCouleurPolice = new QComboBox();
	cCouleurFond = new QComboBox();
	cCouleurBordure = new QComboBox();
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

    cCouleurFond->addItem("Rose");
    cCouleurFond->addItem("Jaune");
    cCouleurFond->addItem("Orange");
    cCouleurFond->addItem("Rouge");
    cCouleurFond->addItem("Violet");
    cCouleurFond->addItem("Bleu");
    cCouleurFond->addItem("Vert");
    cCouleurFond->addItem("Noir");
    cCouleurFond->addItem("Blanc");

    cCouleurBordure->addItem("Rose");
    cCouleurBordure->addItem("Jaune");
    cCouleurBordure->addItem("Orange");
    cCouleurBordure->addItem("Rouge");
    cCouleurBordure->addItem("Violet");
    cCouleurBordure->addItem("Bleu");
    cCouleurBordure->addItem("Vert");
    cCouleurBordure->addItem("Noir");
    cCouleurBordure->addItem("Blanc");

	//******************************************************//
    //       Ajout des widget/layout à l'affichage
    //******************************************************//

	hboxBoutons->addWidget(bValider);
	hboxBoutons->addWidget(bAnnuler);
	vboxCombo->addWidget(cCouleurPolice);
	vboxCombo->addWidget(cCouleurFond);
	vboxCombo->addWidget(cCouleurBordure);
	vboxTexte->addWidget(txtCouleurPolice);
	vboxTexte->addWidget(txtCouleurFond);
	vboxTexte->addWidget(txtCouleurBordure);

	hboxPrincipale->addLayout(vboxTexte);
	hboxPrincipale->addLayout(vboxCombo);
	vboxPrincipale->addLayout(hboxPrincipale);
	vboxPrincipale->addLayout(hboxBoutons);

	this->setWindowTitle("Changer le style du noeud");

}

QPushButton* DialogChangeStyle::getBValider() const
{
	return bValider;
}

QPushButton* DialogChangeStyle::getBAnnuler() const
{
	return bAnnuler;
}

QColor DialogChangeStyle::getCouleurPolice() const
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

QColor DialogChangeStyle::getCouleurFond() const
{

	switch(cCouleurFond->currentIndex()){
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

QColor DialogChangeStyle::getCouleurBordure() const
{
	switch(cCouleurBordure->currentIndex()){
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

void  DialogChangeStyle::setCouleurPolice(QString s)
{
	int i = cCouleurPolice->findText(s, Qt::MatchExactly);
	cCouleurPolice->setCurrentIndex(i);
}
void  DialogChangeStyle::setCouleurFond(QString s)
{
	int i = cCouleurFond->findText(s, Qt::MatchExactly);
	cCouleurFond->setCurrentIndex(i);
}
void  DialogChangeStyle::setCouleurBordure(QString s)
{
	int i = cCouleurBordure->findText(s, Qt::MatchExactly);
	cCouleurBordure->setCurrentIndex(i);
}