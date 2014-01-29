/*
 * SimpleTSFileDataProvider.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "SimpleTSFileDataProvider.h"

#include "../Common/TSPacketStruct.h"

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include <fstream>


using namespace std;
namespace fs = boost::filesystem;
using namespace Multiplexer_DataProvider_V1;



SimpleTSFileConfigObject::SimpleTSFileConfigObject()
{
	TSFileName="";
	IsLockFile=false;
	IsFixCounter=false;
}
void SimpleTSFileConfigObject::xml_serialize(eternity::xmlstring_archive &xml)
{
	if (xml.is_loading())
	{
		xml.read("TSFileName", TSFileName, 0);
		xml.read("IsLockFile", IsLockFile, 0);
		xml.read("IsFixCounter", IsFixCounter, 0);
	}
	else
	{
		xml.write("TSFileName", TSFileName);
		xml.write("IsLockFile", IsLockFile);
		xml.write("IsFixCounter", IsFixCounter);
	}

}

void SimpleTSFileConfigObject::LoadConfig(string StringConfig)
{
	try
	{
		eternity::xmlstring_archive aa;
		aa.open(StringConfig,eternity::archive::load);
		this->xml_serialize(aa);
	}
	catch(eternity::exception *e)
	{
		cout<<"SimpleTSFileConfigObject Load Config Error:"<<e->what()<<endl;
	}
}
string SimpleTSFileConfigObject::SaveToString()
{
	eternity::xmlstring_archive aa;
	aa.open("", eternity::archive::store);
	this->xml_serialize(aa);
	aa.close();
	return aa.Result();
}

void SimpleTSFileDataProvider::Log(string ALogStr)
{
	FLogger.information(ALogStr);
}
SimpleTSFileDataProvider::SimpleTSFileDataProvider(SimpleTSFileConfigObjectPtr aCO) :
	FConfigObject(aCO), FIsActived(false), FFilePos(0), FFileLength(0),FLogger()
	{
	FLogger.setName("SimpleTSFileDataProvider");
	}

SimpleTSFileDataProvider::~SimpleTSFileDataProvider()
{
	DeActive();
	Log("<MEM>已释放");
}
void SimpleTSFileDataProvider::Active()
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
			Log("SimpleTSFileDataProvider : FileOpen Error");
			FIsActived=false;
			FFileLength=0;
			FFilePos=0;
		}

	}

}


void SimpleTSFileDataProvider::ConfigChanged(string aNewConfig)
{
	Log("SimpleTSFileDataProvider ConfigChanging!");
	SimpleTSFileConfigObject TT;
	TT.LoadConfig(aNewConfig);
	fs::path FileName(TT.TSFileName);
	if (!fs::exists(FileName))
	{
		Log("SimpleTSFileDataProvider Error:File Not Exists!");
		return;
	}
	DeActive();
	FConfigObject->LoadConfig(aNewConfig);
	Active();
}

void SimpleTSFileDataProvider::DeActive()
{
	FIsActived=false;
	FFileLength =0;
	FFilePos=0;
	if (FFileStream.is_open())
		FFileStream.close();
}

string SimpleTSFileDataProvider::GetProviderInfo()
{
	string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
	TmpState+="File Length:"+boost::lexical_cast<std::string>(FFileLength)+"\r\n";
	return TmpState;
}

string SimpleTSFileDataProvider::GetProviderStateInfo()
{
	string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
	TmpState+="File Length:"+boost::lexical_cast<std::string>(FFileLength)+"\r\n";
	return TmpState;
}

TSPacketStructPtr SimpleTSFileDataProvider::GetTSPacket()
{
	if (!FIsActived||!FFileStream.is_open())
		return TSPacketStruct::NewNullTSPacket();

	TSPacketStructPtr TmpTSPacketPtr(new TSPacketStruct);
	if(!FFileStream.read((char *)TmpTSPacketPtr->TSData,188))
	{
		FFileStream.close();
		FFileStream.open(FConfigObject->TSFileName.c_str(), ios::binary|ios::in);
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
		//Log("SimpleTSFileDataProvider",boost::lexical_cast<std::string>(TmpTSPacketPtr->GetPID())+":"+boost::lexical_cast<std::string>(TmpTSPacketPtr->Header.continuity_counter));
	}
	return TmpTSPacketPtr;
}

void SimpleTSFileDataProvider::Reset()
{
	DeActive();
	Active();
}

bool SimpleTSFileDataProvider::getIsActived()
{
	return FIsActived;
}

string SimpleTSFileDataProvider::getTypeID()
{
	return SIMPLE_FILE_DATAPROVIDER_GUID;
}

string SimpleTSFileDataProvider::GetCurrentConfig()
{
	if (FConfigObject)
		return FConfigObject->SaveToString();
	else
		return "";
}
