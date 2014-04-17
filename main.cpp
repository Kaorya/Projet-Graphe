#include <Qt/QtGui>

#include "MyMainWindows.h"

/*
TODO : 
	- Vérifier la non superposition des noeuds
	- Mettre des identifiant aux noeud et les repérer lorsqu'on clique dessus
*/

int main(int argc, char** argv){
        QApplication CarteConceptuelle(argc, argv);
        
        MyMainWindows *MainWin = new MyMainWindows;
                
        MainWin->show();      

        return CarteConceptuelle.exec();

};
