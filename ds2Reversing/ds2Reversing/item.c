#include "item.h"
//this is all more or less pseudo code, that is not meant to be executeable
//im using this to determine the size of any struct at devtime . as i cant compile
//template<size_t S> class Sizer { }; Sizer<sizeof(itemAction)> foo;
									//	RCX					RDX			R8				R9	
void decreaseItemCount(UNKNOWNSTRUCT1* rcx, UNKNOWNSTRUCT2* rdx,ds2Item* usedItem, int usedAmount)
{
	ds2Item* usedItemRefClone/*mov in RBX*/ = usedItem;
	int usedAmountClone/*mov in (E/R)SI*/ = usedAmount;

	UNKNOWNSTRUCT2* rbpAsRdx/*mov in RDX*/ = rdx;
	UNKNOWNSTRUCT1* rdiAsRcx = rcx;

	if (rcx->getCheckedAtStart == 0 || rcx->getCheckedAtStart == 1)
	{

	}
	else
	{
		if (usedItemRefClone->count >= usedAmountClone)
		{
			//using up stack. so unlink and stuff
			funcPtrArray* fp = rdiAsRcx->vtable;
			__int32 itemInfoIdClone = usedItemRefClone->itemInfoId;
			//real call is a register relative call
			//fp->func9(rdiAsRcx->vtable, usedItemRefClone->itemInfoId);
			if (sub_13FEEAAE0(rdiAsRcx, usedItem->itemInfoId))
			{
				//fp->func11(rdiAsRcx);
				clearAnotherItemListEntryFromStruct(rdiAsRcx);
			}
			unlinkIfItemFirstEntry(rdiAsRcx, usedItem);
			unlinkIfItemLastEntry(rdiAsRcx, usedItem);
			sub_13FB9D850(rdiAsRcx, rbpAsRdx, usedItemRefClone);
			if (usedItemRefClone->itemInfoId <= 0)
			{
				sub_13FB9A230(rdiAsRcx, usedItemRefClone);
				return usedAmountClone;
			}
			//r8
			int itemCountClone = usedItemRefClone->count;
			//eax
			int itemUnknownInfo = *((byte*)usedItemRefClone->unknown1);//only getting the highest byte of the unknonwn number (little endian)
			rdiAsRcx->gotDeced--;
			//rdx
			byte someCompareValue = usedItemRefClone->unknown1;
			((byte)itemCountClone) <<= 2;//will most likely shift out all 1s
			//cray cray stuff i know exDe
			int compareValueModified = someCompareValue - 6;
			//wtf is this?!
			itemCountClone &= 1;
			//checking how much/many of the used items, we can actually use?
			if (((byte)compareValueModified) & 0xf9 || someCompareValue == 0xc)
			{	
				compareValueModified = 1;
			}
			else
			{
				compareValueModified = usedItemRefClone->count;
			}
			//rdx
			ds2Item* flinkPtrOfUsed = usedItemRefClone->flink;
			//rcx
			ds2Item* blinkPtrOfUsed = usedItemRefClone->blink;
			usedAmountClone -= compareValueModified;
			//unlinking the itemstack from the list
			if (flinkPtrOfUsed != NULL)
			{
				usedItemRefClone->flink->blink = usedItemRefClone->blink;
			}
			if (blinkPtrOfUsed != NULL)
			{
				usedItemRefClone->blink->flink = usedItemRefClone->flink;
			}
			//TODO stopped here 0x13FE6BB89
			//ecx
			WORD itemListIndexCopy = usedItemRefClone->itemListIndex;

			//clearing the item structure, as the stack got used up
			memset(usedItemRefClone, NULL, sizeof(ds2Item));
			usedItemRefClone->itemListIndex = itemListIndexCopy;
			//itemcountclone will be the amount left of this item
			//rcx
			UNKNOWNSTRUCT2* rcxarg = rbpAsRdx;

			if (itemCountClone != 0)
			{
				sub_13F602180(rcxarg, usedItemRefClone);
			}
			else
			{
				if (itemUnknownInfo == 0x2)
				{
					sub_13F6021F0(rcxarg, usedItemRefClone);
				}
				else
				{
					sub_13F602110(rcxarg, usedItemRefClone);
				}
			}
		}
		else
		{
			//dont know what this is. this call leads to madness
			//				R8				R9				RCX			RDX
			callfunc1(usedItemRefClone, usedAmountClone, rdiAsRcx, rbpAsRdx);
			usedItemRefClone->count -= usedAmountClone;
			updateQuickInfoArray(rdiAsRcx, usedItemRefClone);
			return;
		}
	}
}

