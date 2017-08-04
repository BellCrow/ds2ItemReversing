#include <Windows.h>

#define ITEMISINQUICKSLOTBIT 3
typedef struct ds2Item_
{
	ds2Item* blink;//0x0
	ds2Item* flink;//0x8
	__int32 unknown1;//0x10
	__int32 itemInfoId;//0x14  //what item information text is used for the item
	__int32 itemId;// 0x18//the shown image of the item
	WORD itemActioId;//0x1c//what this item will do altering this, will also alter the apperance of the item
	//on uset ot he corresponding item
	byte u3;
	byte u4;
	byte itemPositionFlags;//bit 3 == true -> item is in quickSlot
	int count;
}ds2Item;

//this structure seems to contain a lot of ptr to datastructures
//and func functions, that are associated with item management
typedef struct UNKNOWNSTRUCT1_
{
	funcPtrArray* functionPtrArray;
	paramList* paramStruct;
	ds2Item* itemListEntry;//was dark sign on first check
	ds2Item* quickSlotsArray;
	itemListFan* itemListEntries;
	itemArrayEntry* shortInfoItemArray;
	WORD someShort;//+0x30
	byte pad1[2];
	byte getCheckedAtStart;
	byte QuickSlotArrayIterationLimit;
	byte pad2[3];
	callBacktable* callBackTbl;//in itemuseCall same ptr as first member
	ds2Item* anotherItemListEntry;
	itemArrayEntry* allItemsInPossesionShortInfoArray;
	int bunchOfFlags;

} UNKNOWNSTRUCT1;

	typedef struct itemListFan_
	{
		ds2Item* entryItem;
		ds2Item* middleItem;//?
		ds2Item* lastItem;//?
		ds2Item* lastItem2;//?
	}itemListFan;

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

	typedef struct paramItemBytes_
	{
		int padding[8];
		DWORD checkedAgainst0x1C2;
		DWORD padding2;
	}paramItemBytes;

	//size 0x80 bytes
	typedef struct funcPtrArray_
	{
		int* func1;
		int* func2;
		int* func3;
		int* func4;
		int* func5;
		int* func6;
		int* func7;
		int* func8;
		int* func9;
		int* func10;
		int* func11;
		int* func12;
		int zeroMem;
		int* func13;

	}funcPtrArray;

	typedef struct callBackTable_
	{
		paramList* paramList;
		int functionPtr2;
		int functionPtr3;
		int functionPtr4;
		int functionPtr5;
		int functionPtr6;
		int functionPtr7;
		int functionPtr8;
		int functionPtr9;
		int functionPtr10;
		int zeroMem;
		int* ItemIdArrayInOrder;//is in order? also points to some area with param strings
		int* someUpCountingStructure;
		int zeroMem2;
		int itemId;
		DWORD OnlyFFs;
		DWORD someShortSizedValue;//was 0x2bc on rusted coin use
		int OnlyFFs2;
		DWORD padding;
		short padding2;
		byte padding3;
		byte bitFlags;//should be offset 0x88
	}callBacktable;


	//unused atm
	typedef struct callBackTableLevel2_
	{
		int* funcPtr;
		int* funcPtr2;
		int* usedPtr;
	}callBackTableLevel2;


typedef struct itemArrayEntry_
{
	//determines, whether the item is armor or weapon or consumeable
	__int32 itemClassFlags;//?
	__int32 itemid;
	__int32 itemBehaviourFlagsPack;
	__int32 itemCount;
}itemArrayEntry;

typedef struct UNKNOWNSTRUCT2_
{
	int* functionPtrArray;
	byte otherStuffMaybe[1];//real size unknown at this moment
}UNKNOWNSTRUCT2;

typedef struct itemAction_
{
	char* itemActionString;
	byte u1;
	byte u2;
	__int32 arrayIndex1;//8 byte padding
	__int32 u3;
	int arrayIndex2;//arrayIndex1 and 2 seems to be the same 
}itemAction;

typedef struct itemActionStruct_
{
	__int32 m1;//only usage so far set this to 0
	__int32 itemId;
	byte actionInfoId;
}itemActionStruct;

//used as a local stack var at one point.helps with structurizing the work here
//holds 64 bytes of data 
typedef struct stackFiller_
{
	//8 local Variables
	int stack_loc1;
	int stack_loc2;
	int stack_loc3;
	int stack_loc4;
	int stack_loc5;
	__int32 low6;
	__int32 itemIdHigh;//probably 0
	__int32 itemIdLow;
	__int32 itemActionId;
	WORD itemCount;
	WORD zeroMovedHere;
	__int32 someGlobalValue;

}stackFiller;



#define UNKNOWN byte

//an array filled with a datastructure, that points to functions and other structures with func ptrs
#define GOLBALFUNCPTRARRAY 0x13F7B7D14

//ptr to ptr to a structure, that among others things holds the string "Invalid"
#define GLOBALINVALIDRETSTRING 0x140F5FBC8 
//ptr to ptr , that among others things holds the string "L_hand1"
#define GLOBALACTIONDESCRIPTIONARRAY 0x140F5FBE0 


#define CONSTVALINGETITEMSTRING 0xBF800000
typedef UNKNOWN calledInItemUseFromPtrArray(int* funcPtrTable, int someIterationCounter, WORD itemInfoId, WORD itemCount);