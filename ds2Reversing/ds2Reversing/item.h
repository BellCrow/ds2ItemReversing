#include <Windows.h>

#define ITEMISINQUICKSLOTBIT 3
typedef struct ds2Item_
{
	ds2Item* flink;//0x0
	ds2Item* blink;//0x8
	__int32 unknown1;//0x10
	__int32 itemInfoId;//0x14  //what item information text is used for the item
	__int32 itemId;// 0x18//the shown image of the item
	byte consumationBehaviour;//0x1c//if its is consumed or it has charges or isnt used up at all
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

#define UNKNOWN byte

typedef UNKNOWN calledInItemUseFromPtrArray(int* funcPtrTable, int someIterationCounter, WORD itemInfoId, WORD itemCount);