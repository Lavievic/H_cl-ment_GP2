#pragma once
#include <cstdio>
#include<cstdlib>
#include<string>

class IntArray
{
public:
	std::string name;
	int * data;
	int curSize = 0;
	int maxSize = 0;


	static int TEST;

	int getLenght()
	{
		return curSize;
	}

	int get(int pos) {
		return data[pos];
	}

	int & operator() (int pos) {
		ensure(pos + 1);
		if (pos >= curSize) curSize = pos + 1;
		return data[pos];
	}

	//attention je ne deplace pas le curseur de taille
	int & operator[] (int pos) {
		ensure(pos + 1);
		if (pos >= curSize) curSize = pos + 1;
		return data[pos];
	}

	IntArray(int size, const char * name = "") {
		//
		this->name = name;
		printf("construite! %s\n", this->name.c_str());

		//Version c
		//data = (int *)malloc(size * sizeof(int));
		//memset(data, 0, size * sizeof(int));

		data = new int[size];
		for (int i = 0; i < size; ++i)data[i] = 0;

		maxSize = size;
	}

	~IntArray()
	{
		printf("detruite! %s\n", this->name.c_str());
	}

	void ensure(int size)
	{
		if (size > maxSize)
		{
			int *Tmp = data;
			data = new int[size];
			for (int i = 0; i < maxSize; i++)
				data[i] = Tmp[i];
			maxSize = size;
			delete(Tmp);
		}
	}

	void set(int pos, int elem)
	{
		ensure(pos + 1);
		data[pos] = elem;
		if (pos >= curSize)
			curSize = pos + 1;
	}


	void set_unsafe(int pos, int elem)
	{
		this->data[pos] = elem;
	}

	/*int operator() (int pos)
	{
		return data[pos];
	}*/

	void push_back(int elem)
	{
		ensure(curSize + 1);
		data[curSize] = elem;
		curSize++;


	}

	void push_front(int elem);


	void insert(int pos, int elem);
	/*
	void insert(int pos, int elem)
	{
		ensure(curSize + 1);
		for (int i = curSize; i > pos; i--)
		{
			data[i] = data[i - 1];
		}
		data[pos] = elem;
		curSize++;
	}*/

	int searchPosition(int element)
	{
		// parcourir le contenu
		//si la relation d'ordre n'est pas satisfaite
		//renvoyer la position précédente
		for (int i = 0; i < getLenght(); i++)
		{
			if (element <= data[i])
			{
				return i;
			}
		}

		return getLenght();
	}

	bool remove(int valeur) {
		int idx = -1;
		for (int i = 0; i < getLenght(); i++)
		{
			if (data[i] == valeur);
			{
				idx = i;
				break;
			}
		}
		if (idx == -1)return false;
		for (int i = idx + 1; i < getLenght() - 1; i++)
			data[i] = data[i + 1];
		data[curSize - 1] = 0;
		curSize--;
	}


	void fillWithRandom(int nbElem) {
		ensure(nbElem);
		for (int i = 0; i < nbElem; ++i) {
			int val = std::rand()%100;
			set(i, val);
		}
	}


	void sort()
	{
		IntArray nuData(1, "nudata");
		for (int i = 0; i < getLenght(); i++) {
			int val = get(i);
			printf("val: %d\n", val);

			int pos = nuData.searchPosition(val);
			printf("future pos: %d\n", pos);
			nuData.insert(nuData.searchPosition(val), val);

			printf("[");
			for (int j = 0; j < nuData.getLenght(); j++)
				printf("%d ", nuData[j]);
			printf("]\n");

		}

		for (int i = 0; i < getLenght(); i++) {
			set(i, nuData.get(i));
		}


	}
};
