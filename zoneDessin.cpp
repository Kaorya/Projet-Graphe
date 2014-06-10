#include "zoneDessin.h"

ZoneDessin::ZoneDessin(QWidget *):positionInitiale(0,0), maxX(0), maxY(0), minX(4000), minY(4000)
{
	QRectF rect(0,0,4000,4000);
	scene = new QGraphicsScene(rect,this);
	view = new MyQView(scene,this);
	proxy = new QGraphicsProxyWidget();

	vLayout = new QVBoxLayout();

	vLayout->addWidget(view);
    setLayout(vLayout);

	noeudS = 0;
	noeudC = 0;
	m_ajoutNoeud = false;
	m_ajoutLien = false;
	m_supression = false;
	m_selection = true;
	m_deplacer = false;
	m_onPeutSeDeplacer = false;
	m_press = false,
	m_noeudBouge = false;
	nbrClic = 0;
	derniereSelection = 0;
	dernierEventUndo = -1;
	dernierEventRedo = -1;
	plusHautTexte = 6;
	plusHautRect = 5;

	dernierNoeudSelect = NULL;
	dernierLienSelect = NULL;
	rectangleSelection = NULL;
	noeudSelect = -1;
	lienSelect = -1;


	stack = new QUndoStack(this);
	stack->setUndoLimit(10);

	connect(view, SIGNAL(envoieCoord(int, int)), this, SLOT(recuperationCoord(int, int)));
	connect(view, SIGNAL(mouvementSouris(int, int)), this, SLOT(mouvementNoeud(int , int)));
	connect(view, SIGNAL(relachement(int, int)), this, SLOT(releaseSouris(int, int)));
	connect(view, SIGNAL(envoieClicDroit(int, int)), this, SLOT(clicDroit(int, int)));
	connect(view, SIGNAL(doubleClic(int, int)), this, SLOT(doubleClic(int, int)));
	connect(view, SIGNAL(wheelAction(int, int)), this, SLOT(wheelAction(int, int)));

}

ZoneDessin::~ZoneDessin()
{
	delete scene;
	delete view;
	delete dernierNoeudSelect;
	delete dernierLienSelect;
	delete rectangleSelection;
}

QSize ZoneDessin::sizeHint() const
{
	return QSize(4000,4000);
}



