// ConsoleApplication2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Rec.hpp"







static void TestRec();



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

/*int StrChr2( char*grange, char chat) {

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
	while (grange[counter] != 0) {
		if (grange[counter] == chat)
		{
			return counter;
		}
		counter++;
	}
	return -1;
}

char * StrStr(char * meuledeFoin, char * aiguille) 
{
	int lenMeule = strlen(meuledeFoin);
	int lenAiguille = strlen(aiguille);

	for (int i = 0; i < lenMeule; ++i)
	{
		bool found = true;
		for (int j = 0; j < lenAiguille; ++j)
		{

			if (meuledeFoin[j] != aiguille[j])
			{
				found = false;
				break;
			}
		}
		if (found)
			return meuledeFoin;
		meuledeFoin++;
	}
	return nullptr;
}


int Max(int a, int b)
{
	return (a < b) ? b : a;
}

int Min(int a, int b)
{
	return (a < b ? b : a);
}

int Strcmp(char * meule, char * aiguille)
{
	int lenMeule = strlen(meule);
	int lenAiguille = strlen(aiguille);

	int maxLen = Max(lenMeule, lenAiguille);
	int minlen = Min(lenMeule, lenAiguille);

	for (int i = 0; i < minlen; i++)
	{
		if (meule[i] < aiguille[i])
			return -1;		
		else if (meule[i] > aiguille[i])
			return 1;
	
	}

	if (minlen == maxLen) return 0;
	if (minlen == lenMeule)return 1;

	return -1;
}
*/



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



/*void Mempcy(char * dest, char * src, int size) {
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
}*/

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

/*void strcmp1()
{
	char licorne[] = "licorne";
	char lico[] = "lico";
	printf("%d\n", strcmp(licorne, lico));
	printf("%d\n", Strcmp(licorne, lico));
	int i = 0;
}*/


int main()
{
	/*std::cout << "Hello World!\n";

	const char * licorne = "licorne";
	const char * vomi = "vomit";
	//Mempcy(licorne, vomi, strlen(licorne) + 1);

	printf("contenu de licorne %s\n", licorne);


	const char * chateau = "chateau";
	char soldat = 'e';

	int posSoldat = StrChr(chateau, soldat);
	printf("le soldat est en position %d\n",posSoldat);

	char text[1024] = "Lorem ipsum dolor sit amet";
	char token [1024] = "dolor";
	 
	char * tokenInText = StrStr(text, token);
	int pos = (int)(tokenInText - text);
		printf("le token est en position %d\n", pos);
	int a = 0;
	strcmp1();*/
	TestRec();
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




int add_0(int a, int b) {
	int i = 0;
	for (i = 0; i < a + b; ++i);
	return i;
}

int add_1(int a, int b) {
	int val = a;
	for (int i = 0; i < b; ++i);
	val++;
	return val ;
}

int add_2(int a, int b) {
	if (a == 0)
		return b;
	else		
	return add_2(a-1,b+1);
}

int add_3(int a, int b) {
	
	if (a == 0)return b;
	else if (b == 0)return a;
	else {

		int inter = 1 + add_3(a - 1, b);
	       //printf("a:%d,b:%d, =%d\n", a,b,inter);
		return inter;

	}
}


int sub(int a, int b) {
	/*if (b == 0) return a;
	else
		sub(a = -1, b = -1);*/

	if (b == 0) return a;
	if (a == 0) return b;

}

int subrec2(int a, int b)
{
	printf("a:%d,b:%d, =\n", a, b);
	if (b == 0)return a;
	else if (b > 0)
		return subrec2(a, b - 1) - 1;
	else
		return subrec2(a,b + 1) + 1;

}


int mul(int a, int b)
{
	/*if (a == 0 || b == 0)
		return a;
	else if (b < 0)
		return mul(a, b - 1) - a;
	else 
		return a + mul(a,b - 1) ;*/
	if (a == 0)return 0;
	if (b == 0) return 0;
	if (b < 0) return -mul(a, -b);
	return a + mul(a, b - 1);
}

int mul2(int a, int b) {
	if (a == 0 || b == 0)
		return a;
	else if (b < 0)
		return -a + mul2(a, b + 1);
	else
		return a + mul2(a,b - 1) ;
}


int Div(int a, int b) {
	if (a == 0 )return 0;

	if (b < 0 )return -Div(a, -b);
	else
		return 1 + Div(a - b, b);

}
int Div2(int a, int b)
{
	if (a == 0)		return 0;
	if (b < 0 && a < 0)		return -Div2(a, b);
	if (a < 0)		return -Div2(-a, b);
	if (b < 0)		return -Div2(a, -b);
	if (a < b)		return 0;
	return 1 + Div2(a - b, b);

}

int quotient(int a, int b)
{
	if (a == 0) return 0;
	else
	{
		return a - mul(Div2(a, b), b);
		return (0);
	}
}

int rec_strlen(const char *str)
{
	if (*str == 0)
		return 0 ;
	return  1 + rec_strlen(str+1);
}


int strlcpy(char *dst, const char *src)
{
	*dst = *src;
	if (*src == 0) return 0;
	 strlcpy(dst+1, src + 1);
}

void ZeroMemory(char * dst, int size)
{
	if (size == 0)return;
	*dst = 0;
	ZeroMemory(dst + 1, size -1);
}

void TestRec() {
	int foo = add_2(2, 2);
	int foo2 = add_3(3, 2);
	int foo3 = subrec2(8, 2);
	int foo4 = mul(2, 4);
	int foo5 = mul(2, -4);
	int foo6 = mul2(2, -4);
	int foo7 = Div(20, 2);
	int foo8 = quotient(16, 3);
	int i = 0;

	char dest[30];
	int len = rec_strlen("sapin");
	int leny = strlcpy(dest, "boule");
	int szBuf = 32;

	char * buffer = (char*)malloc(szBuf + 1);
	buffer[32] = 'X';
	ZeroMemory(buffer, szBuf);

	printf("%c", buffer[32]);
	system("pause");
}

