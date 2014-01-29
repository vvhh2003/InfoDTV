/*
 * ScenarioInfoTable.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "ScenarioInfoTable.h"

using namespace std;
using namespace TSLibrary::DVB;
using namespace TSLibrary::InfoDTV;
unsigned int ScenarioInfoTable::GetScenarioInfoSize()
{
	return 2+LinkedObjectIDs.size()*2;
}

ScenarioInfoTable::ScenarioInfoTable()
{

}
ScenarioInfoTable::ScenarioInfoTable(unsigned short aPID, unsigned char aVersion, unsigned char aScenarioID) :
	PID(aPID), Version(aVersion), ScenarioID(aScenarioID)
	{

	}
ScenarioInfoTable::~ScenarioInfoTable()
{

}
void ScenarioInfoTable::CleanLinkedObjectIDs()
{
	LinkedObjectIDs.clear();
	vector<unsigned short>(LinkedObjectIDs).swap(LinkedObjectIDs);
}

void ScenarioInfoTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	//					RawBufferPtr AllBuffer((unsigned char *)std::malloc(8));
	//				    PSIHeadConfig PSIConfig = new PSIHeadConfig(PID, ServiceInfoTableID, true);
	//				           PSIConfig.VersionNumber = Version;
	//
	//				           PSIConfig.Special_ID_Field = 0x0;

	unsigned char RealVersion=((unsigned char)Version<<1)+0xC1;

	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(PID,
			ScenarioInfoTableID, RealVersion,ScenarioID, true);
	PSIHeaderConfig->PSIHeader.version_number=0x1F;
	PSIHeaderConfig->PSIHeader.reserved2BitFiled1=0x1;
	PSIHeaderConfig->PSIHeader.reserved2BitFiled1=0x1;
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
	unsigned int bufferSize=GetScenarioInfoSize();
	//					std::cout<<bufferSize<<std::endl;
	RawBufferPtr TmpBufferPtr((unsigned char *)std::malloc(bufferSize),&free);
	unsigned char * TmpPtr=TmpBufferPtr.get();
	//					for (unsigned int i=0; i<bufferSize; i++)
	//					{
	//						std::cout<<(int)TmpPtr[i]<<std::endl;
	//					}
	TmpPtr[0]=0;
	TmpPtr[1]=(unsigned char)LinkedObjectIDs.size();


	//					std::cout<<LinkedScenarioID.size()<<std::endl;
	for (unsigned int i=1; i<=LinkedObjectIDs.size(); i++)
	{
		TmpPtr[i*2]=(unsigned char)(LinkedObjectIDs[i-1]>>8);
		TmpPtr[i*2+1]=(unsigned char)(LinkedObjectIDs[i-1]&0x00FF);
	}
	//					std::cout<<std::endl;
	//					for (unsigned int i=0; i<bufferSize; i++)
	//					{
	//						std::cout<<(int)TmpPtr[i]<<std::endl;
	//					}

	aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, TmpBufferPtr, bufferSize,
			FDataCounter, FCrc32Counter, false);
}
