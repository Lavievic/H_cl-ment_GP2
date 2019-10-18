// Cours4.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "IntArray.hpp"
#include <time.h>



void StrCat(char * dst, const char * src) {
	if (*dst == 0) {
		if (*src == 0)
			return;
		else {
			*dst = *src;
			*(dst + 1) = 0;
			StrCat(dst + 1, src + 1);
		}
	}
	else
		StrCat(dst + 1, src);
}

int StrCmp(const char * s0, const char * s1) {
	if (*s0 == 0 && *s1 == 0) return 0;
	else if (*s0 < *s1) return 1;
	else if (*s0 > *s1) return -1;
	return StrCmp(s0 + 1, s1 + 1);
}

int _StrChr(const char * s0, char s1, const char * _start) {
	if (*s0 == 0 && s1 != 0)
		return -1;
	else if (*s0 == s1)
		return s0 - _start;//std::distance
	else
		return _StrChr(s0 + 1, s1, _start);
}

int StrChr(const char * s0, char s1) {
	return _StrChr(s0, s1, s0);
}

int StrChr2(const char * s0, char s1, const char*_orig = nullptr) {
	if (_orig == nullptr)
		return StrChr2(s0, s1, s0);

	if (*s0 == 0 && s1 != 0)
		return -1;
	else if (*s0 == s1)
		return s0 - _orig;//std::distance
	else
		return StrChr2(s0 + 1, s1, _orig);
}



bool contains(const char * s0, const char * s1) {
	int len = strlen(s0);
	return s1 >= s0 && s1 <= s0 + len;
}

bool startsWith(const char * s0, const char * s1) {
	if (*s0 == 0 && *s1 != 0)
		return false;
	if (*s1 == 0)
		return true;
	if (*s0 != *s1)
		return false;
	else
		return startsWith(s0 + 1, s1 + 1);
}

const char * StrStr(const char * s0, const char * s1) {
	if (startsWith(s0, s1))
		return s0;
	else
		if (*s0 == 0) {
			if (*s1 == 0)
				return s0;
			else
				return nullptr;
		}
		else
			return StrStr(s0 + 1, s1);
}

void assert(bool b) {
	if (!b) throw std::exception();
}

int main() {



	{
		IntArray toto;
		toto.fillWithRandom(128);
		int i = 0;

		toto.insertSort();

		for (int i = 0; i < toto.getLength()-1; i++)
		{
			assert(toto[i] < toto[i + 1]);
		}
	}


	{
		IntArray test;
		test[0] = 66;
		test[1] = 69;
		test.swap(0, 1);
		assert(test[0] == 69);
	}
	//ici montableau a été détruit

	std::cout << "Hello World!\n";
}

