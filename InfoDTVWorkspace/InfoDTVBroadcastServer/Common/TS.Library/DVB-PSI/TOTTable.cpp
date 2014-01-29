/*
 * TOTTable.cpp
 *
 *  Created on: 2009-2-25
 *      Author: victor
 */
#include "TOTTable.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
using namespace TSLibrary::DVB::PSI;

TOTTable::TOTTable():
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter())
{

}

TOTTable::TOTTable(ITSDataCounterPtr aDataCounter,IPSICrc32CounterPtr aCrc32Counter):
	FDataCounter(aDataCounter), FCrc32Counter(aCrc32Counter)
{

}

TOTTable::~TOTTable()
{
}

void TOTTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(0x14, 0x73,
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

	RawBufferPtr TmpBufferPtr((unsigned char *)std::malloc(17),&free);
	unsigned char * TOTData=TmpBufferPtr.get();
	TOTData[0]=0xF0; //reserved 4 Bit
	TOTData[1]=0x0F; //descriptors_loop_length 12 bit
	TOTData[2]= 0x58;//descriptor_tag
	TOTData[3]=13;//descriptor_length
	TOTData[4]=0x43;//country_code 1 Byte C
	TOTData[5]=0x48;//country_code 1 Byte H
	TOTData[6]=0x4E;//country_code 1 Byte N
	TOTData[7]=0x02; //country_region_id 6 bslbf	reserved 1 bslbf 	local_time_offset_polarity 1 bslbf
	TOTData[8]=0x08; //local_time_offset 16Bit Hi
	TOTData[9]=0x00; //local_time_offset 16Bit Lo
	TOTData[10]=0xCD; //time_of _change
	TOTData[11]=0xEF; //time_of _change
	TOTData[12]=0x08; //time_of _change
	TOTData[13]=0x33; //time_of _change
	TOTData[14]=0x36; //time_of _change
	TOTData[15]=0x08; //next_time_offset
	TOTData[16]=0x00; //next_time_offset

	ITSDataCounterPtr CounterPtr=FDataCounter;
	IPSICrc32CounterPtr Crc32Ptr=FCrc32Counter;
	if(aDataCounter)
		CounterPtr=aDataCounter;
	if(aCrc32Counter)
		Crc32Ptr=aCrc32Counter;
	aStream->WriteSpecialSectionDataToTSStream(aTSStream, PSIHeaderConfig,TmpBufferPtr ,
			17,0,17, CounterPtr, Crc32Ptr);
}