void ZoneDessin::recuperationCoord(int x , int y)
{
	/*
	for(int i = 0; i < g.m_tabNoeud.size(); i++)
	{
		qDebug() << "Position du noeud" << i << " (" << g.m_tabNoeud[i].getPosition().getX() << "," << g.m_tabNoeud[i].getPosition().getY() << ")";
	}
*/
	//qDebug() << "Position (" << x << "," << y << ")";
	//qDebug() << "Position scene : " << view->mapToScene(x,y);

	std::vector<Noeud> listeNoeuds;
	listeNoeuds = estDansLesNoeuds(x, y);
	std::vector<Lien> listeLien;
	listeLien = estDansLesLiens(x, y);
	m_press = true;

	if(rectangleSelection)
	{
		scene->removeItem(rectangleSelection);
		rectangleSelection = NULL;
		//qDebug() << "pointeur deleted au clic";
	}

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


	        	CommandCreerNoeud* commande = new CommandCreerNoeud(this, n.getIndice());
	        	stack->push(commande);

		       
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
			QPen p(Qt::DotLine);
			p.setColor(g.m_tabNoeud[noeudS].getCouleurBordure());
			tabRect[noeudS]->setPen(p);
			//qDebug() << "noeudS : " << noeudS;
		}

	  	if(nbrClic == 2 && !listeNoeuds.empty())
	  	{
	  		QPen p5(Qt::DotLine);
			p5.setColor(g.m_tabNoeud[listeNoeuds[listeNoeuds.size()-1].getIndice()].getCouleurBordure());
			tabRect[listeNoeuds[listeNoeuds.size()-1].getIndice()]->setPen(p5);

	  		emit nouveauLien();
	  		if(m_ajoutLien)
	  		{
		  		noeudC = listeNoeuds[listeNoeuds.size()-1].getIndice();
		  		QPen p5(Qt::DotLine);
				p5.setColor(g.m_tabNoeud[noeudC].getCouleurBordure());
				tabRect[noeudC]->setPen(p5);
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

			  	QPen p4(Qt::SolidLine);
				p4.setColor(g.m_tabNoeud[noeudS].getCouleurBordure());
				tabRect[noeudS]->setPen(p4);

				QPen p6(Qt::SolidLine);
				p6.setColor(g.m_tabNoeud[noeudC].getCouleurBordure());
				tabRect[noeudC]->setPen(p6);

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

				CommandCreerLien* commande = new CommandCreerLien(this, l.getIndice());
				stack->push(commande);

				if(QString::fromStdString(l.getNom()).isEmpty())
				{
					//qDebug() << "indice :" << l.getIndice() << "pouet";
				    tabRectLine[l.getIndice()]->hide();
				}

				
			}
			nbrClic = 0;

		}
		//qDebug() << "Nombre clic : " << nbrClic;
	}
	else if(m_selection)
	{
		for(int i = 0; i < tabRect.size(); i++)
		{
			if(tabRect[i]->pen().style() == Qt::DotLine)
			{
				QPen pen(Qt::SolidLine);
				pen.setColor(g.m_tabNoeud[i].getCouleurBordure());
				tabRect[i]->setPen(pen);
			}
			vNoeud.clear();
		}

		for(int i = 0; i < tabLine.size(); i++)
		{
			if(tabLine[i]->pen().style() == Qt::DotLine)
			{
				QPen pen(Qt::SolidLine);
				pen.setColor(g.m_tabLien[i].getCouleurLien());
				tabLine[i]->setPen(pen);
			}
			vLien.clear();
		}

		if(!listeNoeuds.empty())
		{

		if(lienSelect > -1)
		{
			QPen p3(Qt::SolidLine);
			p3.setColor(g.m_tabLien[lienSelect].getCouleurLien());
			tabLine[lienSelect]->setPen(p3);
		}

		if(noeudSelect > -1)
		{
			QPen p2(Qt::SolidLine);
			p2.setColor(g.m_tabNoeud[noeudSelect].getCouleurBordure());
			tabRect[noeudSelect]->setPen(p2);
		}

			//qDebug() << "on est dans un noeud : no " << listeNoeuds[listeNoeuds.size()-1].getIndice();
			dernierNoeudSelect = new int(listeNoeuds[listeNoeuds.size()-1].getIndice());

			tabTxtRect[*dernierNoeudSelect]->setZValue(plusHautTexte);
			tabRect[*dernierNoeudSelect]->setZValue(plusHautRect);

			plusHautRect+=2;
			plusHautTexte+=2;
			
			QPen p(Qt::DotLine);
			p.setColor(g.m_tabNoeud[*dernierNoeudSelect].getCouleurBordure());
			tabRect[*dernierNoeudSelect]->setPen(p);
			
			derniereSelection = 1;
		}
		else if(!listeLien.empty())
		{
			//qDebug() << "On se situe sur un lien";

		if(lienSelect > -1)
		{
			QPen p3(Qt::SolidLine);
			p3.setColor(g.m_tabLien[lienSelect].getCouleurLien());
			tabLine[lienSelect]->setPen(p3);
		}

		if(noeudSelect > -1)
		{
			QPen p2(Qt::SolidLine);
			p2.setColor(g.m_tabNoeud[noeudSelect].getCouleurBordure());
			tabRect[noeudSelect]->setPen(p2);
		}

			//qDebug() << "on est sur le lien patate no " << listeLien[listeLien.size()-1].getIndice();
			dernierLienSelect = new int(listeLien[listeLien.size()-1].getIndice());

			//mise en évidence du lien selectionné
			QPen p(Qt::DotLine);
			p.setColor(g.m_tabLien[*dernierLienSelect].getCouleurLien());
			tabLine[*dernierLienSelect]->setPen(p);



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
			m_noeudBouge = true;

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
			
			tabRect[*dernierNoeudSelect]->setPos(x - g.m_tabNoeud[*dernierNoeudSelect].getWidth()/2,y - g.m_tabNoeud[*dernierNoeudSelect].getHeight()/2);
			tabTxtRect[*dernierNoeudSelect]->setPos(x - g.m_tabNoeud[*dernierNoeudSelect].getWidth()/2,y - g.m_tabNoeud[*dernierNoeudSelect].getHeight()/2);

		}
		else
		{
			if(m_press)
			{
				if(rectangleSelection)
				{
					scene->removeItem(rectangleSelection);
					rectangleSelection = NULL;
				}

				QColor c(0,153,255);
				QPen bordureSelection(c);
				QBrush fondSelection(c);
				if(x > positionInitiale.getX() && y > positionInitiale.getY())
				{
					QPointF pTopLeft(positionInitiale.getX(), positionInitiale.getY());
					QPointF pBottomRight(x,y);
					QRectF rect(pTopLeft, pBottomRight);
					rectangleSelection = scene->addRect(rect, bordureSelection, fondSelection);
					rectangleSelection->setOpacity(0.6);
					rectangleSelection->setZValue(plusHautTexte);
				}
				else if(x > positionInitiale.getX() && y < positionInitiale.getY())
				{
					QPointF pTopLeft(positionInitiale.getX(), y);
					QPointF pBottomRight(x,positionInitiale.getY());
					QRectF rect(pTopLeft, pBottomRight);
					rectangleSelection = scene->addRect(rect, bordureSelection, fondSelection);
					rectangleSelection->setOpacity(0.6);
					rectangleSelection->setZValue(plusHautTexte);
				}
				else if(x < positionInitiale.getX() && y < positionInitiale.getY())
				{
					QPointF pTopLeft(x, y);
					QPointF pBottomRight(positionInitiale.getX(),positionInitiale.getY());
					QRectF rect(pTopLeft, pBottomRight);
					rectangleSelection = scene->addRect(rect, bordureSelection, fondSelection);
					rectangleSelection->setOpacity(0.6);
					rectangleSelection->setZValue(plusHautTexte);	
				}
				else if(x < positionInitiale.getX() && y > positionInitiale.getY())
				{
					QPointF pTopLeft(x, positionInitiale.getY());
					QPointF pBottomRight(positionInitiale.getX(),y);
					QRectF rect(pTopLeft, pBottomRight);
					rectangleSelection = scene->addRect(rect, bordureSelection, fondSelection);
					rectangleSelection->setOpacity(0.6);
					rectangleSelection->setZValue(plusHautTexte);
				}

			}


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
		if(rectangleSelection)
		{
			scene->removeItem(rectangleSelection);
			rectangleSelection = NULL;
		}		


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
	if(rectangleSelection)
	{
		scene->removeItem(rectangleSelection);
		rectangleSelection = NULL;
	}

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

			if(m_noeudBouge)
			{
				QPoint pAvant(positionInitiale.getX(),positionInitiale.getY());
				QPoint pApres(x,y);
				CommandChangerPositionNoeud* commande = new CommandChangerPositionNoeud(this, noeudSelect, pAvant, pApres);
				stack->push(commande);
				m_noeudBouge = false;
			}
		}	
		positionFinale.setX(x);
		positionFinale.setY(y);

		QRect(positionInitiale.getX(), positionInitiale.getY(), positionFinale.getX() - positionInitiale.getX()
			,positionFinale.getY() - positionInitiale.getY());

		if(dernierLienSelect)
		{
			lienSelect = *dernierLienSelect;
			delete dernierLienSelect;
			dernierLienSelect = NULL;
		}

		if(rectangleSelection)
		{
			for(int i = 0; i < tabRect.size(); i++)
			{
				if(g.m_tabNoeud[i].isVisible())
				{
					if(tabRect[i]->collidesWithItem (rectangleSelection, Qt::IntersectsItemShape))
					{
						QPen p(Qt::DotLine);
						p.setColor(g.m_tabNoeud[i].getCouleurBordure());
						tabRect[i]->setPen(p);

						vNoeud.push_back(i);
					}
				}
			}

			for(int i = 0; i < tabLine.size(); i++)
			{
				if(g.m_tabLien[i].isVisible())
				{
					if(tabLine[i]->collidesWithItem(rectangleSelection, Qt::IntersectsItemShape))
					{
						QPen p(Qt::DotLine);
						p.setColor(g.m_tabLien[i].getCouleurLien());
						tabLine[i]->setPen(p);

						vLien.push_back(i);
					}
				}
			}

			scene->removeItem(rectangleSelection);
			rectangleSelection = NULL;

		}


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
	stack->clear();

	maxX = 0;
	minX = 4000;
	maxY = 0;
	minY = 4000;

	derniereSelection = 0;
	//dernierEvent = -1;

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
			std::sort(tabLien.begin(),tabLien.end());
			//qDebug() << "Noeuds : ";

			for(unsigned int i = 0; i < tabNoeud.size(); i++)
			{
				//qDebug() << "noeud a suppr : " << tabNoeud[i]-i;
				if(g.m_tabNoeud.size() >= 1)
				{
					//effacer les liens correspondant
					for(unsigned int j = 0; j < g.m_tabLien.size(); j++)
					{
						//qDebug() << "for des liens a delete";
						if(g.m_tabLien[j].getNoeudSource() == tabNoeud[i]-i || g.m_tabLien[j].getNoeudCible() == tabNoeud[i]-i)
						{
							if(g.m_tabLien[j].isVisible())

								g.m_tabLien[j].setVisible(false);

								tabLine[j]->setActive(false);
								tabRectLine[j]->setActive(false);
								tabTxtLine[j]->setActive(false);
							
								tabLine[j]->hide();
								tabRectLine[j]->hide();
								tabTxtLine[j]->hide();

							//Ancienne méthode de suppression
							/*
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
							*/
						}
					}
/*
					for(unsigned int j = 0; j < g.m_tabLien.size(); j++)
					{

						if(g.m_tabLien[j].getNoeudSource() > tabNoeud[i]-i)
						{
							g.m_tabLien[j].setNoeudSource(g.m_tabLien[j].getNoeudSource()-1);
						}
						if(g.m_tabLien[j].getNoeudCible() > tabNoeud[i]-i)
						{
							g.m_tabLien[j].setNoeudCible(g.m_tabLien[j].getNoeudCible()-1);
						}
					}
*/

					//qDebug() << " apres le for des liens a delete";

					g.m_tabNoeud[tabNoeud[i]].setVisible(false);

					tabRect[tabNoeud[i]]->setActive(false);
					tabTxtRect[tabNoeud[i]]->setActive(false);
					tabRect[tabNoeud[i]]->hide();
					tabTxtRect[tabNoeud[i]]->hide();

					//scene->removeItem(tabRect[tabNoeud[i]]);
					//scene->removeItem(tabTxtRect[tabNoeud[i]]);

/*
					g.m_tabNoeud.erase(g.m_tabNoeud.begin()+tabNoeud[i]-i);
					scene->removeItem(tabRect[tabNoeud[i]-i]);
					scene->removeItem(tabTxtRect[tabNoeud[i]-i]);
					delete tabRect[tabNoeud[i]-i];
					delete tabTxtRect[tabNoeud[i]-i];
					//qDebug() << " tac 4 : " << tabNoeud[i]-i << "size de tabTxtRect :" << tabTxtRect.size();
					tabTxtRect.erase(tabTxtRect.begin()+tabNoeud[i]-i);
					tabRect.erase(tabRect.begin()+tabNoeud[i]-i);

					//qDebug() << "le noeud et le rectangle doivent etre suppr";

					for(unsigned int j = tabNoeud[i]-i; j < g.m_tabNoeud.size(); j++)
					{
						g.m_tabNoeud[j].setIndice(g.m_tabNoeud[j].getIndice()-1);
						//qDebug() << "Indice du noeud " << j << " : " << g.m_tabNoeud[j].getIndice();
					}
	*/
				}

			}

			for(unsigned int i = 0; i < tabLien.size(); i++)
			{
				//qDebug() << "for des liens a delete";
				

				g.m_tabLien[tabLien[i]].setVisible(false);
				tabRectLine[tabLien[i]]->setActive(false);
				tabLine[tabLien[i]]->setActive(false);
				tabTxtLine[tabLien[i]]->setActive(false);

				tabRectLine[tabLien[i]]->hide();
				tabLine[tabLien[i]]->hide();
				tabTxtLine[tabLien[i]]->hide();
/*
				g.m_tabLien.erase(g.m_tabLien.begin()+tabLien[i]-i);


				delete tabLine[tabLien[i]-i];
				delete tabRectLine[tabLien[i]-i];
				delete tabTxtLine[tabLien[i]-i];
				tabLine.erase(tabLine.begin()+tabLien[i]-i);
				tabRectLine.erase(tabRectLine.begin()+tabLien[i]-i);
				tabTxtLine.erase(tabTxtLine.begin()+tabLien[i]-i);

				for(unsigned int k = tabLien[i]-i; k < g.m_tabLien.size(); k++)
				{
					g.m_tabLien[k].setIndice(g.m_tabLien[k].getIndice()-1);
				}
*/
			}

		}


		lienSelect = -1;
		noeudSelect = -1;
		derniereSelection = 0;
		//qDebug() << "fin des suppression";
		vNoeud.clear();
		vLien.clear();

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

