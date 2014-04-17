#include "zoneDessin.h"


ZoneDessin::ZoneDessin(QWidget *parent)
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
		connect(image, SIGNAL(envoieCoord(int, int, QVector<QRect>)), this, SLOT(recuperationCoord(int, int, QVector<QRect>)));
	}
	image->dessinerCadre();
	
}


void ZoneDessin::recuperationCoord(int x , int y, QVector<QRect> tab)
{

	qDebug() << "Position (" << x << "," << y << ")";	

	 
   


	if(m_ajoutNoeud)
	{

		bool estPositionable = true;

		for(int i=0; i < tab.size(); i++){

		QPainter painter2(image->image);

      	painter2.drawRect(tabNoeud[i].getPosition().getX() - tab[i].width()/2 - 5,
      	 tabNoeud[i].getPosition().getY() - tab[i].height()/2,
      	  tab[i].width() + 10, tab[i].height() + 5);

	      if(x > tabNoeud[i].getPosition().getX() - tab[i].width()/2 - 5 && x < (tabNoeud[i].getPosition().getX() - tab[i].width()/2 - 5 + tab[i].width() + 10)
	        && y > tabNoeud[i].getPosition().getY() - tab[i].height()/2 && y < (tabNoeud[i].getPosition().getY() - tab[i].height()/2 + tab[i].height() + 5)){
	          estPositionable = false;
      }
      
    }

		if(estPositionable){

		  	QString s = QString::fromStdString(m_dernierNom);
		  	qDebug() << "Nom : " << s;

			Noeud n(m_dernierNom, x, y);
			tabNoeud.push_back(n);

			image->dessineRect(x, y, s);
			image->dessineTexte(x, y, s);

		}
		else
			qDebug() << "Nous nous trouvons dans un rectangle déjà existant !";

		m_ajoutNoeud = false;
	}
	else if(m_ajoutLien)
	{
		nbrClic++;

	  	if(nbrClic == 2)
	  	{
	  		Lien l(m_dernierNom,tabNoeud[0],tabNoeud[1]); // a modifier avec identifiant de noeud
		  	QString s = QString::fromStdString(l.getNom());
		  	qDebug() << "Nom : " << s;
		  	tabLien.push_back(l);
			
			image->dessineLigne(l.getNoeudSource().getPosition().getX(), l.getNoeudSource().getPosition().getY(),
				l.getNoeudCible().getPosition().getX(), l.getNoeudCible().getPosition().getY(), s);
			
			m_ajoutLien = false;
			nbrClic = 0;
		}
	}
	
	
	
	
}

void ZoneDessin::paintEvent(QPaintEvent * e)
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
	image->dessinerCadre();
	tabNoeud.clear();
	tabLien.clear();
	image->tabRect.clear();
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