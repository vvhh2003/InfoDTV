/*
 * DyIPInfoTable.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "DyIPInfoTable.h"
using namespace std;
using namespace TSLibrary::DVB;
using namespace TSLibrary::InfoDTV;
unsigned int DyIPInfoTable::GetDyIPInfoTableSize()
{
	return DHCP_SrvName.length()+DHCP_ClientName.length()+14;
}
DyIPInfoTable::DyIPInfoTable():
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter())
	{

	}
DyIPInfoTable::DyIPInfoTable(unsigned short aPID, unsigned long aIPQAM_ID, string aDHCP_SrvName, string aDHCP_ClientName) :
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()),PID(aPID), IPQAM_ID(aIPQAM_ID), DHCP_SrvName(aDHCP_SrvName), DHCP_ClientName(aDHCP_ClientName)
	{

	}
DyIPInfoTable::~DyIPInfoTable()
{

}
void DyIPInfoTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	if(DHCP_SrvName.length()>255)
	{
		DHCP_SrvName=DHCP_SrvName.substr(0,255);
	}
	if(DHCP_ClientName.length()>255)
	{
		DHCP_ClientName=DHCP_ClientName.substr(0,255);
	}
	unsigned long bufferSize=GetDyIPInfoTableSize();
	RawBufferPtr AllBuffer((unsigned char *)std::malloc(bufferSize),&free);
	unsigned char * TmpBufferPtr=AllBuffer.get();
	TmpBufferPtr[0]=(unsigned char)IPQAM_ID>>24;
	TmpBufferPtr[1]=(unsigned char)IPQAM_ID>>16;
	TmpBufferPtr[2]=(unsigned char)IPQAM_ID>>8;
	TmpBufferPtr[3]=(unsigned char)IPQAM_ID;

	TmpBufferPtr[12]=DHCP_SrvName.length();

	unsigned char * TmpServerNameBufferPtr=AllBuffer.get()+13;
	std::memcpy(TmpServerNameBufferPtr,DHCP_SrvName.c_str(),DHCP_SrvName.length());

	TmpServerNameBufferPtr[DHCP_SrvName.length()]=DHCP_ClientName.length();
	TmpServerNameBufferPtr=TmpServerNameBufferPtr+DHCP_SrvName.length();

	std::memcpy(TmpServerNameBufferPtr,DHCP_ClientName.c_str(),DHCP_ClientName.length());

	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(PID,
			DyIPInfoTableID, 0, true);
	PSIHeaderConfig->PSIHeader.version_number=0;
	aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, AllBuffer,
			bufferSize, FDataCounter, FCrc32Counter, true);
}
