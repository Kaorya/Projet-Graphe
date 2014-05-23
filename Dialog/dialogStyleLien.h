#ifndef dialogStyleLien_h
#define dialogStyleLien_h

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

class DialogStyleLien : public QDialog
{

	        Q_OBJECT
	public :
	        DialogStyleLien(QWidget *parent = 0);
	        
	private slots:
	       
	private: 

	        
	       //Déclaration layout

	        QVBoxLayout *vboxPrincipale;
	        QHBoxLayout *hboxPrincipale;
	        QVBoxLayout *vboxTexte;
	        QVBoxLayout *vboxCombo;
	        QHBoxLayout *hboxBoutons;

	        //boutons
	        QLabel		*txtCouleurPolice;
	        QLabel		*txtCouleurLien;
	        QComboBox   *cCouleurPolice;
	        QComboBox   *cCouleurLien;
	        QPushButton *bValider;
	        QPushButton *bAnnuler;

	        //Dialog

	public:

		QPushButton* getBValider() const;
		QPushButton* getBAnnuler() const ;
		QColor getCouleurPolice() const;
		QColor getCouleurLien() const;

		void setCouleurPolice(QString s);
		void setCouleurLien(QString s);
};


#endif