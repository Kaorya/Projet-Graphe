#include "zoneDessin.h"


ZoneDessin::ZoneDessin(QWidget *)
{
	image = NULL;
	imageLabel = new QLabel("");
	scrollArea = new QScrollArea();
	vLayout = new QVBoxLayout();
	m_ajoutNoeud = false;
	m_ajoutLien = false;
	m_suprNoeud = false;
	m_suprLien = false;
	nbrClic = 0;
	scrollArea->horizontalScrollBar()->setMaximum(4000);
}

ZoneDessin::~ZoneDessin()
{
	delete image;
	delete imageLabel;
	delete scrollArea;
}

QSize ZoneDessin::sizeHint() const
{
	return QSize(1000,1000);
}

void ZoneDessin::resizeEvent(QResizeEvent *)
{

	if(!image)
	{
		image = new MyQImage(4000,4000,QImage::Format_RGB32,this);
		image->image->fill(Qt::white);
		connect(image, SIGNAL(envoieCoord(int, int)), this, SLOT(recuperationCoord(int, int)));
		connect(image, SIGNAL(mouvementSouris(int, int)), this, SLOT(mouvementNoeud(int , int)));
	}
	image->dessinerCadre();
	
}


void ZoneDessin::recuperationCoord(int x , int y)
{

	qDebug() << "Position (" << x << "," << y << ")";
	std::vector<Noeud> listeNoeuds;
	listeNoeuds = estDansLesNoeuds(x, y);

	if(m_ajoutNoeud)
	{

		bool estPositionable = true;
		

		if(!listeNoeuds.empty())
		{
		  estPositionable = false;
      	}

		if(estPositionable)
		{
			qDebug() << "Il n'y a aucun noeud où nous avons cliquée";
		  	QString s = QString::fromStdString(m_dernierNom);
		  	QPainter painter(image->image);
		  	qDebug() << "Nom : " << s;
		  	QFontMetrics fontMetrics(painter.font());

			Noeud n(m_dernierNom, x, y, g.getTabNoeud().size(),fontMetrics.width(s),fontMetrics.height());
			g.m_tabNoeud.push_back(n);
			painter.end();
			dessinerGraphe(g);

		}
		else
			qDebug() << "Nous nous trouvons dans un rectangle déjà existant !";

		m_ajoutNoeud = false;
	}
	else if(m_ajoutLien)
	{
		nbrClic++;
		if(listeNoeuds.empty())
		{
			nbrClic--;
		}
		if(nbrClic == 1 && !listeNoeuds.empty())
		{
			noeudS = listeNoeuds[listeNoeuds.size()-1].getIndice();
			listeNoeuds.clear();
			qDebug() << "noeudS : " << noeudS;
		}

	  	if(nbrClic == 2 && !listeNoeuds.empty())
	  	{
	  		noeudC = listeNoeuds[listeNoeuds.size()-1].getIndice();
	  		qDebug() << "noeudC : " << noeudC;
	  		Lien l(m_dernierNom,g.getTabNoeud()[noeudS],g.getTabNoeud()[noeudC]); // a modifier avec identifiant de noeud
	  		qDebug() << "Lien bien créé avec source : " << noeudS << " et pour cible : " << noeudC;
		  	QString s = QString::fromStdString(l.getNom());
		  	qDebug() << "Nom : " << s;
		  	g.m_tabLien.push_back(l);
			
			dessinerGraphe(g);
			
			m_ajoutLien = false;
			nbrClic = 0;

		}
		qDebug() << "Nombre clic : " << nbrClic;
	}
	else
	{

		if(!listeNoeuds.empty())
		{
			qDebug() << "on est dans le cas où on clique simplement et on est dans un noeud : no " << listeNoeuds[listeNoeuds.size()-1].getIndice();
			dernierNoeudSelect = listeNoeuds[listeNoeuds.size()-1].getIndice();
		}
	}
	
	
	
	
}

void ZoneDessin::mouvementNoeud(int x, int y)
{
	if(!m_ajoutLien && !m_ajoutLien)
	{
		std::vector<Noeud> listeNoeuds;
		listeNoeuds = estDansLesNoeuds(x, y);
		if(!listeNoeuds.empty())
		{
			g.m_tabNoeud[dernierNoeudSelect].setPosition(x,y);
			dessinerGraphe(g);
		}
		qDebug() << "position du noeud : (" << g.m_tabNoeud[dernierNoeudSelect].getPosition().getX() << "," << g.m_tabNoeud[dernierNoeudSelect].getPosition().getY() << ")";
	}

}

void ZoneDessin::paintEvent(QPaintEvent *)
{
	//imageLabel->setPixmap(QPixmap::fromImage(*(image->image)));
	//imageLabel->adjustSize();
	scrollArea->setWidget(image);
    vLayout->addWidget(scrollArea);
    setLayout(vLayout);
}


// SLOTS
void ZoneDessin::nouveauGraphe()
{
	image->image->fill(Qt::white);
	g.m_tabNoeud.clear();
	g.m_tabLien.clear();
	repaint();
}

void ZoneDessin::recuperationNomNoeud(std::string s)
{
	m_dernierNom = s;
}


//GETTERS & SETTERS

bool ZoneDessin::getAjoutNoeud() const
{
	return m_ajoutNoeud;
}
bool ZoneDessin::getAjoutLien() const
{
	return m_ajoutLien;
}
bool ZoneDessin::getSuprNoeud() const
{
	return m_suprNoeud;
}
bool ZoneDessin::getSuprLien() const
{
	return m_suprLien;
}

MyQImage* ZoneDessin::getImage() const
{
	return image;
}

void ZoneDessin::setAjoutNoeud(bool b)
{
	m_ajoutNoeud = b;
}
void ZoneDessin::setAjoutLien(bool b)
{
	m_ajoutLien = b;
}
void ZoneDessin::setSuprNoeud(bool b)
{
	m_suprNoeud = b;
}
void ZoneDessin::setSuprLien(bool b)
{
	m_suprLien = b;
}
void ZoneDessin::setNbrClik(int n)
{
	nbrClic = n;
}

std::vector<Noeud> ZoneDessin::estDansLesNoeuds(int x, int y)
{
	std::vector<Noeud> listeNoeud;

	for(unsigned int i = 0; i < g.getTabNoeud().size(); i++)
	{
	      if(x > g.getTabNoeud()[i].getPosition().getX() - g.getTabNoeud()[i].getWidth()/2 - 5 && x < (g.getTabNoeud()[i].getPosition().getX() - g.getTabNoeud()[i].getWidth()/2 - 5 + g.getTabNoeud()[i].getWidth() + 10)
	        && y > g.getTabNoeud()[i].getPosition().getY() - g.getTabNoeud()[i].getHeight()/2 && y < (g.getTabNoeud()[i].getPosition().getY() - g.getTabNoeud()[i].getHeight()/2 + g.getTabNoeud()[i].getHeight() + 5))
	         	listeNoeud.push_back(g.getTabNoeud()[i]);
    }
      	return listeNoeud;
}

void ZoneDessin::dessinerGraphe(Graphe g)
{
	image->image->fill(Qt::white);
  //parcours des tableaux de noeud et de lien et dessin
	for(unsigned int i=0; i < g.getTabLien().size(); i++)
	{
		image->dessineLien(g.getTabLien()[i]);	
	}

	for(unsigned int i=0; i < g.getTabLien().size(); i++)
	{
		image->dessineTexteLien(g.getTabLien()[i]);	
	}

	for(unsigned int i=0; i < g.getTabNoeud().size(); i++)
	{
		image->dessineNoeud(g.getTabNoeud()[i]);	
	}
}
