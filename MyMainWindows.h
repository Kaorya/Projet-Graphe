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
#include "noeud.h"
#include "lien.h"

class MyMainWindows : public QWidget
{
        Q_OBJECT
public :
        MyMainWindows(QWidget *parent = 0);
        
        ~MyMainWindows();

        void sauvegarde(QString chemin);
        void sauvegardeImage(QString chemin);
        void chargement(QString chemin);

signals:
		void signalDNouveauGraphe(QDialog* d);
		void signalDImporter(QDialog* d);
		void signalDExporter(QDialog* d);
		void signalDQuitter(QDialog* d);
        void signalDNouveauNoeud(QDialog *d);
        void signalDNouveauLien(QDialog *d);

        void envoieNomNoeud(std::string s);

private slots:
       	void apparitionDialog(QDialog* d);
       	void appelDNouveauGraphe();
       	void appelDImporter();
       	void appelDExporter();
       	void appelDQuitter();
        void appelDCreerNoeud();
        void appelDCreerLien();

        void ajoutNoeud();
        void ajoutLien();

        void appelDSaveBeforeNouveauGraphe();
        void appelDSaveBeforeImporter();
        void appelDSaveExporter();
        void appelDSaveImage();
        void appelDSaveBeforeQuitter();
        void appelDOpenImporter();

private : 
    //Attributs
        


       //Déclaration layout

        ZoneDessin  *zone;
        QHBoxLayout *hboxPrincipale;
        QVBoxLayout *vboxPrincipale;
        QHBoxLayout *hboxBoutons;
        QVBoxLayout *vboxBoutons1;
        QVBoxLayout *vboxBoutons2;

        QMenuBar 	*menuBar;

        //Menus :
        QMenu 		*menuFichier;
        QMenu 		*menuEdition;
        QAction		*aNouveauGraphe;
        QAction		*aImporter;
        QAction		*aExporter;
        QAction		*aQuitter;
        QAction		*aAnnuler;
        QAction		*aRetablir;
        QAction     *aExporterImage;

        //boutons
        QPushButton *bAjoutNoeud;
        QPushButton *bAjoutLien;
        QPushButton *bSupprimerNoeud;
        QPushButton *bSupprimerLien;

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

};

#endif
