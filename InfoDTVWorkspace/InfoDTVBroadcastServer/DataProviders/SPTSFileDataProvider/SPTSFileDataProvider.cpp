/*
 * SPTSFileDataProvider.cpp
 *
 *  Created on: 2009-3-19
 *      Author: victor
 */
#include "SPTSFileDataProvider.h"
#include "VBR2CBRProcessor.h"
#include "PCRPTSProcessor.h"
#include "Poco/File.h"
#include "../SimpleTSFileDataProvider.h"
namespace Multiplexer_DataProvider_V1
{

	SPTSFileConfigObject::SPTSFileConfigObject()
	{
		TSFileName="";
		PcrPID=401;
		CBRPIDBitRate=6000000;
		IsVBRToCBR=false;
		IsMapPID=true;
		IsFixPCR_PTS=true;
	}
	void SPTSFileConfigObject::xml_serialize(eternity::xmlstring_archive &xml)
	{
		int TmpPID=PcrPID;
		long long int TmpCBRPIDBitRate=CBRPIDBitRate;
		if (xml.is_loading())
		{
			xml.read("TSFileName", TSFileName, 0);
			xml.read("PcrPID", TmpPID, 0);
			PcrPID=TmpPID;
			xml.read("CBRPIDBitRate", TmpCBRPIDBitRate, 0);
			xml.read("IsVBRToCBR", IsVBRToCBR, 0);
			xml.read("IsFixPCR_PTS", IsFixPCR_PTS, 0);
			xml.read("IsMapPID", IsMapPID, 0);
			xml_read(association<primitives,primitives>(), PIDMaps, PIDMaps.begin(),xml, "PIDMaps");
		}
		else
		{
			xml.write("TSFileName", TSFileName);
			xml.write("PcrPID", PcrPID);
			xml.write("CBRPIDBitRate", CBRPIDBitRate);
			xml.write("IsVBRToCBR", IsVBRToCBR);
			xml.write("IsFixPCR_PTS", IsFixPCR_PTS);
			xml.write("IsMapPID", IsMapPID);
			xml_write(association<primitives,primitives>(),PIDMaps.begin(),PIDMaps.end(),xml,"PIDMaps");
		}

	}

	void SPTSFileConfigObject::LoadConfig(string StringConfig)
	{
		try
		{
			cout<<"1"<<endl;
			eternity::xmlstring_archive aa;
			cout<<"2"<<endl;
			aa.open(StringConfig,eternity::archive::load);
			cout<<"3"<<endl;
			this->xml_serialize(aa);
			cout<<"4"<<endl;
		}
//		catch(eternity::exception *e)
//		{
//			cout<<"SPTSFileConfigObject Load Config Error:"<<e->what()<<endl;
//		}
		catch(...)
		{
			cout<<"SPTSFileConfigObject Load Config Error"<<endl;
		}
	}
	string SPTSFileConfigObject::SaveToString()
	{
		eternity::xmlstring_archive aa;
		aa.open("", eternity::archive::store);
		this->xml_serialize(aa);
		aa.close();
		return aa.Result();
	}

	void SPTSFileDataProvider::Log(string aMsg)
	{
		FLogger.information(aMsg);
	}

	SPTSFileDataProvider::SPTSFileDataProvider(SPTSFileConfigObjectPtr aCO,string aGlobalSPTSFileDB):
		FConfigObject(aCO),FSimpleTSFileDataProviderPtr(),
		FVBR2CRBProcessorPtr(),FPCRPTSProcessorPtr(),
		FIsActived(false),FLogger(),FNullPacketPtr(TSPacketStruct::NewNullTSPacket()),
		FGlobalSPTSFileDB(aGlobalSPTSFileDB)
	{
		FLogger.setName("SPTSFileDataProvider");

	}

	SPTSFileDataProvider::~SPTSFileDataProvider()
	{
		FLogger.information("<MEM>已释放");
	}

