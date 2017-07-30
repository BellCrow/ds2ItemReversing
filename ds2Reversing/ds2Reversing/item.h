#include <Windows.h>

#define ITEMISINQUICKSLOTBIT 3
typedef struct ds2Item_
{
	ds2Item* flink;//0x0
	ds2Item* blink;//0x8
	__int32 unknown1;//0x10
	__int32 itemInfoId;//0x14  //what item information text is used for the item
	__int32 itemId;// 0x18//the shown image of the item
	byte itemActioId;//0x1c//what this item will do altering this, will also alter the apperance of the item
	//on uset ot he corresponding item
	byte u3;
	byte u4;
	byte itemPositionFlags;//3->is in quickSlot
	int count;
}ds2Item;


typedef struct UNKNOWNSTRUCT1_
{
	int uVal1;
	int* uPtr1;
	int* uPtr2;
	ds2Item* quickSlotsArray;
	int* pointsToZeroBuffer;
	int* uPtr3;
	WORD someShort;//+0x30
	byte pad1[2];
	byte getCheckedAtStart;
	byte QuickSlotArrayIterationLimit;
	byte pad2[2];
} UNKNOWNSTRUCT1;


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