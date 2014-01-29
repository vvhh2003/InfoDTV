//============================================================================
// Name        : InfoDTVDynamic.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DynamicGlobalConfig.hpp"

#include "../DynamicICESender/DynamicICESender.h"

#include "../TimerProcesser/TimerProcesser.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <map>
#include <vector>
#include <net/if.h>
#include "Poco/SharedPtr.h"
#include "Poco/File.h"
using namespace std;

void TestConfig()
{
	DynamicGlobalConfigObject DGCO;
	DynamicGlobalConfigObjectItem DGCOI,DGCOI2;
	DGCOI.ChannelName="Test1";
	DGCOI.HostIP="192.168.0.177";
	DGCOI.HostIPPort=10007;
	DGCOI.IBLPath="/home/";
	DGCOI.PathGuid="GUID";
	DGCOI.RunMode=0;
	DGCOI.TSParams="12:12:12:12:12";
	DGCOI.TimerInterval=300000;

	DGCOI2.ChannelName="Test1";
	DGCOI2.HostIP="192.168.0.177";
	DGCOI2.HostIPPort=10007;
	DGCOI2.IBLPath="/home/";
	DGCOI2.PathGuid="GUID";
	DGCOI2.RunMode=0;
	DGCOI2.TSParams="12:12:12:12:12";
	DGCOI2.TimerInterval=300000;

	DGCO.Items.push_back(DGCOI);
	DGCO.Items.push_back(DGCOI2);
	DGCO.SaveToFile("TTT.config");
}




//PSIDynamicICESenderPtr GlobalICESenderPtr;
map<string,PSIDynamicICESenderPtr> GlobalICESenderPtrMap;
bool IsStoped=false;



void BuildSendBuffer(const char * aGUIDName,const char * aHostIP,const int aHostIPPort,
		const char * aChannelName)
{
	string PathGuid(aGUIDName);
	string HostIP(aHostIP);
	string ChannelName(aChannelName);
	if(GlobalICESenderPtrMap.count(PathGuid)==0)
	{
		PSIDynamicICESenderPtr TmpSenderPtr=new PSIDynamicICESender(HostIP,aHostIPPort,ChannelName);
		GlobalICESenderPtrMap[PathGuid]=TmpSenderPtr;
	}
}

bool SendBuffer(const char * aUUIDName,const unsigned char * Buffer,const unsigned int BufferLength)
{
	string UUIDName(aUUIDName);
	if(GlobalICESenderPtrMap.count(UUIDName)>0)
	{
		RawBufferPtr TmpDataBuffer((unsigned char *)std::malloc(BufferLength),&free);
		std::memcpy(TmpDataBuffer.get(),Buffer,BufferLength);
		PSIDynamicICESenderPtr TmpSenderPtr=GlobalICESenderPtrMap[UUIDName];
		TmpSenderPtr.get()->SendAllBuffer(TmpDataBuffer,BufferLength);
		return true;
	}

	return false;
}


//LINUX Parts

vector<InfoDTVTimerProcesserPtr> TimerProcesserPtrList;
void InitGlobalObjects(DynamicGlobalConfigObject & GlobalConfig,const BuildSendBufferFunction aBuildSendBufferFunction,const SendBufferFunction aSendBufferFunction)
{
	for(unsigned int i=0;i<GlobalConfig.Items.size();i++)
	{
		aBuildSendBufferFunction(GlobalConfig.Items[i].PathGuid.c_str(),
				GlobalConfig.Items[i].HostIP.c_str(),
				GlobalConfig.Items[i].HostIPPort,
				GlobalConfig.Items[i].ChannelName.c_str());
		InfoDTVTimerProcesserPtr TmpPtr(new InfoDTVTimerProcesser(GlobalConfig.Items[i].HostIP,
				GlobalConfig.Items[i].HostIPPort,
				GlobalConfig.Items[i].ChannelName,
				GlobalConfig.Items[i].PID,
				GlobalConfig.Items[i].TSParams,
				GlobalConfig.Items[i].IBLPath,
				GlobalConfig.Items[i].PathGuid,
				GlobalConfig.Items[i].TimerInterval,
				GlobalConfig.Items[i].RunMode,
				GlobalConfig.Items[i].DebugPath,
				aSendBufferFunction));
		TimerProcesserPtrList.push_back(TmpPtr);
	}
}


