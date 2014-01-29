//============================================================================
// Name        : InfoDTVPSIDynamic.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Poco/NumberParser.h"
#include "Poco/File.h"
#include "../PSIDynamicICESender/PSIDynamicICESender.h"

#include "../TimerProcesser/TimerProcesser.h"
#include "PSIDynamicGlobalConfig.hpp"


#include <unistd.h>
#include <stdio.h>
#include <signal.h>

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
bool IsStoped=false;
void EndRun(int unused)
{
	IsStoped=true;
	std::cout<<"stoping.."<<std::endl;
}
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

void MainRun(const char * aDefineXMLFile,const char * aValueXMLFile,const int aTimerInt,const SendBufferFunction aSendBufferFnPtr,const int aRunMode=0)
{
	string DefineXMLFile(aDefineXMLFile);
	string ValueXMLFile(aValueXMLFile);
	TimerProcesser TP(DefineXMLFile,ValueXMLFile,aTimerInt,aSendBufferFnPtr,aRunMode);
	std::cout<<"start runing.."<<std::endl;
	TP.start();
	string CmdStr;
	cin>>CmdStr;
	signal(SIGHUP, EndRun); //* 下面设置三个信号的处理方法
	signal(SIGINT, EndRun);
	signal(SIGQUIT, EndRun);
	while(!IsStoped)
	{
		sleep(6000);
	}
	TP.stop();
}

void Help()
{
	cout<<""<<endl;


}

int main(int argc, char* argv[]) {

	cout << "InfoDTV Dynamic ver 1.0 for DVB-PSI @CopyRight Victor 2009" << endl; // prints !!!Hello World!!!
	cout<<"Build Date:"<<__DATE__<<"  "<<__TIME__<<endl;
	string MainConfigFile="InfoDTVPSIDynamic.config";
	PSIDynamicGlobalConfigObject GCObject;
	if(argc==1)
	{


		Poco::File ConfigFile(MainConfigFile);
		if(ConfigFile.exists())
		{
			GCObject.LoadConfig(MainConfigFile,true);
			InitGlobalObjects(GCObject.HostIP,GCObject.HostIPPort,GCObject.ChannelName);
			MainRun(GCObject.DefineXMLFile.c_str(),GCObject.ValueXMLFile.c_str(),GCObject.TimerInterval,SendBuffer,GCObject.RunMode);
		}
	}
	if(argc<8)
	{
		cout<<"Bad agrvalue"<<endl;
		Help();
		return -1;
	}


	GCObject.HostIP=argv[1];
	string HostPortStr=argv[2];
	GCObject.ChannelName=argv[3];
	GCObject.DefineXMLFile=argv[4];
	GCObject.ValueXMLFile=argv[5];
	string TimerIntStr=argv[6];
	string RunModeStr=argv[7];
	GCObject.HostIPPort=Poco::NumberParser::parse(HostPortStr);
	GCObject.TimerInterval=Poco::NumberParser::parse(TimerIntStr);
	GCObject.RunMode=Poco::NumberParser::parse(RunModeStr);
	GCObject.SaveToFile(MainConfigFile);

	InitGlobalObjects(GCObject.HostIP,GCObject.HostIPPort,GCObject.ChannelName);
	MainRun(GCObject.DefineXMLFile.c_str(),GCObject.ValueXMLFile.c_str(),GCObject.TimerInterval,SendBuffer,GCObject.RunMode);

	return 0;
}
