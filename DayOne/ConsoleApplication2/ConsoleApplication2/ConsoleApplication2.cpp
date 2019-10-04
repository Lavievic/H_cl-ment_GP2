// ConsoleApplication2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>



/*int StrChr(const char*grange, char chat) {
	
	for (int i = 0;grange[i] != 0; i++)
	{
		if (grange[i] == chat)
		{
			return i;
		}
		

	}
	return -1;
}*/

int StrChr2( char*grange, char chat) {

	char * oldGrange = grange;


	while (*grange) {
		if (*grange == chat)
		{
			return (int)(grange - oldGrange);
		}
		grange++;
	}
	return -1;
}

int StrChr(const char*grange, char chat) {
	
	int counter = 0;
	while (grange[counter] !=0 ) {
		if (grange[counter] == chat)
		{
			return counter;
		}
		counter++;
	}
	return -1;
}


/*int StrChr(const char*grange, char chat) {
	int pos = -1;
	int size
	for (int i = 0; grange[i] != 0; i++)
	{
		if (grange[i] == chat)
		{
			return i + 1;
		}


	}
	return -1;
}*/



void Mempcy(char * dest, char * src, int size) {
	for (int i = 0; i < size; i++) 
	{
		dest[i] = src[i];
	}
}

void Mempy2(char * dest, char * src, int size) {
	while (size--)
	{
		dest[size] = src[size]; 
		size--;
	}
}

/* --size / size--
 valeur sur la pile
 executeur (size)
 while(size)

while (size--)
tant que valeur sur la pile
laisser la valeur de size sur la pile
faire le tant que
decremente la valeur de size
*/
int main()
{
	std::cout << "Hello World!\n";

	const char * licorne = "licorne";
	const char * vomi = "vomit";
	//Mempcy(licorne, vomi, strlen(licorne) + 1);

	printf("contenu de licorne %s\n", licorne);


	const char * chateau = "chateau";
	char soldat = 'e';

	int posSoldat = StrChr(chateau, soldat);
	printf("le soldat est en position %d\n",posSoldat);
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
