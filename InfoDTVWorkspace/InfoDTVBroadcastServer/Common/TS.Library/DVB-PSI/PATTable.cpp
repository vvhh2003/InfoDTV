/*
 * PATTable.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */
#include "PATTable.h"
using namespace TSLibrary::DVB::PSI;



PATTable::PATTable():
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()), FTransport_ID(1000)
{

}
PATTable::PATTable(int aTransport_ID) :
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()), FTransport_ID(aTransport_ID)
	{

	}
PATTable::~PATTable()
{
	for (std::vector<PATDataRecord *>::iterator i = FPATDataRecords.begin(); i
	!= FPATDataRecords.end(); ++i)
	{
		delete *i;
	}
}


void PATTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	RawBufferPtr AllBuffer((unsigned char *)std::malloc(FPATDataRecords.size()*4),&free);
	int count=FPATDataRecords.size();
	for (int i=0; i<count; i++)
	{
		unsigned char * TmpPtr=(unsigned char *)&(FPATDataRecords[i]->Program_number);
		unsigned char * TmpBufferPtr=AllBuffer.get()+i*4;
		TmpBufferPtr[1]=TmpPtr[0];
		TmpBufferPtr[0]=TmpPtr[1];


		//							TmpBufferPtr+=1;
		//							*TmpBufferPtr=*TmpPtr;
		//							TmpBufferPtr-=1;
		//							*TmpBufferPtr=*(TmpPtr+1);
		//
		//							TmpBufferPtr+=2;
		TmpPtr=(unsigned char *)&(FPATDataRecords[i]->Program_map_PID);
		TmpBufferPtr[3]=TmpPtr[0];
		TmpBufferPtr[2]=TmpPtr[1];
		//							TmpBufferPtr+=1;
		//							*TmpBufferPtr=*TmpPtr;
		//							TmpBufferPtr-=1;
		//							*TmpBufferPtr=*(TmpPtr+1);
	};
	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(0, 0,
			FTransport_ID, true);
	PSIHeaderConfig->PSIHeader.version_number=FVersion;
	aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, AllBuffer,
			FPATDataRecords.size()*4, FDataCounter, FCrc32Counter, true);
}

void PATTable::SetVersion(unsigned char aVersion )
{
	FVersion=aVersion;
}


void PATTable::AddProgram(int aProgram_number, int aProgram_map_PID)
{
	//						PATDataRecordPtr TT(new PATDataRecord());
	//						FPATDataRecords.push_back(TT);
	FPATDataRecords.push_back(new PATDataRecord());
	FPATDataRecords[FPATDataRecords.size()-1]->Program_number=aProgram_number;
	FPATDataRecords[FPATDataRecords.size()-1]->Program_map_PID=aProgram_map_PID;
}
