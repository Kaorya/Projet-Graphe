#include "zoneDessin.h"
//TODO : Essayer de récupéré les coord lorsqu'un clic est effectué sur la zone

ZoneDessin::ZoneDessin(QWidget *):positionInitiale(0,0), maxX(0), maxY(0), minX(4000), minY(4000)
{
	QRectF rect(0,0,4000,4000);
	scene = new QGraphicsScene(rect,this);
	view = new MyQView(scene,this);
	proxy = new QGraphicsProxyWidget();

	//scene->setBackgroundBrush(Qt::white);

	vLayout = new QVBoxLayout();

	vLayout->addWidget(view);
    setLayout(vLayout);

	noeudS = 0;
	noeudC = 0;
	m_ajoutNoeud = false;
	m_ajoutLien = false;
	m_supression = false;
	m_selection = false;
	m_deplacer = false;
	m_onPeutSeDeplacer = false;
	m_press = false,
	nbrClic = 0;
	derniereSelection = 0;
	plusHautTexte = 6;
	plusHautRect = 5;
	//view->horizontalScrollBar()->setMaximum(4000);

	dernierNoeudSelect = NULL;
	dernierLienSelect = NULL;
	connect(view, SIGNAL(envoieCoord(int, int)), this, SLOT(recuperationCoord(int, int)));
	connect(view, SIGNAL(mouvementSouris(int, int)), this, SLOT(mouvementNoeud(int , int)));
	connect(view, SIGNAL(relachement(int, int)), this, SLOT(releaseSouris(int, int)));
	connect(view, SIGNAL(envoieClicDroit(int, int)), this, SLOT(clicDroit(int, int)));
	connect(view, SIGNAL(doubleClic(int, int)), this, SLOT(doubleClic(int, int)));

}

ZoneDessin::~ZoneDessin()
{
	delete scene;
	delete view;
	delete dernierNoeudSelect;
	delete dernierLienSelect;
}

QSize ZoneDessin::sizeHint() const
{
	return QSize(4000,4000);
}

void ZoneDessin::resizeEvent(QResizeEvent *e)
{

		


	
}

void ZoneDessin::paintEvent(QPaintEvent *e)
{
	/*
    vLayout->addWidget(view);
    setLayout(vLayout);
    */
}


