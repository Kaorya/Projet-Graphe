#include "MyMainWindows.h"
#include <string>

MyMainWindows::MyMainWindows(QWidget * parent) : QWidget(parent)
{
    //******************************************************//
    //       Déclarations des Widgets et Layouts
    //******************************************************//

     	hboxPrincipale = new QHBoxLayout(this);
      vboxPrincipale = new QVBoxLayout();
      zone = new ZoneDessin();
      hboxBoutons = new QHBoxLayout();
      vboxBoutons1 = new QVBoxLayout();
      vboxBoutons2 = new QVBoxLayout();


      menuBar = new QMenuBar(this);
      menuFichier = new QMenu("Fichier",menuBar);
      menuEdition = new QMenu("Edition",menuBar);
      //actions
      aNouveauGraphe = new QAction("Nouveau Graphe",menuFichier);
      aImporter = new QAction("Importer",menuFichier);
      aExporter = new QAction("Exporter",menuFichier);
      aExporterImage = new QAction("Exporter en tant qu'image",menuFichier);
      aQuitter = new QAction("Quitter",menuFichier);

      aAnnuler = new QAction("Annuler",menuEdition);
      aRetablir = new QAction("Retablir",menuEdition);
        
      //Déclaration boutons
      bAjoutNoeud = new QPushButton("Ajouter noeud");
      bAjoutLien = new QPushButton("Ajouter lien");
      bSupprimerNoeud = new QPushButton("Supprimer noeud");
      bSupprimerLien = new QPushButton("Supprimer lien");  

      //Déclaration des dialog
      dNouveauGraphe = new DialogSave("Le fichier en cours va etre efface, voulez-vous le sauvegarder ?");
      dImporter = new DialogSave("Le fichier en cours va etre efface, voulez-vous le sauvegarder ?");
      dExporter = new DialogSave("Voulez-vous sauvegarder ?");
      dQuitter = new DialogSave("Le fichier en cours va etre efface, voulez-vous le sauvegarder ?");

      dCreerNoeud = new DialogCreerNoeud();
      dCreerLien = new DialogCreerNoeud();
      
      dSaveBeforeNouveauGraphe = new QFileDialog();
      dSaveBeforeImporter = new QFileDialog();
      dSaveExporter = new QFileDialog();
      dSaveImage = new QFileDialog();
      dSaveBeforeQuitter = new QFileDialog();
      dOpenImporter = new QFileDialog();
  
      //******************************************************//
      //                SLOTS ET SIGNAUX
      //******************************************************//

      //MenuFichier
      //Nouveau Graphe : 
      connect(aNouveauGraphe, SIGNAL(triggered()), this, SLOT(appelDNouveauGraphe()));
      connect(this, SIGNAL(signalDNouveauGraphe(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      //Nouveau graphe : sauvegarder ? -> non :
      connect(dNouveauGraphe->getBNon(), SIGNAL(clicked()), dNouveauGraphe, SLOT(close()));
      connect(dNouveauGraphe->getBNon(), SIGNAL(clicked()), zone, SLOT(nouveauGraphe()));
      //Nouveau graphe : sauvegarder ? -> oui : 
      connect(dNouveauGraphe->getBOui(),SIGNAL(clicked()), dNouveauGraphe, SLOT(close()));
      connect(dNouveauGraphe->getBOui(),SIGNAL(clicked()), this, SLOT(appelDSaveBeforeNouveauGraphe()));
      //Nouveau graphe : sauvegarder ? -> oui -> annuler : automatique
      //Nouveau graphe : sauvegarder ? -> oui -> enregistrer :
      // à faire
      connect(dSaveBeforeNouveauGraphe, SIGNAL(rejected()), zone, SLOT(nouveauGraphe()));
         
      //Importer :
      connect(aImporter, SIGNAL(triggered()), this, SLOT(appelDImporter()));
      connect(this, SIGNAL(signalDImporter(QDialog*)),this, SLOT(apparitionDialog(QDialog*)));
      //Importer : sauvegarder ? -> non
      connect(dImporter->getBNon(), SIGNAL(clicked()), dImporter, SLOT(close()));
      connect(dImporter->getBNon(), SIGNAL(clicked()), this, SLOT(appelDOpenImporter()));
      //Importer : sauvegarder ? -> oui
      connect(dImporter->getBOui(), SIGNAL(clicked()), dImporter, SLOT(close()));
      connect(dImporter->getBOui(), SIGNAL(clicked()), this, SLOT(appelDSaveBeforeImporter())); 

      //Exporter :
      connect(aExporter, SIGNAL(triggered()), this, SLOT(appelDExporter()));
      connect(this, SIGNAL(signalDExporter(QDialog*)),this, SLOT(apparitionDialog(QDialog*)));
      //Exporter : sauvegarder ? -> non
      connect(dExporter->getBNon(), SIGNAL(clicked()), dExporter, SLOT(close()));
      //Exporter : sauvegarder ? -> oui
      connect(dExporter->getBOui(),SIGNAL(clicked()), dExporter, SLOT(close()));
      connect(dExporter->getBOui(),SIGNAL(clicked()), this ,SLOT(appelDSaveExporter()));   

      //Exporter Image :
      connect(aExporterImage, SIGNAL(triggered()), this, SLOT(appelDSaveImage()));

      //Quitter : 
      connect(aQuitter, SIGNAL(triggered()), this, SLOT(appelDQuitter()));
      connect(this, SIGNAL(signalDQuitter(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      //Quitter : sauvegarder ? -> non
      connect(dQuitter->getBNon(), SIGNAL(clicked()), this, SLOT(close()));
      connect(dQuitter->getBNon(), SIGNAL(clicked()), dQuitter, SLOT(close()));
      //Quitter : sauvegarder ? -> oui
      connect(dQuitter->getBOui(),SIGNAL(clicked()), dQuitter, SLOT(close()));
      connect(dQuitter->getBOui(),SIGNAL(clicked()), this ,SLOT(appelDSaveBeforeQuitter()));

      //Creer Noeud
      connect(bAjoutNoeud, SIGNAL(clicked()), this, SLOT(appelDCreerNoeud()));
      connect(this, SIGNAL(signalDNouveauNoeud(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      //Creer Noeud : Annuler
      connect(dCreerNoeud->getBAnnuler(), SIGNAL(clicked()), dCreerNoeud, SLOT(close()));
      //Creer Noeud : Creer
      connect(dCreerNoeud->getBCreer(), SIGNAL(clicked()), dCreerNoeud, SLOT(close()));
      connect(dCreerNoeud->getBCreer(), SIGNAL(clicked()), this, SLOT(ajoutNoeud()));

      //Creer Lien
      connect(bAjoutLien, SIGNAL(clicked()), this, SLOT(appelDCreerLien()));
      connect(this, SIGNAL(signalDNouveauLien(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      //Creer Lien : Annuler
      connect(dCreerLien->getBAnnuler(), SIGNAL(clicked()), dCreerLien, SLOT(close()));
      //creer Lien : Creer
      connect(dCreerLien->getBCreer(), SIGNAL(clicked()), dCreerLien, SLOT(close()));
      connect(dCreerLien->getBCreer(), SIGNAL(clicked()), this, SLOT(ajoutLien()));

      //Envoie du nom du noeud/lien a Zone
      connect(this, SIGNAL(envoieNomNoeud(std::string)), zone, SLOT(recuperationNomNoeud(std::string)));

      //******************************************************//
      //       Ajout des widget/layout à l'affichage
      //******************************************************//
    
       //Affichage
        menuBar->addMenu(menuFichier);
        menuBar->addMenu(menuEdition);
        menuFichier->addAction(aNouveauGraphe);
        menuFichier->addAction(aImporter);
        menuFichier->addAction(aExporter);
        menuFichier->addAction(aExporterImage);
        menuFichier->addAction(aQuitter);

        menuEdition->addAction(aAnnuler);
        menuEdition->addAction(aRetablir);

        //Ajout des widgets aux layout

        //vboxs des boutons

        vboxBoutons1->addWidget(bAjoutNoeud);
        vboxBoutons1->addWidget(bSupprimerNoeud);
        vboxBoutons2->addWidget(bAjoutLien);
        vboxBoutons2->addWidget(bSupprimerLien);

        hboxBoutons->addLayout(vboxBoutons1);
        hboxBoutons->addLayout(vboxBoutons2);
       
        //vboxPrincipale
        vboxPrincipale->addLayout(hboxBoutons);
        vboxPrincipale->addStretch(5);

        //hboxPrincipale 
        hboxPrincipale->setMenuBar(menuBar);
        hboxPrincipale->addLayout(vboxPrincipale);
        hboxPrincipale->addWidget(zone);

}

MyMainWindows::~MyMainWindows()
{
  delete hboxPrincipale;
  delete vboxPrincipale;
  delete menuBar;
}

//SLOTS de mymainWindows


void MyMainWindows::apparitionDialog(QDialog* d)
{
  if(!d->isVisible())
  {
    d->exec();
  }

}

void MyMainWindows::appelDNouveauGraphe()
{
  emit signalDNouveauGraphe(dNouveauGraphe);
}

void MyMainWindows::appelDImporter()
{
  emit signalDImporter(dImporter);
}
void MyMainWindows::appelDExporter()
{
  emit signalDExporter(dExporter);
}

void MyMainWindows::appelDQuitter()
{
  emit signalDQuitter(dQuitter);
}

void MyMainWindows::appelDCreerNoeud()
{
  emit signalDNouveauNoeud(dCreerNoeud);
}
void MyMainWindows::appelDCreerLien()
{
  emit signalDNouveauLien(dCreerLien);
}

void MyMainWindows::appelDSaveBeforeNouveauGraphe()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveBeforeNouveauGraphe, "Enregistrer votre progression", QString(), "Extension (*.pouet)");
  if(!cheminFichier.isEmpty())
  {
    //TODO RECUPERER LE CHEMIN VERS L'INFINI !!
    qDebug() << "Le chemin n'est pas vide : " << cheminFichier;
    sauvegarde(cheminFichier);
  }
  zone->nouveauGraphe();
}
void MyMainWindows::appelDSaveBeforeImporter()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveBeforeImporter, "Enregistrer votre progression", QString(), "Extension (*.pouet)");
  if(!cheminFichier.isEmpty())
  {
    sauvegarde(cheminFichier);
  }
  appelDOpenImporter();
}
void MyMainWindows::appelDOpenImporter()
{
  cheminFichier = QFileDialog::getOpenFileName(dOpenImporter, "Charger un fichier", QString(), "Extension (*.pouet)");
  if(!cheminFichier.isEmpty())
  {
    chargement(cheminFichier);
  }
}
void MyMainWindows::appelDSaveExporter()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveExporter, "Enregistrer votre progression", QString(), "Extension (*.pouet)");
  if(!cheminFichier.isEmpty())
  {
    sauvegarde(cheminFichier);
  }
}

void MyMainWindows::appelDSaveImage()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveImage, "Enregistrer sous forme d'image", QString(), "Extension (*.*)");
  if(!cheminFichier.isEmpty())
  {
    sauvegardeImage(cheminFichier);
  }
}


void MyMainWindows::appelDSaveBeforeQuitter()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveBeforeQuitter, "Enregistrer votre progression", QString(), "Extension (*.pouet)");
  if(!cheminFichier.isEmpty())
  {
    sauvegarde(cheminFichier);
  }
  this->close();
}

void MyMainWindows::ajoutNoeud()
{
  zone->setAjoutNoeud(true);
  envoieNomNoeud(dCreerNoeud->getNomNoeud().toStdString());
  dCreerNoeud->setNomNoeud("");
}

void MyMainWindows::ajoutLien()
{
  if(!(zone->getAjoutLien()))
    zone->setAjoutLien(true);
  else
  {
    zone->setNbrClik(0);
  }
  envoieNomNoeud(dCreerLien->getNomNoeud().toStdString());
  dCreerLien->setNomNoeud("");
}

void MyMainWindows::sauvegarde(QString chemin)
{
  qDebug() << "Sauvegarde en cours...";
  qDebug() << "Le chemin n'est pas vide : " << chemin;
}

void MyMainWindows::sauvegardeImage(QString chemin)
{
  qDebug() << "Sauvegarde de l'image en cours...";
  qDebug() << "position x et y max : (" << zone->getImage()->maxX << "," << zone->getImage()->maxY << ")" ;
  qDebug() << "position x et y min : (" << zone->getImage()->minX << "," << zone->getImage()->minY << ")" ;
  zone->getImage()->imageSave = zone->getImage()->image->copy(zone->getImage()->minX - 10, zone->getImage()->minY - 10,zone->getImage()->maxX - zone->getImage()->minX + 10, zone->getImage()->maxY - zone->getImage()->minY + 20);

  QString s(".png");
  if(!chemin.endsWith(s, Qt::CaseSensitive))
  {
    qDebug() << "Le fichier ne se finit pas par .png";
    chemin.insert(chemin.size(),s);
  }
  qDebug() << "Le chemin n'est pas vide : " << chemin;
  zone->getImage()->imageSave.save(chemin,"PNG", -1);

  
}

void MyMainWindows::chargement(QString chemin)
{
  qDebug() << "Chargement en cours...";
  qDebug() << "Le chemin n'est pas vide : " << chemin;
}

