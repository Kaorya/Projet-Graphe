#ifndef dialog_save_formulaire_h
#define dialog_save_formulaire_h

#include <QtCore>
#include <QtGui>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QListView>
#include <QComboBox>
#include <QLabel>
#include <iostream>
#include <QDialog>
#include <QString>
#include <QLineEdit>

class DialogCreerNoeud : public QDialog
{
        Q_OBJECT
public :
        DialogCreerNoeud(QWidget *parent = 0);
        
private slots:
       
private : 

        
       //Déclaration layout

        QVBoxLayout *vboxPrincipale;
        QHBoxLayout *hboxTexte;
        QHBoxLayout *hboxBoutons;

        //boutons
        QLabel		*texte;
        QLineEdit   *nomNoeud;
        QPushButton *bCreer;
        QPushButton *bAnnuler;

        //Dialog

public:

	QPushButton* getBCreer() const;
	QPushButton* getBAnnuler() const ;
    QString getNomNoeud() const;
    void setNomNoeud(QString s);

};




#endif