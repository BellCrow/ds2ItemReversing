#include <Windows.h>
static int itemCount;



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

typedef struct globalManagerClass_
{
	void* uFunc;
	__int64 uVal;
	void* uFuncs[26];
	firstLevelStruct* secondLevel;//+D0 
}globalManagerClass;

typedef struct firstLevelStruct_
{
	firstLevelStructVtable* vtable;
	void* objectsAndProperties[109];
	uclass1* uclass;
}firstLevelStruct;

typedef struct firstLevelStructVtable_
{
	void* otherfunctions[35];
	UNKNOWN(*calledInGetFuncPtr);//+0x120
}firstLevelStructVtable;

typedef struct uclass1_
{
	uclass1Vtable* empty;

}uclass1;
typedef struct uclass1VTable_
{
	void* functions[88];
	
}uclass1Vtable;

//an array filled with a datastructure, that points to functions and other structures with func ptrs
static globalManagerClass* globMgr;


//ptr to ptr to a structure, that among others things holds the string "Invalid"
#define GLOBALINVALIDRETSTRING 0x140F5FBC8 
//ptr to ptr , that among others things holds the string "L_hand1"
#define GLOBALACTIONDESCRIPTIONARRAY 0x140F5FBE0 


#define CONSTVALINGETITEMSTRING 0xBF800000
typedef UNKNOWN calledInItemUseFromPtrArray(int* funcPtrTable, int someIterationCounter, WORD itemInfoId, WORD itemCount);
typedef UNKNOWN calledInGetFunctionPtr();