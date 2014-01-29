/*
 * TimerProcesser.cpp
 *
 *  Created on: 2009-2-19
 *      Author: Victor
 */
#include "TimerProcesser.h"
#include "Common/TS.Library/DVB-PSI/PSITableBuilder.h"
#include "Common/TS.Library/DVB-PSI/PSITableBuilder2.h"
#include "Common/TS.Library/DVB/DefaultPSICrc32Counter.h"
#include "Common/TS.Library/DVB/DefaultPSIDataStream.h"
#include "Common/TS.Library/DefaultTSDataStream.h"
#include "Common/TS.Library/DefaultDataCounter.h"

#include <iostream>
#include <fstream>
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>
//#include <boost/lexical_cast.hpp>
#include "Poco/LocalDateTime.h"
#include "Poco/File.h"
#include "Poco/DateTime.h"

using Poco::LocalDateTime;
using Poco::DateTime;


//bool CheckDateTime()
//{
//	//	string ExpireDatestr="2009-12-31";
//
//
//	LocalDateTime today;
//	DateTime dt(2010,1,1);
//	LocalDateTime ExpireDate(dt);
//	if( ExpireDate>today)
//	{
//		return true;
//	}
//	else
//	{
//		cout<<"Application has Expired,please  connect with author."<<endl;
//		return false;
//	}
//
/*
//}

void BuildMultiRootTSStream(const string aTagretXMLFileName,const string aValueXMLFileName,const SendBufferFunction aSendBufferFnPtr)
{
	TSLibrary::ITSDataStreamPtr  FTSStreamPtr(new TSLibrary::DefaultTSDataStream());
	TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
	TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
	TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());


	XMLBIN::XMLBINProcessor FXMLBINProcessor(aTagretXMLFileName);
	XMLBIN::XMLBINRecordPtrList TmpXMLBINRecordPtrList=FXMLBINProcessor.ProcessMultiRootXML(aValueXMLFileName);

	if(TmpXMLBINRecordPtrList.size()==0)
	{
		cout<<"Error:"<<endl;
		cout<<FXMLBINProcessor.GetError()<<endl;
		cout<<"Quit"<<endl;
		return;
	}
	for(unsigned int i=0;i<TmpXMLBINRecordPtrList.size();i++)
	{

		TSLibrary::DVB::PSI::PSITableBuilder FPSITableBuilder;
		if(!FPSITableBuilder.setRecoder(TmpXMLBINRecordPtrList[i]))
		{
			cout<<"Error:Result Index:"<<i<<endl;
			cout<<"Quit"<<endl;
			return;
		}
		FPSITableBuilder.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}
	int AllDataSize=FTSStreamPtr->GetDumpDataSize();
	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	FTSStreamPtr->ClearData();
	if(aSendBufferFnPtr)
		aSendBufferFnPtr(TmpDataBuffer.get(),AllDataSize);
}

void BuildMultiRootTSStream2(const string aTagretXMLFileName,const string aValueXMLFileName,const SendBufferFunction aSendBufferFnPtr)
{
	TSLibrary::ITSDataStreamPtr  FTSStreamPtr(new TSLibrary::DefaultTSDataStream());
	TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
	TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
	TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());


	PSIXMLBIN::PSIXMLBINProcessor FXMLBINProcessor(aTagretXMLFileName);
	PSIXMLBIN::PSIXMLBINRecordPtrList TmpXMLBINRecordPtrList=FXMLBINProcessor.ProcessMultiRootXML(aValueXMLFileName);

	if(TmpXMLBINRecordPtrList.size()==0)
	{
		cout<<"Error:"<<endl;
		cout<<FXMLBINProcessor.GetError()<<endl;
		cout<<"Quit"<<endl;
		return;
	}
	for(unsigned int i=0;i<TmpXMLBINRecordPtrList.size();i++)
	{

		TSLibrary::DVB::PSI::PSITableBuilder2 FPSITableBuilder;
		if(!FPSITableBuilder.setRecoder(TmpXMLBINRecordPtrList[i]))
		{
			cout<<"Error:Result Index:"<<i<<endl;
			cout<<"Quit"<<endl;
			return;
		}
		FPSITableBuilder.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
	}
	int AllDataSize=FTSStreamPtr->GetDumpDataSize();
	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
	FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
	FTSStreamPtr->ClearData();
	if(aSendBufferFnPtr)
		aSendBufferFnPtr(TmpDataBuffer.get(),AllDataSize);
}
*/