void ZoneDessin::recuperationCoord(int x , int y)
{
	//qDebug() << "Position (" << x << "," << y << ")";
	std::vector<Noeud> listeNoeuds;
	listeNoeuds = estDansLesNoeuds(x, y);
	std::vector<Lien> listeLien;
	listeLien = estDansLesLiens(x, y);
	m_press = true;

	if(m_ajoutNoeud)
	{

		bool estPositionable = true;
		

		if(!listeNoeuds.empty())
		{
		  estPositionable = false;
      	}

		if(estPositionable)
		{
			emit nouveauNoeud();
			if(m_ajoutNoeud)
			{
				//qDebug() << "Il n'y a aucun noeud où nous avons cliquée";
			  	QString s = QString::fromStdString(m_dernierNom);
			
			  	QFontMetrics fontMetrics(view->font());

				Noeud n(m_dernierNom, x, y, g.m_tabNoeud.size(),fontMetrics.width(s) + 10,fontMetrics.height()+10);
				g.m_tabNoeud.push_back(n);
				QRect rect(0, 0, fontMetrics.width(s) + 7, fontMetrics.height()+7);
				QRectF rectNoeud(rect);
				//QGraphicsRectItem* rectItem();

				tabTxtRect.push_back(scene->addText(s,scene->font()));
				tabTxtRect[n.getIndice()]->setZValue(4);
				//tabTxtRect[n.getIndice()]->setParentItem(tabRect[n.getIndice()]);
				QPoint point(x - 5 - fontMetrics.width(s)/2, y - fontMetrics.height()/2 - 5);
				QPointF p(point);
				tabTxtRect[n.getIndice()]->setDefaultTextColor(n.getCouleurPolice());
				tabTxtRect[n.getIndice()]->setPos(p);

				QPen pen(n.getCouleurBordure());
				QBrush brush(n.getCouleurFond(), Qt::SolidPattern);

				tabRect.push_back(scene->addRect(rectNoeud, pen, brush));
				tabRect[n.getIndice()]->setZValue(3);
				tabRect[n.getIndice()]->setPos(p);
				//tabRect[n.getIndice()]->setParentItem(tabTxtRect[n.getIndice()]);

				if(x + n.getWidth()/2 + 10 > maxX)
				    maxX = x + n.getWidth()/2 + 10;
				if(y + n.getHeight()/2 + 5 > maxY)
				    maxY = y + n.getHeight()/2 + 5;
				if(x - n.getWidth()/2 - 5 < minX)
				    minX = x - n.getWidth()/2 -5 ;
				if(y - n.getHeight()/2 < minY)
				    minY = y - n.getHeight()/2;
				

			
			}

		}

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
			//qDebug() << "noeudS : " << noeudS;
		}

	  	if(nbrClic == 2 && !listeNoeuds.empty())
	  	{
	  		emit nouveauLien();
	  		if(m_ajoutLien)
	  		{
		  		noeudC = listeNoeuds[listeNoeuds.size()-1].getIndice();
		  		//qDebug() << "noeudC : " << noeudC;
		  		Lien l(m_dernierNom,noeudS,noeudC, g.m_tabLien.size()); // a modifier avec identifiant de noeud
		  		int x1 = g.m_tabNoeud[l.getNoeudSource()].getPosition().getX();
	 			int x2 = g.m_tabNoeud[l.getNoeudCible()].getPosition().getX();
	 			int y1 = g.m_tabNoeud[l.getNoeudSource()].getPosition().getY();
	 			int y2 = g.m_tabNoeud[l.getNoeudCible()].getPosition().getY();
	 			int x = (x1 + x2)/2;
	 			int y = (y1 + y2)/2;
				l.setPositionNomLien(x,y);

				QString s2 = QString::fromStdString(l.getNom());
				QFontMetrics fontMetrics(view->font());
				l.setWidth(fontMetrics.width(s2));
 				l.setHeight(fontMetrics.height());

		  		//qDebug() << "Lien bien créé avec source : " << noeudS << " et pour cible : " << noeudC;
			  	QString s = QString::fromStdString(l.getNom());
			  	//qDebug() << "Nom : " << s;
			  	g.m_tabLien.push_back(l);

			  	QLine line(x1, y1, x2, y2);
			  	QLineF ligneLien(line);
			  	QPen pen(l.getCouleurLien());

			  	tabLine.push_back(scene->addLine(ligneLien, pen));
			  	tabLine[l.getIndice()]->setZValue(0);

			  	QPoint point(x - l.getWidth()/2, y - l.getHeight());
				QPointF p(point);

			  	QRect rect(2, 5, fontMetrics.width(s)+4, fontMetrics.height());
				QRectF rectLien(rect);
				QPen pen2(Qt::white);
				QBrush brush(Qt::white, Qt::SolidPattern);

				tabRectLine.push_back(scene->addRect(rectLien, pen2, brush));
				tabRectLine[l.getIndice()]->setZValue(1);

				tabRectLine[l.getIndice()]->setPos(p);


			  	tabTxtLine.push_back(scene->addText(s,scene->font()));
				tabTxtLine[l.getIndice()]->setDefaultTextColor(l.getCouleurPoliceLien());
				tabTxtLine[l.getIndice()]->setPos(p);
				
				tabTxtLine[l.getIndice()]->setZValue(2);


				
			}
			nbrClic = 0;

		}
		//qDebug() << "Nombre clic : " << nbrClic;
	}
	else if(m_selection)
	{
		if(!listeNoeuds.empty())
		{
			//qDebug() << "on est dans un noeud : no " << listeNoeuds[listeNoeuds.size()-1].getIndice();
			dernierNoeudSelect = new int(listeNoeuds[listeNoeuds.size()-1].getIndice());
			//qDebug() << "dernier noeud select = " << *dernierNoeudSelect;
			//qDebug() << "plusHautRect : " << plusHautRect << " , plusHautTexte : " << plusHautTexte;
			tabTxtRect[*dernierNoeudSelect]->setZValue(plusHautTexte);
			tabRect[*dernierNoeudSelect]->setZValue(plusHautRect);

			plusHautRect+=2;
			plusHautTexte+=2;
			
			
			derniereSelection = 1;
		}
		else if(!listeLien.empty())
		{
			//qDebug() << "on est sur le lien patate no " << listeLien[listeLien.size()-1].getIndice();
			dernierLienSelect = new int(listeLien[listeLien.size()-1].getIndice());
			derniereSelection = 2;
		}
		positionInitiale.setX(x);
		positionInitiale.setY(y);
	}
	else if(m_deplacer)
	{
		m_onPeutSeDeplacer = true;
		positionInitiale.setX(x);
		positionInitiale.setY(y);
		//qDebug() << "Position initiale : (" << positionInitiale.getX() << "," << positionInitiale.getY() << ")";
	}
	
}

