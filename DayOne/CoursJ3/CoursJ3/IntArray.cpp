

#include "pch.h"
#include "IntArray.hpp"


int IntArray::TEST = 66;

 void IntArray::push_front(int elem)
{
	ensure(curSize + 1);
	//for (int i = 0; i < curSize; i++)
	for (int i = curSize; i > 0; i--)
	{
		data[i] = data[i - 1];
	}
	data[0] = elem;
	curSize++;
}

 void IntArray::insert(int pos, int elem)
 {
	 ensure((pos >= curSize) ? (pos + 1) : (curSize + 1));

	 for (int i = curSize; i > pos; i--)
		 data[i] = data[i - 1];

	 data[pos] = elem;
	 if (pos >= curSize)
		 curSize = pos + 1;
	 else
		 curSize++;
}
