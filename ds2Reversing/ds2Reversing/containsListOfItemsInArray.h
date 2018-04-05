#pragma once
#include "Util.h"

typedef struct uStructWithObjects_
{
	UNKNOWN objects[10];
}uStructWithObjects;

class containsListOfItemsInArray
{
public:
	containsListOfItemsInArray();
	~containsListOfItemsInArray();
	//entry ommited cause oop feature and invisible
	//void* vtable

	void* unknwnObj[2];
	//these string are about some Heaps e.g. "FileDataHeap"
	UNKNOWN* ptrToStructWithStringPtrsAroundIt;
	uStructWithObjects* uStruct;
};
