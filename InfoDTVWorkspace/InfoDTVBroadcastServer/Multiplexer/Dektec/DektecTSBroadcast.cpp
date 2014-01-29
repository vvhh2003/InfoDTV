/*
 * DektecTSBroadcast.cpp
 *
 *  Created on: 2009-4-10
 *      Author: victor
 */

#include "DektecTSBroadcast.h"
#include "Poco/File.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"

using namespace MultiplexerCore_V1;



void DektecTSBroadcast::CreatPath(string aConfigPath)
{
	Poco::File FF(aConfigPath);
	if(!FF.exists())
	{
		FF.createDirectories();
	}
}



void DektecTSBroadcast::InitICEAdapter()
{
	//				FCommunicator=Ice::Util::initialize();

	string TmpStr=GetICEEndpointConfig();
	FICEAdapter=communicator()->createObjectAdapterWithEndpoints("DektecBroadcastServer", GetICEEndpointConfig());
	Log("Dectec服务器控制监听器初始化中..");
	Ice::Identity ID=communicator()->stringToIdentity("DektecBroadcastServer");
	//	FICEAdapter->add(FBroadcastControllerPtr.get() , ID);
	FICEAdapter->add(FBroadcastControllerPtr, ID);
	FICEAdapter->activate();
	Log("Dectec服务器控制监听器成功初始化！");
}



string DektecTSBroadcast::GetICEEndpointConfig()
{
	string TmpStr="default -p "+Poco::NumberFormatter::format(FHostPort) +" -h "+FHostIP;

	Log("网络配置："+TmpStr);
	return TmpStr;
}



void DektecTSBroadcast::interruptCallback(int aInt)
{
    Log(string(appName())+"receive signal");
//	cout << appName()<<"receive signal"<<endl;

}


DektecTSBroadcast::~DektecTSBroadcast()
{
	if(FIsBroadcasting)
	StopBroadcast();
}



DektecTSBroadcast::DektecTSBroadcast(bool aIsQAMMode,int aDeviceType,long aQAMFreqHz,string aHostIP,int aHostPort,string aDBPath):FLogger(),
FIsBroadcasting(false),FIsQAMMode(aIsQAMMode),FDeviceType(aDeviceType),FQAMFreqHz(aQAMFreqHz),FBitRate(0),FHostIP(aHostIP),FHostPort(aHostPort),
FBroadcastControllerPtr(new InfoDTV::Broadcast::BroadcastControllerI(this)),FDBPath(aDBPath),FTSDataPrepThreadPtr(),FDektecTSBroadcastThreadPtr(),
FCurrentDBFile(""),FDebugTSFile("")
{
	FLogger.setName("DektecTSBroadcast");
	Log("初始化");
	Poco::File DBPath(FDBPath);
	if(!DBPath.exists())
	CreatPath(FDBPath);
}

DektecTSBroadcast::DektecTSBroadcast(GlobalConfigObjectPtr aGCO):
	FLogger(),FIsBroadcasting(false),FIsQAMMode(aGCO->IsQAMMode),FDeviceType(aGCO->DeviceType),FQAMFreqHz(aGCO->QAMFreqHz),FBitRate(0),FHostIP(aGCO->HostIP),FHostPort(aGCO->HostIPPort),
FBroadcastControllerPtr(new InfoDTV::Broadcast::BroadcastControllerI(this)),FDBPath(aGCO->DBPath),FTSDataPrepThreadPtr(),FDektecTSBroadcastThreadPtr(),
FCurrentDBFile(""),FDebugTSFile(aGCO->DebugTSFile),FGlobalConfigObjPtr(aGCO)
{
	FLogger.setName("DektecTSBroadcast");
	Log("初始化");
//	fs::path DBPath(FDBPath);
//	if(!fs::exists(DBPath))
//	CreatPath(DBPath);
	Poco::File DBPath(FDBPath);
	if(!DBPath.exists())
	CreatPath(FDBPath);
}




DektecTSBroadcast::DektecTSBroadcast(bool aIsQAMMode,int aDeviceType,long aQAMFreqHz,string aHostIP,int aHostPort,string aDBPath,string aDebugTSFile):
	FLogger(),FIsBroadcasting(false),FIsQAMMode(aIsQAMMode),FDeviceType(aDeviceType),FQAMFreqHz(aQAMFreqHz),FBitRate(0),FHostIP(aHostIP),FHostPort(aHostPort),
