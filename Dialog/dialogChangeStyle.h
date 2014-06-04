#ifndef dialogChangeStyle_h
#define dialogChangeStyle_h

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

class DialogChangeStyle : public QDialog
{

	        Q_OBJECT
	public :
	        DialogChangeStyle(QWidget *parent = 0);
	        
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
	        QLabel		*txtCouleurFond;
	        QLabel		*txtCouleurBordure;
	        QComboBox   *cCouleurPolice;
	        QComboBox   *cCouleurFond;
	        QComboBox   *cCouleurBordure;
	        QPushButton *bValider;
	        QPushButton *bAnnuler;

	        //Dialog

	public:

		QPushButton* getBValider() const;
		QPushButton* getBAnnuler() const ;
		QColor getCouleurPolice() const;
		QColor getCouleurFond() const;
		QColor getCouleurBordure() const;

		void setCouleurPolice(QString s);
		void setCouleurFond(QString s);
		void setCouleurBordure(QString s);


};


#endif