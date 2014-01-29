/*
 * TimerProcesser.cpp
 *
 *  Created on: 2009-2-19
 *      Author: Victor
 */
#include "TimerProcesser.h"
#include "XMLBINProcessor/XMLBINProcessor.h"
#include "Common/TS.Library/DVB-PSI/PSITableBuilder.h"
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
//}
void BuildMultiRootTSStream(const string aTagretXMLFileName,const string aValueXMLFileName,const SendBufferFunction aSendBufferFnPtr)
{
	TSLibrary::ITSDataStreamPtr  FTSStreamPtr(new TSLibrary::DefaultTSDataStream());
	TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
	TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
	TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());


	XMLBIN::XMLBINProcessor FXMLBINProcessor(aTagretXMLFileName);
	XMLBINRecordPtrList TmpXMLBINRecordPtrList=FXMLBINProcessor.ProcessMultiRootXML(aValueXMLFileName);

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
TimerProcesser::TimerProcesser(const string aDefineFile,const string aValueFile,const unsigned int aTimerInterval,const SendBufferFunction SendBufferFnPtr):
	FDefineFile(aDefineFile),FValueFile(aValueFile),FTimerInterval(aTimerInterval),FTimer(1000,FTimerInterval),
	FTimerCallback(*this, &TimerProcesser::onTimer),FSendBufferFnPtr(SendBufferFnPtr)
	{

	}
void TimerProcesser::onTimer(Poco::Timer& atimer)
{
	cout<<"----------->Start Refresh XML<----------"<<endl;
//	boost::filesystem::path DFPath(FDefineFile);
	Poco::File DFPath(FDefineFile);
//	if(!boost::filesystem::exists(DFPath))
	if(!DFPath.exists())
	{
		cout<<"----------->Can't find Define File<----------"<<endl;
		return;
	}
//	boost::filesystem::path VFPath(FValueFile);
	Poco::File VFPath(FValueFile);
//	if(!boost::filesystem::exists(VFPath))
	if(!VFPath.exists())
	{
		cout<<"----------->Can't find Value File<----------"<<endl;
		return;
	}
	BuildMultiRootTSStream(FDefineFile,FValueFile,FSendBufferFnPtr);
	cout<<"----------->End  Refresh  XML<-----------"<<endl;
}

void TimerProcesser::start()
{
	FTimer.start(FTimerCallback);
}
void TimerProcesser::stop()
{
	FTimer.stop();
}
