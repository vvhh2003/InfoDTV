/*
 * DefaultTSPacketDataOperator.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */
#include "DefaultTSPacketDataOperator.h"
using namespace TSLibrary;
 int DefaultTSPacketDataOperator::BuildTSPacket(TSPacketStructPtr aSrcTSPacket,TSPacketStructPtr aDestTSPacket, ITSDataCounterPtr aDataCounter)
 {
	 *aDestTSPacket=*aSrcTSPacket;
	 aDestTSPacket->FixCount(aDataCounter->GetNextCounter());
	 if (aDestTSPacket->Header.payload_unit_start_indicator)
	 {
		 aSrcTSPacket->Data[0]=0;
		 return 183;
	 }
	 else
		 return 184;
 }


 int DefaultTSPacketDataOperator:: WriteTSData(TSPacketStructPtr aTSPacket, RawBufferPtr aSrcData, int aStartIndex,int aWriteSize)
 {

	 if (!aSrcData)
		 return 0;

	 if (aTSPacket->Header.payload_unit_start_indicator && aWriteSize > 183)
		 return 0;
	 if (aWriteSize>184)
		 return 0;

	 if (aTSPacket->Header.payload_unit_start_indicator)
	 {
		 //Buffer.BlockCopy(aSrcData, aStartIndex, aTSPacket, 5, aWriteSize);
		 void * Tmp=(void *)(aTSPacket->Data+1);
		 void * SrcTmp=aSrcData.get()+aStartIndex;
		 std::memcpy(Tmp, SrcTmp, aWriteSize);//避开指针域
	 }
	 else
	 {
		 void * SrcTmp=aSrcData.get()+aStartIndex;
		 //Buffer.BlockCopy(aSrcData, aStartIndex, aTSPacket, 4, aWriteSize);
		 std::memcpy((void *)aTSPacket->Data, SrcTmp, aWriteSize);
	 }
	 return aWriteSize;
 }