int ZoneDessin::getDernierLienSelect() const
{
	return lienSelect;
}

int ZoneDessin::getDerniereSelection() const
{
	return derniereSelection;
}

int ZoneDessin::getDernierEventUndo() const
{
	return dernierEventUndo;
}
int ZoneDessin::getDernierEventRedo() const
{
	return dernierEventRedo;
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

void ZoneDessin::setDernierEventUndo(int i)
{
	dernierEventUndo = i;
}
void ZoneDessin::setDernierEventRedo(int i)
{
	dernierEventRedo = i;
}

void ZoneDessin::wheelAction(int hori, int verti)
{/*
	qDebug() << "Position du noeud 0 avant : " << tabRect[0]->pos();

	int x = tabRect[0]->x() - hori + view->horizontalScrollBar()->sliderPosition();
	int y = tabRect[0]->y() - verti + view->verticalScrollBar()->sliderPosition();

	tabRect[0]->setX(x);
	tabRect[0]->setY(y);

	qDebug() << "Position du noeud 0 apres : " << tabRect[0]->pos();
	*/
}

std::vector<Noeud> ZoneDessin::estDansLesNoeuds(int x, int y)
{
	std::vector<Noeud> listeNoeud;
	int maxZ = 0;

	for(unsigned int i = 0; i < g.m_tabNoeud.size(); i++)
	{
		if(g.m_tabNoeud[i].isVisible())
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
		if(g.m_tabLien[i].isVisible())
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

		if(QString::fromStdString(g.m_tabLien[i].getNom()).isEmpty())
		{
			tabRectLine[g.m_tabLien[i].getIndice()]->hide();
		}
	}
}