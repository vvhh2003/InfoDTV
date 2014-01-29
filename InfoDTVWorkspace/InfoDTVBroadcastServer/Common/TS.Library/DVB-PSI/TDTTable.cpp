/*
 * TDTTable.cpp
 *
 *  Created on: 2009-2-24
 *      Author: victor
 */

#include "TDTTable.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include <string>
using namespace TSLibrary::DVB::PSI;


TDTTable::TDTTable():
	FDataCounter(new DefaultDataCounter()), FCrc32Counter()
{

}


TDTTable::TDTTable(ITSDataCounterPtr aDataCounter):
	FDataCounter(aDataCounter), FCrc32Counter()
{

}

TDTTable::~TDTTable()
{
}


void TDTTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(0x14, 0x70,
			0, false);

	Poco::LocalDateTime PLD;
	Poco::DateTime LDT=PLD.utc();

	unsigned short L=0;
	if(LDT.month()==1||LDT.month()==2) L=1;
	unsigned short MJD=14956+LDT.day()+int((LDT.year()-1900-L)* 365.25) +int((LDT.month() + 1 + L * 12) * 30.6001);
	RawBufferPtr TmpTDTData((unsigned char *)std::malloc(5),&free);
	unsigned char * TDTData=TmpTDTData.get();
//	PSIHeaderConfig->PSIHeader.PSIHeadLastPartData[0]=(MJD>>8);
//	PSIHeaderConfig->PSIHeader.PSIHeadLastPartData[1]=MJD&0x00FF;
//	PSIHeaderConfig->PSIHeader.PSIHeadLastPartData[2]=getBCDByte(LDT.hour());
//	PSIHeaderConfig->PSIHeader.PSIHeadLastPartData[3]=getBCDByte(LDT.minute());
//	PSIHeaderConfig->PSIHeader.PSIHeadLastPartData[4]=getBCDByte(LDT.second());
	TDTData[0]=(MJD>>8);
	TDTData[1]=MJD&0x00FF;
	TDTData[2]=getBCDByte(LDT.hour());
	TDTData[3]=getBCDByte(LDT.minute());
	TDTData[4]=getBCDByte(LDT.second());

	unsigned char *  PSIHeaderPtr=(unsigned char *)&(PSIHeaderConfig->PSIHeader);

	PSIHeaderPtr=PSIHeaderPtr+3;

	std::memcpy(PSIHeaderPtr,TDTData,5);
	RawBufferPtr Tmp;
	ITSDataCounterPtr CounterPtr=FDataCounter;
	IPSICrc32CounterPtr Crc32Ptr=FCrc32Counter;
	if(aDataCounter)
		CounterPtr=aDataCounter;
	aStream->WriteSpecialSectionDataToTSStream(aTSStream, PSIHeaderConfig,Tmp,
			0,0,0, CounterPtr, Crc32Ptr);
}
