//============================================================================
// Name        : InfoDTVPSIDynamic.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Poco/NumberParser.h"
#include "../PSIDynamicICESender/PSIDynamicICESender.h"

#include "../TimerProcesser/TimerProcesser.h"

using namespace std;

/* 作用：
 * 1、起线程，监视目录中值文件的变化
 * 2、根据定义文件与值文件生成TS流
 * 3、将生成的TS流发送到Mux中
 *
 * 参数
 *HostIP HostPort aServiceName aDefineXMLFile aValueXMLFile aTimerInt
 */

PSIDynamicICESenderPtr GlobalICESenderPtr;
void InitGlobalObjects(string aHostIP,unsigned int aHostPort,string aServiceName)
{
	GlobalICESenderPtr=new PSIDynamicICESender(aHostIP,aHostPort,aServiceName);
//	GlobalICESenderPtr->Connect();
}

bool SendBuffer(const unsigned char * Buffer,const unsigned int BufferLength)
{
	RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(BufferLength),&free);
	std::memcpy(TmpDataBuffer.get(),Buffer,BufferLength);
	GlobalICESenderPtr->SendAllBuffer(TmpDataBuffer,BufferLength);
	return true;
}

void MainRun(const char * aDefineXMLFile,const char * aValueXMLFile,const int aTimerInt,const SendBufferFunction aSendBufferFnPtr)
{
	string DefineXMLFile(aDefineXMLFile);
	string ValueXMLFile(aValueXMLFile);
	TimerProcesser TP(DefineXMLFile,ValueXMLFile,aTimerInt,aSendBufferFnPtr);
	std::cout<<"start runing.."<<std::endl;
	TP.start();
	string CmdStr;
	cin>>CmdStr;
	while(CmdStr!="q")
	{
		cin>>CmdStr;
	}
	TP.stop();
}

void Help()
{
	cout<<""<<endl;


}

int main(int argc, char* argv[]) {

	cout << "InfoDTV Dynamic ver 1.0 for DVB-PSI @CopyRight Victor 2009" << endl; // prints !!!Hello World!!!

	if(argc<7)
	{
		cout<<"Bad agr value"<<endl;
		Help();
		return -1;
	}
	string HostIP=argv[1];
	string HostPortStr=argv[2];
	string ServiceName=argv[3];
	string DefineXMLFile=argv[4];
	string ValueXMLFile=argv[5];
	string TimerIntStr=argv[6];

	unsigned int HostPort=Poco::NumberParser::parse(HostPortStr);
	unsigned int TimerInt=Poco::NumberParser::parse(TimerIntStr);
	InitGlobalObjects(HostIP,HostPort,ServiceName);
	MainRun(DefineXMLFile.c_str(),ValueXMLFile.c_str(),TimerInt,SendBuffer);

	return 0;
}
