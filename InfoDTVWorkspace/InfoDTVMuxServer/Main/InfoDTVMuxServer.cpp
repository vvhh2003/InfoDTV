//============================================================================
// Name        : InfoDTVMuxServer.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Common/Log/Log.h"

#include "Common/GlobalConfig.hpp"

#include "Multiplexer/UDP/UDPTSBroadcastThread.h"
#include "Multiplexer/UDP/UDPTSBroadcast.h"

#include "Multiplexer/Dektec/DektecTSBroadcastThread.h"
#include "Multiplexer/Dektec/DektecTSBroadcast.h"

#include "DynamicFileDataProviderGlobalConfig.h"

#include <boost/archive/tmpdir.hpp>
#include "Poco/File.h"
#include "Poco/NumberParser.h"
#include <sys/types.h>
#include <sys/stat.h>

#include "Test.h"




using namespace std;
/*参数说明：
 *目的IP
 * 目的端口
 * 监听IP
 * 监听端口
 * 配置文件目录
 * 调试文件名称
 */





const string LogName="主应用";
InfoDTV_Common_Log::InfoDTVLogger Logger;
void LogInfo(string aMsg)
{
	Logger.information(aMsg);
}




int main(int argc, char* argv[]) {

	Logger.setName("主应用");
	LogInfo("InfoDTV 广播服务器，CopyRight @2008 By Victor Ho");
	cout<<"Build Date:"<<__DATE__<<"  "<<__TIME__<<endl;
//	TESTPocoPath();
//	return 0;

	string MainConfigFile="InfoDTVMuxServer.config";
//	MainConfigFile=MainConfigFile+".config";
	if(argc==1)
	{

		Poco::File ConfigFile(MainConfigFile);
		if(ConfigFile.exists())
		{
			GlobalConfigObjectPtr GCO(new GlobalConfigObject());
			GCO->LoadConfig(MainConfigFile,true);
			if(GCO->IsDVBMode)
			{
				LogInfo("Dektec输出模式!!");
				MultiplexerCore_V1::DektecTSBroadcast FDektecTSBroadcast(GCO);
				FDektecTSBroadcast.main(argc,argv);
			}
			else
			{
				if(GCO->IsDebugMode)
				{
					LogInfo("调试输出模式!!");
					//				MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO->TargetIP,GCO->TargetIPPort,GCO->HostIP,GCO->HostIPPort,GCO->DBPath,GCO->DebugTSFile);
					MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO);
					FUDPTSBroadcast.main(argc,argv);
				}
				else
				{
					LogInfo("正式服务模式!!");
					GCO->DebugTSFile="";
					//				MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO->TargetIP,GCO->TargetIPPort,GCO->HostIP,GCO->HostIPPort,GCO->DBPath);
					MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO);
					FUDPTSBroadcast.main(argc,argv);
				}
			}

		}
		else
		{
			cout<<"参数出错!!或配置文件不存在"<<endl;
			cout<<"参数说明：\r\n目的IP 目的端口  监听IP 监听端口  配置文件目录 数据临时目录 [ 调试文件名称]"<<endl;
			cout<<"\r\n    或者：[XML配置文件] 缺省为 exec.config"<<endl;
			return -1;
		}
	}
	/*
	else
	if(argc==2)
	{
		MainConfigFile=argv[1];
		Poco::File ConfigFile(MainConfigFile);
		if(ConfigFile.exists())
		{
			GlobalConfigObjectPtr GCO(new GlobalConfigObject());
			GCO->LoadConfig(MainConfigFile,true);
			if(GCO->IsDebugMode)
			{
				LogInfo("调试输出模式!!");
				MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO->TargetIP,GCO->TargetIPPort,GCO->HostIP,GCO->HostIPPort,GCO->DBPath,GCO->DebugTSFile);
				FUDPTSBroadcast.main(argc,argv);
			}
			else
			{
				LogInfo("正式服务模式!!");
				MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO->TargetIP,GCO->TargetIPPort,GCO->HostIP,GCO->HostIPPort,GCO->DBPath);
				FUDPTSBroadcast.main(argc,argv);
			}
		}
		else
		{
			cout<<"参数出错!!或配置文件不存在"<<endl;
			cout<<"参数说明：\r\n目的IP 目的端口  监听IP 监听端口  配置文件目录 数据临时目录 [ 调试文件名称]"<<endl;
			cout<<"\r\n    或者：[XML配置文件] 缺省为 exec.config"<<endl;
			return -1;
		}
	}
	*/
	else
	if(argc==7)
	{
		GlobalConfigObjectPtr GCO(new GlobalConfigObject());
		GCO->IsDebugMode=false;
		GCO->TargetIP=argv[1];

		unsigned int TmpInt=0;
		if(Poco::NumberParser::tryParseUnsigned(string(argv[2]),TmpInt))
		{
			GCO->TargetIPPort=TmpInt;
		}

		GCO->HostIP=argv[3];

		if(Poco::NumberParser::tryParseUnsigned(string(argv[4]),TmpInt))
		{
			GCO->HostIPPort=TmpInt;
		}

		GCO->DBPath=argv[5];
		GCO->DynamicFileTmpPath=argv[6];
		GCO->DebugTSFile="";
		GCO->SaveToFile(MainConfigFile);
		LogInfo("正式服务模式!!");
//		MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO->TargetIP,GCO->TargetIPPort,GCO->HostIP,GCO->HostIPPort,GCO->DBPath);
		MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO);
		FUDPTSBroadcast.main(argc,argv);
	}
	else
	if(argc==8)
	{
		GlobalConfigObjectPtr GCO(new GlobalConfigObject());
		GCO->IsDebugMode=true;
		GCO->TargetIP=argv[1];

		unsigned int TmpInt=0;
		if(Poco::NumberParser::tryParseUnsigned(string(argv[2]),TmpInt))
		{
			GCO->TargetIPPort=TmpInt;
		}

		GCO->HostIP=argv[3];

		if(Poco::NumberParser::tryParseUnsigned(string(argv[4]),TmpInt))
		{
			GCO->HostIPPort=TmpInt;
		}

		GCO->DBPath=argv[5];
		GCO->DynamicFileTmpPath=argv[6];

		GCO->DebugTSFile=argv[7];
		GCO->SaveToFile(MainConfigFile);
		LogInfo("调试输出模式!!");
//		MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO->TargetIP,GCO->TargetIPPort,GCO->HostIP,GCO->HostIPPort,GCO->DBPath,GCO->DebugTSFile);
		MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(GCO);
		FUDPTSBroadcast.main(argc,argv);
	}
	else
	{
		cout<<"参数出错!!"<<endl;
		cout<<"参数说明：\r\n目的IP 目的端口  监听IP 监听端口  配置文件目录 数据临时目录 [ 调试文件名称]"<<endl;
		cout<<"\r\n    或者：[XML配置文件] 缺省为 exec.config"<<endl;
		return -1;
	}

	LogInfo("正常退出！");

	//MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast("127.0.0.1",8500,"127.0.0.1",10001,"/home/Victor/InfoDTVTest/");
	//MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast("172.16.26.18",8500,"127.0.0.1",10001,"/home/Victor/InfoDTVTest/");
	//MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast("224.0.0.1",8500,"172.16.26.15",10001,"/home/Victor/InfoDTVTest/");
	//FUDPTSBroadcast.main(argc,argv);
	return 0;
}