void EndRun(int unused)
{
	IsStoped=true;
	std::cout<<"now stoping.."<<std::endl;
}


void MainRun(const char * aConfigFileName,const BuildSendBufferFunction aBuildSendBufferFunction,
		const SendBufferFunction aSendBufferFunction)
{
	string ConfigFileName(aConfigFileName);
	DynamicGlobalConfigObject DGCO;
	DGCO.LoadConfig(aConfigFileName,true);
	InitGlobalObjects(DGCO,aBuildSendBufferFunction,aSendBufferFunction);
	for(unsigned int i=0;i<TimerProcesserPtrList.size();i++)
	{
		TimerProcesserPtrList[i]->start();
	}
	signal(SIGHUP, EndRun); //* 下面设置三个信号的处理方法
	signal(SIGINT, EndRun);
	signal(SIGQUIT, EndRun);
	while(!IsStoped)
	{
		sleep(6000);
	}
	for(unsigned int i=0;i<TimerProcesserPtrList.size();i++)
	{
		TimerProcesserPtrList[i]->stop();
	}
}

/*
void MainRun(const char * aHostIP,const int aHostIPPort,
		const char * aChannelName,const char * aTSParams,const char * aIBLPath,
		const char *aPathGuid,const int aTimerInt,const int aRunMode,
		const SendBufferFunction aSendBufferFunction)
{
	string HostIP(aHostIP);
	string ChannelName(aChannelName);
	string TSParams(aTSParams);
	string IBLPath(aIBLPath);
	string PathGuid(aPathGuid);
	TimerProcesser TP(HostIP,aHostIPPort,ChannelName,TSParams,IBLPath,PathGuid,aTimerInt,aRunMode,aSendBufferFnPtr);
	std::cout<<"start runing.."<<std::endl;
	TP.start();
	string CmdStr;
	cin>>CmdStr;
	signal(SIGHUP, EndRun); // 下面设置三个信号的处理方法
	signal(SIGINT, EndRun);
	signal(SIGQUIT, EndRun);
	while(!IsStoped)
	{
		sleep(6000);
	}
	TP.stop();
}
*/

void Help()
{
	cout<<"need a config file."<<endl;


}

int get_interf(const char *interf)
{

    int ret = -1;
    struct if_nameindex *ifp, *ifpsave;
    ifpsave = ifp = if_nameindex();

    if (!ifp)
        return -1;

    while (ifp->if_index) {
        if (strcmp(ifp->if_name, interf) == 0) {
            ret = 0;
            break;
        }
        ifp++;
    }

    if_freenameindex(ifpsave);
    return ret;
}


void list_interf()
{


	struct if_nameindex *ifp, *ifpsave;
	ifpsave = ifp = if_nameindex();

	if (!ifp)
		return ;

	while (ifp->if_index)
	{
		string IfNAME(ifp->if_name);
		cout<<IfNAME<<endl;
		ifp++;
	}

	if_freenameindex(ifpsave);

}


int main(int argc, char* argv[]) {
	cout << "InfoDTV(R) Dynamic ver 1.0  (C)CopyRight Victor @2009" << endl; // prints !!!Hello World!!!
	cout<<"Build Date:"<<__DATE__<<"  "<<__TIME__<<endl;
	string MainConfigFile="InfoDTVDynamic.config";
	if(argc==1)
	{
		Poco::File ConfigFile(MainConfigFile);
		if(ConfigFile.exists())
		{
			MainRun(MainConfigFile.c_str(),BuildSendBuffer,SendBuffer);
		}
	}
	else if(argc==2)
	{
		MainConfigFile=argv[1];
		Poco::File ConfigFile(MainConfigFile);
		if(ConfigFile.exists())
		{
			MainRun(MainConfigFile.c_str(),BuildSendBuffer,SendBuffer);
		}
	}
	else
	{
		Help();
	}
	return 0;
}