void ZoneDessin::mouvementNoeud(int x, int y)
{
	if(m_selection)
	{

		//qDebug() << "on entre dans la fonction mouvementNoeud";
		if(x<0)
			x = 0;
		else if(x > scene->width())
			x = scene->width();
		if(y<0)
			y = 0;
		else if(y > scene->height())
			y = scene->height();
		if(dernierNoeudSelect)
		{	
			g.m_tabNoeud[*dernierNoeudSelect].setPosition(x,y);
			
			for(unsigned int i = 0; i < g.m_tabLien.size(); i++)
			{//vérifier que le lien contienne le noeud en mouvement en cible ou en source
				if(g.m_tabLien[i].getNoeudSource() == *dernierNoeudSelect || g.m_tabLien[i].getNoeudCible() == *dernierNoeudSelect)
				{
			  		int x1 = g.m_tabNoeud[g.m_tabLien[i].getNoeudSource()].getPosition().getX();
		 			int x2 = g.m_tabNoeud[g.m_tabLien[i].getNoeudCible()].getPosition().getX();
		 			int y1 = g.m_tabNoeud[g.m_tabLien[i].getNoeudSource()].getPosition().getY();
		 			int y2 = g.m_tabNoeud[g.m_tabLien[i].getNoeudCible()].getPosition().getY();
		 			int x3 = (x1 + x2)/2;
		 			int y3 = (y1 + y2)/2;
					g.m_tabLien[i].setPositionNomLien(x3,y3);
					tabLine[i]->setLine(x1,y1,x2,y2);

					tabRectLine[i]->setPos(x3 - tabRectLine[i]->rect().width()/2, y3 - tabRectLine[i]->rect().height()/2);
					tabTxtLine[i]->setPos(x3 - tabRectLine[i]->rect().width()/2, y3 - tabRectLine[i]->rect().height()/2);
					
					tabRectLine[i]->setZValue(2.5);
					tabTxtLine[i]->setZValue(2.5);
				}
			}
			
			//qDebug() << "pos (" << x << "," << y << ")"; 
			tabRect[*dernierNoeudSelect]->setPos(x - g.m_tabNoeud[*dernierNoeudSelect].getWidth()/2,y - g.m_tabNoeud[*dernierNoeudSelect].getHeight()/2);
			tabTxtRect[*dernierNoeudSelect]->setPos(x - g.m_tabNoeud[*dernierNoeudSelect].getWidth()/2,y - g.m_tabNoeud[*dernierNoeudSelect].getHeight()/2);

			//dessinerGraphe(g);
			//qDebug() << "dernierNoeudSelect not null";
		}
		else
		{
			/*
			QColor c(0,153,255,50);
			if(x > positionInitiale.getX() && y > positionInitiale.getY())
				image->dessineRect(positionInitiale.getX(), positionInitiale.getY(), x - positionInitiale.getX(), y - positionInitiale.getY(), c, c);
			else if(x > positionInitiale.getX() && y < positionInitiale.getY())
				image->dessineRect(positionInitiale.getX(), positionInitiale.getY(), x - positionInitiale.getX(), positionInitiale.getY() - y, c, c);
			*/
		}			
		

		//qDebug() << "position du noeud : (" << g.m_tabNoeud[dernierNoeudSelect].getPosition().getX() << "," << g.m_tabNoeud[dernierNoeudSelect].getPosition().getY() << ")";
	}
	else if(m_deplacer)
	{
		if(m_onPeutSeDeplacer)
		{
			if(x < positionInitiale.getX())
				view->horizontalScrollBar()->setSliderPosition(view->horizontalScrollBar()->sliderPosition()+10);
			else
				view->horizontalScrollBar()->setSliderPosition(view->horizontalScrollBar()->sliderPosition()-10);
			if(y < positionInitiale.getY())
				view->verticalScrollBar()->setSliderPosition(view->verticalScrollBar()->sliderPosition()+10);
			else
					view->verticalScrollBar()->setSliderPosition(view->verticalScrollBar()->sliderPosition()-10);
		
		}
		
	}

}