InfoDTVTimerProcesser::InfoDTVTimerProcesser(const string aHostIP,const int aHostIPPort,
		const string aChannelName,const unsigned short aPID,
		const string aTSParams,const string aIBLPath,
		const string aPathGuid,const int aTimerInt,const int aRunMode,
		const string aDebugPath,
		const SendBufferFunction SendBufferFnPtr):
			FHostIP(aHostIP),FHostIPPort(aHostIPPort),
			FChannelName(aChannelName),
			FPID(aPID),
			FTSParams(aTSParams),FIBLPath(aIBLPath),FPathGuid(aPathGuid),
			FTimerInterval(aTimerInt),
			FRunMode(aRunMode),
			FDebugPath(aDebugPath),
			FTimer(1000,FTimerInterval),
			FTimerCallback(*this, &InfoDTVTimerProcesser::onTimer),
			FSendBufferFnPtr(SendBufferFnPtr),
			FBuilder(FPathGuid,FTSParams,FPID,FIBLPath)
	{

	}
void InfoDTVTimerProcesser::onTimer(Poco::Timer& atimer)
{
	cout<<"----------->Start Build InfoDTV Service <----------"<<endl;
//	boost::filesystem::path DFPath(FDefineFile);
	Poco::File IBLPath(FIBLPath);
//	if(!boost::filesystem::exists(DFPath))
	if(!IBLPath.exists())
	{
		cout<<"----------->Can't find IBL Path<---------->"<<FIBLPath<<endl;
		return;
	}
//	boost::filesystem::path VFPath(FValueFile);
	Poco::File IndexFile(FIBLPath+"Index.IBL");
//	if(!boost::filesystem::exists(VFPath))
	if(!IndexFile.exists())
	{
		cout<<"----------->Can't find Index.IBL File<----------"<<FIBLPath+"Index.IBL"<<endl;
		return;
	}
/*	if(FRunMode==0)
		BuildMultiRootTSStream(FDefineFile,FValueFile,FSendBufferFnPtr);
	else
		BuildMultiRootTSStream2(FDefineFile,FValueFile,FSendBufferFnPtr);*/
	FBuilder.Process();
	switch (FRunMode)
	{
		case 0:
		{
			cout<<"Mode 0"<<endl;
			RawBufferPtr TmpBuffer=FBuilder.BufferManager.BeginRead();
			int size=FBuilder.BufferManager.GetBufferLength();
			if(FSendBufferFnPtr)
				FSendBufferFnPtr(FPathGuid.c_str(),TmpBuffer.get(),size);
			break;
		}
		case 1:
			{
				cout<<"Mode 1"<<endl;
				RawBufferPtr TmpBuffer=FBuilder.BufferManager.BeginRead();
				int size=FBuilder.BufferManager.GetBufferLength();
				if(FSendBufferFnPtr)
					FSendBufferFnPtr(FPathGuid.c_str(),TmpBuffer.get(),size);
				std::ofstream OutLogFileStream;
				OutLogFileStream.open((FDebugPath+FPathGuid+".LOG").c_str(),std::ios::binary);
				FBuilder.PrintAllToStream(OutLogFileStream);
				OutLogFileStream.close();
				break;
			}
		case 100:
		{
			cout<<"Mode 100"<<endl;
			RawBufferPtr TmpBuffer=FBuilder.BufferManager.BeginRead();
			int size=FBuilder.BufferManager.GetBufferLength();
			if(FSendBufferFnPtr)
				FSendBufferFnPtr(FPathGuid.c_str(),TmpBuffer.get(),size);
			std::ofstream OutFileStream;
			OutFileStream.open((FDebugPath+FPathGuid+".TS").c_str(),std::ios::binary);
			OutFileStream.write((char *)(TmpBuffer.get()), size);
			OutFileStream.close();
			break;
		}
		case 101:
		{
			cout<<"Mode 101"<<endl;
			std::ofstream OutFileStream;
			std::ofstream OutLogFileStream;
			OutFileStream.open((FDebugPath+FPathGuid+".TS").c_str(),std::ios::binary);
			OutLogFileStream.open((FDebugPath+FPathGuid+".LOG").c_str(),std::ios::binary);
			RawBufferPtr TmpBuffer=FBuilder.BufferManager.BeginRead();
			int size=FBuilder.BufferManager.GetBufferLength();
			OutFileStream.write((char *)(TmpBuffer.get()), size);
			OutFileStream.close();
			FBuilder.PrintAllToStream(OutLogFileStream);
			OutLogFileStream.close();
			break;
		}
		default:
		{
			cout<<"Mode default"<<endl;
			RawBufferPtr TmpBuffer=FBuilder.BufferManager.BeginRead();
			int size=FBuilder.BufferManager.GetBufferLength();
			if(FSendBufferFnPtr)
				FSendBufferFnPtr(FPathGuid.c_str(),TmpBuffer.get(),size);
			break;
		}

	}

	cout<<"----------->End  Build InfoDTV Service<-----------"<<endl;
}

void InfoDTVTimerProcesser::start()
{
	FBuilder.Init();
	FTimer.start(FTimerCallback);
}
void InfoDTVTimerProcesser::stop()
{
	FTimer.stop();
}
