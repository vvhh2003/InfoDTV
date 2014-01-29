/*
 * PMTTable.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "PMTTable.h"

using namespace TSLibrary::DVB::PSI;

unsigned short PMTTable::GetPMTBufferSize()
{
	return 4+FPMTDataRecords.size()*5;

}


PMTTable::~PMTTable()
{
	for(std::vector<PMTDataRecord *>::iterator i = FPMTDataRecords.begin(); i != FPMTDataRecords.end(); ++i)
	{
		delete *i;
	}
}
PMTTable::PMTTable():
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()), FPID(100),FPcr_PID(0x1fff),FProgram_number(1000)
{

}
PMTTable::PMTTable(unsigned short aPID,unsigned short aProgram_number) :
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()), FPID(aPID),FPcr_PID(0x1fff),FProgram_number(aProgram_number)
	{

	}
PMTTable::PMTTable(unsigned short aPID,unsigned short aPcr_PID,unsigned short aProgram_number) :
	FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()), FPID(aPID),FPcr_PID(aPcr_PID),FProgram_number(aProgram_number)
	{

	}

void PMTTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	RawBufferPtr AllBuffer((unsigned char *)std::malloc(GetPMTBufferSize()),&free);
	unsigned char * TmpAllBufferPtr=AllBuffer.get();
	TmpAllBufferPtr[0]=(FPcr_PID>>8)&0x1F; //Pcr_PID Hi;
	TmpAllBufferPtr[1]=FPcr_PID&0xFF; //PCR_PID Lo
	TmpAllBufferPtr[2]=0;
	TmpAllBufferPtr[3]=0;
	for (unsigned int i=0; i<FPMTDataRecords.size(); i++)
	{

		unsigned char * TmpBufferPtr=AllBuffer.get()+4+i*5;
		TmpBufferPtr[0]=FPMTDataRecords[i]->StreamType;
		TmpBufferPtr[1]=(FPMTDataRecords[i]->elementary_PID>>8)&0x1F; //elementary_PID_Hi
		TmpBufferPtr[2]=FPMTDataRecords[i]->elementary_PID&0xFF; //elementary_PID_Lo
		TmpBufferPtr[3]=0;
		TmpBufferPtr[4]=0;

	};
	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(FPID,0x2,FProgram_number, true);
	PSIHeaderConfig->PSIHeader.version_number=FVersion;
	aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, AllBuffer,
			GetPMTBufferSize(), FDataCounter, FCrc32Counter, true);
}

void PMTTable::SetVersion(unsigned char aVersion)
{
	FVersion=aVersion;
}

void PMTTable::AddElementary(unsigned char aStreamType, unsigned short aElementary_PID)
{
	//					PMTDataRecordPtr TT(new PMTDataRecord());
	//					FPMTDataRecords.push_back(TT);
	FPMTDataRecords.push_back(new PMTDataRecord());
	FPMTDataRecords[FPMTDataRecords.size()-1]->StreamType=aStreamType;
	FPMTDataRecords[FPMTDataRecords.size()-1]->elementary_PID=aElementary_PID;
}

