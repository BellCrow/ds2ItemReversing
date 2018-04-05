#pragma once
#include "Util.h"
#include "ItemManager.h"

class FunctionTable
{
public:
	
	UNKNOWN uFunc1();
	UNKNOWN uFunc2();
	UNKNOWN uFunc3();
	UNKNOWN uFunc4();
	UNKNOWN uFunc5();
	UNKNOWN uFunc6();
	UNKNOWN uFunc7();
	UNKNOWN uFunc8();
	UNKNOWN itemUseFunction(containsListOfItemsInArray*,byte*,Ds2Item*,int);
	UNKNOWN uFunc10();


	static FunctionTable* instance()
	{
		if (tab == nullptr)
		{
			tab = new FunctionTable();
		}
		return tab;
	}

private:
	
	FunctionTable();
	~FunctionTable();
	static FunctionTable* tab;
};

