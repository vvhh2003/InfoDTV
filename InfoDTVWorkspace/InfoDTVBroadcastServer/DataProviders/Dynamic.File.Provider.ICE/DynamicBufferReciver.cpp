/*
 * BufferReciver.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "DynamicBufferReciver.h"
using namespace Multiplexer_DataProvider_V1;
void DynamicICEBufferReciver::InitCommunicator()
{
	try
	{
		Ice::StringSeq args;
		string Tmp=GetICECommunicatorConfig();
		args.push_back(Tmp);
//		args.push_back("");
//		args.push_back("");
//		FCommunicator = Ice::initialize(args);
		FCommunicator = Ice::initialize();
		Log(FServiceName+":通讯器成功初始化！" );
	}
	catch (const Ice::Exception & e)
	{
		Log(string(e.what()));
	}

	catch (...)
	{

		Log(FServiceName+":通讯器初始化失败！");
		// Console.Error.WriteLine(ex);
	}
}

string DynamicICEBufferReciver::GetICECommunicatorConfig()
{
	return "DynamicBufferTransfer.Endpoints=default -p "+boost::lexical_cast<std::string>(FIPPort)+" -h "+ FHostIP;
}

string DynamicICEBufferReciver::GetICEEndpointConfig()
{
	return "default -p "+boost::lexical_cast<std::string>(FIPPort)+" -h "+ FHostIP;
}

DynamicICEBufferReciver::DynamicICEBufferReciver(FileManagerPtr aFileManager,string aChannelName,string aChannelIP,
		int aChannelIPPort,bool aIsLogInfo,string aDynamicFileDataProvider_GlobalDBPath):
FFileManager(aFileManager),FHostIP(aChannelIP),FIPPort(aChannelIPPort),FServiceName(aChannelName),
FIsLogInfo(aIsLogInfo),FLogger(),FDynamicFileDataProvider_GlobalDBPath(aDynamicFileDataProvider_GlobalDBPath)
{
    FLogger.setName("DynamicICEBufferReciver");
}
void DynamicICEBufferReciver::InitICEAdapter()
{
	try
	{
	    Log("1");
	    string TmpConfig=GetICEEndpointConfig();
	    FICEAdapter=FCommunicator->createObjectAdapterWithEndpoints("DynamicBufferTransfer", TmpConfig);
	    Log("2");
	    FICEAdapter->add(new InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferI(FFileManager, FServiceName,FIsLogInfo,FDynamicFileDataProvider_GlobalDBPath),FCommunicator->stringToIdentity("DynamicBufferTransfer"));
	    Log("3");
	    FICEAdapter->activate();
	    Log(FServiceName+":监听对象成功初始化！");
	}
	catch (const Ice::Exception & e)
	{
		Log(FServiceName+string(e.what()));
	}
	catch (...)
	{
		Log(FServiceName+":对象适配器初始化失败！");

	}
}
void DynamicICEBufferReciver::Start()
{
	InitCommunicator();
	InitICEAdapter();
}

void DynamicICEBufferReciver::Stop()
{
	Log(FServiceName+"正在停止");

	if (FICEAdapter)
	{
		try
		{
		    FICEAdapter->deactivate();
		    FICEAdapter->destroy();
		}
		catch(Ice::Exception ex)
		{
			Log(FServiceName+"停止适配器出错！"+string(ex.what()));
		}
		//					FICEAdapter = null;
	    }

	    if (FCommunicator)
	    {
		    try
		    {
			    FCommunicator->shutdown();
//			    if (FCommunicator)
//			    FCommunicator->waitForShutdown();
			    FCommunicator->destroy();

		    }
		    catch (Ice::Exception ex)
		    {
			    Log(FServiceName+"停止通讯器出错！"+string(ex.what()));
		    }
		    //					FCommunicator = null;
	    }
	    Log(FServiceName+":动态接收器已经停止!");
    }
