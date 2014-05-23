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
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QGraphicsItem>
#include <QMatrix>
#include "myQView.h"

class ZoneDessin : public QWidget
{
	Q_OBJECT

		QVBoxLayout *vLayout;
		int nbrClic;
		bool	m_ajoutNoeud;
		bool	m_ajoutLien;
		bool	m_supression;
		bool	m_selection;
		bool	m_deplacer;
		bool 	m_onPeutSeDeplacer;
		bool	m_press;



/*
		bool	m_nouveauGraphe;
		bool	m_importation;
		bool	m_exportation;
		bool	m_quitter;
*/
		int noeudS;
		int noeudC;
		int *dernierNoeudSelect;
		int noeudSelect;
		int *dernierLienSelect;
		int derniereSelection;
		Position positionInitiale;
		Position positionFinale;
		qreal plusHautTexte;
		qreal plusHautRect;

		
        std::string m_dernierNom;

	public:
		std::vector<int> vNoeud;
		std::vector<int> vLien;

		QVector<QGraphicsRectItem *> tabRect;
		QVector<QGraphicsTextItem *> tabTxtRect;
		QVector<QGraphicsTextItem *> tabTxtLine;
		QVector<QGraphicsLineItem *> tabLine;
		QVector<QGraphicsRectItem *> tabRectLine;

		QGraphicsScene *scene;
		MyQView *view;
		QGraphicsProxyWidget *proxy;
		Graphe g;

		int maxX;
        int maxY;
        int minX;
        int minY;

        ZoneDessin(QWidget *parent = 0);
        ~ZoneDessin();

        QSize sizeHint() const;
        void dessinerGraphe(Graphe g);

        bool getAjoutNoeud() const;
        bool getAjoutLien() const;
        bool getSupression() const;
        bool getDeplacer() const;
        bool getSelection() const;
        QGraphicsScene* getScene() const;
        int getDernierNoeudSelect() const;
        int* getDernierLienSelect() const;
        int getDerniereSelection() const;


        void setAjoutNoeud(bool b);
        void setAjoutLien(bool b);
        void setSupression(bool b);
        void setSelection(bool b);
        void setDeplacer(bool b);
        void setNbrClik(int n);

        std::vector<Noeud> estDansLesNoeuds(int x, int y);
        std::vector<Lien> estDansLesLiens(int x, int y);

        std::vector<int> triVectorInt(std::vector<int> v);


	signals:
		void nouveauNoeud();
		void nouveauLien();
		void afficherMenu(int x, int y);
		void afficherMenuLien(int x, int y);
		void changerNomNoeud(int x,int y);
		void changerNomLien(int x,int y);

	public slots:
	void nouveauGraphe();
	void recuperationNomNoeud(std::string s);
	void recuperationCoord(int x, int y);
	void mouvementNoeud(int x, int y);
	void clicDroit(int x, int y);
	void doubleClic(int x, int y);
	void suppression(std::vector<int> tabNoeud, std::vector<int> tabLien);
	void releaseSouris(int x, int y);

    protected:
	 	virtual void resizeEvent(QResizeEvent *e);
	 	//virtual void mousePressEvent(QMouseEvent *e);
	 	virtual void paintEvent(QPaintEvent *e);
	 	//virtual void mouseReleaseEvent(QMouseEvent *e);

};


#endif