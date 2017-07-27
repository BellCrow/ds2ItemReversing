#include "item.h"
										//R8				R9				RCX					RDX
UNKNOWN decreaseItemCount(ds2Item* usedItem, int usedAmount, UNKNOWNSTRUCT1* rcx, UNKNOWNSTRUCT2* rdx)
{
	ds2Item* usedItemRefClone/*mov in RBX*/ = usedItem;
	int usedAmountClone/*mov in (E/R)SI*/ = usedAmount;

	UNKNOWNSTRUCT2* rbpAsRdx/*mov in RDX*/ = rdx;
	UNKNOWNSTRUCT1* rdiAsRcx = rcx;

	if (rcx->getCheckedAtStart == 0)
	{

	}
	else
	{
		if (rcx->getCheckedAtStart == 1)
		{
			if (usedItemRefClone->count == usedAmountClone)
			{
				//using up stack. so unlink and stuff
			}
			else
			{					//R8			R9				RCX			RDX
				callfunc1(usedItemRefClone, usedAmountClone, rdiAsRcx, rbpAsRdx);
			}
		}
		else
		{

		}
	}
}

//								R8				R9				RCX					RDX
UNKNOWN callfunc1(ds2Item* usedItem, int usedAmount, UNKNOWNSTRUCT1* uarg1, UNKNOWNSTRUCT2* uarg2)
{
	int shadowspace[4];
	shadowspace[0] = 0;//rbx
	shadowspace[1] = 0;//rbp
	shadowspace[2] = 0;//rsi
	shadowspace[3] = 0;//rdi

	UNKNOWNSTRUCT1* RDIuarg1Copy = uarg1;
	SHORT unknownShort = uarg1->someShort;//tested later if this is 0x2bc

	INT32 callSaveUsedAmount = (INT32)usedAmount;//ebp
	ds2Item* callSaveItemPtr = usedItem;//rbx

	WORD subtractValue = 0x2bc;
	UNKNOWNSTRUCT2* callSaveUStruct = uarg2;//RSI

	if (isValueBelow0x2ba(unknownShort) != 0x00)
	{

	}
	else
	{
		if (isValueBelow0x2bc(RDIuarg1Copy->someShort) == 0)
			return;
		else
		{
			if (!RDIuarg1Copy->someShort == subtractValue)
				return;
			else
			{
				if (callSaveItemPtr->itemPositionFlags & ITEMISINQUICKSLOTBIT != 1)//ITEMQUICKSLOTSTATE3 means it is in the quickslot
					return;
				else
				{
					if (uarg1->QuickSlotArrayIterationLimit == 0)
						return;
					DWORD iterationCounter = 0;
					ds2Item* iterator = (uarg1->quickSlotsArray);
					//iterate through the quick itemslotsto get to the used item
					while (iterator != usedItem)
					{
						iterator++;
						iterationCounter++;
						//there are only 0xa (10) quick item slots, to iterate through
						if (iterationCounter >= uarg1->QuickSlotArrayIterationLimit)
							return;
					}
					//at this point ew have either found the correct item ptr in the quickslots, or we must have already left the function
					//due to array bounds
					int currentItemCount = iterator->count;
					//decrease itemCount
					currentItemCount -= callSaveUsedAmount;

					if (subtractValue == 0x258)
					{

					}
					else if (subtractValue == uarg1->someShort)//should be always true?
					{
						int* funcPtrArryEntry = callSaveUStruct->functionPtrArray;
						int itemInfoId = callSaveItemPtr->itemInfoId;
						iterationCounter += 0x12;//???
						//not sure what this is yet
						//calling the 011th function from the given table, using the exact same table asn an argument
						//the code in the next line is the "real" code, i changed it here, so that i can write the function actually down
						//((calledInItemUseFromPtrArray*)(funcPtrArryEntry + (0x88 / sizeof(funcPtrArryEntry))))(funcPtrArryEntry);
						functionThatIsInFuncPtrArrayGotCalledOnItemConsume(funcPtrArryEntry, iterationCounter,itemInfoId,callSaveItemPtr->count);
					}
				}
			}
		}
	}
}

byte isValueBelow0x2ba(short someShortValue)
{

	if (someShortValue <= 0x2ba)
		return 0x1;
	return 0x00;
}
byte isValueBelow0x2bc(short someShortValue)
{
	if (someShortValue <= 0x2bc)
		return 0x1;
	return 0x00;
}

UNKNOWN functionThatIsInFuncPtrArrayGotCalledOnItemConsume(int* funcPtrTable, int someIterationCounter,WORD itemInfoId,WORD itemCount)
{
	//EDI
	WORD itemInfoIdCopy = funcPtrTable;
	//EBP
	WORD itemCountCopy = itemCount;
	//RSI
	int someIterationCounterCopy = someIterationCounter;
	//R15
	int* funcPtrTableCopy = funcPtrTable;

}

UNKNOWN gotCalledFromAboveFunction(void)
{

}