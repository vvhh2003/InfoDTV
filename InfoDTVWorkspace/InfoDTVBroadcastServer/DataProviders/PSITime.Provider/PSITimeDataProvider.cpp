/*
 * PSITimeDataProvider.cpp
 *
 *  Created on: 2009-2-27
 *      Author: victor
 */

#include "../../Common/TSPacketStruct.h"
#include "PSITimeDataProvider.h"
#include "../../Common/TS.Library/DefaultDataCounter.h"
#include "../../Common/TS.Library/DefaultTSDataStream.h"
#include "../../Common/TS.Library/DVB/DefaultPSICrc32Counter.h"

using namespace std;

using namespace Multiplexer_DataProvider_V1;



void PSITimeDataProvider::Log(string ALogStr)
{
	FLogger.information(ALogStr);
}
PSITimeDataProvider::PSITimeDataProvider() :
	FIsActived(false),FLogger(),FGetCount(0),
	FTDTTable(),FTOTTable(),
	FDataCounter(new TSLibrary::DefaultDataCounter()), FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter())
	{
	FLogger.setName("PSITimeDataProvider");
	}

PSITimeDataProvider::~PSITimeDataProvider()
{
	DeActive();
	Log("<MEM>已释放");
}
void PSITimeDataProvider::Active()
{
	FIsActived=true;
}


void PSITimeDataProvider::ConfigChanged(string aNewConfig)
{
}

void PSITimeDataProvider::DeActive()
{
	FIsActived=false;

}

string PSITimeDataProvider::GetProviderInfo()
{
	string TmpState="TIME TDT TOT";
	return TmpState;
}

string PSITimeDataProvider::GetProviderStateInfo()
{
	string TmpState="TIME TDT TOT";
	return TmpState;
}

TSPacketStructPtr PSITimeDataProvider::GetTSPacket()
{
	if (!FIsActived)
		return TSPacketStruct::NewNullTSPacket();


	TSLibrary::ITSDataStreamPtr FTSStreamPtr(new TSLibrary::DefaultTSDataStream());

	TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());

//	TSLibrary::DVB::PSI::PATTable PAT;
//	PAT.AddProgram(2000,1022);
//	PAT.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	if(FGetCount==0)
	{
		FTDTTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FGetCount=1;
	}
	else
	{
		FTOTTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FGetCount=0;
	}

	TSPacketStructPtr TmpTSPacketPtr(new TSPacketStruct);

	if(FTSStreamPtr->GetDumpDataSize()==188)
	{
		RawBufferPtr TmpBuffer((unsigned char *)std::malloc(188),&free);
		FTSStreamPtr->DumpToBuffer(TmpBuffer);
		std::memcpy((void *) TmpTSPacketPtr.get(), TmpBuffer.get(), 188);
	}
	else
		return TSPacketStruct::NewNullTSPacket();
	return TmpTSPacketPtr;
}

void PSITimeDataProvider::Reset()
{
	DeActive();
	Active();
}

bool PSITimeDataProvider::getIsActived()
{
	return FIsActived;
}

string PSITimeDataProvider::getTypeID()
{
	return PSI_TIME_DATAPROVIDER_GUID;
}

string PSITimeDataProvider::GetCurrentConfig()
{
		return "";
}
