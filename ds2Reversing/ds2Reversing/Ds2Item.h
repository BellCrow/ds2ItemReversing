#pragma once
#include <Windows.h>

#define ITEMISINQUICKSLOTBIT 0x3 //is 0b10 and will therefore test the second bit

class Ds2Item
{
	
public:

	Ds2Item();
	~Ds2Item();

	//properties
	Ds2Item* blink;//0x0
	Ds2Item* flink;//0x8
	__int32 constZero;//seems at least so
	__int32 itemInfoId;//0x14  //what item information text is used for the item
	__int32 itemId;// 0x18//the shown image of the item
	WORD itemListIndex;//0x1c//what this item will do. altering this, will also alter the apperance of the item
	//0x1e has something to do with the amount of this item can actually be used
	byte unknown1;
	//0x1d
	byte unknown2;
	//on use to the corresponding item
	byte u3;
	byte itemStatusFlags;
	byte itemPositionFlags;//bit 3 == true -> item is in quickSlot
	int count;

};

