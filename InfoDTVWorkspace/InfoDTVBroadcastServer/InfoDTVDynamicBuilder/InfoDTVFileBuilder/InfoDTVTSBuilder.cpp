/*
 * InfoDTVTSBuilder.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "InfoDTVTSBuilder.h"
#include "Poco/ScopedLock.h"
using namespace InfoDTV::DynamicBuilder::FileBuilder;


InfoDTVTSBufferManager::InfoDTVTSBufferManager() :FBuffer(),FBackupBuffer(),
FHasNewBuffer(false),FBackupBufferLength(0),
FBufferLength(0),FMutex()
{

}

uint InfoDTVTSBufferManager::GetBackupBufferLength()
{
	return FBackupBufferLength;
}

uint InfoDTVTSBufferManager::GetBufferLength()
{
	return FBufferLength;
}

RawBufferPtr InfoDTVTSBufferManager::BeginRead()
{
	EndRead();
	return FBuffer;
}

void InfoDTVTSBufferManager::EndRead()
{
	if (FHasNewBuffer)
	{
//		IceUtil::Mutex::Lock lock(FMutex);
	    FMutex.lock();
	    try
	    {
		FBuffer = FBackupBuffer;
		FBufferLength = FBackupBufferLength;
		FBackupBuffer.reset();//Add On 5.8
		FHasNewBuffer = false;
	    }
	    catch(...)
	    {
		FMutex.unlock();
	    }
	    FMutex.unlock();

	}
}

void InfoDTVTSBufferManager::SetNewBuffer(RawBufferPtr aBuffer, int aBufferLength)
{
//	IceUtil::Mutex::Lock lock(FMutex);
    FMutex.lock();
    try
    {
	FBackupBuffer = aBuffer;
	FBackupBufferLength = aBufferLength;
	FHasNewBuffer = true;
    }
    catch(...)
    {
	FMutex.unlock();
    }
    FMutex.unlock();
}





void InfoDTVTSBuilder::BeginProcessPath(string aFilePath)
{
	FGlobalPassCount++;
	Log("开始处理,PassCount :" + boost::lexical_cast<string>(FGlobalPassCount));
	FPProcesser.Start(FGlobalPassCount, aFilePath);
	Log("处理完成,PassCount :" + boost::lexical_cast<string>(FGlobalPassCount));
}

void InfoDTVTSBuilder::InsertNULLPackets()
{
	for(int i=0;i<2;i++)
		FTSStreamPtr->InsertNullPacket();
}


void  InfoDTVTSBuilder::BuildBuffer1()
{
	unsigned short ObjectEndID=FObjectList.size();

	//FServiceInfoTable.SetServiceInfo(0,1,TotalObjects,256,ObjectEndID+1);
	FServiceInfoTable.SetServiceInfo(0,1,255,256,ObjectEndID+254);


	FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);


	for(unsigned short OI=0;OI<255;OI++)
	{

		FObjectList[OI]->ScenarioInfo->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}

	for(unsigned short OI=0;OI<FObjectList.size();OI++)
	{
		FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}

	int AllDataSize=FTSStreamPtr->GetDumpDataSize();

	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	std::memset(TmpDataBuffer.get(),0,AllDataSize);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	BufferManager.SetNewBuffer(TmpDataBuffer,AllDataSize);
	FTSStreamPtr->ClearData();
}


void InfoDTVTSBuilder::BuildBuffer2()
{
	unsigned short ObjectEndID=FObjectList.size();

	//FServiceInfoTable.SetServiceInfo(0,1,TotalObjects,256,ObjectEndID+1);
	FServiceInfoTable.SetServiceInfo(0,1,255,256,ObjectEndID+254);

	FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);

	for(unsigned short OI=0;OI<255;OI++)
	{

		FObjectList[OI]->ScenarioInfo->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}

	for(unsigned short OI=0;OI<FObjectList.size();OI++)
	{
		if(FObjectList[OI]->IsBinding())
		{
			FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
			FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		}
	}

	int AllDataSize=FTSStreamPtr->GetDumpDataSize();

	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	FTSStreamPtr->ClearData();
	BufferManager.SetNewBuffer(TmpDataBuffer,AllDataSize);
}

void InfoDTVTSBuilder::BuildBuffer3()
{
	unsigned short ObjectEndID=FObjectList.size();

	//FServiceInfoTable.SetServiceInfo(0,1,TotalObjects,256,ObjectEndID+1);
	FServiceInfoTable.SetServiceInfo(0,1,255,256,ObjectEndID+254);

	FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);

	for(unsigned short OI=0;OI<255;OI++)
	{

		FObjectList[OI]->ScenarioInfo->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}

	for(unsigned short OI=255;OI<FObjectList.size();OI++)
	{
		FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}

	int AllDataSize=FTSStreamPtr->GetDumpDataSize();

	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	FTSStreamPtr->ClearData();
	BufferManager.SetNewBuffer(TmpDataBuffer,AllDataSize);
}

void InfoDTVTSBuilder::BuildBuffer4()
{
	unsigned short ObjectEndID=FObjectList.size();
	cout<<"Total Object:"<<ObjectEndID+255<<endl;
	//FServiceInfoTable.SetServiceInfo(0,1,TotalObjects,256,ObjectEndID+1);
	FServiceInfoTable.SetServiceInfo(0,1,255,256,ObjectEndID+255);

	FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);

	for(unsigned short OI=0;OI<255;OI++)
	{


		FObjectList[OI]->ScenarioInfo->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		if(FObjectList[OI]->IsBinding())
		{
			FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		}
	}

	for(unsigned short OI=255;OI<FObjectList.size();OI++)
	{
		FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}

	int AllDataSize=FTSStreamPtr->GetDumpDataSize();

	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	FTSStreamPtr->ClearData();
	BufferManager.SetNewBuffer(TmpDataBuffer,AllDataSize);
}

void InfoDTVTSBuilder::BuildBuffer5()
{
	unsigned short ObjectEndID=FObjectList.size();

	//FServiceInfoTable.SetServiceInfo(0,1,TotalObjects,256,ObjectEndID+1);
	FServiceInfoTable.SetServiceInfo(0,1,255,256,ObjectEndID+254);

	FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);

	for(unsigned short OI=0;OI<255;OI++)
	{

		if(FObjectList[OI]->IsBinding())
		{
			FObjectList[OI]->ScenarioInfo->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
			FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
			FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		}
	}

	for(unsigned short OI=255;OI<FObjectList.size();OI++)
	{
		FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}

	int AllDataSize=FTSStreamPtr->GetDumpDataSize();

	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	FTSStreamPtr->ClearData();
	BufferManager.SetNewBuffer(TmpDataBuffer,AllDataSize);
}


void  InfoDTVTSBuilder::BuildBuffer()
{
	unsigned short ObjectEndID=FObjectList.size();

	//FServiceInfoTable.SetServiceInfo(0,1,TotalObjects,256,ObjectEndID+1);
	FServiceInfoTable.SetServiceInfo(0,1,255,256,ObjectEndID+254);

	FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);


	for(unsigned short OI=0;OI<255;OI++)
	{
		if(OI<255)
		{
			FObjectList[OI]->ScenarioInfo->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
//								InsertNULLPackets();
			FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
		}

	}

	for(unsigned short OI=0;OI<FObjectList.size();OI++)
	{
//							if(OI<255)
//							{
//								FObjectList[OI]->ScenarioInfo->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
//								InsertNULLPackets();
//							}
//							if(OI%6==0)
//							{
//								FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
//								InsertNULLPackets();
//							}
		if(FObjectList[OI]->IsBinding())
      	{
			FObjectList[OI]->Object->TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
			FServiceInfoTable.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
      	}
//							InsertNULLPackets();


	}

	int AllDataSize=FTSStreamPtr->GetDumpDataSize();

	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	FTSStreamPtr->ClearData();
	BufferManager.SetNewBuffer(TmpDataBuffer,AllDataSize);
}

void  InfoDTVTSBuilder::RegisterToManager()
{
	GlobalBuilderManager.RegisterBuilder(FUUID,this,FTSParams);
}
void  InfoDTVTSBuilder::UnRegisterToManager()
{
	GlobalBuilderManager.UnRegisterBuilder(FUUID);
}


InfoDTVTSBuilder::InfoDTVTSBuilder(string aUUID,string aTSParams,unsigned short aPID,string aFilePath) :
	FUUID(aUUID),FTSParams(aTSParams),
	FGlobalPassCount(0), FLogger(), FTSStreamPtr(new TSLibrary::DefaultTSDataStream()),
	        FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream()), FDataCounter(
	                new TSLibrary::DefaultDataCounter()), FCrc32Counter(  new TSLibrary::DVB::DefaultPSICrc32Counter()),FPProcesser(aPID,
	                FObjectList, FileIDIndexer, FProcessDeque,FCrc32Counter),FFilePath(aFilePath),FServiceInfoTable(aPID),PID(aPID)
{
	//FObjectList.reserve(8);
	FLogger.setName("InfoDTV应用生成器 ID："+aUUID);
}

InfoDTVTSBuilder::InfoDTVTSBuilder(string aUUID,string aTSParams,unsigned short aPID,string aFilePath, TSLibrary::ITSDataCounterPtr aDataCounter) :
	FUUID(aUUID),FTSParams(aTSParams),FGlobalPassCount(0), FLogger(), FTSStreamPtr(new TSLibrary::DefaultTSDataStream()),
	        FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream()), FDataCounter(aDataCounter),
	        FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter()), FPProcesser(aPID,
	                FObjectList, FileIDIndexer, FProcessDeque,FCrc32Counter), FFilePath(aFilePath),FServiceInfoTable(aPID),PID(aPID)

{
	FLogger.setName("InfoDTV应用生成器 ID："+aUUID);
}
//
//					InfoDTVTSBuilder(unsigned short aPID, string aFilePath,TSLibrary::ITSDataCounterPtr aDataCounter ) :
//						FGlobalPassCount(0), FLogCounter(0), FTSStreamPtr(new TSLibrary::DefaultTSDataStream()),
//						        FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream()), FDataCounter(aDataCounter),
//						        FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter()), FPProcesser(FFileNameList,
//						                FObjectList, FileIDIndexer, FProcessDeque,FCrc32Counter), FFilePath(aFilePath),PID(aPID)
//					{
//
//					}

InfoDTVTSBuilder::~InfoDTVTSBuilder()
{
//						FFileNameList.clear();
//						vector<string>(FFileNameList).swap(FFileNameList);
	FObjectList.clear();
	vector<InfoDTVObjectPtr>(FObjectList).swap(FObjectList);
	FileIDIndexer.clear();
	map<string, unsigned short>(FileIDIndexer).swap(FileIDIndexer);
}


void InfoDTVTSBuilder::Init()
{
	FPProcesser.Init();
	// PrintAll();
	if (!FFilePath.empty())
		BeginProcessPath(FFilePath);
	BuildBuffer4();
}

void InfoDTVTSBuilder::Process()
{
	BeginProcessPath(FFilePath);
	//BuildBuffer();
	BuildBuffer4();
}

void InfoDTVTSBuilder::PrintAllToStream(std::ostream &aOut)
{
	aOut<<"--->Total Objects: "<<FObjectList.size()<<"<---"<<std::endl;
	for(unsigned int i=0;i<FObjectList.size();i++)
	{
		aOut<<"---------------------------------------------------------------\n";
		aOut<<"ID:\t"<<FObjectList[i]->ID<<std::endl;
		aOut<<"File Name:\t"<<FObjectList[i]->FileName<<std::endl;
		aOut<<"Last File Date Time:\t"<<FObjectList[i]->LastFileDateTime<<std::endl;
		aOut<<"PassCount:\t"<<FObjectList[i]->PassCount<<std::endl;
		aOut<<"<<<<<<<<<<<<<Scenario Part>>>>>>>>>>>>>>"<<std::endl;
		if(i<255)
		{
			if(FObjectList[i]->ScenarioInfo)
			{
				aOut<<"\tScenarioInfo ID:\t"<<(int)FObjectList[i]->ScenarioInfo->ScenarioID<<std::endl;
				aOut<<"\tScenarioInfo PID:\t"<<(int)FObjectList[i]->ScenarioInfo->PID<<std::endl;
				aOut<<"\tIBL Version:\t"<<(int)FObjectList[i]->ScenarioInfo->Version<<std::endl;
				aOut<<"\t>>>>>Total Linked Object:  "<<FObjectList[i]->ScenarioInfo->LinkedObjectIDs.size()<<" <<<<<"<<std::endl;
				for(unsigned int SI=0;SI<FObjectList[i]->ScenarioInfo->LinkedObjectIDs.size();SI++)
				{
					aOut<<"\t\tLinked Object ID:\t"<<FObjectList[i]->ScenarioInfo->LinkedObjectIDs[SI]<<std::endl;
				}
			}
			else
			{
				aOut<<"\t<<Is Not IBL InfoDTVObject>>"<<std::endl;
			}
			aOut<<"####################IBL Content Part Start####################"<<std::endl;
			aOut<<FObjectList[i]->IBLFileContent;
			aOut<<"\r\n####################IBL Content Part End####################"<<std::endl;

		}


		aOut<<"<<<<<<<<<<<<<Object Part>>>>>>>>>>>>>>"<<std::endl;
		if(FObjectList[i]->Object)
		{
			aOut<<"\tObject ID:\t"<<(int)FObjectList[i]->Object->ObjectID<<std::endl;
			aOut<<"\tObject PID:\t"<<(int)FObjectList[i]->Object->PID<<std::endl;
			aOut<<"\tObject Type:\t"<<(int)FObjectList[i]->Object->GetObjectType()<<std::endl;
			aOut<<"\tObject Size:\t"<<FObjectList[i]->Object->GetObjectSize()<<std::endl;
			aOut<<"\t>>>>>>Total Link From Object:  "<<FObjectList[i]->LinkFromIDs.size()<<" <<<<<<"<<std::endl;
			for(unsigned int SI=0;SI<FObjectList[i]->LinkFromIDs.size();SI++)
			{
				aOut<<"\t\tLink Form Object ID:\t"<<FObjectList[i]->LinkFromIDs[SI]<<std::endl;
			}
			if(i<255)
			{
				aOut<<"####################Object Content Part Start####################"<<std::endl;
				RawBufferPtr ContentPtr(FObjectList[i]->Object->GetObjectContentPtr());
				unsigned int size=FObjectList[i]->Object->GetObjectSize();
				aOut.write((char *)ContentPtr.get(),size);
				aOut<<"\r\n####################Object Content Part End####################"<<std::endl;
			}
		}
		else
		{
			aOut<<"\t<<ERROR !!Is No Object in InfoDTVObject>>"<<std::endl;
		}
	}

	{
		aOut<<"\n\n<<<<<<<<<File ID Internal Part Index Part>>>>>>>>>>>>>>"<<std::endl;
		aOut<<"\tTotal IDs:  "<<FileIDIndexer.size()<<std::endl;

		aOut<<"\tObject ID\t\tFile Name"<<std::endl;
		map<string,unsigned short>::iterator   it=FileIDIndexer.begin();
		for(;it!=FileIDIndexer.end();++it)
		{
			string Name=it->first;
			unsigned short ID=it->second;
			aOut<<"\t  "<<ID<<"\t\t\t\t  "<<Name<<std::endl;
		}
	}

	aOut<<"\n\n<<<<<<<<<File ID Final Index Part>>>>>>>>>>>>>>"<<std::endl;
	aOut<<"\tTotal IDs:  "<<FileIDIndexer.size()<<std::endl;

	aOut<<"\tObject ID\t\tFile Name"<<std::endl;
	map<string,unsigned short>::iterator   it=FileIDIndexer.begin();
	for(;it!=FileIDIndexer.end();++it)
	{
		string Name=it->first;
		unsigned short ID=it->second;
		unsigned short PrintID=0;
		if(ID+1>255)
		{
			PrintID=ID+1+255;
		}
		else
		{
			PrintID=ID+1;
		}
		aOut<<"\t  "<<PrintID<<"\t\t\t\t  "<<Name<<std::endl;
	}
}

void InfoDTVTSBuilder::PrintAll()
{
	int TmpInt=0;
	TmpInt=FObjectList.size();
	cout<<"--->Total Objects: "<<TmpInt<<"<---"<<std::endl;

	for(unsigned int i=0;i<FObjectList.size();i++)
	{
		cout<<"---------------------------------------------------------------\n";
		TmpInt=FObjectList[i]->ID;
		cout<<"ID:\t"<<TmpInt<<std::endl;
		cout<<"File Name:\t"<<FObjectList[i]->FileName<<std::endl;
		long TmpLong=(long) FObjectList[i]->LastFileDateTime;
		cout<<"Last File Date Time:\t"<<TmpLong<<std::endl;
		TmpInt=FObjectList[i]->PassCount;
		cout<<"PassCount:\t"<<TmpInt<<std::endl;
		cout<<"<<<<<<<<<<<<<Scenario Part>>>>>>>>>>>>>>"<<std::endl;
		if(i<255)
		{
			if(FObjectList[i]->ScenarioInfo)
			{
				int TT=(int)FObjectList[i]->ScenarioInfo->ScenarioID;
				cout<<"\tScenarioInfo ID:\t"<<TT<<std::endl;
				TT=(int)FObjectList[i]->ScenarioInfo->PID;
				cout<<"\tScenarioInfo PID:\t"<<TT<<std::endl;
				TT=(int)FObjectList[i]->ScenarioInfo->Version;
				cout<<"\tIBL Version:\t"<<TT<<std::endl;
				TmpInt=FObjectList[i]->ScenarioInfo->LinkedObjectIDs.size();
				cout<<"\t>>>>>Total Linked Object:  "<<TmpInt<<" <<<<<"<<std::endl;
				for(unsigned int SI=0;SI<FObjectList[i]->ScenarioInfo->LinkedObjectIDs.size();SI++)
				{
					TT=FObjectList[i]->ScenarioInfo->LinkedObjectIDs[SI];
					cout<<"\t\tLinked Object ID:\t"<<TT<<std::endl;
				}
			}
			else
			{
				cout<<"\t<<Is Not IBL InfoDTVObject>>"<<std::endl;
			}
		}
		cout<<"<<<<<<<<<<<<<Object Part>>>>>>>>>>>>>>"<<std::endl;
		if(FObjectList[i]->Object)
		{
			int TT=(int)FObjectList[i]->Object->ObjectID;
			cout<<"\tObject ID:\t"<<TT<<std::endl;
			TT=(int)FObjectList[i]->Object->PID;
			cout<<"\tObject PID:\t"<<TT<<std::endl;
			TT=(int)FObjectList[i]->Object->GetObjectType();
			cout<<"\tObject type:\t"<<TT<<std::endl;
			TmpInt=FObjectList[i]->LinkFromIDs.size();
			cout<<"\t>>>>>>Total Link From Object:  "<<TmpInt<<" <<<<<<"<<std::endl;
			for(unsigned int SI=0;SI<FObjectList[i]->LinkFromIDs.size();SI++)
			{
				TT=FObjectList[i]->LinkFromIDs[SI];
				cout<<"\t\tLink Form Object ID:\t"<<TT<<std::endl;
			}
		}
		else
		{
			cout<<"\t<<ERROR !!Is No Object in InfoDTVObject>>"<<std::endl;
		}
	}
}


