//============================================================================
// Name        : InfoDTVXMLPSITSBuilder.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
#include<boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "../XMLBINProcessor/XMLBINProcessor.h"
#include "../XMLBINProcessor/PSIXMLBINProcessor.h"
#include "../Common/TS.Library/DVB-PSI/PSITableBuilder.h"
#include "../Common/TS.Library/DVB-PSI/PSITableBuilder2.h"
#include "../Common/TS.Library/DVB/DefaultPSICrc32Counter.h"
#include "../Common/TS.Library/DVB/DefaultPSIDataStream.h"
#include "../Common/TS.Library/DefaultTSDataStream.h"
#include "../Common/TS.Library/DefaultDataCounter.h"

using namespace std;

/*
 * 使用方法：
 * 输入参数
 * PSIXMLBINBuilder 定义XML  值XML 输出TS文件名称
 */


bool CheckDateTime()
{
//	string ExpireDatestr="2009-12-31";
	using namespace boost::posix_time;
	using namespace boost::gregorian;

    date today = day_clock::local_day();

	date ExpireDate(2009,12,31);
	if( ExpireDate>today)
	{
		return true;
	}
	else
	{
		cout<<"Application has Expired,please  connect with author."<<endl;
		return false;
	}

}

void BuildMultiRootTSFile2(string aTagretXMLFileName,string aValueXMLFileName,string aOutPutFileName)
{
	TSLibrary::ITSDataStreamPtr  FTSStreamPtr(new TSLibrary::DefaultTSDataStream());
	TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
	TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
	TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());

	if(!CheckDateTime())
		return ;

	PSIXMLBIN::PSIXMLBINProcessor FPSIXMLBINProcessor(aTagretXMLFileName);
	PSIXMLBIN::PSIXMLBINRecordPtrList TmpXMLBINRecordPtrList=FPSIXMLBINProcessor.ProcessMultiRootXML(aValueXMLFileName);

	if(TmpXMLBINRecordPtrList.size()==0)
	{
		cout<<"Error:"<<endl;
		cout<<FPSIXMLBINProcessor.GetError()<<endl;
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
	std::ofstream OutFileStream;
	OutFileStream.open(aOutPutFileName.c_str(),std::ios::binary);
	OutFileStream.write((char *)(TmpDataBuffer.get()), AllDataSize);
	OutFileStream.close();
}


void BuildMultiRootTSFile(string aTagretXMLFileName,string aValueXMLFileName,string aOutPutFileName)
{
	TSLibrary::ITSDataStreamPtr  FTSStreamPtr(new TSLibrary::DefaultTSDataStream());
	TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
	TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
	TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());

	if(!CheckDateTime())
		return ;

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
	std::ofstream OutFileStream;
	OutFileStream.open(aOutPutFileName.c_str(),std::ios::binary);
	OutFileStream.write((char *)(TmpDataBuffer.get()), AllDataSize);
	OutFileStream.close();
}

void BuildSingleRootTSFile(string aTagretXMLFileName,string aValueXMLFileName,string aOutPutFileName)
{
	if(!CheckDateTime())
		return ;
	TSLibrary::ITSDataStreamPtr  FTSStreamPtr(new TSLibrary::DefaultTSDataStream());
		TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
		TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
		TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());


		XMLBIN::XMLBINProcessor FXMLBINProcessor(aTagretXMLFileName);
		XMLBIN::XMLBINRecordPtr TmpXMLBINRecordPtr=FXMLBINProcessor.ProcessXML(aValueXMLFileName);

		if(!TmpXMLBINRecordPtr)
		{
			cout<<"Error:"<<endl;
			cout<<FXMLBINProcessor.GetError()<<endl;
			cout<<"Quit"<<endl;
			return;
		}
		TSLibrary::DVB::PSI::PSITableBuilder FPSITableBuilder;
		if(!FPSITableBuilder.setRecoder(TmpXMLBINRecordPtr))
		{
			cout<<"Error:Result Empty"<<endl;
			cout<<"Quit"<<endl;
			return;
		}
		FPSITableBuilder.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);

		int AllDataSize=FTSStreamPtr->GetDumpDataSize();
		RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(AllDataSize),&free);
		FTSStreamPtr->DumpToBuffer(TmpDataBuffer);
		FTSStreamPtr->ClearData();
		std::ofstream OutFileStream;
		OutFileStream.open(aOutPutFileName.c_str(),std::ios::binary);
		OutFileStream.write((char *)(TmpDataBuffer.get()), AllDataSize);
		OutFileStream.close();
}

