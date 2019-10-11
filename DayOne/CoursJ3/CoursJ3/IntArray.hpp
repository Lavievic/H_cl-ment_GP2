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
		if (pos < maxSize)
		{
			this->data[pos] = elem;
		}
		else {
			ensure(pos);
		}
		this->data[pos] = elem;
		curSize++;
	}


	void set_unsafe(int pos, int elem)
	{
		this->data[pos] = elem;
	}

	int operator() (int pos)
	{
		return data[pos];
	}
	
	void push_back(int elem)
	{
		ensure(curSize+1);
		data[curSize] = elem;
		curSize++;

		
	}

	void push_front(int elem)
	{
		ensure(curSize+1);
		//for (int i = 0; i < curSize; i++)
		for (int i = curSize; i > 0; i--)
		{
			data[i] = data[i-1];
		}
		data[0] = elem;
		curSize++;
	}

	
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

};