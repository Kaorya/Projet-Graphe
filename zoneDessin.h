#ifndef zoneDessin_h
#define zoneDessin_h

#include <QtCore>
#include <iostream>
#include <string>
#include <Qt/QtGui>
#include <QScrollBar>
#include <QScrollArea>
#include <QLabel>
#include <QGridLayout>
#include <QAbstractScrollArea>
#include <QAbstractSlider>
#include <vector>
#include "noeud.h"
#include "lien.h"
#include <QFontMetrics>
#include "myQImage.h"
#include <QVector>
#include "graphe.h"


class ZoneDessin : public QWidget
{
	Q_OBJECT

		MyQImage *image;
		QScrollArea *scrollArea;
		QLabel *imageLabel;
		QVBoxLayout *vLayout;
		int nbrClic;
		bool	m_ajoutNoeud;
		bool	m_ajoutLien;
		bool	m_suprNoeud;
		bool	m_suprLien;
		int noeudS;
		int noeudC;
		int dernierNoeudSelect;

		Graphe g;
        std::string m_dernierNom;

	public :
        ZoneDessin(QWidget *parent = 0);
        ~ZoneDessin();

        QSize sizeHint() const;
        void dessinerGraphe(Graphe g);

        bool getAjoutNoeud() const;
        bool getAjoutLien() const;
        bool getSuprNoeud() const;
        bool getSuprLien() const;
        MyQImage* getImage() const;


        void setAjoutNoeud(bool b);
        void setAjoutLien(bool b);
        void setSuprNoeud(bool b);
        void setSuprLien(bool b);
        void setNbrClik(int n);

        std::vector<Noeud> estDansLesNoeuds(int x, int y);


	signals:


	public slots:
	void nouveauGraphe();
	void recuperationNomNoeud(std::string s);
	void recuperationCoord(int x, int y);
	void mouvementNoeud(int x, int y);

    protected :
	 	virtual void resizeEvent(QResizeEvent *e);
	 	//virtual void mousePressEvent(QMouseEvent *e);
	 	virtual void paintEvent(QPaintEvent *e);

};


#endif