//0x13F602110
UNKNOWN sub_13F602110(UNKNOWNSTRUCT2* rcx, ds2Item* usedItem)
{

}

//0x13F6021F0
UNKNOWN sub_13F6021F0(UNKNOWNSTRUCT2* rcx, ds2Item* usedItem)
{

}

//0x13F602180
UNKNOWN sub_13F602180(UNKNOWNSTRUCT2* rcx, ds2Item* usedItem)
{

}
//0x13FB9A230
//								RCX					  RDX
void sub_13FB9A230(UNKNOWNSTRUCT1* arg, ds2Item* usedItem)
{
	//rax				4069d
	WORD subtractValue = 0x1000;
	//r8
	int localItemListIndexCopy = usedItem->itemListIndex;
	//trying to determine, what kind of item we are dealing with
	if (localItemListIndexCopy < subtractValue)
	{					//3850d
		subtractValue = 0xF00;//f00 is the item carry limit
		if (localItemListIndexCopy < subtractValue)
		{
			//if we enter this branch, then we most likely deal with an item
			//this line was XOR eax,eax
			subtractValue = 0;
			if (localItemListIndexCopy < 0)
				localItemListIndexCopy = 0;
			else
				localItemListIndexCopy = -1;
		}
	}

	localItemListIndexCopy -= subtractValue;

	localItemListIndexCopy <<= 4;
	localItemListIndexCopy += (int)arg->shortInfoItemArray;

	*(int*)localItemListIndexCopy = arg;
	*(((int*)localItemListIndexCopy)+1) = arg;
}

//0x13FB9D850
//								RCX					  RDX			   R8
UNKNOWN sub_13FB9D850(UNKNOWNSTRUCT1* arg, UNKNOWNSTRUCT2* arg2, ds2Item* usedItem)
{

	if (!(usedItem->itemStatusFlags & 0x2))
		return;

	//ALOT OF MISSING CODE HERE
	//debugged call just took the return
}

//0x13FB9A3A0
void unlinkIfItemLastEntry(UNKNOWNSTRUCT1* arg, ds2Item* usedItem)
{
	ds2Item* raxEndItem = arg->itemListEnd;
	if (raxEndItem != usedItem)
		return;
	//only one item in list
	if (arg->itemListEnd == arg->itemListEntry)
		arg->itemListEnd = NULL;
	else
		arg->itemListEnd = arg->itemListEnd->blink;
}

//0x13FE9A370
void unlinkIfItemFirstEntry(UNKNOWNSTRUCT1* arg, ds2Item* usedItem)
{
	ds2Item* raxEntryItem = arg->itemListEntry;
	if (raxEntryItem != usedItem)
		return;
	//only one element in the list?
	if (arg->itemListEntry == arg->itemListEnd)
		arg->itemListEntry = NULL;
	else//the new entry is the one after the used up item
		arg->itemListEntry = arg->itemListEntry->flink;
}

//0x13FE9B210
void clearAnotherItemListEntryFromStruct(UNKNOWNSTRUCT1* arg)
{
	arg->anotherItemListEntry = 0;
}
//13FEEAAE0(was this address on prismstone(i think) useage
//									RCX				  RDX
BOOL sub_13FEEAAE0(UNKNOWNSTRUCT1* structArray, __int32 itemInfoId)
{
	//RBX
	UNKNOWNSTRUCT1* localCopy = structArray;
	BOOL ret = calledAtRandomMoments(structArray->callBackTbl, itemInfoId);
	paramList* params = structArray->callBackTbl->paramList;
	//actually a jump
	return checkParamListMember(params->paramItemBytes);
}
//000000013FEF7980
//this function is called from various different 
//functions. Also on the loading screen. it probably is some item enumeration code
BOOL calledAtRandomMoments(callBacktable* callBackTable, __int32 itemInfoId)
{
	//this is the ID of the santiers spear
	WORD shadow2_38 = 0x319750;
	//rbx
	int* localCallBackFuncCopy = callBackTable;
	//this is also the id of the santiers spear???
	if (itemInfoId != 0x319b38)//is this a way to make 2 ids stand for the same item?
		shadow2_38 = itemInfoId;
	//is this a skip code on iteration
	if (shadow2_38 == callBackTable->itemId && callBackTable->bitFlags & 1)
	{
		return;
	}
	//lots of code missing here
	
}

