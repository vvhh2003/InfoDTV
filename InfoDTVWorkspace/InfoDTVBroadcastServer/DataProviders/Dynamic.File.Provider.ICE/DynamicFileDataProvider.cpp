/*
 * DynamicIPDataProvier.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <map>
#include <iostream>
#include <fstream>
#include "Poco/File.h"
#include "DynamicFileDataProvider.h"
#include "DynamicFileDataProviderGlobalConfig.h"

using namespace std;
using namespace Multiplexer_DataProvider_V1;
namespace fs = boost::filesystem;

void DynamicFileDataProviderConfigObject::xml_serialize(xmlstring_archive &xml)
{
	if (xml.is_loading())
	{
		xml.read("ChannelName", ChannelName, 0);
		xml.read("ChannelIPPort", ChannelIPPort, 0);
		xml.read("ChannelIP", ChannelIP, 0);
		xml.read("IsLogInfo", IsLogInfo, 0);
	}
	else
	{
		xml.write("ChannelName", ChannelName);
		xml.write("ChannelIPPort", ChannelIPPort);
		xml.write("ChannelIP", ChannelIP);
		xml.write("IsLogInfo", IsLogInfo);
	}

}

void DynamicFileDataProviderConfigObject::LoadConfig(string StringConfig)
{
	try
	{
		eternity::xmlstring_archive aa;
		aa.open(StringConfig, eternity::archive::load);
		this->xml_serialize(aa);
	}
	catch (eternity::exception *e)
	{
		cout << "DynamicFileDataProviderConfigObject Load Config Error:" << e->what() << endl;
	}
}

string DynamicFileDataProviderConfigObject::SaveToString()
{
	eternity::xmlstring_archive aa;
	aa.open("", eternity::archive::store);
	this->xml_serialize(aa);
	aa.close();
	return aa.Result();
}

void DynamicFileDataProvider::SetInitProtectStream()
{
	//将文件载入到保护内存
}

void DynamicFileDataProvider::SetReciver()
{
	FRBufferReciver.reset();
	FRBufferReciver.reset(new DynamicICEBufferReciver(FFileManager, FConfigObject->ChannelName,
			FConfigObject->ChannelIP,
			FConfigObject->ChannelIPPort,
			FConfigObject->IsLogInfo,
			FGCOPtr->DynamicFileTmpPath));
	FRBufferReciver->Start();
}

void DynamicFileDataProvider::ResetReciver()
{
	if (FRBufferReciver)
	{
		FRBufferReciver->Stop();
		FRBufferReciver.reset();
	}

}

DynamicFileDataProvider::DynamicFileDataProvider(DynamicFileDataProviderConfigObjectPtr aConfigObject,GlobalConfigObjectPtr aGCOPtr):
	FConfigObject(aConfigObject), FFileManager(new FileManager(aConfigObject->IsLogInfo)),FFileStream(), FBufPosition(0), FTmpTsPacket(new TSPacketStruct),
	FLogger(),FGCOPtr(aGCOPtr)
	{
	FLogger.setName("DynamicFileDataProvier");
	Log("<MEM>构造！");
	}
DynamicFileDataProvider::~DynamicFileDataProvider()
{
	ResetReciver();
	Log("<MEM>已释放！");
}

void DynamicFileDataProvider::Active()
{

	SetInitProtectStream();
	ResetReciver();
	SetReciver();
	//BuildTSData();
	Log("Active！");
	FIsActived = true;
}

void DynamicFileDataProvider::DeActive()
{
	FIsActived = false;
	ResetReciver();
	Log("DeActive！");
}

TSPacketStructPtr DynamicFileDataProvider::GetTSPacket()
{
	if (!FIsActived)
	{
		return TSPacketStruct::NewNullTSPacket();
	}
	//Byte[] TmpBuf = new Byte[188];
	int TmpDebugCount = 0;
	try
	{
		if (!FFileStream.is_open())
		{
			string FileName=FFileManager->BeginRead();
			if(FileName!="")
			{
				Poco::File FF(FileName);
				if(!FF.exists())
				{
					LogError(FileName+"文件不存在!");
					return TSPacketStruct::NewNullTSPacket();
				}

				try
				{
					FFileStream.open(FileName.c_str());
					Log(FileName+"文件成功打开！");
					FFileStream.seekg(0, ios::end);
					unsigned int FileLength=FFileStream.tellg();
					FFileStream.seekg(0, ios::beg);
					if(FileLength<188*1024)
					{
						//TODO:ReadMode
					}
				}
				catch(std::exception &ex)
				{
					string Msg=ex.what();
					LogError("打开文件错误："+Msg);
					CloseFile(FileName);
					return TSPacketStruct::NewNullTSPacket();
				}
				FBufPosition = 0;
			}
			return TSPacketStruct::NewNullTSPacket();
		}



//		if(FFileStream.eof())
//		{
//			FFileManager->EndRead();
//			FFileStream.close();
//			Log("------------->文件关闭！");
//			return TSPacketStruct::NewNullTSPacket();
//		}


		TmpDebugCount = 2;
		if(!FFileStream.read((char *)FTmpTsPacket->TSData,188))
		{

			CloseFile("");
			return TSPacketStruct::NewNullTSPacket();
		}
//		Log("文件读取成功");
//		void * Buf = FTSDataBuffer.get() + FBufPosition;
//		FFileStream.read(FTmpTsPacket.get(),188);
		TmpDebugCount = 3;
		FBufPosition += 188;

		//}
	}
	catch (...)
	{
		LogError("DynamicFileDataProvider.GetTSPacket " + boost::lexical_cast<std::string>(TmpDebugCount));

		DeActive();
	}
	return FTmpTsPacket;
}

void DynamicFileDataProvider::CloseFile(const string aFileName)
{
	if(FFileStream.is_open())
		FFileStream.close();
	FFileManager->EndRead();
	Log(FConfigObject->ChannelName+":"+aFileName+"文件成功关闭！");
}

void DynamicFileDataProvider::ConfigChanged(string aNewConfig)
{
	try
	{
		Log("开始重新配置！：\r\n" + aNewConfig);
		DynamicFileDataProviderConfigObject TT;
		TT.LoadConfig(aNewConfig);
		DeActive();
		FConfigObject->LoadConfig(aNewConfig);
		Active();
	}
	catch (...)
	{
		Log("重新配置出现异常！");
		return;
	}
	return;
}

string DynamicFileDataProvider::GetProviderInfo()
{
	//				string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
	//				TmpState+="File Length:"+boost::lexical_cast<std::string>(FFileLength)+"\r\n";
	//				return TmpState;
	return "Config too Complex to write please ask Victor :(";
}

string DynamicFileDataProvider::GetProviderStateInfo()
{
	if (FIsActived)
	{
		return "Runing";
	}
	else
	{
		return "Deactived";
	}
}

string DynamicFileDataProvider::getTypeID()
{
	return DYNAMIC_FILE_DATAPROVIDER_GUID;
}

bool DynamicFileDataProvider::getIsActived()
{
	return FIsActived;
}

void DynamicFileDataProvider::Reset()
{
	DeActive();
	Active();
}

string DynamicFileDataProvider::GetCurrentConfig()
{
	if (FConfigObject)
		return FConfigObject->SaveToString();
	else
		return "";
}

