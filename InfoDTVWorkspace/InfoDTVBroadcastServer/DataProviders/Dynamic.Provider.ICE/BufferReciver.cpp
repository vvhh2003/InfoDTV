/*
 * BufferReciver.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "BufferReciver.h"
using namespace Multiplexer_DataProvider_V1;
void ICEBufferReciver::InitCommunicator()
{
	try
	{
		Ice::StringSeq args;
		args.push_back(GetICECommunicatorConfig());
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

string ICEBufferReciver::GetICECommunicatorConfig()
{
	return "BufferTransfer.Endpoints=default -p "+boost::lexical_cast<std::string>(FIPPort)+" -h "+ FHostIP;
}

string ICEBufferReciver::GetICEEndpointConfig()
{
	return "default -p "+boost::lexical_cast<std::string>(FIPPort)+" -h "+ FHostIP;
}

ICEBufferReciver::ICEBufferReciver(BufferManagerPtr aBufManager,string aChannelName,string aChannelIP,int aChannelIPPort):
FBufManager(aBufManager),FHostIP(aChannelIP),FIPPort(aChannelIPPort),FServiceName(aChannelName),FLogger()
{
    FLogger.setName("ICEBufferReciver");
}
void ICEBufferReciver::InitICEAdapter()
{
	try
	{
	    Log("1");
	    string TmpConfig=GetICEEndpointConfig();
	    FICEAdapter=FCommunicator->createObjectAdapterWithEndpoints("BufferTransfer", TmpConfig);
	    Log("2");
	    FICEAdapter->add(new InfoDTV::Multiplexer::Dynamic::Provider::BufferTransferI(FBufManager, FServiceName),FCommunicator->stringToIdentity("BufferTransfer"));
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
void ICEBufferReciver::Start()
{
	InitCommunicator();
	InitICEAdapter();
}

void ICEBufferReciver::Stop()
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
