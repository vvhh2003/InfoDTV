/*
 * DyDoorwayInfoTable.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "DyDoorwayInfoTable.h"
using namespace std;
using namespace TSLibrary::DVB;
using namespace TSLibrary::InfoDTV;
DyDoorwayInfoTable::DyDoorwayInfoTable():
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter())
	{

	}
DyDoorwayInfoTable::DyDoorwayInfoTable(unsigned short aPID, unsigned long aVODDoorway_IP, unsigned long aStatusDoorway_IP) :
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()),PID(aPID), VODDoorway_IP(aVODDoorway_IP), StatusDoorway_IP(aStatusDoorway_IP)
	{

	}
DyDoorwayInfoTable::~DyDoorwayInfoTable()
{

}
void DyDoorwayInfoTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{

	unsigned long bufferSize=32;
	RawBufferPtr AllBuffer((unsigned char *)std::malloc(bufferSize),&free);
	unsigned char * TmpBufferPtr=AllBuffer.get();
	TmpBufferPtr[4]=(unsigned char)VODDoorway_IP>>24;
	TmpBufferPtr[5]=(unsigned char)VODDoorway_IP>>16;
	TmpBufferPtr[6]=(unsigned char)VODDoorway_IP>>8;
	TmpBufferPtr[7]=(unsigned char)VODDoorway_IP;


	TmpBufferPtr[12]=(unsigned char)StatusDoorway_IP>>24;
	TmpBufferPtr[13]=(unsigned char)StatusDoorway_IP>>16;
	TmpBufferPtr[14]=(unsigned char)StatusDoorway_IP>>8;
	TmpBufferPtr[15]=(unsigned char)StatusDoorway_IP;

	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(PID,
			DyDoorwayInfoTableID, 0, true);
	PSIHeaderConfig->PSIHeader.version_number=0;
	aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, AllBuffer,
			bufferSize, FDataCounter, FCrc32Counter, true);
}
