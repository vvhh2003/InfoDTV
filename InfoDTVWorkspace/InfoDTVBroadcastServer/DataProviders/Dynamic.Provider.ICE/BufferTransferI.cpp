/*
 * BufferTransferI.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */
#include "BufferTransferI.h"
#include <boost/lexical_cast.hpp>
using namespace Multiplexer_DataProvider_V1;

BufferManager::BufferManager():FHasNewBuffer(false),FBackupBufferLength(0),FBufferLength(0)
{

}

uint BufferManager::GetBackupBufferLength()
{
	return FBackupBufferLength;
}

uint BufferManager::GetBufferLength()
{
	return FBufferLength;
}

RawBufferPtr BufferManager::BeginRead()
{
	EndRead();
	return FBuffer;
}

void BufferManager::EndRead()
{
	if (FHasNewBuffer)
	{
		IceUtil::Mutex::Lock lock(FMutex);
		FBuffer=FBackupBuffer;
		FBufferLength=FBackupBufferLength;
		FBackupBuffer.reset();//Add On 5.8
		FHasNewBuffer = false;
	}
}

void BufferManager::SetNewBuffer(RawBufferPtr aBuffer,int aBufferLength)
{
	IceUtil::Mutex::Lock lock(FMutex);
	FBackupBuffer= aBuffer;
	FBackupBufferLength=aBufferLength;
	FHasNewBuffer = true;
}


using namespace InfoDTV::Multiplexer::Dynamic::Provider;


BufferTransferI::BufferTransferI(Multiplexer_DataProvider_V1::BufferManagerPtr aBufferManager,
		string aServiceName) :
			FBufferManager(aBufferManager), FServiceName(aServiceName),FSessionID(""),
			FTotalRecvLength(0),FTotalToBeRecvedLength(0),FLogger()
			{
			    FLogger.setName(aServiceName+"-接收器");
			}

BufferTransferI::~BufferTransferI()
{

}
void BufferTransferI::Login(const Ice::Current & _Current)
{
	return;
}

void BufferTransferI::SendBuffer(const string& aServiceName, ::Ice::Int aBufferLength,
		const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq,
		const ::Ice::Current& _Current)
{

}

void BufferTransferI::SendBuffer2(const string& aServiceName, const string& aBufferGuid,
		::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength,
		const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&aSeq,
		const ::Ice::Current& _Current)
{
    if (aServiceName != FServiceName)
	{
	    FLogger.warn("动态接收投递名称不符！->需要"+FServiceName+"，实际接收的为："+aServiceName);
	    return;
	}

    if (FSessionID != aBufferGuid)
	{
	    Log(aServiceName+":动态接收开始！->总数据长度：{1}"+boost::lexical_cast<string>(aTotalBufferLength));
	    FSessionID = aBufferGuid;
	    FTotalToBeRecvedLength=aTotalBufferLength;
	    FTotalRecvLength=0;
	    FBuffer.reset((unsigned char *)std::malloc(FTotalToBeRecvedLength),&free);

	}

    Log(aServiceName+":动态接收！->数据索引："+boost::lexical_cast<string>(aSendIndex));

    if (aCurrentBufferLength !=(int) aSeq.size())
	{
	    FLogger.error(FServiceName+"{0}:动态接收错误！->数据长度描述不一致,实际为:"+boost::lexical_cast<string>(aSeq.size()));
	    return;
	}

    Log(aServiceName+":动态接收！->发送的数据长度："+boost::lexical_cast<string>(aCurrentBufferLength));

    if (FTotalToBeRecvedLength >= FTotalRecvLength + aCurrentBufferLength)
	{
//	    Buffer.BlockCopy(aSeq, 0, TBuffer, TotalRecvLength, aCurrentBufferLength);
	     void * TmpPtr=FBuffer.get()+FTotalRecvLength;
	    std::memcpy(TmpPtr,aSeq.data(),aCurrentBufferLength);
	    Log(aServiceName+":动态接收！->成功数据长度："+boost::lexical_cast<string>(aCurrentBufferLength));
	    FTotalRecvLength += aCurrentBufferLength;
	}


    if(FTotalRecvLength==FTotalToBeRecvedLength)
	{
	    FBufferManager->SetNewBuffer(FBuffer,FTotalToBeRecvedLength);
	    FBuffer.reset();
	    Log(FServiceName+"动态接收完成！->实际数据长度："+ boost::lexical_cast<string>(aTotalBufferLength));
	}
}
