// CoursJ3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "IntArray.hpp"

void assert(bool b)
{
	if (!b) throw std::exception();
}

int main()
{
    

	auto nameTab0 = "tab0";
	auto nameTab1 = "tab1";
	
	IntArray tab0 = IntArray(16, nameTab0);		
	tab0.ensure(20);
	tab0.set(30, 1);

	IntArray *tab1 = new IntArray(16, nameTab1);
		delete(tab1);
		tab1 = nullptr;



		{
			IntArray t(16);
			for (int i = 0; i < 6; i++)
			{
				t.set(i, i*i);
			}
			t.push_back(5);
			t.push_front(2);
			t.insert(5, 66);
		}

		{
			/*IntArray t(3);
			t.set ;
			t[1] = 69;
			t[2] = 70;

			t.remove(t[1]);
			assert(t[0] == 68);
			assert(t[1] == 70);
			int i = 0;*/
			tab0.data[0] = 69;
			tab0.data[1] = 70;
			tab0.data[2] = 72;
			tab0.data[3] = 73;
			tab0.data[4] = 74;
			tab0.data[5] = 75;


			tab0.remove(70);

			
		}


		{
			IntArray t(1);
			t.set(0, 5);
			t.set(1, 6);
			t.set(2, 10);
			

			printf("%d\n", t.searchPosition(1)) ;
			printf("%d\n", t.searchPosition(5)) ;
			printf("%d\n", t.searchPosition(6)) ;
			printf("%d\n", t.searchPosition(8)) ;
		}
		
	
	std::cout << "Hello World!\n";
}




// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