FBroadcastControllerPtr(new InfoDTV::Broadcast::BroadcastControllerI(this)),FDBPath(aDBPath),FTSDataPrepThreadPtr(),FDektecTSBroadcastThreadPtr(),
FCurrentDBFile(""),FDebugTSFile(aDebugTSFile)
{
	FLogger.setName("DektecTSBroadcast");
	Log("初始化");
//	fs::path DBPath(FDBPath);
//	if(!fs::exists(DBPath))
//	CreatPath(DBPath);
	Poco::File DBPath(FDBPath);
	if(!DBPath.exists())
	CreatPath(FDBPath);
}



int DektecTSBroadcast::run(int, char*[])
{

	Log("开始启动服务器");
	InitICEAdapter();
	FMuxConfigIdentity=communicator()->stringToIdentity("DektecBroadcastServerRuntimeConfiger");
	Log("控制服务初始化完成！");
	Log("服务器启动完成");
	if(FGlobalConfigObjPtr->DefaultBitRate>0)
	{
		Log("发现默认启动配置");
		Poco::File ConfigFile(FDBPath+FGlobalConfigObjPtr->DefaultDBName);
		if(ConfigFile.exists())
		{
			Log("正在启动默认配置");
			StartBroadcast(FGlobalConfigObjPtr->DefaultDBName,FGlobalConfigObjPtr->DefaultBitRate);
			Log("默认配置启动成功！");
		}
		else
		{
			Log("默认启动配置不存在！");
		}
	}
	communicator()->waitForShutdown();
	StopBroadcast();
	return EXIT_SUCCESS;
}


bool DektecTSBroadcast::StartBroadcast(::std::string aConfigDBName,long aOutputBitRate)
{
	Log("正在启动播出！");
	FBitRate=aOutputBitRate;

	Poco::StringTokenizer ST(aConfigDBName,"?",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);

	FCurrentDBFile=ST[0];
//	if(ST.count()==3)
//	{
//		FTargetIP=ST[1];
//		unsigned int TmpTargetPort=FTargetPort;
//		if(Poco::NumberParser::tryParseUnsigned(ST[2],TmpTargetPort))
//		{
//			FTargetPort=TmpTargetPort;
//		}
//
//	}
//	Log("正在启动播出--目标IP："+FTargetIP+" 目标端口："+Poco::NumberFormatter::format(FTargetPort));

	FCircularBufferPtr.reset(new CircularBuffer("Dektec Broadcast",5,TS_DataBuffer_Length));

	if(!FCircularBufferPtr)
	    return false;
	Log("正在启动播出--缓冲初始化完成！");
	FSoftMultiplexerPtr=SoftMultiplexer::Create(FBitRate);
	if(!FSoftMultiplexerPtr)
		return false;
	Log("正在启动播出--复用器初始化完成！");

	Ice::ObjectPtr TmpMuxRuntimeConfigPtr(new MuxRuntimeConfigI(FSoftMultiplexerPtr,FDBPath+FCurrentDBFile,FDBPath+FCurrentDBFile+"_backup",FGlobalConfigObjPtr));
	Log("正在启动播出--运行时配置初始化完成！");
	(dynamic_cast<MuxRuntimeConfigI*>(&*TmpMuxRuntimeConfigPtr))->InitConfig();
	Log("正在启动播出--运行时配置 复用配置完成！");

//	FTSDataPrepThreadPtr=new TSDataPrepThread(FSoftMultiplexerPtr,FCircularBufferPtr);
	FTSDataPrepThreadPtr.reset(new TSDataPrepThread(FSoftMultiplexerPtr,FCircularBufferPtr));
	if(!FTSDataPrepThreadPtr)
	    return false;
	Log("正在启动播出--数据准备线程初始化完成！");


	FDektecTSBroadcastThreadPtr.reset(new DektecTSBroadcastThread(FDeviceType,FQAMFreqHz,FBitRate,FCircularBufferPtr));


	if(!FDektecTSBroadcastThreadPtr)
	return false;
	Log("正在启动播出--数据播出线程初始化完成！");

	FICEAdapter->add(TmpMuxRuntimeConfigPtr,FMuxConfigIdentity);
	Log("正在启动播出--Adapter初始化完成！");
	Log("复用器通讯装置设置完成！");
	FTSDataPrepThreadPtr->Start();
	sleep(2);
	Log("数据准备线程对象启动完成！");
	FDektecTSBroadcastThreadPtr->Start();
	Log("播出线程对象启动完成！");
	FIsBroadcasting=true;
	return true;
}



