#ifndef dialog_save_h
#define dialog_save_h

#include <QtCore>
#include <QtGui>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QListView>
#include <QComboBox>
#include <QLabel>
#include <iostream>
#include <string>
#include <QMenuBar>
#include <QMenu>
#include <QDialog>
#include <QString>

class DialogSave : public QDialog
{
        Q_OBJECT
public :
        DialogSave(QString message ,QWidget *parent = 0);
        
private slots:
       
private : 

        
       //Déclaration layout

        QHBoxLayout *hboxPrincipale;
        QVBoxLayout *vboxPrincipale;
        QHBoxLayout *hboxBoutons;

        //boutons
        QLabel		*texte;
        QPushButton *bOui;
        QPushButton *bNon;

        //Dialog

public:

	QPushButton* getBOui();
	QPushButton* getBNon();

};




#endif