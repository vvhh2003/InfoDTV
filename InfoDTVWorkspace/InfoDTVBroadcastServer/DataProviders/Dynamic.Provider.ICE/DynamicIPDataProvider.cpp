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

#include "DynamicIPDataProvider.h"

using namespace std;
using namespace Multiplexer_DataProvider_V1;
namespace fs = boost::filesystem;

void DynamicIPDataProviderConfigObject::xml_serialize(xmlstring_archive &xml)
{
    if (xml.is_loading())
	{
	    xml.read("ChannelName", ChannelName, 0);
	    xml.read("ChannelIPPort", ChannelIPPort, 0);
	    xml.read("ChannelIP", ChannelIP, 0);
//	    xml.read("ProtectedTSFileName", ProtectedTSFileName, 0);
	}
    else
	{
	    xml.write("ChannelName", ChannelName);
	    xml.write("ChannelIPPort", ChannelIPPort);
	    xml.write("ChannelIP", ChannelIP);
//	    xml.write("ProtectedTSFileName", ProtectedTSFileName);

	}

}

void DynamicIPDataProviderConfigObject::LoadConfig(string StringConfig)
{
    try
	{
	    eternity::xmlstring_archive aa;
	    aa.open(StringConfig, eternity::archive::load);
	    this->xml_serialize(aa);
	}
    catch (eternity::exception *e)
	{
	    cout << "DynamicIPDataProvierConfigObject Load Config Error:" << e->what() << endl;
	}
}

string DynamicIPDataProviderConfigObject::SaveToString()
{
    eternity::xmlstring_archive aa;
    aa.open("", eternity::archive::store);
    this->xml_serialize(aa);
    aa.close();
    return aa.Result();
}

void DynamicIPDataProvider::SetInitProtectStream()
{
    //将文件载入到保护内存
}

void DynamicIPDataProvider::SetReciver()
{
    FRBufferReciver.reset();
    FRBufferReciver.reset(new ICEBufferReciver(FBufManager, FConfigObject->ChannelName, FConfigObject->ChannelIP, FConfigObject->ChannelIPPort));
    FRBufferReciver->Start();
}

void DynamicIPDataProvider::ResetReciver()
{
    if (FRBufferReciver)
	{
	    FRBufferReciver->Stop();
	}

}

DynamicIPDataProvider::DynamicIPDataProvider(DynamicIPDataProviderConfigObjectPtr aConfigObject) :
    FConfigObject(aConfigObject), FBufManager(new BufferManager()), FBufPosition(0), FLogger()
{
    FLogger.setName("DynamicIPDataProvier");
    Log("<MEM>构造！");
}
DynamicIPDataProvider::~DynamicIPDataProvider()
{
    ResetReciver();
    Log("<MEM>已释放！");
}

void DynamicIPDataProvider::Active()
{
    FTSDataBuffer.reset();
    SetInitProtectStream();
    ResetReciver();
    SetReciver();
    //BuildTSData();
    Log("Active！");
    FIsActived = true;
}

void DynamicIPDataProvider::DeActive()
{
    FIsActived = false;
    ResetReciver();
    Log("DeActive！");
}

TSPacketStructPtr DynamicIPDataProvider::GetTSPacket()
{
    if (!FIsActived)
	{
	    return TSPacketStruct::NewNullTSPacket();
	}
    TSPacketStructPtr FTmpTsPacket(new TSPacketStruct);
    //Byte[] TmpBuf = new Byte[188];
    int TmpDebugCount = 0;
    try
	{
	    if (!FTSDataBuffer)
		{
		    FTSDataBuffer = FBufManager->BeginRead();
		    FBufPosition = 0;
		    return TSPacketStruct::NewNullTSPacket();
		}

	    if ((FBufPosition + 188) > FBufManager->GetBufferLength())
		{
		    FBufPosition = 0;
		    Log("------------->缓冲结束！Event Set");
		    //Event Here;
		    FBufManager->EndRead();
		    FTSDataBuffer.reset();
		    return TSPacketStruct::NewNullTSPacket();
		}

	    TmpDebugCount = 2;
	    //Array.Copy(FTSDataBuffer, FBufPosition, TmpBuf, 0, 188);
	    //Buffer.BlockCopy(FTSDataBuffer, FBufPosition, TmpBuf,0,188);

	    void * Buf = FTSDataBuffer.get() + FBufPosition;
	    std::memcpy((void *) FTmpTsPacket.get(), Buf, 188);

	    TmpDebugCount = 3;
	    FBufPosition += 188;

	    //}
	}
    catch (...)
	{
	    Log("DynamicIPDataProvider.GetTSPacket " + boost::lexical_cast<std::string>(TmpDebugCount));

	    DeActive();
	}
    return FTmpTsPacket;
}

void DynamicIPDataProvider::ConfigChanged(string aNewConfig)
{
    try
	{
	    Log("开始重新配置！：\r\n" + aNewConfig);
	    DynamicIPDataProviderConfigObject TT;
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

string DynamicIPDataProvider::GetProviderInfo()
{
    //				string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
    //				TmpState+="File Length:"+boost::lexical_cast<std::string>(FFileLength)+"\r\n";
    //				return TmpState;
    return "Config too Complex to write please ask Victor :(";
}

string DynamicIPDataProvider::GetProviderStateInfo()
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

string DynamicIPDataProvider::getTypeID()
{
    return DYNAMIC_IP_DATAPROVIDER_GUID;
}

bool DynamicIPDataProvider::getIsActived()
{
    return FIsActived;
}

void DynamicIPDataProvider::Reset()
{
    DeActive();
    Active();
}

string DynamicIPDataProvider::GetCurrentConfig()
{
    if (FConfigObject)
	return FConfigObject->SaveToString();
    else
	return "";
}