bool DektecTSBroadcast::StopBroadcast()
{
	if(!FIsBroadcasting)
	return true;
	Log("播出停止过程中...");
	if(FDektecTSBroadcastThreadPtr)
	{
		FDektecTSBroadcastThreadPtr->Stop();
//		if (FCircularBufferPtr->IsBufferReaderBlocked())
//				    {
//					Log("停止中..正在解决播出线程缓冲锁...");
//					long BufferLength=FCircularBufferPtr->getBufferLength();
//
//					//					RawBufferPtr TmpBuffer(new unsigned char[BufferLength]);
//					RawBufferPtr TmpBuffer((unsigned char *)std::malloc(BufferLength),&free);
//					std::memset((void *)TmpBuffer.get(), 0, BufferLength);
//					FCircularBufferPtr->setBuffer(BufferLength, TmpBuffer);
//					Log("停止中..播出线程缓冲锁已解决...");
//				    }
		FDektecTSBroadcastThreadPtr.reset();
		Log("数据播出停止完成...");
	}
	if(FTSDataPrepThreadPtr)
	{
		FTSDataPrepThreadPtr->Stop();
//		if (FCircularBufferPtr->IsBufferWriterBlocked())
//		{
//			//					RawBufferPtr TmpBuffer(new unsigned char[TS_DataBuffer_Length]);
//			Log("停止中..正在解决数据准备缓冲锁...");
//			FCircularBufferPtr->getBuffer();
//			Log("停止中..数据准备缓冲锁已解决...");
//		}
		FTSDataPrepThreadPtr.reset();
		Log("数据准备停止完成...");
	}


	FICEAdapter->remove(FMuxConfigIdentity);

	Log("远程复用控制停止完成...");

	Log("重置播出完成...");

	Log("重置数据准备完成...");

	Log("重置运行时配置完成...");

	FSoftMultiplexerPtr->Clear();
	Log("复用器通道清除完成...");

	FSoftMultiplexerPtr.reset();
	Log("重置复用器完成...");

	FCircularBufferPtr.reset();
	Log("重置缓冲完成...");

	FIsBroadcasting=false;
	Log("播出停止完成！");
	return true;
}

bool DektecTSBroadcast::RestartBroadcast()
{
	if(FIsBroadcasting)
		StopBroadcast();
	StartBroadcast(FCurrentDBFile,FBitRate);
	return true;
}


bool DektecTSBroadcast::IsInBroadcasting()
{
	return FIsBroadcasting;
}

long DektecTSBroadcast::GetBroadcastBitRate()
{
	return FBitRate;
}

BroadcastCore::StringSeq DektecTSBroadcast::GetRuntimeConfigDatabaseNameList()
{
	StringSeq Result;
	fs::path fpath(FDBPath);
	fs::directory_iterator beg_iter(fpath);
	fs::directory_iterator end_iter;
	for (; beg_iter != end_iter; ++beg_iter)
	{
		if (fs::is_directory(*beg_iter))
		{
			continue;
		}
		else
		{
			Result.push_back(beg_iter->leaf());
		}
	}
	return Result;
}


string DektecTSBroadcast::GetBroadcastConfigDBName()
{
	return FCurrentDBFile;
}

int DektecTSBroadcast::DeleteRuntimeConfigDB(::std::string aRuntimeConfigDB)
{
	string ConfigFile=FDBPath +aRuntimeConfigDB;
	if(FCurrentDBFile==ConfigFile)
	{
		return -1;
	}
	else
	{
		return fs::remove( FCurrentDBFile );
	}
}

void DektecTSBroadcast::StartServer()
{
	Log("开始启动服务器");
	InitICEAdapter();
	Log("控制服务初始化完成！");
	Log("服务器启动完成");

	communicator()->waitForShutdown();

}


void DektecTSBroadcast::StopServer()
{

	StopBroadcast();
	communicator()->shutdown();
	communicator()->destroy();
	Log("服务器停止完成");
}


