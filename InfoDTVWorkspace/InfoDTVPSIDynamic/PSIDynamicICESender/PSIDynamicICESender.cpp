/*
 * PSIDynamicICESender.cpp
 *
 *  Created on: 2009-3-3
 *      Author: victor
 */

#include "PSIDynamicICESender.h"
#include "DynamicBufferTransferI.h"
#include "Poco/NumberFormatter.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/UUID.h"

string GetICECommunicatorConfig(string aHostIP,unsigned int aHostIPPort)
{
	return "DynamicBufferTransfer.Endpoints=default -p "+Poco::NumberFormatter::format(aHostIPPort)+" -h "+ aHostIP;
}

string GetICEObjectConfig(string aHostIP,unsigned int aHostIPPort)
{
	return "DynamicBufferTransfer:default -p "+Poco::NumberFormatter::format(aHostIPPort)+" -h "+aHostIP;
}

PSIDynamicICESender::PSIDynamicICESender(string aHostIP,unsigned int aHostPort,string aServiceName):
	FHostIP(aHostIP),FHostPort(aHostPort),FServiceName(aServiceName)
{

}

PSIDynamicICESender::~PSIDynamicICESender()
{
	if(FCommunicatorPtr)
		FCommunicatorPtr->destroy();
}

bool PSIDynamicICESender::Connect()
{
	try
	{
		if(!FCommunicatorPtr)
		{
			Ice::StringSeq args;
			string Tmp=GetICECommunicatorConfig(FHostIP,FHostPort);
			args.push_back(Tmp);
			args.push_back("Ice.ACM.Client=0");
			args.push_back("Ice.MessageSizeMax=30000");
			//		FCommunicator = Ice::initialize(args);
			FCommunicatorPtr = Ice::initialize();
			cout<<FServiceName+":通讯器成功初始化！" <<std::endl;
		}
		Ice::ObjectPrx base=FCommunicatorPtr->stringToProxy(GetICEObjectConfig(FHostIP,FHostPort));
		FSendBufferPrx=InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPrx::checkedCast(base);
		if(!FSendBufferPrx)
		{
			if(FCommunicatorPtr)
			{
				FCommunicatorPtr->destroy();
				FCommunicatorPtr=NULL;
			}
			return false;
		}
	}
	catch (const Ice::Exception & e)
	{
		cout<<string(e.what())<<std::endl;
		if(FCommunicatorPtr)
		{
			FCommunicatorPtr->destroy();
			FCommunicatorPtr=NULL;
		}
		return false;
	}
	catch (...)
	{

		cout<<FServiceName+":Connect：通讯器初始化失败！"<<std::endl;
		// Console.Error.WriteLine(ex);
		if(FCommunicatorPtr)
		{
			FCommunicatorPtr->destroy();
			FCommunicatorPtr=NULL;
		}
		return false;
	}


	return true;

}

void PSIDynamicICESender::SendAllBuffer(RawBufferPtr aBuffer,unsigned int aBufferSize)
{

	if(!aBuffer||(aBufferSize==0))
	{
		cout<<FServiceName+"：SendAllBuffer:无效缓冲区！"<<std::endl;
		return;
	}
	if((!FCommunicatorPtr)||(!FSendBufferPrx))
	{
		if(!Connect())
		{
			cout<<FServiceName+"：SendAllBuffer:对象连接失败！"<<std::endl;
			return ;
		}
	}
	Poco::UUIDGenerator UG;
	Poco::UUID uid=UG.createOne();
	string FUUIDStr=uid.toString();
	const unsigned int SendBufferBlockLength = 188*300;


	if(aBufferSize<=SendBufferBlockLength)
	{
		try
		{
			Ice::ByteSeq ByteSeqBlockBuffer(aBufferSize,0);
			std::memcpy(ByteSeqBlockBuffer.data(),aBuffer.get(),aBufferSize);
			FSendBufferPrx->SendBuffer(FServiceName,FUUIDStr,0,aBufferSize,aBufferSize,ByteSeqBlockBuffer);
		}
		catch (const Ice::Exception & e)
		{
			cout<<FServiceName+":SendAllBuffer:异常1！"<<std::endl;
			cout<<string(e.what())<<std::endl;
				if(FCommunicatorPtr)
				{
					FCommunicatorPtr->destroy();
					FCommunicatorPtr=NULL;
				}
			return ;
		}
		catch (...)
		{

			cout<<FServiceName+":SendAllBuffer:异常1-1！";
			// Console.Error.WriteLine(ex);
			if(FCommunicatorPtr)
			{
				FCommunicatorPtr->destroy();
				FCommunicatorPtr=NULL;
			}
			return ;
		}
		return ;
	}

	unsigned int SendIndex=0;
	unsigned int TotalCopyLength=0;
	unsigned char * TmpBufferPtr=aBuffer.get();
	try
	{
		while(TotalCopyLength<aBufferSize)
		{
			int CopyLength = 0;
			if (TotalCopyLength + SendBufferBlockLength <= aBufferSize)
			{
				CopyLength = SendBufferBlockLength;
			}
			else
			{
				CopyLength = aBufferSize - TotalCopyLength;
			}

			Ice::ByteSeq ByteSeqBlockBuffer(CopyLength,0);

			std::memcpy(ByteSeqBlockBuffer.data(),TmpBufferPtr,CopyLength);

			FSendBufferPrx->SendBuffer(FServiceName,FUUIDStr,SendIndex,aBufferSize,CopyLength,ByteSeqBlockBuffer);
			TotalCopyLength += CopyLength;
			TmpBufferPtr+=CopyLength;
			SendIndex++;



		}
	}
	catch (const Ice::Exception & e)
	{
		cout<<FServiceName+":SendAllBuffer:异常2！"<<std::endl;
		cout<<string(e.what())<<std::endl;
		if(FCommunicatorPtr)
			FCommunicatorPtr->destroy();
	}
	catch (...)
	{

		cout<<FServiceName+":SendAllBuffer:异常2！"<<std::endl;
		// Console.Error.WriteLine(ex);
		if(FCommunicatorPtr)
			FCommunicatorPtr->destroy();
	}

}
