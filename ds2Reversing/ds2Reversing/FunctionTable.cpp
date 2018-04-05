#include "FunctionTable.h"
#include "Ds2Item.h"


UNKNOWN FunctionTable::itemUseFunction(containsListOfItemsInArray* RCXuarg,
										byte* RDXoutPtr,
										Ds2Item* useditem,
										int usedAmount)
{
	containsListOfItemsInArray* RBXuStructCopy = RCXuarg;
	uStructWithObjects* RCXuStructWithObjects = RCXuarg->uStruct;
	byte* RDIbyteOutPtrCopy = RDXoutPtr;
	short RDXsomeConstValue = 0x2BC;

	//TODO stopped here 5.4.2018
}

FunctionTable::FunctionTable()
{
}


FunctionTable::~FunctionTable()
{
}
