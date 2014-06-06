#include "MyMainWindows.h"
#include <string>
#include <QCursor>
#include <QUndoStack>
#include <QUndoCommand>

MyMainWindows::MyMainWindows(QWidget * parent) : QWidget(parent)
{
    //******************************************************//
    //       Déclarations des Widgets et Layouts
    //******************************************************//

     	hboxPrincipale = new QHBoxLayout(this);
      vboxPrincipale = new QVBoxLayout();
      zone = new ZoneDessin();
      hboxBoutons = new QHBoxLayout();
      vboxBoutons = new QVBoxLayout();
      vboxBoutons1 = new QVBoxLayout();
      vboxBoutons2 = new QVBoxLayout();

      m_changeNoeud = false;
      m_changeLien = false;


      menuBar = new QMenuBar(this);
      menuFichier = new QMenu("Fichier",menuBar);
      menuEdition = new QMenu("Edition",menuBar);
      menuAPropos = new QMenu("A propos",menuBar);

      menuClicDroit = new QMenu();
      menuClicDroitLien = new QMenu();
      //actions
      aNouveauGraphe = new QAction("Nouveau Graphe",menuFichier);
      aImporter = new QAction("Importer",menuFichier);
      aExporter = new QAction("Exporter",menuFichier);
      aExporterImage = new QAction("Exporter en tant qu'image",menuFichier);
      aQuitter = new QAction("Quitter",menuFichier);
      aAboutQt = new QAction("About Qt", menuAPropos);
/*
      aAnnuler = new QAction("Annuler",menuEdition);
      aRetablir = new QAction("Retablir",menuEdition);
*/
      aAnnuler = zone->stack->createUndoAction(this, "Annuler");
      aRetablir = zone->stack->createRedoAction(this, "Retablir");

      changerStyle = new QAction("Changer Style", menuClicDroit);
      aChangerStyleLien = new QAction("Changer Style", menuClicDroitLien);
      //aAjouterPointCassure = new QAction("Ajouter un point de Cassure", menuClicDroitLien);
        
      //Déclaration boutons
      bAjoutNoeud = new QPushButton("Ajouter noeud");
      bAjoutLien = new QPushButton("Ajouter lien");
      bSupprimer = new QPushButton("Supprimer");
      bSelection = new QPushButton("Selection");
      bDeplacer = new QPushButton("Se deplacer");  

      //editnom

      editNom = new QLineEdit();
      editNom->setWindowTitle("Changer Nom");

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
      dChangerStyle = new DialogChangeStyle();
      dChangerStyleLien = new DialogStyleLien();

      dImporter->setWindowTitle("Sauvegarde");
      dNouveauGraphe->setWindowTitle("Sauvegarde");
      dQuitter->setWindowTitle("Sauvegarde");
      dExporter->setWindowTitle("Sauvegarde");
      dCreerNoeud->setWindowTitle("Nouveau noeud");
      dCreerLien->setWindowTitle("Nouveau lien");
      this->setWindowTitle("Visualisation de Graphe");
  
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
      connect(zone, SIGNAL(nouveauNoeud()), this, SLOT(emissionSignal()));
      connect(this, SIGNAL(signalDNouveauNoeud(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      //Creer Noeud : Annuler
      connect(dCreerNoeud->getBAnnuler(), SIGNAL(clicked()), dCreerNoeud, SLOT(close()));
      connect(dCreerNoeud->getBAnnuler(), SIGNAL(clicked()), this, SLOT(annulation()));
      //Creer Noeud : Creer
      connect(dCreerNoeud->getBCreer(), SIGNAL(clicked()), dCreerNoeud, SLOT(close()));
      connect(dCreerNoeud->getBCreer(), SIGNAL(clicked()), this, SLOT(ajoutNoeud()));

      //Creer Lien
      connect(bAjoutLien, SIGNAL(clicked()), this, SLOT(appelDCreerLien()));
      connect(zone, SIGNAL(nouveauLien()), this, SLOT(emissionSignal()));
      connect(this, SIGNAL(signalDNouveauLien(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      //Creer Lien : Annuler
      connect(dCreerLien->getBAnnuler(), SIGNAL(clicked()), dCreerLien, SLOT(close()));
      connect(dCreerLien->getBAnnuler(), SIGNAL(clicked()), this, SLOT(annulation()));
      //creer Lien : Creer
      connect(dCreerLien->getBCreer(), SIGNAL(clicked()), dCreerLien, SLOT(close()));
      connect(dCreerLien->getBCreer(), SIGNAL(clicked()), this, SLOT(ajoutLien()));

      //Envoie du nom du noeud/lien a Zone
      connect(this, SIGNAL(envoieNomNoeud(std::string)), zone, SLOT(recuperationNomNoeud(std::string)));

      //Selection
      connect(bSelection, SIGNAL(clicked()), this, SLOT(enSelection()));

      //Deplacement
      connect(bDeplacer, SIGNAL(clicked()), this, SLOT(enDeplacement()));

      //suppression
      connect(bSupprimer, SIGNAL(clicked()), this, SLOT(suppression()));
      connect(this, SIGNAL(signalSupression(std::vector<int>, std::vector<int>)), zone, SLOT(suppression(std::vector<int>, std::vector<int>)));

      //connexion au petit menu
      connect(zone, SIGNAL(afficherMenu(int, int)), this, SLOT(affichageMenu(int, int)));
      connect(changerStyle, SIGNAL(triggered()), this, SLOT(appelDChange()));
      connect(this, SIGNAL(signalDChange(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      connect(dChangerStyle->getBValider(), SIGNAL(clicked()), this, SLOT(changerStyleNoeud()));
      connect(dChangerStyle->getBValider(), SIGNAL(clicked()), dChangerStyle, SLOT(close()));
      connect(dChangerStyle->getBAnnuler(), SIGNAL(clicked()), dChangerStyle, SLOT(close()));

      //connexion au petit menu pour lien
      connect(zone, SIGNAL(afficherMenuLien(int, int)), this, SLOT(affichageMenuLien(int, int)));
      connect(aChangerStyleLien, SIGNAL(triggered()), this, SLOT(appelDChangeLien()));
      connect(this, SIGNAL(signalDChangeLien(QDialog*)), this, SLOT(apparitionDialog(QDialog*)));
      connect(dChangerStyleLien->getBValider(), SIGNAL(clicked()), this, SLOT(changerStyleLien()));
      connect(dChangerStyleLien->getBValider(), SIGNAL(clicked()), dChangerStyleLien, SLOT(close()));
      connect(dChangerStyleLien->getBAnnuler(), SIGNAL(clicked()), dChangerStyleLien, SLOT(close()));

      //QLineEdit nom/Lien
      connect(editNom, SIGNAL(returnPressed()), this, SLOT(changerNom()));
      connect(editNom, SIGNAL(returnPressed()), editNom, SLOT(close()));
      connect(zone, SIGNAL(changerNomNoeud(int, int)), this, SLOT(changerNomNoeud(int, int)));
      connect(zone, SIGNAL(changerNomLien(int, int)), this, SLOT(changerNomLien(int, int)));

      //Connect/Disconnect pour undo/redo
      //connect(aAnnuler, SIGNAL(triggered()), zone->stack, SLOT(undo()));
      //connect(aRetablir, SIGNAL(triggered()), zone->stack, SLOT(redo()));
      //******************************************************//
      //                     SHORTCUTS                        //
      //******************************************************//

      QKeySequence raccourciNoeud("n");
      bAjoutNoeud->setShortcut(raccourciNoeud);
      QKeySequence raccourciLien("l");
      bAjoutLien->setShortcut(raccourciLien);
      QKeySequence raccourciSelection("s");
      bSelection->setShortcut(raccourciSelection);
      QKeySequence raccourciDeplacer("d");
      bDeplacer->setShortcut(raccourciDeplacer);
      QKeySequence raccourciSupprimer("Del");
      bSupprimer->setShortcut(raccourciSupprimer);

      QKeySequence raccourciNouveauGraphe("Ctrl+n");
      aNouveauGraphe->setShortcut(raccourciNouveauGraphe);
      QKeySequence raccourciImporter("Ctrl+i");
      aImporter->setShortcut(raccourciImporter);
      QKeySequence raccourciExporter("Ctrl+s");
      aExporter->setShortcut(raccourciExporter);
      QKeySequence raccourciExporterImage("Ctrl+p");
      aExporterImage->setShortcut(raccourciExporterImage);
      QKeySequence raccourciQuitter("Ctrl+q");
      aQuitter->setShortcut(raccourciQuitter);

      QKeySequence raccourciAnnuler("Ctrl+z");
      aAnnuler->setShortcut(raccourciAnnuler);    
      QKeySequence raccourciRetablir("Ctrl+y");
      aRetablir->setShortcut(raccourciRetablir);

      //******************************************************//
      //       Ajout des widget/layout à l'affichage
      //******************************************************//
    
       //Affichage
        menuBar->addMenu(menuFichier);
        menuBar->addMenu(menuEdition);
        menuBar->addMenu(menuAPropos);
        menuFichier->addAction(aNouveauGraphe);
        menuFichier->addAction(aImporter);
        menuFichier->addAction(aExporter);
        menuFichier->addAction(aExporterImage);
        menuFichier->addAction(aQuitter);

        menuEdition->addAction(aAnnuler);
        menuEdition->addAction(aRetablir);

        menuAPropos->addAction(aAboutQt);

        menuClicDroit->addAction(changerStyle);

        menuClicDroitLien->addAction(aChangerStyleLien);
        //menuClicDroitLien->addAction(aAjouterPointCassure);

        //Ajout des widgets aux layout

        //vboxs des boutons

        vboxBoutons1->addWidget(bAjoutNoeud);
        vboxBoutons1->addWidget(bSelection);
        vboxBoutons2->addWidget(bAjoutLien);
        vboxBoutons2->addWidget(bDeplacer);
        

        hboxBoutons->addLayout(vboxBoutons1);
        hboxBoutons->addLayout(vboxBoutons2);
        vboxBoutons->addLayout(hboxBoutons);
        vboxBoutons->addWidget(bSupprimer);

        //vboxPrincipale
        vboxPrincipale->addLayout(vboxBoutons);
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
  delete zone;
  delete hboxBoutons;
  delete vboxBoutons;
  delete vboxBoutons1;
  delete vboxBoutons2;

  delete menuFichier;
  delete menuEdition;
  delete aNouveauGraphe;
  delete aImporter;
  delete aExporter;
  delete aQuitter;
  delete aAnnuler;
  delete aRetablir;
  delete aExporterImage;

  delete menuClicDroit;
  delete changerStyle;
  delete menuClicDroitLien;
  delete aChangerStyleLien;
  //delete aAjouterPointCassure;

  delete bAjoutNoeud;
  delete bAjoutLien;
  delete bSupprimer;
  delete bSelection;
  delete bDeplacer;

  delete dCreerNoeud;
  delete dCreerLien;

  delete dSaveBeforeNouveauGraphe;
  delete dSaveBeforeImporter;
  delete dSaveExporter;
  delete dSaveBeforeQuitter;
  delete dOpenImporter;
  delete dSaveImage;

  delete dChangerStyle;
  delete dChangerStyleLien;      

}

QAction* MyMainWindows::getAboutQt()
{
  return aAboutQt;
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
  //if(!zone->g.m_tabNoeud.empty())
    emit signalDNouveauGraphe(dNouveauGraphe);
}

void MyMainWindows::appelDImporter()
{
  if(!zone->g.m_tabNoeud.empty())
    emit signalDImporter(dImporter);
  else
    appelDOpenImporter();
}
void MyMainWindows::appelDExporter()
{
  emit signalDExporter(dExporter);
}

void MyMainWindows::appelDQuitter()
{
  if(!zone->g.m_tabNoeud.empty())
    emit signalDQuitter(dQuitter);
  else
    this->close();
}

void MyMainWindows::appelDChange()
{
  emit signalDChange(dChangerStyle);
}

void MyMainWindows::appelDChangeLien()
{
  emit signalDChangeLien(dChangerStyleLien);
}

void MyMainWindows::appelDCreerNoeud()
{
  this->setCursor(Qt::CrossCursor);
  bAjoutNoeud->setDown(true);
  bAjoutLien->setDown(false);
  bSelection->setDown(false);
  bDeplacer->setDown(false);
  bSupprimer->setDown(false);
  zone->setAjoutNoeud(true);

}
void MyMainWindows::appelDCreerLien()
{
  this->setCursor(Qt::CrossCursor);
  bAjoutNoeud->setDown(false);
  bAjoutLien->setDown(true);
  bSelection->setDown(false);
  bDeplacer->setDown(false);
  bSupprimer->setDown(false);
  zone->setAjoutLien(true);
}
void MyMainWindows::enSelection()
{
  this->setCursor(Qt::ArrowCursor);
  bAjoutNoeud->setDown(false);
  bAjoutLien->setDown(false);
  bSelection->setDown(true);
  bDeplacer->setDown(false);
  bSupprimer->setDown(false);
  zone->setSelection(true);
}
void MyMainWindows::enDeplacement()
{
  this->setCursor(Qt::OpenHandCursor);
  bAjoutNoeud->setDown(false);
  bAjoutLien->setDown(false);
  bSelection->setDown(false);
  bDeplacer->setDown(true);
  bSupprimer->setDown(false);
  zone->setDeplacer(true);
}


void MyMainWindows::appelDSaveBeforeNouveauGraphe()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveBeforeNouveauGraphe, "Enregistrer votre progression", QString(), "Extension (*.xml)");
  if(!cheminFichier.isEmpty())
  {
    //qDebug() << "Le chemin n'est pas vide : " << cheminFichier;
    sauvegarde(cheminFichier);
  }
  zone->nouveauGraphe();
}
void MyMainWindows::appelDSaveBeforeImporter()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveBeforeImporter, "Enregistrer votre progression", QString(), "Extension (*.xml)");
  if(!cheminFichier.isEmpty())
  {
    sauvegarde(cheminFichier);
  }
  appelDOpenImporter();
}
void MyMainWindows::appelDOpenImporter()
{
  cheminFichier = QFileDialog::getOpenFileName(dOpenImporter, "Charger un fichier", QString(), "Extension (*.xml)");
  if(!cheminFichier.isEmpty())
  {
    chargement(cheminFichier);
  }
}
void MyMainWindows::appelDSaveExporter()
{
  cheminFichier = QFileDialog::getSaveFileName(dSaveExporter, "Enregistrer votre progression", QString(), "Extension (*.xml)");
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
  cheminFichier = QFileDialog::getSaveFileName(dSaveBeforeQuitter, "Enregistrer votre progression", QString(), "Extension (*.xml)");
  if(!cheminFichier.isEmpty())
  {
    sauvegarde(cheminFichier);
  }
  this->close();
}

void MyMainWindows::ajoutNoeud()
{
  bAjoutNoeud->setDown(true);
  envoieNomNoeud(dCreerNoeud->getNomNoeud().toStdString());
  dCreerNoeud->setNomNoeud("");
}

void MyMainWindows::ajoutLien()
{
  bAjoutLien->setDown(true);
  if(!(zone->getAjoutLien()))
    zone->setAjoutLien(true);
  else
  {
    zone->setNbrClik(0);
  }
  envoieNomNoeud(dCreerLien->getNomNoeud().toStdString());
  dCreerLien->setNomNoeud("");
}

void MyMainWindows::emissionSignal()
{
  if(zone->getAjoutNoeud())
    emit signalDNouveauNoeud(dCreerNoeud);
  else if(zone->getAjoutLien())
    emit signalDNouveauLien(dCreerLien);
}

void MyMainWindows::annulation()
{
  if(zone->getAjoutNoeud())
  {
    zone->setAjoutNoeud(false);
    bAjoutNoeud->setDown(false);
    this->setCursor(Qt::ArrowCursor);
  }
  if(zone->getAjoutLien())
  {
    zone->setAjoutLien(false);
    bAjoutLien->setDown(false);
    this->setCursor(Qt::ArrowCursor);
  }
}


void MyMainWindows::suppression()
{
  std::vector<int> v;
  std::vector<int> v2;
    if(zone->vNoeud.empty() && zone->vLien.empty())
    {
      //qDebug() << "vNoeud et vLien sont vide";
      if(zone->getDerniereSelection() == 1)
      { //qDebug() << "derniereSelection : noeud";
         // qDebug() << "dernierNoeudSelect : " << (zone->getDernierNoeudSelect());
          v.push_back((zone->getDernierNoeudSelect()));

          CommandSupprimerNoeud* commande = new CommandSupprimerNoeud(zone, zone->getDernierNoeudSelect());
          zone->stack->push(commande);

      }
      else if(zone->getDerniereSelection() == 2)
      { //qDebug() << "derniereSelection : lien";
          v2.push_back((zone->getDernierLienSelect()));

          CommandSupprimerLien* commande = new CommandSupprimerLien(zone, zone->getDernierLienSelect());
          zone->stack->push(commande);

          zone->lienDejaSuppr.push_back((zone->getDernierLienSelect()));
/*
          qDebug() << "dernierEvent undo:" << zone->getDernierEventUndo();
          if(zone->getDernierEventUndo() >= 0)
          {
            //deconnecter(zone->tabEvent.size()-1, true);
            deconnecter(zone->getDernierEventUndo(), true);
          }
          if(zone->getDernierEvent()+1 < zone->tabEvent.size())
          {
            deconnecter(zone->getDernierEventRedo()+1,false);
          }

          qDebug() << "erase de " << zone->getDernierEvent()+1 << " à " << zone->tabEvent.size();
          zone->tabEvent.erase(zone->tabEvent.begin()+zone->getDernierEvent()+1, zone->tabEvent.end());

          Event* e = new Event(zone->getDernierLienSelect(), Event::LIENDELETED);
          zone->tabEvent.push_back(e);
          connect(zone->tabEvent[zone->tabEvent.size()-1], SIGNAL(remettreLien(int)), zone, SLOT(remettreLien(int)));
          connect(zone->tabEvent[zone->tabEvent.size()-1], SIGNAL(enleverLien(int)), zone, SLOT(enleverLien(int)));

          zone->setDernierEvent(zone->tabEvent.size()-1);
          qDebug() << "dernierEvent après:" << zone->getDernierEvent();

          connecter(zone->getDernierEventUndo(), true);
          qDebug() << "----------";
*/
      }
      emit signalSupression(v,v2);
    }
    else
    {
      CommandSupprimerSelection* commande = new CommandSupprimerSelection(zone, zone->vNoeud, zone->vLien);
      zone->stack->push(commande);

      emit signalSupression(zone->vNoeud, zone->vLien);
    }

}

void MyMainWindows::affichageMenu(int x, int y)
{
  std::vector<Noeud> listeNoeuds;
  listeNoeuds = zone->estDansLesNoeuds(x, y);
  dernierNoeudSelect = listeNoeuds[listeNoeuds.size()-1].getIndice();
  QPoint p(10 + x + zone->view->x() + zone->x() + this->x() - zone->view->horizontalScrollBar()->value(), 30 + y + zone->view->y() + zone->y() + this->y() - zone->view->verticalScrollBar()->value());
  menuClicDroit->popup(p, changerStyle);
  dChangerStyle->setCouleurPolice(couleurToNom(zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurPolice()));
  dChangerStyle->setCouleurFond(couleurToNom(zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurFond()));
  dChangerStyle->setCouleurBordure(couleurToNom(zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurBordure()));
  menuClicDroit->show();
}

void MyMainWindows::affichageMenuLien(int x, int y)
{
  std::vector<Lien> listeLien;
  listeLien = zone->estDansLesLiens(x,y);
  dernierLienSelect = listeLien[listeLien.size()-1].getIndice();
  QPoint p(10 + x + zone->view->x() + zone->x() + this->x() - zone->view->horizontalScrollBar()->value(), 30 + y + zone->view->y() + zone->y() + this->y() - zone->view->verticalScrollBar()->value());
  menuClicDroitLien->popup(p, aChangerStyleLien);
  dChangerStyleLien->setCouleurPolice(couleurToNom(zone->g.m_tabLien[dernierLienSelect].getCouleurPoliceLien()));
  dChangerStyleLien->setCouleurLien(couleurToNom(zone->g.m_tabLien[dernierLienSelect].getCouleurLien()));

  menuClicDroitLien->show();
}

void MyMainWindows::changerStyleNoeud()
{
  CommandChangerCouleurNoeud * command = new CommandChangerCouleurNoeud(zone, dernierNoeudSelect, zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurBordure(), zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurPolice(), zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurFond(),
    dChangerStyle->getCouleurBordure(), dChangerStyle->getCouleurPolice(), dChangerStyle->getCouleurFond());
  zone->stack->push(command);
/*
  zone->g.m_tabNoeud[dernierNoeudSelect].setCouleurPolice(dChangerStyle->getCouleurPolice());
  zone->g.m_tabNoeud[dernierNoeudSelect].setCouleurFond(dChangerStyle->getCouleurFond());
  zone->g.m_tabNoeud[dernierNoeudSelect].setCouleurBordure(dChangerStyle->getCouleurBordure());

  zone->tabRect[dernierNoeudSelect]->setPen(zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurBordure());
  zone->tabRect[dernierNoeudSelect]->setBrush(zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurFond());
  zone->tabTxtRect[dernierNoeudSelect]->setDefaultTextColor(zone->g.m_tabNoeud[dernierNoeudSelect].getCouleurPolice());
  //redessiner seulement le noeud
  */
}

void MyMainWindows::changerStyleLien()
{
  CommandChangerCouleurLien * command = new CommandChangerCouleurLien(zone, dernierLienSelect, zone->g.m_tabLien[dernierLienSelect].getCouleurLien(), zone->g.m_tabLien[dernierLienSelect].getCouleurPoliceLien(), dChangerStyleLien->getCouleurLien(), dChangerStyleLien->getCouleurPolice());
  zone->stack->push(command);
  /*
  zone->g.m_tabLien[dernierLienSelect].setCouleurPoliceLien(dChangerStyleLien->getCouleurPolice());
  zone->g.m_tabLien[dernierLienSelect].setCouleurLien(dChangerStyleLien->getCouleurLien());

  zone->tabLine[dernierLienSelect]->setPen(zone->g.m_tabLien[dernierLienSelect].getCouleurLien());
  zone->tabTxtLine[dernierLienSelect]->setDefaultTextColor(zone->g.m_tabLien[dernierLienSelect].getCouleurPoliceLien());
  //redessiner seulement le lien;
  */
}

void MyMainWindows::changerNomNoeud(int x, int y)
{
  editNom->move(x + zone->view->x() + zone->x() + this->x() - zone->view->horizontalScrollBar()->value(),y + zone->view->y() + zone->y() + this->y() - zone->view->verticalScrollBar()->value());
  std::vector<Noeud> listeNoeuds;
  listeNoeuds = zone->estDansLesNoeuds(x,y);
  dernierNoeudSelect = listeNoeuds[listeNoeuds.size()-1].getIndice();
  QString s = QString::fromStdString(zone->g.m_tabNoeud[dernierNoeudSelect].getNom());
  editNom->setText(s);
  editNom->show();
  m_changeNoeud = true;
}

void MyMainWindows::changerNomLien(int x, int y)
{
  editNom->move(x + zone->view->x() + zone->x() + this->x() - zone->view->horizontalScrollBar()->value(),y + zone->view->y() + zone->y() + this->y() - zone->view->verticalScrollBar()->value());
  std::vector<Lien> listeLien = zone->estDansLesLiens(x,y);
  dernierLienSelect = listeLien[listeLien.size()-1].getIndice();
  QString s = QString::fromStdString(zone->g.m_tabLien[dernierLienSelect].getNom());
  editNom->setText(s);
  editNom->show();
  m_changeLien = true;
}

void MyMainWindows::changerNom()
{
  if(m_changeNoeud)
  {
    std::string s = editNom->text().toStdString();
    CommandChangerNomNoeud * commande = new CommandChangerNomNoeud(zone, dernierNoeudSelect, QString::fromStdString(zone->g.m_tabNoeud[dernierNoeudSelect].getNom()), editNom->text());
    zone->stack->push(commande);

    m_changeNoeud = false;
  }
  else if(m_changeLien)
  {

    std::string s = editNom->text().toStdString();

    CommandChangerNomLien * commande = new CommandChangerNomLien(zone, dernierLienSelect, QString::fromStdString(zone->g.m_tabLien[dernierLienSelect].getNom()), editNom->text());
    zone->stack->push(commande);
 

    m_changeLien = false;
  }
}


QString MyMainWindows::couleurToNom(QColor c)
{
  if(c.name() == "#000000")
  {
    QString s("Noir");
    return s;
  }
  else if(c.name() == "#ff0000")
  {
    QString s("Rouge");
    return s;
  }
  else if(c.name() == "#00ff00")
  {
    QString s("Vert");
    return s;
  }
  else if(c.name() == "#0000ff")
  {
    QString s("Bleu");
    return s;
  }
  else if(c.name() == "#ff6699")
  {
    QString s("Rose");
    return s;
  }
  else if(c.name() == "#ffcc00")
  {
    QString s("Jaune");
    return s;
  }
  else if(c.name() == "#ff6600")
  {
    QString s("Orange");
    return s;
  }
  else if(c.name() == "#660099")
  {
    QString s("Violet");
    return s;
  }
  else if(c.name() == "#ffffff")
  {
    QString s("Blanc");
    return s;
  }
  else
  {
    QString s("Noir");
    return s;
  }
}

/************************************************/
/*                SAUVEGARDE                    */
/************************************************/


void MyMainWindows::sauvegarde(QString chemin)
{
  QDomDocument doc;
  QDomElement graphe;
  QDomElement noeuds;
  QDomElement liens;
  QFile file;
  QTextStream out;

  graphe = doc.createElement("graphe");

  if(zone->g.m_tabNoeud.size() > 0)
      noeuds = doc.createElement("noeuds");
  if(zone->g.m_tabLien.size() > 0)
      liens = doc.createElement("liens");

  QString s(".xml");
  if(!chemin.endsWith(s, Qt::CaseSensitive))
  {
    //qDebug() << "Le fichier ne se finit pas par .xml";
    chemin.insert(chemin.size(),s);
  }
  //qDebug() << "Le chemin n'est pas vide : " << chemin;
  file.setFileName(chemin);
  if(!file.open(QIODevice::WriteOnly))
    return;
  out.setDevice(&file);
  //sauvegarde des noeuds et liens

  if(zone->g.m_tabNoeud.size() > 0)
  {
    int nbrInvisible = 0;
    for(unsigned int i = 0; i < zone->g.m_tabNoeud.size(); i++)
    {
      if(zone->g.m_tabNoeud[i].isVisible())
      {
        QDomElement noeud = doc.createElement("noeud");
        noeuds.appendChild(noeud);
        noeud.setAttribute("indice",QString::number(zone->g.m_tabNoeud[i].getIndice()-nbrInvisible));
        //nom
        QDomElement nom = doc.createElement("nom");
        noeud.appendChild(nom);

        QDomText tnom = doc.createTextNode(QString::fromStdString(zone->g.m_tabNoeud[i].getNom()));
        nom.appendChild(tnom);

        //positionX
        QDomElement positionX = doc.createElement("positionX");
        noeud.appendChild(positionX);

        QDomText tposX = doc.createTextNode(QString::number(zone->g.m_tabNoeud[i].getPosition().getX()));
        positionX.appendChild(tposX);

        //positionY
        QDomElement positionY = doc.createElement("positionY");
        noeud.appendChild(positionY);

        QDomText tposY = doc.createTextNode(QString::number(zone->g.m_tabNoeud[i].getPosition().getY()));
        positionY.appendChild(tposY);

        //largeur
        QDomElement largeur = doc.createElement("largeur");
        noeud.appendChild(largeur);

        QDomText tlargeur = doc.createTextNode(QString::number(zone->g.m_tabNoeud[i].getWidth()));
        largeur.appendChild(tlargeur);

        //hauteur
        QDomElement hauteur = doc.createElement("hauteur");
        noeud.appendChild(hauteur);

        QDomText thauteur = doc.createTextNode(QString::number(zone->g.m_tabNoeud[i].getHeight()));
        hauteur.appendChild(thauteur);

        //positionCouleurFond
        QDomElement couleurFond = doc.createElement("couleurFond");
        noeud.appendChild(couleurFond);

        QDomText tcouleurFond = doc.createTextNode(zone->g.m_tabNoeud[i].getCouleurFond().name());
        couleurFond.appendChild(tcouleurFond);

        //positionCouleurPolice
        QDomElement couleurPolice = doc.createElement("couleurPolice");
        noeud.appendChild(couleurPolice);

        QDomText tcouleurPolice = doc.createTextNode(zone->g.m_tabNoeud[i].getCouleurPolice().name());
        couleurPolice.appendChild(tcouleurPolice);

        //positionCouleurBordure
        QDomElement couleurBordure = doc.createElement("couleurBordure");
        noeud.appendChild(couleurBordure);

        QDomText tcouleurBordure = doc.createTextNode(zone->g.m_tabNoeud[i].getCouleurBordure().name());
        couleurBordure.appendChild(tcouleurBordure);
      }
      else
        nbrInvisible++;
    }
    graphe.appendChild(noeuds);
  }

  if(zone->g.m_tabLien.size() > 0)
  {
    int nbrInvisible = 0;
    for(unsigned int i = 0; i < zone->g.m_tabLien.size(); i++)
    {
     
      if(zone->g.m_tabLien[i].isVisible())
      {

        QDomElement lien = doc.createElement("lien");
        liens.appendChild(lien);
        lien.setAttribute("indice",QString::number(zone->g.m_tabLien[i].getIndice()-nbrInvisible));
        //nom
        QDomElement nom = doc.createElement("nom");
        lien.appendChild(nom);

        QDomText tnom = doc.createTextNode(QString::fromStdString(zone->g.m_tabLien[i].getNom()));
        nom.appendChild(tnom);

        int noeudInvisible = 0;
        for(int j = 0; j < zone->g.m_tabLien[i].getNoeudSource(); j++)
        {
          if(!zone->g.m_tabNoeud[j].isVisible())
          {
              noeudInvisible++;
          }
        }
        //noeudSource
        QDomElement noeudSource = doc.createElement("noeudSource");
        lien.appendChild(noeudSource);

        QDomText tnoeudSource = doc.createTextNode(QString::number(zone->g.m_tabLien[i].getNoeudSource()-noeudInvisible));
        noeudSource.appendChild(tnoeudSource);

        noeudInvisible = 0;
        for(int j = 0; j <= zone->g.m_tabLien[i].getNoeudCible(); j++)
        {
          if(!zone->g.m_tabNoeud[j].isVisible())
            noeudInvisible++;
        }

        //noeudCible
        QDomElement noeudCible = doc.createElement("noeudCible");
        lien.appendChild(noeudCible);

        QDomText tnoeudCible = doc.createTextNode(QString::number(zone->g.m_tabLien[i].getNoeudCible()-noeudInvisible));
        noeudCible.appendChild(tnoeudCible);

        //positionX
        QDomElement positionX = doc.createElement("positionX");
        lien.appendChild(positionX);

        QDomText tpositionX = doc.createTextNode(QString::number(zone->g.m_tabLien[i].getPosition().getX()));
        positionX.appendChild(tpositionX);

        //positionY
        QDomElement positionY = doc.createElement("positionY");
        lien.appendChild(positionY);

        QDomText tpositionY = doc.createTextNode(QString::number(zone->g.m_tabLien[i].getPosition().getY()));
        positionY.appendChild(tpositionY);

        //largeur
        QDomElement largeur = doc.createElement("largeur");
        lien.appendChild(largeur);

        QDomText tlargeur = doc.createTextNode(QString::number(zone->g.m_tabLien[i].getWidth()));
        largeur.appendChild(tlargeur);

        //hauteur
        QDomElement hauteur = doc.createElement("hauteur");
        lien.appendChild(hauteur);

        QDomText thauteur = doc.createTextNode(QString::number(zone->g.m_tabLien[i].getHeight()));
        hauteur.appendChild(thauteur);


        //couleurLien
        QDomElement couleurLien = doc.createElement("couleurLien");
        lien.appendChild(couleurLien);

        QDomText tcouleurLien = doc.createTextNode(zone->g.m_tabLien[i].getCouleurLien().name());
        couleurLien.appendChild(tcouleurLien);

        //couleurPoliceLien
        QDomElement couleurPoliceLien = doc.createElement("couleurPoliceLien");
        lien.appendChild(couleurPoliceLien);

        QDomText tcouleurPoliceLien = doc.createTextNode(zone->g.m_tabLien[i].getCouleurPoliceLien().name());
        couleurPoliceLien.appendChild(tcouleurPoliceLien);
/*
        //fleche
        QDomElement fleche = doc.createElement("fleche");
        lien.appendChild(fleche);

        QDomText tfleche = doc.createTextNode(QString::number(zone->g.m_tabLien[i].getFleche()));
        fleche.appendChild(tfleche);
  */
        /*
        QDomElement pointsCassure = doc.createElement("pointsCassure");
        lien.appendChild(pointsCassure);

          for(unsigned int j = 0; j < zone->g.m_tabLien[i].m_tabCassure; j++)
          {
            QDomElement point = doc.createElement("point");
            pointsCassure.appendChild(point);

            //positionPointX
            QDomElement positionPointX = doc.createElement("positionPointX");
            point.appendChild(positionPointX);

            QDomText tpositionPointX = doc.createTextNode(QString::number(zone->g.m_tabLien[i].m_tabCassure[j].getX()));
            positionPointX.appendChild(tpositionPointX);
            
            //positionPointY
            QDomElement positionPointY = doc.createElement("positionPointY");
            point.appendChild(positionPointY);

            QDomText tpositionPointY = doc.createTextNode(QString::number(zone->g.m_tabLien[i].m_tabCassure[j].getY()));
            positionPointY.appendChild(tpositionPointY);

          }
        */
      }
        else
        {
          nbrInvisible++;
        }
    }
    graphe.appendChild(liens);
  }
  doc.appendChild(graphe);

  //fin sauvegarde
  QDomNode n = doc.createProcessingInstruction("xml","version=\"1.0\"");
  doc.insertBefore(n,doc.firstChild());

  doc.save(out,2);
  file.close();


}

void MyMainWindows::sauvegardeImage(QString chemin)
{
  QImage image(4000,4000,QImage::Format_RGB32);
  image.fill(Qt::white);

  QPainter painter(&image);
  zone->scene->render(&painter);

  QImage imageSave(4000,4000,QImage::Format_RGB32);
  imageSave.fill(Qt::white);

  for(unsigned int i = 0; i < zone->g.m_tabNoeud.size(); i++)
  {
    if(zone->g.m_tabNoeud[i].getPosition().getX() + zone->g.m_tabNoeud[i].getWidth()/2 + 10 > zone->maxX)
       zone->maxX = zone->g.m_tabNoeud[i].getPosition().getX() + zone->g.m_tabNoeud[i].getWidth()/2 + 10;
    if(zone->g.m_tabNoeud[i].getPosition().getY() + zone->g.m_tabNoeud[i].getHeight()/2 + 5 > zone->maxY)
      zone->maxY = zone->g.m_tabNoeud[i].getPosition().getY() + zone->g.m_tabNoeud[i].getHeight()/2 + 5;
    if(zone->g.m_tabNoeud[i].getPosition().getX() - zone->g.m_tabNoeud[i].getWidth()/2 - 5 < zone->minX)
      zone->minX = zone->g.m_tabNoeud[i].getPosition().getX() - zone->g.m_tabNoeud[i].getWidth()/2 -5 ;
    if(zone->g.m_tabNoeud[i].getPosition().getY() - zone->g.m_tabNoeud[i].getHeight()/2 < zone->minY)
       zone->minY = zone->g.m_tabNoeud[i].getPosition().getY() - zone->g.m_tabNoeud[i].getHeight()/2;
  }


  imageSave = image.copy(zone->minX - 10, zone->minY - 10,zone->maxX - zone->minX + 10, zone->maxY - zone->minY + 20);

   QString s(".png");
  if(!chemin.endsWith(s, Qt::CaseSensitive))
  {
    chemin.insert(chemin.size(),s);
  }

  imageSave.save(chemin,"PNG", -1);

}

void MyMainWindows::chargement(QString chemin)
{
  zone->nouveauGraphe();

  QDomDocument doc;
  QFile file(chemin);

  if(!file.open(QIODevice::ReadOnly)){
      return;
  }

  if(!doc.setContent(&file))
  {
    //qDebug() << "return setContent";
  }
  file.close();

  QString indice;
  QDomNodeList tab;
  QDomElement noeud;
  QDomElement lien;
  QDomElement racine = doc.documentElement();
  QDomNode n = racine.firstChild();
  QDomNode n2 = n.firstChild();

  while(!n2.isNull())
  {
    noeud = n2.toElement();

    if(noeud.tagName() == "noeud")
    {
        indice = noeud.attribute("indice");
        tab = noeud.childNodes();

        QString nom = tab.item(0).firstChild().toText().data();
        QString positionX = tab.item(1).firstChild().toText().data();
        QString positionY = tab.item(2).firstChild().toText().data();
        QString largeur = tab.item(3).firstChild().toText().data();
        QString hauteur = tab.item(4).firstChild().toText().data();
        QString cFond = tab.item(5).firstChild().toText().data();
        QString cPolice = tab.item(6).firstChild().toText().data();
        QString cBordure = tab.item(7).firstChild().toText().data();

        Noeud nouveauNoeud(nom.toStdString(), positionX.toInt(NULL, 10), positionY.toInt(NULL, 10),
          indice.toInt(NULL, 10), largeur.toInt(NULL, 10), hauteur.toInt(NULL, 10));

        QColor tempFond(cFond);
        QColor tempPolice(cPolice);
        QColor tempBordure(cBordure);

        nouveauNoeud.setCouleurFond(tempFond);
        nouveauNoeud.setCouleurPolice(tempPolice);
        nouveauNoeud.setCouleurBordure(tempBordure);

        zone->g.m_tabNoeud.push_back(nouveauNoeud);

        //qDebug() << indice;
        
        n2 = n2.nextSibling();
    }
  }

    n = n.nextSibling();
    n2 = n.firstChild();
   // qDebug() << n2.nodeName();

    

    while(!n2.isNull())
    {
        lien = n2.toElement();

        if(lien.tagName() == "lien")
        {
          indice = lien.attribute("indice");
          tab = lien.childNodes();

          QString nom = tab.item(0).firstChild().toText().data();
          QString noeudSource = tab.item(1).firstChild().toText().data();
          QString noeudCible = tab.item(2).firstChild().toText().data();
          QString positionX = tab.item(3).firstChild().toText().data();
          QString positionY = tab.item(4).firstChild().toText().data();
          QString largeur = tab.item(5).firstChild().toText().data();
          QString hauteur = tab.item(6).firstChild().toText().data();
          QString cLien = tab.item(7).firstChild().toText().data();
          QString cPolice = tab.item(8).firstChild().toText().data();

          Lien nouveauLien(nom.toStdString(), noeudSource.toInt(NULL, 10), noeudCible.toInt(NULL, 10), indice.toInt(NULL, 10));

          QColor tempLien(cLien);
          QColor tempPolice(cPolice);

          nouveauLien.setPositionNomLien(positionX.toInt(NULL, 10), positionY.toInt(NULL, 10));
          nouveauLien.setCouleurLien(tempLien);
          nouveauLien.setCouleurPoliceLien(tempPolice);
          nouveauLien.setWidth(largeur.toInt(NULL, 10));
          nouveauLien.setHeight(hauteur.toInt(NULL, 10));

          zone->g.m_tabLien.push_back(nouveauLien);


        }

          n2 = n2.nextSibling();
    }
  //zone->nouveauGraphe();
  zone->dessinerGraphe(zone->g);

}

