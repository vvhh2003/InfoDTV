/*
 * DynamicBufferTransferI.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */
#include "DynamicBufferTransferI.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "Poco/File.h"
//#include "Poco/Path.h"
#include "DynamicFileDataProviderGlobalConfig.h"
using namespace Multiplexer_DataProvider_V1;

FileManager::FileManager(bool aIsLogInfo):FLogger(),FHasNewFile(false),FIsInRead(false),
FCurrentFileName(""),FNewFileName(""),FIsLogInfo(aIsLogInfo)
{

}

FileManager::~FileManager()
{
	if(FIsInRead)
	{
		EndRead();
	}
	if(FCurrentFileName!="")
	{
		Poco::File FF(FCurrentFileName);
		try
		{
			if(FF.exists())
			{
				FF.remove(true);
				Log(FCurrentFileName+"已经删除！");
			}
		}
		catch(std::exception &ex)
		{
			string Msg=ex.what();
			LogError("FileManager Delete Error:"+Msg);
		}
	}
}

void FileManager::SetLoggerName(string aName)
{
	FLogger.setName(aName);
}

string FileManager::BeginRead()
{
	EndRead();
	FIsInRead=true;
//	Log("BeginRead:"+FCurrentFileName);
	return FCurrentFileName;
}

void FileManager::EndRead()
{
	if (FHasNewFile)
	{

		Poco::FastMutex::ScopedLock lock(FMutex);
//		Log("EndRead:"+FCurrentFileName);
		string OldFileName=FCurrentFileName;
		FCurrentFileName=FNewFileName;
		FNewFileName="";
		FHasNewFile = false;
		if(OldFileName!="")
		{
			Poco::File FF(OldFileName);
			try
			{
				if(FF.exists()&&FF.isFile())
					FF.remove(true);
				Log(OldFileName+"已经删除！");
			}
			catch(std::exception &ex)
			{
				string Msg=ex.what();
				LogError("FileManager Delete Error:"+OldFileName+":"+Msg);
			}
		}
	}
	FIsInRead=false;
}

void FileManager::SetNewFile(const string aNewFileName)
{
	if(aNewFileName!=FCurrentFileName)
	{

		Poco::FastMutex::ScopedLock lock(FMutex);
//		Log("SetNewFile:"+aNewFileName);
		if(FNewFileName!=aNewFileName)
		{
			if(FNewFileName=="")
			{
				FNewFileName= aNewFileName;
				FHasNewFile = true;
				return ;
			}
			string OldFileName=FNewFileName;
			FNewFileName= aNewFileName;
			FHasNewFile = true;
			if(OldFileName!="")
			{
				Poco::File FF(OldFileName);
				try
				{
					if(FF.exists()&&FF.isFile())
						FF.remove(true);
					Log(OldFileName+"已经删除！");
				}
				catch(std::exception &ex)
				{
					string Msg=ex.what();
					LogError("FileManager Delete Error:"+OldFileName+":"+Msg);
				}
			}
		}

	}
}


using namespace InfoDTV::Multiplexer::Dynamic::Provider;


DynamicBufferTransferI::DynamicBufferTransferI(Multiplexer_DataProvider_V1::FileManagerPtr aFileManager,
		string aServiceName,bool aIsLogInfo,string aDynamicFileDataProvider_GlobalDBPath) :
			FFileManager(aFileManager), FServiceName(aServiceName),FSessionID(""),FIsLogInfo(aIsLogInfo),
			FTotalRecvLength(0),FTotalToBeRecvedLength(0),FLogger(),FDynamicFileDataProvider_GlobalDBPath(aDynamicFileDataProvider_GlobalDBPath),FFileStream()
			{
	FLogger.setName(aServiceName+"-Dynamic接收器");
	FFileManager->SetLoggerName(aServiceName+"-Dynamic接收器");
	ClearDynamicFileDataProviderDBPath(FDynamicFileDataProvider_GlobalDBPath,FServiceName);

			}

DynamicBufferTransferI::~DynamicBufferTransferI()
{

}

//string GetFileName(string aFilePath,string aGuid)
//{
//	return aFilePath+aGuid+".TS";
//}

void DynamicBufferTransferI::SendBuffer(const string& aServiceName, const string& aBufferGuid,
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
		Log(aServiceName+":新数据接收开始！->总数据长度："+boost::lexical_cast<string>(aTotalBufferLength)
				+"  数据索引："+boost::lexical_cast<string>(aSendIndex));

		if(FFileStream.is_open())
		{

			Poco::File FF(GetDynamicFileDataProviderFileName(FDynamicFileDataProvider_GlobalDBPath,FServiceName,FSessionID));
			FFileStream.close();
			if(FF.exists())
			{
				FF.remove(true);
			}
			Log(aServiceName+":原文件并未生成完成，已删除！");
		}
		FSessionID = aBufferGuid;
		FTotalToBeRecvedLength=aTotalBufferLength;
		FTotalRecvLength=0;
		try
		{
			CreateDynamicFileDataProviderDBPath(FDynamicFileDataProvider_GlobalDBPath,FServiceName);
			FFileStream.open((GetDynamicFileDataProviderFileName(FDynamicFileDataProvider_GlobalDBPath,FServiceName,FSessionID)).c_str(),std::ios_base::out);
		}
		catch(std::exception &ex)
		{
			LogError(aServiceName+" Error!"+ex.what());
		}
	}



	if (aCurrentBufferLength !=(int) aSeq.size())
	{
		LogError(FServiceName+":动态接收错误！->数据长度描述不一致,实际为:"+boost::lexical_cast<string>(aSeq.size()));
		return;
	}

	Log(aServiceName+":动态接收！->发送的数据长度："+boost::lexical_cast<string>(aCurrentBufferLength)
			+"  数据索引："+boost::lexical_cast<string>(aSendIndex));

	if (FTotalToBeRecvedLength >= FTotalRecvLength + aCurrentBufferLength)
	{
		//	    Buffer.BlockCopy(aSeq, 0, TBuffer, TotalRecvLength, aCurrentBufferLength);
		if(FFileStream.is_open())
		{
			try
			{
				FFileStream.write((const char *)(aSeq.data()),aCurrentBufferLength);
				FFileStream.flush();
			}
			catch(std::exception &ex)
			{
				string Msg=ex.what();
				Msg=" Error!"+Msg;
				LogError(aServiceName+Msg);
			}
		}
		else
		{
			LogError(aServiceName+"Error!Stream is Close!");
		}
		Log(aServiceName+":动态接收！->成功数据长度："+boost::lexical_cast<string>(aCurrentBufferLength)
				+"  数据索引："+boost::lexical_cast<string>(aSendIndex));
		FTotalRecvLength += aCurrentBufferLength;
	}


	if(FTotalRecvLength==FTotalToBeRecvedLength)
	{
		FFileStream.close();
		FFileManager->SetNewFile((GetDynamicFileDataProviderFileName(FDynamicFileDataProvider_GlobalDBPath,FServiceName,FSessionID)).c_str());
		Log(FServiceName+"动态接收完成！->实际数据长度："+ boost::lexical_cast<string>(aTotalBufferLength));
	}
}
