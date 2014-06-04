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
#include <QVector>
#include "graphe.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QGraphicsItem>
#include <QMatrix>
#include "myQView.h"
#include <QUndoStack>
#include <QUndoCommand>
#include "UndoCommand/commandCreerNoeud.h"
#include "UndoCommand/commandSupprimerNoeud.h"
#include "UndoCommand/commandCreerLien.h"
#include "UndoCommand/commandSupprimerLien.h"
#include "UndoCommand/commandSupprimerSelection.h"
#include "UndoCommand/commandChangerPositionNoeud.h"

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
		bool	m_noeudBouge;


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
		int lienSelect;
		int derniereSelection;
		int dernierEventUndo;
		int dernierEventRedo;
		Position positionInitiale;
		Position positionFinale;
		qreal plusHautTexte;
		qreal plusHautRect;
		QGraphicsRectItem* rectangleSelection;

		
        std::string m_dernierNom;

	public:
		std::vector<int> vNoeud;
		std::vector<int> vLien;

		QVector<int> lienDejaSuppr;

		QVector<QGraphicsRectItem *> tabRect;
		QVector<QGraphicsTextItem *> tabTxtRect;
		QVector<QGraphicsTextItem *> tabTxtLine;
		QVector<QGraphicsLineItem *> tabLine;
		QVector<QGraphicsRectItem *> tabRectLine;

		QGraphicsScene *scene;
		MyQView *view;
		QGraphicsProxyWidget *proxy;
		Graphe g;
		QUndoStack* stack;


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
        int getDernierLienSelect() const;
        int getDerniereSelection() const;
        int getDernierEventUndo() const;
        int getDernierEventRedo() const;


        void setAjoutNoeud(bool b);
        void setAjoutLien(bool b);
        void setSupression(bool b);
        void setSelection(bool b);
        void setDeplacer(bool b);
        void setNbrClik(int n);
        void setDernierEventUndo(int i);
        void setDernierEventRedo(int i);

        std::vector<Noeud> estDansLesNoeuds(int x, int y);
        std::vector<Lien> estDansLesLiens(int x, int y);


	signals:
		void nouveauNoeud();
		void nouveauLien();
		void afficherMenu(int x, int y);
		void afficherMenuLien(int x, int y);
		void changerNomNoeud(int x,int y);
		void changerNomLien(int x,int y);

		void deconnecter(int i, bool annuler); // undo = 0 redo = 1
		void connecter(int i, bool annuler); // undo = 0 redo = 1

	public slots:
	void nouveauGraphe();
	void recuperationNomNoeud(std::string s);
	void recuperationCoord(int x, int y);
	void mouvementNoeud(int x, int y);
	void clicDroit(int x, int y);
	void doubleClic(int x, int y);
	void suppression(std::vector<int> tabNoeud, std::vector<int> tabLien);
	void releaseSouris(int x, int y);

	void wheelAction(int hori, int verti);
};


#endif