void BuildBINFile(string aTagretXMLFileName,string aValueXMLFileName,string aOutPutFileName)
{
	if(!CheckDateTime())
		return ;
	XMLBIN::XMLBINProcessor FXMLBINProcessor(aTagretXMLFileName);
	XMLBIN::XMLBINRecordPtr TmpXMLBINRecordPtr=FXMLBINProcessor.ProcessXML(aValueXMLFileName);

	if(!TmpXMLBINRecordPtr)
	{
		cout<<"Direct BIN Error:"<<endl;
		cout<<FXMLBINProcessor.GetError()<<endl;
		cout<<"Quit"<<endl;
		return;
	}

	std::ofstream OutFileStream;
	int AllDataSize=TmpXMLBINRecordPtr->BufferLength;
	OutFileStream.open(aOutPutFileName.c_str(),std::ios::binary);
	OutFileStream.write((char *)(TmpXMLBINRecordPtr->Buffer.get()), AllDataSize);
	OutFileStream.close();
}

void BuildSimple(string aTagretXMLFileName,string aOutPutFileName)
{
	XMLBIN::XMLBINProcessor FXMLBINProcessor(aTagretXMLFileName);
	string SampleText=FXMLBINProcessor.BuildSample();
	std::ofstream OutFileStream;
	int AllDataSize=SampleText.size();
	OutFileStream.open(aOutPutFileName.c_str(),std::ios::binary);
	OutFileStream.write((char *)(SampleText.c_str()), AllDataSize);
	OutFileStream.close();
}

void BuildSimple2(string aTagretXMLFileName,string aOutPutFileName)
{
	PSIXMLBIN::PSIXMLBINProcessor FXMLBINProcessor(aTagretXMLFileName);
	string SampleText=FXMLBINProcessor.BuildSample();
	std::ofstream OutFileStream;
	int AllDataSize=SampleText.size();
	OutFileStream.open(aOutPutFileName.c_str(),std::ios::binary);
	OutFileStream.write((char *)(SampleText.c_str()), AllDataSize);
	OutFileStream.close();
}



void help()
{
	cout<<"Usage:"<<endl;
	cout<<"PSIXMLBINBuilder SourceDefine ValueDefine Output Mode"<<endl;
	cout<<"SourceDefine:SourceDefine file Name"<<endl;
	cout<<"ValueDefine:ValueDefine file Name"<<endl;
	cout<<"Output:Output file Name"<<endl;
	cout<<"Mode:\r\n \
			\t0(default)-MultiRoot TS Mode\r\n \
			\t1-Single Root TS Mode\r\n \
			\t2-Direct BIN Mode\r\n \
			\t3-Build Value Define XML Sample\r\n \
			\t4-Build Value Define XML Sample with New Tech\r\n \
			\t5--MultiRoot TS Mode with NewTech"<<endl;
}

int main(int argc,char* argv[]) {
	cout << "-->PSIXMLBINBuilder V0.5 @Copyright by Victor 2009<--" << endl;
	if(!CheckDateTime())
		return -255 ;
	if(argc<4)
	{
		cout<<"Params -1 Error!"<<endl;
		help();
		return -1;
	}

	//cout<<"Source:"<<TagretXMLFileName<<"\tValue:"<<ValueXMLFileName<<"\tOutput:"<<OutPutTSFileName<<endl;
	string TagretXMLFileName=argv[1];
	string ValueXMLFileName=argv[2];
	string OutPutFileName=argv[3];

	boost::filesystem::path TmpPath = TagretXMLFileName;
	if (!boost::filesystem::exists(TmpPath))
	{
		cout<<argv[0]<<"Error! -2 No Source Define File:"<<TmpPath<<endl;
		help();
		return -2;
	}
	TmpPath=ValueXMLFileName;

	if (!boost::filesystem::exists(TmpPath))
	{
		cout<<"Error! -3 No Value Define File"<<endl;
		help();
		return -3;
	}

	int RunMode=0;
	if(argc>4)
	{
		string RunModeStr=argv[4];
		RunMode=boost::lexical_cast<int>(RunModeStr);
	}
	switch(RunMode)
	{
		case 0:
			//MultiRoot TS Mode
			cout<<"--->MultiRoot TS Mode<---"<<endl;
			BuildMultiRootTSFile(TagretXMLFileName,ValueXMLFileName,OutPutFileName);
			break;
		case 1:
			//Single Root TS Mode
			cout<<"--->Single Root TS Mode<---"<<endl;
			BuildSingleRootTSFile(TagretXMLFileName,ValueXMLFileName,OutPutFileName);
			break;
		case 2:
			//Direct BIN Mode
			cout<<"--->Direct BIN Mode<---"<<endl;
			BuildBINFile(TagretXMLFileName,ValueXMLFileName,OutPutFileName);
			break;
		case 3:
			cout<<"--->Build Simple Mode<---"<<endl;
			BuildSimple(TagretXMLFileName,OutPutFileName);
			break;

		case 4:
			cout<<"--->Build New Tech for PSI Simple Mode<---"<<endl;
			BuildSimple2(TagretXMLFileName,OutPutFileName);
			break;
		case 5:
			cout<<"--->Build New Tech for PSI TS Mode<---"<<endl;
			BuildMultiRootTSFile2(TagretXMLFileName,ValueXMLFileName,OutPutFileName);
			break;
		default:
		{
			cout<<"Error! -4 RunMode Error"<<endl;
				help();
		}
	}

	cout<<"Done !"<<endl;
	return 0;
}