//0x13FE98160
//										RCX					RDX
//the call to this function was actually a jmp
BOOL checkParamListMember(paramItemBytes* itemBytes)
{
	if (itemBytes != NULL && itemBytes->checkedAgainst0x1C2 == 0x1C2)//450d
		return TRUE;
	return FALSE;
}

//0x13FEEA2D0
void updateQuickInfoArray(UNKNOWNSTRUCT1* rcx, ds2Item* usedItem)
{
	//r8
	WORD localCopyItemActionId = usedItem->itemListIndex;
	//r9
	UNKNOWNSTRUCT1* localUStructCopy = rcx;
					//4069d
	short subValue = 0x1000;
	//the subvalue can be 0x1000(4069d), 0xF00(3840d),0 or 0xFFFF(-1d/65535d) 
	if (usedItem->itemListIndex <  subValue)
	{
		subValue = 0xF00;
		if (usedItem->itemListIndex < subValue)
		{
			subValue = 1;
			if (usedItem->itemListIndex == 0)//Darksign has item actionId 0
				subValue += 1;
		}
	}

	itemArrayEntry* ref = localUStructCopy->shortInfoItemArray;
	localCopyItemActionId -= subValue;
	

	//this is done in the assembly to make up for the size of the structure of the array, that is accesed next
	//localCopyItemActionId *= 2;
	//updating the count in the quickarray
	ref[localCopyItemActionId].itemCount = usedItem->count;
}