	void SPTSFileDataProvider::Active()
	{
		SimpleTSFileConfigObjectPtr TmpSimpleTSFileConfigObjectPtr(new SimpleTSFileConfigObject);
		TmpSimpleTSFileConfigObjectPtr->TSFileName = FGlobalSPTSFileDB+FConfigObject->TSFileName;
		TmpSimpleTSFileConfigObjectPtr->IsLockFile = false;
		TmpSimpleTSFileConfigObjectPtr->IsFixCounter = false;
		FSimpleTSFileDataProviderPtr.reset(new SimpleTSFileDataProvider(TmpSimpleTSFileConfigObjectPtr));
		FSimpleTSFileDataProviderPtr->Active();
		if (FConfigObject->IsVBRToCBR)
		{
			FVBR2CRBProcessorPtr.reset(new VBR2CBRProcessor(FSimpleTSFileDataProviderPtr, FConfigObject->PcrPID, FConfigObject->CBRPIDBitRate));
			FVBR2CRBProcessorPtr->Active();
		}
		if (FConfigObject->IsFixPCR_PTS)
		{
			if (FVBR2CRBProcessorPtr)
				FPCRPTSProcessorPtr.reset(new PCRPTSProcessor(FVBR2CRBProcessorPtr));
			else
				FPCRPTSProcessorPtr.reset(new PCRPTSProcessor(FSimpleTSFileDataProviderPtr));
			FPCRPTSProcessorPtr->Active();
		}
		FIsActived=true;
	}

	void SPTSFileDataProvider::ConfigChanged(string aNewConfig)
	{
			SPTSFileConfigObject TT;
			TT.LoadConfig(aNewConfig);
			Poco::File FileName(FGlobalSPTSFileDB+TT.TSFileName);

			if (!FileName.exists())
			{
				Log("SPTSFileDataProvider Error:File Not Exists!");
				return;
			}
			DeActive();
			FConfigObject->PIDMaps.clear();
			FConfigObject->LoadConfig(aNewConfig);
			Active();
	}

	void SPTSFileDataProvider::DeActive()
	{
		if (FConfigObject->IsVBRToCBR)
		{
			if(FVBR2CRBProcessorPtr)
				FVBR2CRBProcessorPtr->DeActive();
			FVBR2CRBProcessorPtr.reset();
		}
		if (FConfigObject->IsFixPCR_PTS)
		{
			if(FPCRPTSProcessorPtr)
				FPCRPTSProcessorPtr->DeActive();
			FPCRPTSProcessorPtr.reset();
		}
		FSimpleTSFileDataProviderPtr->DeActive();
		FSimpleTSFileDataProviderPtr.reset();
		FIsActived=false;
	}

	string SPTSFileDataProvider::GetProviderInfo()
	{
		string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
		return TmpState;
	}
	string SPTSFileDataProvider::GetProviderStateInfo()
	{
		string TmpState="FileName:"+FConfigObject->TSFileName+"\r\n";
				return TmpState;
	}

	TSPacketStructPtr SPTSFileDataProvider::GetTSPacket()
	{

		if (!FIsActived)
			return TSPacketStruct::NewNullTSPacket();
		TSPacketStructPtr TmpTSPacketPtr=FNullPacketPtr;
		if (FConfigObject->IsFixPCR_PTS)
		{
			if(FPCRPTSProcessorPtr)
				TmpTSPacketPtr=FPCRPTSProcessorPtr->GetTSPacket();
		}
		else if (FConfigObject->IsVBRToCBR)
		{
			if(FVBR2CRBProcessorPtr)
			TmpTSPacketPtr=FVBR2CRBProcessorPtr->GetTSPacket();
		}
		else
		{
			if(FSimpleTSFileDataProviderPtr)
				TmpTSPacketPtr=FSimpleTSFileDataProviderPtr->GetTSPacket();
		}

		if(FConfigObject->IsMapPID)
		{

			unsigned short PID=TmpTSPacketPtr->GetPID();
			if(FConfigObject->PIDMaps.count(PID)>0)
			{
				TmpTSPacketPtr->SetPID(FConfigObject->PIDMaps[PID]);
			}
			else
			{
				TmpTSPacketPtr=FNullPacketPtr;
			}
		}
		return TmpTSPacketPtr;

	}

	void SPTSFileDataProvider::Reset()
	{
		DeActive();
		Active();
	}

	bool SPTSFileDataProvider::getIsActived()
	{
		return FIsActived;
	}

	string SPTSFileDataProvider::getTypeID()
	{
		return SPTS_FILE_DATAPROVIDER_GUID;
	}

	string SPTSFileDataProvider::GetCurrentConfig()
	{
		if (FConfigObject)
			return FConfigObject->SaveToString();
		else
			return "";
	}

}


