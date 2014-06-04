#ifndef MyMainWindows_h
#define MyMainWindows_h

#include <QSpinBox>
#include <QHBoxLayout>
#include <QListView>
#include <QComboBox>
#include <QLabel>
#include <iostream>
#include <string>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QFileDialog>
#include "zoneDessin.h"
#include "Dialog/dialogSave.h"
#include "Dialog/dialogCreerNoeud.h"
#include "Dialog/dialogChangeStyle.h"
#include "Dialog/dialogStyleLien.h"
#include "noeud.h"
#include "lien.h"
#include <QtXml>
#include "UndoCommand/commandCreerNoeud.h"
#include "UndoCommand/commandChangerNomNoeud.h"
#include "UndoCommand/commandChangerNomLien.h"
#include "UndoCommand/commandChangerCouleurNoeud.h"
#include "UndoCommand/commandChangerCouleurLien.h"


#include <QKeySequence>


class MyMainWindows : public QWidget
{
        Q_OBJECT
public :
        MyMainWindows(QWidget *parent = 0);
        
        ~MyMainWindows();

        void sauvegarde(QString chemin);
        void sauvegardeImage(QString chemin);
        void chargement(QString chemin);
        QString couleurToNom(QColor c);
        QAction* getAboutQt();

        

signals:
		void signalDNouveauGraphe(QDialog* d);
		void signalDImporter(QDialog* d);
		void signalDExporter(QDialog* d);
		void signalDQuitter(QDialog* d);
        void signalDNouveauNoeud(QDialog *d);
        void signalDNouveauLien(QDialog *d);
        void signalDChange(QDialog *d);
        void signalDChangeLien(QDialog *d);

        void signalSupression(std::vector<int> tabNoeud, std::vector<int> tabLien);

        void envoieNomNoeud(std::string s);

private slots:
       	void apparitionDialog(QDialog* d);
       	void appelDNouveauGraphe();
       	void appelDImporter();
       	void appelDExporter();
       	void appelDQuitter();
        void appelDCreerNoeud();
        void appelDCreerLien();
        void appelDChange();
        void appelDChangeLien();

        void ajoutNoeud();
        void ajoutLien();

        void appelDSaveBeforeNouveauGraphe();
        void appelDSaveBeforeImporter();
        void appelDSaveExporter();
        void appelDSaveImage();
        void appelDSaveBeforeQuitter();
        void appelDOpenImporter();

        void emissionSignal();
        void enSelection();
        void enDeplacement();

        void annulation();
        void affichageMenu(int x, int y);
        void affichageMenuLien(int x, int y);
        void changerStyleNoeud();
        void changerStyleLien();
        void changerNomNoeud(int x, int y);
        void changerNomLien(int x,int y);
        void changerNom();

        void suppression();


private: 
    //Attributs

        int dernierNoeudSelect;
        int dernierLienSelect;

        bool m_changeNoeud;
        bool m_changeLien;

       //Déclaration layout

        ZoneDessin  *zone;
        QHBoxLayout *hboxPrincipale;
        QVBoxLayout *vboxPrincipale;
        QHBoxLayout *hboxBoutons;
        QVBoxLayout *vboxBoutons;
        QVBoxLayout *vboxBoutons1;
        QVBoxLayout *vboxBoutons2;

        QMenuBar 	*menuBar;

        //Menus :
        QMenu 		*menuFichier;
        QMenu 		*menuEdition;
        QMenu       *menuAPropos;
        QAction		*aNouveauGraphe;
        QAction		*aImporter;
        QAction		*aExporter;
        QAction		*aQuitter;
        QAction		*aAnnuler;
        QAction		*aRetablir;
        QAction     *aExporterImage;
        QAction     *aAboutQt;

        QMenu       *menuClicDroit;
        QAction     *changerStyle;
        QMenu       *menuClicDroitLien;
        QAction     *aChangerStyleLien;
        //QAction     *aAjouterPointCassure;


        //boutons
        QPushButton *bAjoutNoeud;
        QPushButton *bAjoutLien;
        QPushButton *bSupprimer;
        QPushButton *bSelection;
        QPushButton *bDeplacer;

        //QLineEdit pour les nom
        QLineEdit   *editNom;

        //Path
        QString     cheminFichier;

        //Dialog
        DialogSave		*dNouveauGraphe;
        DialogSave		*dImporter;
        DialogSave		*dExporter;
        DialogSave		*dQuitter;

        DialogCreerNoeud *dCreerNoeud;
        DialogCreerNoeud *dCreerLien;

        QFileDialog    *dSaveBeforeNouveauGraphe;
        QFileDialog    *dSaveBeforeImporter;
        QFileDialog    *dSaveExporter;
        QFileDialog    *dSaveBeforeQuitter;
        QFileDialog    *dOpenImporter;
        QFileDialog    *dSaveImage;

        DialogChangeStyle *dChangerStyle;
        DialogStyleLien *dChangerStyleLien;

};

#endif