#pragma region callFuncStuff
//								RCX					  RDX			   R8				 R9				
UNKNOWN callfunc1(UNKNOWNSTRUCT1* uarg1, UNKNOWNSTRUCT2* uarg2,ds2Item* usedItem, int usedAmount )
{
	
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
				//if the item we just used is not in a quickslot, then all is fine and the function returns
				if (callSaveItemPtr->itemPositionFlags & ITEMISINQUICKSLOTBIT != 1)//ITEMQUICKSLOTSTATE3 means it is in the quickslot
					return;
				//but if it is in a quickslot this wild ride begins
				else
				{
					if (uarg1->QuickSlotArrayIterationLimit == 0)
						return;
					DWORD iterationCounter = 0;
					ds2Item* iterator = (uarg1->itemListEnd);
					//iterate through the quick itemslotsto get to the used item
					while (iterator != usedItem)
					{
						iterator++;
						iterationCounter++;
						//there are only 0xa (10) quick item slots, to iterate through
						if (iterationCounter >= uarg1->QuickSlotArrayIterationLimit)
							return;
					}
					//at this point we have either found the correct item ptr in the quickslots, or we must have already left the function
					//due to array bounds
					int currentItemCount = iterator->count;
					//decrease itemCount
					currentItemCount -= callSaveUsedAmount;

					if (subtractValue == 0x258)
					{

					}
					else if (subtractValue == uarg1->someShort)//should be always true?
					{
						int* funcPtrArryEntry = callSaveUStruct->vtable;
						int itemInfoId = callSaveItemPtr->itemInfoId;
						iterationCounter += 0x12;//???
						//not sure what this is yet
						//calling the 011th function from the given table, using the exact same table as an argument
						//the code in the next line is the "real" code, i changed it here, so that i can write the function actually down
						//((calledInItemUseFromPtrArray*)(funcPtrArryEntry + (0x88 / sizeof(funcPtrArryEntry))))(funcPtrArryEntry);
						//here begins the madness
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

//0x000000013F8F2D20
void functionThatIsInFuncPtrArrayGotCalledOnItemConsume(int* funcPtrTable, int someIterationCounter,WORD itemInfoId,WORD itemCount)
{
	//EDI
	WORD itemInfoIdCopy = itemInfoId;
	//EBP
	WORD itemCountCopy = itemCount;
	//RSI
	int someIterationCounterCopy = someIterationCounter;
	//R15
	int* funcPtrTableCopy = funcPtrTable;

	int* functionToExecute = getSomeFunctionPtr();
	if (functionToExecute == NULL)
		return;
	__int32 itemInfoCallArg = -1;
	if (itemInfoIdCopy != NULL)
		itemInfoCallArg = itemInfoIdCopy;
	
	//opposite of what happened before calling this function. was +12 in the caller function
	//ECX
	WORD modifiedIterationCounter = someIterationCounter - 0x12;
	//is now again the zero based index of the quickslot 
	//the item was in

	//look if it is a consumeable with an amount?
	if (itemCountCopy == 0 && itemInfoIdCopy > 0)
	{
		//some ptr arithmetic, that will end up putting the itemCount into the itemCountCopyArg
		//cant hink of a reason, where this would be executed
		//but at that point in execution, there is a ptr in R15, that is used with the 
		//someIterationcounter Argument to calculate the base address of the used item
		//TODO find out the relation between these pointers
	}
	//EAX
	WORD secondModIterCounter = modifiedIterationCounter + 0x14;//??was actually call with just one line an no epi- or prolog
	getItemUsageString(functionToExecute, secondModIterCounter, itemInfoCallArg, itemCountCopy);

}

int* getSomeFunctionPtr(void)
{

	int* functions[] = *(int*)GOLBALFUNCPTRARRAY;
	if (functions == NULL)
		return FALSE;
	int* functionPtrFromArray = (int*)functions[208 / sizeof(void*)];//was hex D0
	functionPtrFromArray = getFunctionFromArray(functionPtrFromArray);
	if (functionPtrFromArray == NULL)
		return FALSE;
	int* funcPtrArrayRDX = *functionPtrFromArray;
	//the entry in this array is called with the given arg. changed here for easier working
	//((&callIntoFunctionPtrArray)(funcPtrArrayRDX[96/sizeof(void*)]))();
	//there are some identical functions to this one, where the only difference is the given array offset from this line
	return callIntoFunctionPtrArray(functionPtrFromArray);
}
int* getFunctionFromArray(int* funcPtrArrayBase)
{
	//????
	return funcPtrArrayBase[888/sizeof(void*)];
}
int* callIntoFunctionPtrArray(int* funcPtrBase)
{
	return funcPtrBase[32];
}



//returns ptr to "Item[9]" if you use the item in the last Quickslot
//0x000000013FA812E0
//									RCX					  RDX				R8						 R9			
char* getItemUsageString(int* functionPtr, int modifiedQuickSlotIndex, __int32 itemInfoId, __int32 itemCount)
{
	//saving register into the shadow space

	

	//RDI
	int* functionPtrLocalCopy = functionPtr;
	__int32 itemCountLocalCopy = itemCount;
	
	//takes for some reason a pointer
	itemAction* temp = convertModifiedQuickSlotIndexToActionstring((SHORT*)&modifiedQuickSlotIndex);
	itemActionStruct itemActionStructure;
	fillArgsInStruct(&itemActionStructure, temp->u2, itemInfoId);

	//edx
	int modifiedQuickslotIndexCopy = modifiedQuickSlotIndex;
	stackFiller local;
	//r8
	__int32* structEntryCopy = &local.itemIdHigh;

	local.itemCount = itemCountLocalCopy;
	local.zeroMovedHere = 0;
	local.itemIdHigh = itemActionStructure.m1;
	local.itemIdLow = itemActionStructure.itemId;
	local.itemActionId = itemActionStructure.actionInfoId;//was 4 on spell urn use
	local.someGlobalValue = CONSTVALINGETITEMSTRING;

	sub_13F3BFFE0();
}

//000000013FB51D60
//retunrns some kind of structure,
//																	RCX	
											
itemAction* convertModifiedQuickSlotIndexToActionstring(short* modifiedQuickSlotIndex)
{
	short indexTester = *modifiedQuickSlotIndex;
	if (indexTester > 0x33)//= 51. is also char '3'. is this some kind of enum limit?
		return (CHAR*)GLOBALINVALIDRETSTRING;

	itemAction* actionDescriptorArray = (itemAction*)GLOBALACTIONDESCRIPTIONARRAY;
	//will calculate the itemslot, that is used from the given id.
	//if you use the item in your third quickslot. you will get the string
	//"Item[2]" back
	//basically from the given array start we calculate an offset into the string ptr table
	//one of the structs,used is 3 * 8 bytes big
	actionDescriptorArray += /*3 *  8 */ indexTester;
	return actionDescriptorArray;
}

//0x13FB51BF0
//													RCX					  RDX				R8	
itemActionStruct* fillArgsInStruct(itemActionStruct* ustruct1, byte someactionValue, int itemInfoId)//could also be the itemId. but it would be the same id anyways
{
	ustruct1->m1 = 0;
	//rax
	itemActionStruct* localCopy = ustruct1;
	//filling the args into some the given structure pointer
	ustruct1->itemId = itemInfoId;
	ustruct1->actionInfoId = someactionValue;
	return localCopy;
}


//000000013F3BFFE0
//									RCX					  RDX				R8						 R9			
UNKNOWN sub_13F3BFFE0()
{
	//where even am I right now?!!
}

#pragma endregion