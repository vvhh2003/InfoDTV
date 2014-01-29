/*
 * ServiceInfoTable.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "ServiceInfoTable.h"
using namespace std;
using namespace TSLibrary::DVB;
using namespace TSLibrary::InfoDTV;

ServiceInfoTableRecord::ServiceInfoTableRecord():
	Service_Object_ID_Start_Hi(0),
	Service_Object_ID_Start_Lo(0),
	Service_Object_ID_End_Hi(0),
	Service_Object_ID_End_Lo(0),
	Reserved1(0),
	Service_Scenario_ID_Start(0),
	Reserved2(0),
	Service_Scenario_ID_End(0)
	{

	}
void ServiceInfoTableRecord::Init()
{
	Service_Object_ID_Start_Lo=0;
	Service_Object_ID_Start_Hi=0;
	Service_Object_ID_End_Lo=0;
	Service_Object_ID_End_Hi=0;
	Reserved1=0xFF;
	Service_Scenario_ID_Start=0;
	Service_Scenario_ID_End=0;
	Reserved2=0xFF;
}

void ServiceInfoTableRecord::setServiceObjectID(unsigned short aService_Object_ID_Start, unsigned short aService_Object_ID_End)
{
	Service_Object_ID_Start_Hi=aService_Object_ID_Start>>8;

	Service_Object_ID_Start_Lo=(unsigned char)(aService_Object_ID_Start&0x00ff);

	Service_Object_ID_End_Hi=aService_Object_ID_End>>8;
	Service_Object_ID_End_Lo=(unsigned char)(aService_Object_ID_End&0x00ff);
}



ServiceInfoTable::ServiceInfoTable()
{
	ServiceInfoRec.Init();
}

ServiceInfoTable::ServiceInfoTable(unsigned short aPID):PID(aPID),Version(0)
{
	ServiceInfoRec.Init();
}
ServiceInfoTable::ServiceInfoTable(unsigned short aPID, unsigned char aVersion, unsigned char aScenarioStartID,
		unsigned char aScenarioEndID, unsigned short aObjectStartID, unsigned short aObjectEndID) :
			PID(aPID), Version(aVersion)
			{
	ServiceInfoRec.Init();
	ServiceInfoRec.setServiceObjectID(aObjectStartID, aObjectEndID);
	ServiceInfoRec.Service_Scenario_ID_Start=aScenarioStartID;
	ServiceInfoRec.Service_Scenario_ID_End=aScenarioEndID;
			}
ServiceInfoTable::~ServiceInfoTable()
{

}
void ServiceInfoTable::SetServiceInfo(unsigned char aVersion, unsigned char aScenarioStartID,
		unsigned char aScenarioEndID, unsigned short aObjectStartID, unsigned short aObjectEndID)
{
	Version=aVersion;
	ServiceInfoRec.setServiceObjectID(aObjectStartID, aObjectEndID);
	ServiceInfoRec.Service_Scenario_ID_Start=aScenarioStartID;
	ServiceInfoRec.Service_Scenario_ID_End=aScenarioEndID;
}

void ServiceInfoTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	//					RawBufferPtr AllBuffer((unsigned char *)std::malloc(8));
	//				    PSIHeadConfig PSIConfig = new PSIHeadConfig(PID, ServiceInfoTableID, true);
	//				           PSIConfig.VersionNumber = Version;
	//
	//				           PSIConfig.Special_ID_Field = 0x0;

	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(PID,
			ServiceInfoTableID, 0, true);
	PSIHeaderConfig->PSIHeader.version_number=Version;
	if (!aDataCounter)
	{
		if (!FDataCounter)
			FDataCounter.reset(new DefaultDataCounter());
	}
	else
	{
		FDataCounter=aDataCounter;
	}

	if (!aCrc32Counter)
	{
		if (!FCrc32Counter)
			FCrc32Counter.reset(new DefaultPSICrc32Counter());
	}
	else
	{
		FCrc32Counter=aCrc32Counter;
	}
	RawBufferPtr TmpPtr((unsigned char *)std::malloc(8),&free);
	void * TT=&ServiceInfoRec;
	std::memcpy(TmpPtr.get(), TT, 8);
	//	unsigned char * BufferPtr=(unsigned char *)&ServiceInfoRec;
	aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, TmpPtr, 8, FDataCounter,
			FCrc32Counter, true);
}

