//============================================================================
// Name        : InfoDTVBroadcastServer.cpp
// Author      : Victor
// Version     :
// Copyright   : CopyRight @2008 By Victor
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../Common/Log/Log.h"
#include <boost/lexical_cast.hpp>
#include "../Multiplexer/UDP/UDPTSBroadcastThread.h"
#include "../Multiplexer/UDP/UDPTSBroadcast.h"

#include "../Common/TS.Library/DVB-PSI/PMTTable.h"
#include "../Common/TS.Library/DVB-PSI/PATTable.h"

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

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

void TestXMLSerialization()
{
	TSLibrary::DVB::PSI::PATTable PAT(1200);
	PAT.AddProgram(120,1200);
	PAT.AddProgram(120,1200);

}

int main(int argc, char* argv[]) {
	Logger.setName("主应用");
	LogInfo("InfoDTV 广播服务器，CopyRight @2008 By Victor Ho");

	if(argc==6)
	{
		string TargetIP(argv[1]);
		string TmpStr(argv[2]);
		int TargetIPPort=boost::lexical_cast<int>(TmpStr);
		string HostIP(argv[3]);
		TmpStr=argv[4];
		int HostIPPort=boost::lexical_cast<int>(TmpStr);
		string DBPath(argv[5]);
		LogInfo("正式服务模式!!");
		MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(TargetIP,TargetIPPort,HostIP,HostIPPort,DBPath);
		FUDPTSBroadcast.main(argc,argv);
	}
	else
	if(argc==7)
	{
		string TargetIP(argv[1]);
		string TmpStr(argv[2]);
		int TargetIPPort=boost::lexical_cast<int>(TmpStr);
		string HostIP(argv[3]);
		TmpStr=argv[4];
		int HostIPPort=boost::lexical_cast<int>(TmpStr);
		string DBPath(argv[5]);
		string DebugTSFile(argv[6]);
		LogInfo("调试输出模式!!");
		MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast(TargetIP,TargetIPPort,HostIP,HostIPPort,DBPath,DebugTSFile);
		FUDPTSBroadcast.main(argc,argv);
	}
	else
	{
		cout<<"参数出错!!"<<endl;
		cout<<"参数说明：\r\n目的IP 目的端口  监听IP 监听端口  配置文件目录 [ 调试文件名称]"<<endl;
		return -1;
	}

	LogInfo("正常退出！");

	//MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast("127.0.0.1",8500,"127.0.0.1",10001,"/home/Victor/InfoDTVTest/");
	//MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast("172.16.26.18",8500,"127.0.0.1",10001,"/home/Victor/InfoDTVTest/");
	//MultiplexerCore_V1::UDPTSBroadcast FUDPTSBroadcast("224.0.0.1",8500,"172.16.26.15",10001,"/home/Victor/InfoDTVTest/");
	//FUDPTSBroadcast.main(argc,argv);
	return 0;
}
