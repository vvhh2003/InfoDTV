/*
 * TSFilterOutFileDataProvider.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "TSFilterOutFileDataProvider.h"


#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
namespace fs = boost::filesystem;
using namespace Multiplexer_DataProvider_V1;


TSFilterOutFileConfigObject::TSFilterOutFileConfigObject()
{

	TSFileName="";
	IsLockFile=false;
	IsFixCounter=false;
}

void TSFilterOutFileConfigObject::xml_serialize(xmlstring_archive &xml)
{
	if (xml.is_loading())
	{
		xml.read("TSFileName", TSFileName, 0);
		xml.read("IsLockFile", IsLockFile, 0);
		xml.read("IsFixCounter", IsFixCounter, 0);
		xml_read(association<primitives,primitives>(), PIDMaps, PIDMaps.begin(),xml, "PIDMaps");
	}
	else
	{
		xml.write("TSFileName", TSFileName);
		xml.write("IsLockFile", IsLockFile);
		xml.write("IsFixCounter", IsFixCounter);
		xml_write(association<primitives,primitives>(),PIDMaps.begin(),PIDMaps.end(),xml,"PIDMaps");
	}

}

void TSFilterOutFileConfigObject::AddPidmap(unsigned short aOrgPID,unsigned short aOutPID)
{
	PIDMaps.insert(map<int ,int >::value_type(aOrgPID,aOutPID));
}

void TSFilterOutFileConfigObject::LoadConfig(string StringConfig)
{
	try
	{
		eternity::xmlstring_archive aa;
		aa.open(StringConfig,eternity::archive::load);
		this->xml_serialize(aa);
	}
	catch(eternity::exception *e)
	{
		cout<<"TSFilterOutFileConfigObject Load Config Error:"<<e->what()<<endl;
	}
}

string TSFilterOutFileConfigObject::SaveToString()
{
	eternity::xmlstring_archive aa;
	aa.open("", eternity::archive::store);
	this->xml_serialize(aa);
	aa.close();
	return aa.Result();
}




void TSFilterOutFileDataProvider::Log(string aMsg)
{
    FLogger.information(aMsg);
}

TSFilterOutFileDataProvider::TSFilterOutFileDataProvider(TSFilterOutFileConfigObjectPtr aCO) :
	FConfigObject(aCO), FIsActived(false), FFilePos(0), FFileLength(0),FLogger()
	{
	FLogger.setName("TSFilterOutFileConfigObject");
	Log("<MEM>创建");
	}

TSFilterOutFileDataProvider::~TSFilterOutFileDataProvider()
{
	DeActive();
	Log("<MEM>已释放");
}
void TSFilterOutFileDataProvider::Active()
{
	if (FConfigObject)
	{
		try
		{
			FFileStream.open(FConfigObject->TSFileName.c_str(), ios::binary|ios::in);
			FFileStream.seekg(0, ios::end);
			FFileLength = FFileStream.tellg();
			FFileStream.seekg(0, ios::beg);
			FFilePos=0;
			FIsActived=true;
		}
		catch(...)
		{
			Log("TSFilterOutFileDataProvider : FileOpen Error");
			FIsActived=false;
			FFileLength=0;
			FFilePos=0;
		}

	}

}
void TSFilterOutFileDataProvider::ConfigChanged(string aNewConfig)
{
	TSFilterOutFileConfigObject TT;
	TT.LoadConfig(aNewConfig);
	fs::path FileName(TT.TSFileName);
	if (!fs::exists(FileName))
	{
		Log("TSFilterOutFileDataProvider Error:File Not Exists!");
		return;
	}
	DeActive();
	FConfigObject->LoadConfig(aNewConfig);
	Active();
}

void TSFilterOutFileDataProvider::DeActive()
{
	FIsActived=false;
	FFileLength =0;
	FFilePos=0;
	if (FFileStream.is_open())
		FFileStream.close();
}

string TSFilterOutFileDataProvider::GetProviderInfo()
{
	string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
	TmpState+="File Length:"+boost::lexical_cast<std::string>(FFileLength)+"\r\n";
	return TmpState;
}

string TSFilterOutFileDataProvider::GetProviderStateInfo()
{
	string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
	TmpState+="File Length:"+boost::lexical_cast<std::string>(FFileLength)+"\r\n";
	return TmpState;
}

TSPacketStructPtr TSFilterOutFileDataProvider::GetTSPacket()
{
	if (!FIsActived||!FFileStream.is_open())
		return TSPacketStruct::NewNullTSPacket();

	TSPacketStructPtr TmpTSPacketPtr(new TSPacketStruct);
	if(!FFileStream.read((char *)TmpTSPacketPtr->TSData,188))
	{
		FFileStream.close();
		FFileStream.open(FConfigObject->TSFileName.c_str(), ios::binary|ios::in);
	}

	if(FConfigObject->PIDMaps.count(TmpTSPacketPtr->GetPID())==0)
	{
		return TSPacketStruct::NewNullTSPacket();
	}
	else
	{
		unsigned short NewPID=(unsigned short)FConfigObject->PIDMaps[TmpTSPacketPtr->GetPID()];
		TmpTSPacketPtr->SetPID(NewPID);
	}

	if(FConfigObject->IsFixCounter)
	{
		int PID=TmpTSPacketPtr->GetPID();
		if(PID==0x1fff)
			return TmpTSPacketPtr;
		if(FPIDMaps.count(PID)==0)
		{
			FPIDMaps[PID]=TSLibrary::DefaultDataCounterPtr(new TSLibrary::DefaultDataCounter);
		}
		TmpTSPacketPtr->FixCount(FPIDMaps[PID]->GetNextCounter());
	}

	if(FConfigObject->IsFixCounter)
	{
		int PID=TmpTSPacketPtr->GetPID();
		if(PID==0x1fff)
			return TmpTSPacketPtr;
		if(FPIDMaps.count(PID)==0)
		{
			FPIDMaps[PID]=TSLibrary::DefaultDataCounterPtr(new TSLibrary::DefaultDataCounter);
		}
		TmpTSPacketPtr->FixCount(FPIDMaps[PID]->GetNextCounter());
	}
	return TmpTSPacketPtr;
}

void TSFilterOutFileDataProvider::Reset()
{
	DeActive();
	Active();
}

bool TSFilterOutFileDataProvider::getIsActived()
{
	return FIsActived;
}

string TSFilterOutFileDataProvider::getTypeID()
{
	return TS_FILTER_OUT_FILE_DATAPROVIDER_GUID;
}

string TSFilterOutFileDataProvider::GetCurrentConfig()
{
	if (FConfigObject)
		return FConfigObject->SaveToString();
	else
		return "";
}
