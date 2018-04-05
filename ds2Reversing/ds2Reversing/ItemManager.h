#pragma once
#include "Ds2Item.h"
#include "UnknownClass2.h"

#include "Util.h"
#include "containsListOfItemsInArray.h"

typedef struct quickSlot_
{
	Ds2Item* quickUseSlotItems[10];
}quickSlot;

typedef struct paramItemBytes_
{
	int padding[8];
	DWORD checkedAgainst0x1C2;
	DWORD padding2;
}paramItemBytes;

//thenames are just derived from a fixed offset of the address, 
//where these ptr point, that contains a unicode string
typedef struct paramList_
{
	int* itemTypeParam;
	int* itemUsageParam;
	int* itemLotParam;
	int* estusflaskLvDataParam;
	int* menuCategoryIconParam;
	int* shopLineUpParam;
	int* soundObjectBreakParam;
	//something with the same itemids in the first two fields
	paramItemBytes* paramItemBytes;
}paramList;

typedef struct itemArrayEntry_
{
	//determines, whether the item is armor or weapon or consumeable
	__int32 itemClassFlags;//?
	__int32 itemid;
	__int32 itemBehaviourFlagsPack;
	__int32 itemCount;
}itemArrayEntry;


class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void decrementItemCount(UnknownClass2* rdx, Ds2Item* usedItem, int usedAmount);

	//properties
	//funcPtrArray* vtable;
	paramList* paramStruct;//0x0
	Ds2Item* itemListEntry;//0x8
	Ds2Item* itemListEnd;//0x10
	quickSlot* quickSlotItems;//0x18
	itemArrayEntry* shortInfoItemArray;//0x20

	WORD someShort;//0x28
	byte pad1;//0x2A
	byte gotDeced;//0x2B
	byte getCheckedAtStart;//0x2C
	byte quickSlotCount;//0x2D
	byte pad2[2];//0x2E-0x2F
	//in itemuseCall same ptr as first member
	callBacktable* callBackTbl; //0x30
	Ds2Item* anotherItemListEntry;//0x38
	itemArrayEntry* allItemsInPossesionShortInfoArray;//0x40
	int bunchOfFlags;//0x48

	//static
	static void doUseItem(containsListOfItemsInArray* RCXuArg,ItemManager* RDXitemMgr,Ds2Item* R8usedItem,int R9usedAmount,byte RSP60uArg2);
};



//this should all go into a seperate class
/*
#pragma region USTRUCT2VTABLE 

struct USTRUCT2VTABLE;

UNKNOWN extractingFuncPtr(USTRUCT2VTABLE*, int, int, int);

struct USTRUCT2VTABLE_
{
	
	UNKNOWN (*extractingFuncPtr)();
}USTRUCT2VTABLE;

typedef struct UNKNOWNSTRUCT2_
{
	//are these two vtables?
	USTRUCT2VTABLE* vtable;
	void* someOtherFuncPtrArray;//real size unknown at this moment
	WORD incedInUseItemEpilog;
}UNKNOWNSTRUCT2;

#pragma endregion

*/