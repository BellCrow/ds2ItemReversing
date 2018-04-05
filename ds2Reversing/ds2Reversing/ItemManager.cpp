#include "ItemManager.h"
#include "FunctionTable.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::doUseItem(containsListOfItemsInArray* RCXuArg,
							ItemManager* RDXitemMgr,
							Ds2Item* R8usedItem,
							int R9usedAmount, 
							byte RSP60usedFunctionIndex)
{
	byte EAX_RSP60usedFunctionIndexCopy = RSP60usedFunctionIndex;
	//get the singleton instance
	FunctionTable* R10itemFunctionTableBase = FunctionTable::instance();
	int EDIusedAmountCopy = R9usedAmount;
	Ds2Item* RSIusedItemCopy = R8usedItem;
	ItemManager* RBPitemMgrCopy = RDXitemMgr;
	containsListOfItemsInArray* RBXuArgCopy = RCXuArg;
	byte RSP20uArgOutByte = 0;
	byte* RDXbytePtr = &RSP20uArgOutByte;
	R10itemFunctionTableBase->itemUseFunction(RCXuArg,RDXbytePtr,R8usedItem,R9usedAmount);
}

void ItemManager::decrementItemCount(UnknownClass2* rdx, Ds2Item* usedItem, int usedAmount)
{
	Ds2Item* usedItemRefClone/*mov in RBX*/ = usedItem;
	int usedAmountClone/*mov in (E/R)SI*/ = usedAmount;

	UnknownClass2* rbpAsRdx/*mov in RDX*/ = rdx;
	ItemManager* rdiAsRcx = this;

	if (this->getCheckedAtStart == 0 || this->getCheckedAtStart == 1)
	{

	}
	else
	{
		if (usedItemRefClone->count <= usedAmountClone)
		{
			//using up stack. so unlink and stuff
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
			itemCountClone = (byte) (itemCountClone <<= 2);//will most likely shift out all 1s
			//cray cray stuff i know 
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
			Ds2Item* flinkPtrOfUsed = usedItemRefClone->flink;
			//rcx
			Ds2Item* blinkPtrOfUsed = usedItemRefClone->blink;
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
			//ecx
			WORD itemListIndexCopy = usedItemRefClone->itemListIndex;

			//clearing the item structure, as the stack got used up
			memset(usedItemRefClone, NULL, sizeof(ds2Item));
			//writing back the itemListIndex in the empty srtucture
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

//13FEEAAE0(was this address on prismstone(i think) useage
//									RCX				  RDX
BOOL ItemManager::sub_13FEEAAE0( __int32 itemInfoId)
{
	//RBX
	ItemManager* localCopy = this;
	BOOL ret = calledAtRandomMoments(structArray->callBackTbl, itemInfoId);
	paramList* params = structArray->callBackTbl->paramList;
	//actually a jump
	return checkParamListMember(params->paramItemBytes);
}