void ZoneDessin::clicDroit(int x, int y)
{

		std::vector<Noeud> listeNoeud = estDansLesNoeuds(x,y);
		std::vector<Lien> listeLien = estDansLesLiens(x,y);
		//ouvrir petit menu
		if(!listeNoeud.empty())
			emit afficherMenu(x, y);
		else
			if(!listeLien.empty())
				emit afficherMenuLien(x, y);
		//qDebug() << "Envoie d'affichage du petit menu";

}

void ZoneDessin::doubleClic(int x, int y)
{
	if(m_selection)
	{
		std::vector<Noeud> listeNoeud = estDansLesNoeuds(x,y);
		std::vector<Lien> listeLien = estDansLesLiens(x,y);
		if(!listeNoeud.empty())
		{
			//qDebug() << "on a fait un double clic sur un noeud";
			emit changerNomNoeud(x,y);
		}
		else
			if(!listeLien.empty())
			{
				//qDebug() << "on a fait un double clic sur un lien";
				emit changerNomLien(x,y);
			}
				

	}
}

void ZoneDessin::releaseSouris(int x, int y)
{
	m_press = false;
	if(m_selection)
	{
		if(dernierNoeudSelect)
		{
			//tabRect[*dernierNoeudSelect]->setZValue(3);
			//tabTxtRect[*dernierNoeudSelect]->setZValue(4);

			noeudSelect = *dernierNoeudSelect;
			delete dernierNoeudSelect;
			//qDebug() << "dernierNoeudSelect deleted";
			dernierNoeudSelect = NULL;
		}	
		positionFinale.setX(x);
		positionFinale.setY(y);

		QRect(positionInitiale.getX(), positionInitiale.getY(), positionFinale.getX() - positionInitiale.getX()
			,positionFinale.getY() - positionInitiale.getY());

	}
	m_onPeutSeDeplacer = false;
}

// SLOTS
void ZoneDessin::nouveauGraphe()
{
	QGraphicsItemGroup* group = scene->createItemGroup(scene->items());
	scene->destroyItemGroup(group);
	g.m_tabNoeud.clear();
	g.m_tabLien.clear();
	tabRect.clear();
	tabTxtRect.clear();
	tabLine.clear();
	tabTxtLine.clear();
	tabRectLine.clear();

	delete scene;
	QRectF rect(0,0,4000,4000);
	scene = new QGraphicsScene(rect,this);
	view->setScene(scene);
	view->horizontalScrollBar()->setSliderPosition(view->horizontalScrollBar()->maximum()/2);
	view->verticalScrollBar()->setSliderPosition(view->verticalScrollBar()->maximum()/2);
}

void ZoneDessin::recuperationNomNoeud(std::string s)
{
	m_dernierNom = s;
}

void ZoneDessin::suppression(std::vector<int> tabNoeud, std::vector<int> tabLien)
{
	if(!m_press)
	{
		if(!(tabNoeud.empty()) || !(tabLien.empty()))
		{	
			//qDebug() << "il y a quelque chose a supprimer";
			std::sort(tabNoeud.begin(),tabNoeud.end());
			for(unsigned int i = 0; i < tabNoeud.size(); i++)
			{
				qDebug() << tabNoeud[i];
			}
			for(unsigned int i = 0; i < tabNoeud.size(); i++)
			{
				//qDebug() << "noeud a suppr : " << tabNoeud[i];
				if(g.m_tabNoeud.size() >= 1)
				{
					//qDebug() << "Il y a au moins 1 noeud a delete";
					//effacer les liens correspondant
					for(unsigned int j = 0; j < g.m_tabLien.size(); j++)
					{

						if(g.m_tabLien[j].getNoeudSource() == tabNoeud[i] || g.m_tabLien[j].getNoeudCible() == tabNoeud[i])
						{


							g.m_tabLien.erase(g.m_tabLien.begin()+j);
							scene->removeItem(tabLine[j]);
							scene->removeItem(tabRectLine[j]);
							scene->removeItem(tabTxtLine[j]);

							delete tabLine[j];
							delete tabRectLine[j];
							delete tabTxtLine[j];
							tabLine.erase(tabLine.begin()+j);
							tabRectLine.erase(tabRectLine.begin()+j);
							tabTxtLine.erase(tabTxtLine.begin()+j);
							j--;

							for(unsigned int k = j+1; k < g.m_tabLien.size(); k++)
							{
								g.m_tabLien[k].setIndice(g.m_tabLien[k].getIndice()-1);
							}
						}
					}

					for(unsigned int j = 0; j < g.m_tabLien.size(); j++)
					{

						if(g.m_tabLien[j].getNoeudSource() > tabNoeud[i])
						{
							g.m_tabLien[j].setNoeudSource(g.m_tabLien[j].getNoeudSource()-1);
						}
						if(g.m_tabLien[j].getNoeudCible() > tabNoeud[i])
						{
							g.m_tabLien[j].setNoeudCible(g.m_tabLien[j].getNoeudCible()-1);
						}
					}
					

					

					g.m_tabNoeud.erase(g.m_tabNoeud.begin()+tabNoeud[i]);
					scene->removeItem(tabRect[tabNoeud[i]]);
					scene->removeItem(tabTxtRect[tabNoeud[i]]);
					delete tabRect[tabNoeud[i]];
					delete tabTxtRect[tabNoeud[i]];
					tabTxtRect.erase(tabTxtRect.begin()+tabNoeud[i]);
					tabRect.erase(tabRect.begin()+tabNoeud[i]);

					for(unsigned int j = tabNoeud[i]; j < g.m_tabNoeud.size(); j++)
					{
						g.m_tabNoeud[j].setIndice(g.m_tabNoeud[j].getIndice()-1);
						//qDebug() << "Indice du noeud " << j << " : " << g.m_tabNoeud[j].getIndice();
					}
				}

			}

		}

		derniereSelection = 0;

	}
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
bool ZoneDessin::getSupression() const
{
	return m_supression;
}
bool ZoneDessin::getSelection() const
{
	return m_selection;
}
bool ZoneDessin::getDeplacer() const
{
	return m_deplacer;
}

QGraphicsScene* ZoneDessin::getScene() const
{
	return scene;
}

int ZoneDessin::getDernierNoeudSelect() const
{
	return noeudSelect;
}

int* ZoneDessin::getDernierLienSelect() const
{
	return dernierLienSelect;
}

int ZoneDessin::getDerniereSelection() const
{
	return derniereSelection;
}

void ZoneDessin::setAjoutNoeud(bool b)
{
	m_ajoutNoeud = b;
	if(b)
	{
		m_ajoutLien = false;
		m_selection = false;
		m_deplacer = false;
		m_supression = false;
	}
}
void ZoneDessin::setAjoutLien(bool b)
{
	m_ajoutLien = b;
	if(b)
	{
		m_ajoutNoeud = false;
		m_selection = false;
		m_deplacer = false;
		m_supression = false;
	}
}
void ZoneDessin::setSupression(bool b)
{
	m_supression = b;
	if(b)
	{
		m_ajoutLien = false;
		m_selection = false;
		m_deplacer = false;
		m_ajoutNoeud = false;
	}
}
void ZoneDessin::setDeplacer(bool b)
{
	m_deplacer = b;
	if(b)
	{
		m_ajoutLien = false;
		m_selection = false;
		m_supression = false;
		m_ajoutNoeud = false;
	}
}
void ZoneDessin::setSelection(bool b)
{
	m_selection = b;
	if(b)
	{
		m_ajoutLien = false;
		m_supression = false;
		m_deplacer = false;
		m_ajoutNoeud = false;
	}
}
void ZoneDessin::setNbrClik(int n)
{
	nbrClic = n;
}

std::vector<Noeud> ZoneDessin::estDansLesNoeuds(int x, int y)
{
	std::vector<Noeud> listeNoeud;
	int maxZ = 0;

	for(unsigned int i = 0; i < g.m_tabNoeud.size(); i++)
	{
		QRect rect(g.m_tabNoeud[i].getPosition().getX() - g.m_tabNoeud[i].getWidth()/2, g.m_tabNoeud[i].getPosition().getY() - g.m_tabNoeud[i].getHeight()/2,
					g.m_tabNoeud[i].getWidth()-3, g.m_tabNoeud[i].getHeight());

		if(rect.contains(x,y))
		{
			if(tabRect[i]->zValue() <= maxZ)
			{
				listeNoeud.insert(listeNoeud.begin(), g.m_tabNoeud[i]);
			}
			else
			{
				maxZ = tabRect[i]->zValue();
				listeNoeud.push_back(g.m_tabNoeud[i]);
			}
		}
    }
      	return listeNoeud;
}

std::vector<Lien> ZoneDessin::estDansLesLiens(int x, int y)
{
	std::vector<Lien> listeLien;

	QPoint nSource(x-5,y-5);
	QPoint nCible(x+5,y+5);
	QLine positionCurseur(nSource, nCible);
	QLineF positionCurseurF(positionCurseur);

	for(unsigned int i = 0; i < g.m_tabLien.size(); i++)
	{
		QLine lineEntiere(g.m_tabNoeud[g.m_tabLien[i].getNoeudSource()].getPosition().getX(),
  					g.m_tabNoeud[g.m_tabLien[i].getNoeudSource()].getPosition().getY(),
  					g.m_tabNoeud[g.m_tabLien[i].getNoeudCible()].getPosition().getX(),
  					g.m_tabNoeud[g.m_tabLien[i].getNoeudCible()].getPosition().getY());
  		QLineF lineReal(lineEntiere);

  		QPointF pointIntersection(0,0);
  		QLineF::IntersectType intersection = lineReal.intersect(positionCurseurF, &pointIntersection);
  		if(intersection == QLineF::BoundedIntersection)
  		{
  			listeLien.push_back(g.m_tabLien[i]);
  		}
  		else
  		{
  			QRect rect(g.m_tabLien[i].getPosition().getX() - g.m_tabLien[i].getWidth()/2, g.m_tabLien[i].getPosition().getY() - g.m_tabLien[i].getHeight(),
					g.m_tabLien[i].getWidth(), g.m_tabLien[i].getHeight()+5);
  			if(rect.contains(x,y))
  			{
  				listeLien.push_back(g.m_tabLien[i]);
  			}

  		}

	}
	return listeLien;
}


void ZoneDessin::dessinerGraphe(Graphe g)
{
	for(unsigned int i=0; i < g.m_tabNoeud.size(); i++)
	{
        QRect rect(0, 0, g.m_tabNoeud[i].getWidth() -3, g.m_tabNoeud[i].getHeight() - 3);
        QRectF rectNoeud(rect);
        //QGraphicsRectItem* rectItem();

        tabTxtRect.push_back(scene->addText(QString::fromStdString(g.m_tabNoeud[i].getNom()),scene->font()));
        tabTxtRect[g.m_tabNoeud[i].getIndice()]->setZValue(4);
        //tabTxtRect[n.getIndice()]->setParentItem(tabRect[n.getIndice()]);
        QPoint point(g.m_tabNoeud[i].getPosition().getX() - 5 - g.m_tabNoeud[i].getWidth()/2, g.m_tabNoeud[i].getPosition().getY() - g.m_tabNoeud[i].getHeight()/2 - 5);
        QPointF p(point);
        tabTxtRect[g.m_tabNoeud[i].getIndice()]->setDefaultTextColor(g.m_tabNoeud[i].getCouleurPolice());
        tabTxtRect[g.m_tabNoeud[i].getIndice()]->setPos(p);

        QPen pen(g.m_tabNoeud[i].getCouleurBordure());
        QBrush brush(g.m_tabNoeud[i].getCouleurFond(), Qt::SolidPattern);

        tabRect.push_back(scene->addRect(rectNoeud, pen, brush));
        tabRect[g.m_tabNoeud[i].getIndice()]->setZValue(3);
        tabRect[g.m_tabNoeud[i].getIndice()]->setPos(p);
        //tabRect[n.getIndice()]->setParentItem(tabTxtRect[n.getIndice()]);

        if(g.m_tabNoeud[i].getPosition().getX() + g.m_tabNoeud[i].getWidth()/2 + 10 > maxX)
            maxX = g.m_tabNoeud[i].getPosition().getX() + g.m_tabNoeud[i].getWidth()/2 + 10;
        if(g.m_tabNoeud[i].getPosition().getY() + g.m_tabNoeud[i].getHeight()/2 + 5 > maxY)
            maxY = g.m_tabNoeud[i].getPosition().getY() + g.m_tabNoeud[i].getHeight()/2 + 5;
        if(g.m_tabNoeud[i].getPosition().getX() - g.m_tabNoeud[i].getWidth()/2 - 5 < minX)
            minX = g.m_tabNoeud[i].getPosition().getX() - g.m_tabNoeud[i].getWidth()/2 -5 ;
        if(g.m_tabNoeud[i].getPosition().getY() - g.m_tabNoeud[i].getHeight()/2 < minY)
            minY = g.m_tabNoeud[i].getPosition().getY() - g.m_tabNoeud[i].getHeight()/2;
	}

	for(unsigned int i=0; i < g.m_tabLien.size(); i++)
	{
		int x1 = g.m_tabNoeud[g.m_tabLien[i].getNoeudSource()].getPosition().getX();
		int x2 = g.m_tabNoeud[g.m_tabLien[i].getNoeudCible()].getPosition().getX();
		int y1 = g.m_tabNoeud[g.m_tabLien[i].getNoeudSource()].getPosition().getY();
		int y2 = g.m_tabNoeud[g.m_tabLien[i].getNoeudCible()].getPosition().getY();
		int x = (x1 + x2)/2;
		int y = (y1 + y2)/2;

		QString s = QString::fromStdString(g.m_tabLien[i].getNom());

		QLine line(x1, y1, x2, y2);
	  	QLineF ligneLien(line);
	  	QPen pen(g.m_tabLien[i].getCouleurLien());

	  	tabLine.push_back(scene->addLine(ligneLien, pen));
	  	tabLine[g.m_tabLien[i].getIndice()]->setZValue(0);

	  	QPoint point(x - g.m_tabLien[i].getWidth()/2, y - g.m_tabLien[i].getHeight());
		QPointF p(point);

	  	QRect rect(2, 5, g.m_tabLien[i].getWidth()+4, g.m_tabLien[i].getHeight());
		QRectF rectLien(rect);
		QPen pen2(Qt::white);
		QBrush brush(Qt::white, Qt::SolidPattern);

		tabRectLine.push_back(scene->addRect(rectLien, pen2, brush));
		tabRectLine[g.m_tabLien[i].getIndice()]->setZValue(1);

		tabRectLine[g.m_tabLien[i].getIndice()]->setPos(p);

	  	tabTxtLine.push_back(scene->addText(s,scene->font()));
		tabTxtLine[g.m_tabLien[i].getIndice()]->setDefaultTextColor(g.m_tabLien[i].getCouleurPoliceLien());
		tabTxtLine[g.m_tabLien[i].getIndice()]->setPos(p);
		
		tabTxtLine[g.m_tabLien[i].getIndice()]->setZValue(2);
	}
}