/*
 * ICERuntimeConfiger.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include"ICERuntimeConfiger.h"
#include "../../../DataProviders/SimpleTSFileDataProviderFactory.h"
#include "../../../DataProviders/TSFilterOutFileDataProviderFactory.h"
#include "../../../DataProviders/Dynamic.Provider.ICE/DynamicIPDataProviderFactory.h"
#include "../../../DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProviderFactory.h"

using namespace InfoDTV::Multiplexer::RuntimeConfig;

void StorageChannelInfo::xml_serialize(eternity::xmlstring_archive &xml)
{
	if (xml.is_loading())
	{
		xml.read("ChannelName", ChannelName, 0);
		xml.read("OutputBitRate", OutputBitRate, 0);
		xml.read("IsFixOutputCounter", IsFixOutputCounter, 0);
		xml.read("DataProviderTypeID", DataProviderTypeID, 0);
		xml.read("DataProviderConfig", DataProviderConfig, 0);
		DataProviderConfig=eternity::base64_decode(DataProviderConfig);
	}
	else
	{
		xml.write("ChannelName", ChannelName);
		xml.write("OutputBitRate", OutputBitRate);
		xml.write("IsFixOutputCounter", IsFixOutputCounter);
		xml.write("DataProviderTypeID", DataProviderTypeID);
		xml.write("DataProviderConfig", eternity::base64_encode((unsigned char * )DataProviderConfig.c_str(),DataProviderConfig.size()));
	}

}
void StorageChannelInfo::xml_serialize(eternity::xml_archive &xml)
{
	if (xml.is_loading())
	{
		xml.read("ChannelName", ChannelName, 0);
		xml.read("OutputBitRate", OutputBitRate, 0);
		xml.read("IsFixOutputCounter", IsFixOutputCounter, 0);
		xml.read("DataProviderTypeID", DataProviderTypeID, 0);
		xml.read("DataProviderConfig", DataProviderConfig, 0);
		DataProviderConfig=eternity::base64_decode(DataProviderConfig);
	}
	else
	{
		xml.write("ChannelName", ChannelName);
		xml.write("OutputBitRate",OutputBitRate);
		xml.write("IsFixOutputCounter", IsFixOutputCounter);
		xml.write("DataProviderTypeID", DataProviderTypeID);
		xml.write("DataProviderConfig", eternity::base64_encode((unsigned char * )DataProviderConfig.c_str(),DataProviderConfig.size()));
		//xml.write("DataProviderConfig", DataProviderConfig);
	}

}


void MuxRuntimeConfigI::InitLoadProviderFactorys()
{
	Log("初始化全部Provider工厂中..");
	ITSDataProviderFactoryPtr
	IDPF(new Multiplexer_DataProvider_V1::SimpleTSFileDataProviderFactory());
	RegisterProviderFactory(IDPF->getProviderTypeID(), IDPF);
	IDPF.reset(new Multiplexer_DataProvider_V1::TSFilterOutFileDataProviderFactory());
	RegisterProviderFactory(IDPF->getProviderTypeID(), IDPF);
	IDPF.reset(new Multiplexer_DataProvider_V1::DynamicIPDataProviderFactory());
	RegisterProviderFactory(IDPF->getProviderTypeID(), IDPF);
	IDPF.reset(new Multiplexer_DataProvider_V1::DynamicFileDataProviderFactory(FGCOPtr));
	RegisterProviderFactory(IDPF->getProviderTypeID(), IDPF);

	//						//RegisterProviderFactory()
	//						ITSDataProviderFactoryPtr IDPF;
	//						//#if TSFilterFileDataProviderFactory
	//						IDPF = new TSFilterFileDataProviderFactory();
	//						RegisterProviderFactory(IDPF.ProviderTypeID, IDPF);
	//						Log.Info(IDPF.ProviderTypeID);
	//						//#endif
	//						//#if TSFilterOutFileDataProviderFactory
	//						IDPF = new TSFilterOutFileDataProviderFactory();
	//						RegisterProviderFactory(IDPF.ProviderTypeID, IDPF);
	//						Log.Info(IDPF.ProviderTypeID);
	//						//#endif
	//						//#if PSIDataProviderFactory
	//						IDPF = new PSIDataProviderFactory();
	//						RegisterProviderFactory(IDPF.ProviderTypeID, IDPF);
	//						Log.Info(IDPF.ProviderTypeID);
	//						//#endif
	//						//#if TSFileDataProviderFactory
	//						IDPF = new TSFileDataProviderFactory();
	//						RegisterProviderFactory(IDPF.ProviderTypeID, IDPF);
	//						Log.Info(IDPF.ProviderTypeID);
	//						//#endif
	//						////#if DynamicDBProviderFactory
	//						//            IDPF = new DynamicDBProviderFactory();
	//						//            RegisterProviderFactory(IDPF.ProviderTypeID, IDPF);
	//						//            Log.Info(IDPF.ProviderTypeID);
	//						////#endif
	//						IDPF = new InfoDTV.Multiplexer.Dynamic.Provider.ICE.DynamicDBProviderFactory();
	//						RegisterProviderFactory(IDPF.ProviderTypeID, IDPF);
	//						Log.Info(IDPF.ProviderTypeID);
	Log("初始化全部Provider工厂 完成！");
}

void MuxRuntimeConfigI::SaveChannelConfig()
{

	vector<StorageChannelInfo> CIS;
	ITSMuxChannelStreamsPtr TmpCS=FTSMultiplexer.get()->getMuxChannelStreams();
	StringListPtr StreamNames=TmpCS.get()->GetOutputStreamNames();
	StringList::iterator iter;
	for (iter = StreamNames.get()->begin(); iter!= StreamNames.get()->end(); iter++)
	{
		ITSChannelStreamPtr TSStream= TmpCS.get()->GetTSChannelByName(*iter);

		if (TSStream)
		{
			StorageChannelInfo Info;
			if(TSStream.get()->getStreamName()==NULLSTREAM_NAME)
				continue;
			//CIS.push_back(new ChannelInfo());
			Info.ChannelName=TSStream.get()->getStreamName();
			ITSDataProviderPtr TmpDP =TSStream.get()->getDataProvider();
			Info.DataProviderConfig=TmpDP.get()->GetCurrentConfig();
			Info.DataProviderTypeID=TmpDP.get()->getTypeID();
			Info.IsFixOutputCounter=TSStream.get()->getIsFixOutputCounter();
			Info.OutputBitRate=TSStream.get()->getOutputBitRate();
			CIS.push_back(Info);
		}
	}
	eternity::xml_archive aa;
	try
	{
		aa.open(FDBFileName,eternity::archive::store);
		eternity::xml_write(eternity::sequence <eternity::objects>() ,CIS.begin(), CIS.end(), aa, MuxRuntimeConfigSaveString);
		aa.close();
	}
	catch(eternity::exception *e)
	{
		string TmpStr="!!ICERuntimeConfiger ERROR:";
		TmpStr.append(e->what());
		Log(TmpStr);
	}

}


//					void DeleteChannelConfig()
//					{
//						//将DBPath目录下的全部文件删除
//					}
//					void BackupChannelConfig()
//					{
//						//将DBPath目录下的全部文件复制到BackupDBPath的DBPathName+日期 目录 中
//					}

void MuxRuntimeConfigI::LoadChannelConfig()
{
	//载入DBPath目录下的全部.ChannelInfo文件
	fs::path DBFile=FDBFileName;
	Log("正在载入通道配置");
	if (fs::exists(DBFile))
	{
		vector<StorageChannelInfo> CIS;
		eternity::xml_archive aa;
		try
		{
			aa.open(FDBFileName,eternity::archive::load);
			eternity::xml_read(eternity::sequence <eternity::objects>() ,CIS,CIS.begin(), aa, MuxRuntimeConfigSaveString);
			aa.close();
		}
		catch(eternity::exception *e)
		{
			Log("!!ICERuntimeConfiger eternity ERROR:"+string(e->what()));
		}
		catch(std::exception *e)
		{
			Log("!!ICERuntimeConfiger STD ERROR:"+string(e->what()));
		}
		vector<StorageChannelInfo>::iterator iter;
		ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
		for (iter=CIS.begin(); iter!=CIS.end(); iter++)
		{
			Log("正在载入通道配置--"+iter->ChannelName);

			InitAddTSChannelStream(*iter, MuxChannelStreams);
		}
	}
}


/*ITSChannelStreamPtr*/
void MuxRuntimeConfigI::InitAddTSChannelStream(StorageChannelInfo &info, ITSMuxChannelStreamsPtr MuxChannelStreams)
{
	//InfoDTVTSDataProviderInfo DPI = GetDataProvider(FDB,info);
	//if (DPI != null)
	if (!info.DataProviderTypeID.empty())
	{
		if (FTSDataProviderFactoryTable.count(info.DataProviderTypeID))
		{
			//BuildPriovider
			ITSDataProviderFactoryPtr Factory =
				FTSDataProviderFactoryTable[info.DataProviderTypeID];
			//								string CheckResult=Factory->CheckConfig(info.DataProviderConfig);
			//								if(!CheckResult.empty())
			//								{
			//									cout<<"!!InitAddTSChannelStream DataProvider CheckConfig Error>>"<<info.ChannelName;
			//								}
			Log("输出码率：\t"+boost::lexical_cast<string>((long)info.OutputBitRate));
			Log("配置如下：\n"+info.DataProviderConfig);
			ITSDataProviderPtr DataProvider = Factory->CreateProvider(info.DataProviderConfig);
			if (!DataProvider)
			{
				Log("输出通道"+info.ChannelName+"：输出通道数据提供者："+info.DataProviderTypeID+"初始化出错！");
				return;
			}
			//AddDataProvider
			ITSChannelStreamPtr aStream = MuxChannelStreams->AddChannelStream(info.ChannelName,
					info.OutputBitRate, DataProvider, info.IsFixOutputCounter);
			if (!aStream)
			{
				Log("添加输出通道"+info.ChannelName+"失败：输出通道码流设置大于总体复用器带宽！");
			}
			else
			{
				Log("添加输出通道"+info.ChannelName+"成功！");
			}
			//return aStream;
		}
		else
		{

			Log("输出通道"+info.ChannelName+"：输出通道数据提供者"+info.DataProviderTypeID+"不存在！");
			info.DataProviderTypeID="";
			AddNullProviderTSChannelStream(info, MuxChannelStreams);
			//return AddNullProviderTSChannelStream(info, MuxChannelStreams);
		}

	}
	else
	{
		AddNullProviderTSChannelStream(info, MuxChannelStreams);
		//return AddNullProviderTSChannelStream(info, MuxChannelStreams);
	}
}

ITSChannelStreamPtr MuxRuntimeConfigI::AddNullProviderTSChannelStream(StorageChannelInfo &info,
		ITSMuxChannelStreamsPtr MuxChannelStreams)
{
	//Bulid a Null Provider Stream
    Log("输出通道"+info.ChannelName+"：输出通道没有对应的Provider！");
//	cout<<"输出通道"<<info.ChannelName<<"：输出通道没有对应的Provider！";
	ITSDataProviderPtr DataProvider;
	ITSChannelStreamPtr aStream = MuxChannelStreams->AddChannelStream(info.ChannelName,
			info.OutputBitRate, DataProvider, info.IsFixOutputCounter);
	if (aStream)
	{

	    Log("添加输出通道"+info.ChannelName+"失败：输出通道码流设置大于总体复用带宽！");
//		cout<<"添加输出通道"<<info.ChannelName<<"失败：输出通道码流设置大于总体复用带宽！";
	}
	return aStream;
}





MuxRuntimeConfigI::~MuxRuntimeConfigI()
{
	Log("<MEM>已释放...");
}
MuxRuntimeConfigI::MuxRuntimeConfigI(IMultiplexerPtr aIMultiplexer, string aDBFileName, string aBackupDBFileName) //,Ice::CommunicatorPtr aICECommunicator,string aHostIP,int aServerPort const MultiplexerCore_V1::MuxRuntimeConfig  * _MuxRuntimeConfigIPtr
:FLogger(), FTSMultiplexer(aIMultiplexer), FDBFileName(aDBFileName),
FBackupDBFileName(aBackupDBFileName),FGCOPtr()//,FCommunicatorPtr(aICECommunicator),FServerIP(aHostIP),FIPPort(aServerPort)
{
    FLogger.setName("远程管理配置器");
    Log("<MEM>创建！");
}

MuxRuntimeConfigI::MuxRuntimeConfigI(IMultiplexerPtr aIMultiplexer, string aDBFileName, string aBackupDBFileName,GlobalConfigObjectPtr aGCOPtr) //,Ice::CommunicatorPtr aICECommunicator,string aHostIP,int aServerPort const MultiplexerCore_V1::MuxRuntimeConfig  * _MuxRuntimeConfigIPtr
:FLogger(), FTSMultiplexer(aIMultiplexer), FDBFileName(aDBFileName),
FBackupDBFileName(aBackupDBFileName),FGCOPtr(aGCOPtr)//,FCommunicatorPtr(aICECommunicator),FServerIP(aHostIP),FIPPort(aServerPort)
{
    FLogger.setName("远程管理配置器");
    Log("<MEM>创建！");
}



void MuxRuntimeConfigI::InitConfig()
{

	Log("初始化中！");
	try
	{
		InitLoadProviderFactorys();
		LoadChannelConfig();
	}
	catch(...)
	{
		Log("初始化过程中出现错误！");
	}
	Log("初始化完成！");
}

void MuxRuntimeConfigI::RegisterProviderFactory(string aProviderTypeID, ITSDataProviderFactoryPtr aProviderFactory)
{
	Log("正在添加Provider "+aProviderTypeID+" 的工厂");
	if (aProviderFactory)
		FTSDataProviderFactoryTable[aProviderTypeID]=aProviderFactory;
}

ChannelInfoSeq MuxRuntimeConfigI::GetAllChannelInfos(const Ice::Current & _Current)
{
	//						Log("GET ALL CHANNEL INFOS");
	ChannelInfoSeq CIS;
	//						Log("1");
	ITSMuxChannelStreamsPtr TmpCS=FTSMultiplexer.get()->getMuxChannelStreams();
	if (!TmpCS)
		Log("TmpCS NULL");
	//						Log("2");
	StringListPtr StreamNames=TmpCS.get()->GetOutputStreamNames();
	if (!StreamNames)
		Log("StreamNames NULL");
	//						Log("3");
	StringList::iterator iter;
	//						if (StreamNames->size()==0)
	//							Log("Size =0");
	//						Log("Size ="+boost::lexical_cast<string>(StreamNames->size()));
	for (iter = StreamNames.get()->begin(); iter!= StreamNames.get()->end(); iter++)
	{
		ITSChannelStreamPtr TSStream= TmpCS.get()->GetTSChannelByName(*iter);
		Log(TSStream.get()->getStreamName());
		//							Log("4");
		if (TSStream)
		{
			if(TSStream.get()->getStreamName()==NULLSTREAM_NAME)
				continue;
			ChannelInfo Info;
			//CIS.push_back(new ChannelInfo());
			Info.ChannelName=TSStream.get()->getStreamName();
			//								Log("4-1");
			ITSDataProviderPtr TmpDP =TSStream.get()->getDataProvider();
			//								Log("4-2");
			if(TmpDP)
			{

				Info.DataProviderConfig=TmpDP.get()->GetCurrentConfig();
				//									Log("4-3");
				Info.DataProviderTypeID=TmpDP.get()->getTypeID();
				//									Log("4-4");
			}
			else
				Log("<<WARN!!>> "+Info.ChannelName+" DataProvider Is NULL");

			Info.IsFixOutputCounter=TSStream.get()->getIsFixOutputCounter();
			//								Log("4-5");
			Info.OutputBitRate=TSStream.get()->getOutputBitRate();
			Log("BitRate:"+boost::lexical_cast<string>(Info.OutputBitRate));
			//								Log("4-6");
			CIS.push_back(Info);
			//	CIS.push_back(*Info);
		}
	}
	//						Log("5");
	return CIS;
}

DataProviderInfoSeq MuxRuntimeConfigI::GetAllDataProviders(const Ice::Current & _Current)
{
	DataProviderInfoSeq DIS;
	TSDataProviderFactoryMap::iterator iter;
	for (iter=FTSDataProviderFactoryTable.begin(); iter != FTSDataProviderFactoryTable.end(); iter++)
	{
		DataProviderInfo DPI;
		DPI.TypeID=iter->first;
		DPI.Name=iter->second.get()->GetProviderName();
		DPI.Info=iter->second.get()->GetProviderInfo();
		DIS.push_back(DPI);
	}
	return DIS;
}

AddChannelResult MuxRuntimeConfigI::AddChannel(const ChannelInfo& aChannel, const Ice::Current & _Current)
{
	//AddChannelResult ACR;
	Log("NOW AddChannel->1");
	ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
	Log("NOW AddChannel->2");
	ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannel.ChannelName);
	if (TmpStream)
		return ACRSameName;
	Log("NOW AddChannel->3");
	if (FTSDataProviderFactoryTable.count(aChannel.DataProviderTypeID)==0)
	{
//		cout<<"输出通道"<<aChannel.ChannelName<<"：输出通道数据提供者"<< aChannel.DataProviderTypeID<<"不存在！";
		Log("输出通道"+aChannel.ChannelName+"：输出通道数据提供者"+ aChannel.DataProviderTypeID+"不存在！");
		return ACRNoDP;
	}
	ITSDataProviderFactoryPtr Factory =FTSDataProviderFactoryTable[aChannel.DataProviderTypeID];
	//						 Factory.get()->CheckConfig()
	ITSDataProviderPtr DataProvider = Factory.get()->CreateProvider(aChannel.DataProviderConfig);
	if (!DataProvider)
		return ACRDPInitError;
	ITSChannelStreamPtr aStream =MuxChannelStreams.get()->AddChannelStream(aChannel.ChannelName, aChannel.OutputBitRate, DataProvider,
			aChannel.IsFixOutputCounter);

	if (!aStream)
	{
		Log("添加输出通道:"+aChannel.ChannelName+"失败：输出通道码流设置大于总体复用器带宽!  ");
		return ACROBError;
	}
	else
	{
		Log("添加输出通道"+ aChannel.ChannelName+"成功！");

		//							FDB.Set(info);
		//							FDB.Commit();
		SaveChannelConfig();
		return ACROK;
	}
}

bool MuxRuntimeConfigI::DelectChannel(const ::std::string& aChannelName, const Ice::Current & _Current)
{
	if (aChannelName == NULLSTREAM_NAME)
		return false;
	ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
	ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
	if (!TmpStream)
		return false;
	MuxChannelStreams.get()->DeleteChannelStream(aChannelName);
	SaveChannelConfig();
	return true;
}

string MuxRuntimeConfigI::CheckDataProviderConfig(const string& aProviderTypeID, const string& aTmpConfig,
		const Ice::Current& _Current)
{
	string ResultStr;
	if (FTSDataProviderFactoryTable.count(aProviderTypeID)==0)
	{
		return "Server Not Find Data Provider!!";
	}
	ITSDataProviderFactoryPtr Factory =FTSDataProviderFactoryTable[aProviderTypeID];
	ResultStr=Factory.get()->CheckConfig(aTmpConfig);
	return ResultStr;
}

bool MuxRuntimeConfigI::ModifyChanneIsFixOutputCounter(const string& aChannelName, bool aNewIsFixOutputCounter,
		const Ice::Current& _Current)
{
	if (aChannelName == NULLSTREAM_NAME)
		return false;
	ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
	ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
	if (!TmpStream)
	{
		Log("刷新配置失败:通道"+aChannelName+"：输出通道不存在！");
		return false;
	}
	if (TmpStream.get()->getIsFixOutputCounter()!=aNewIsFixOutputCounter)
	{
		Log("刷新配置:通道:"+aChannelName+"属性IsFixOutputCounter从"+boost::lexical_cast<string>(TmpStream.get()->getIsFixOutputCounter()) +"改变为"+boost::lexical_cast<string>(aNewIsFixOutputCounter));
		TmpStream.get()->setIsFixOutputCounter(aNewIsFixOutputCounter);
		SaveChannelConfig();
		Log("刷新配置:通道"+aChannelName+" OK!");
		return true;
	}
	return false;
}

//					virtual bool ModifyChannelOutputBitRate(const string& aChannelName,
//					        const ::Ice::Long aNewOutputBitRate, const Ice::Current & _Current)
//					{
//						if (aChannelName == NULLSTREAM_NAME)
//							return false;
//						ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
//						ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
//						if (!TmpStream)
//						{
//							cout<<"刷新配置失败:通道"<<aChannelName<<"：输出通道不存在！";
//							return false;
//						}
//						if (TmpStream.get()->getOutputBitRate()!=aNewOutputBitRate)
//						{
//							cout<<"刷新配置:通道"<<aChannelName<<"属性OutputBitRate从"<<TmpStream.get()->getOutputBitRate() <<"改变为"<<aNewOutputBitRate;
//							TmpStream.get()->setOutputBitRate(aNewOutputBitRate);
//							SaveChannelConfig();
//							cout<<"刷新配置:通道"<<aChannelName<<" OK!";
//							return true;
//						}
//						return false;
//					}

bool MuxRuntimeConfigI::ModifyChannelOutputBitRate(const string& aChannelName, Ice::Long aNewOutputBitRate,
		const Ice::Current& _Current)
{
	Log("正在修改通道速度！");
	if (aChannelName == NULLSTREAM_NAME)
		return false;
	ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
	ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
	if (!TmpStream)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：输出通道不存在！");
//	    cout<<"刷新配置失败:通道"<<aChannelName<<"：输出通道不存在！"<<endl;
		return false;
	}

	long CurrentOutput=FTSMultiplexer.get()->GetCurrentTotalTSChannelBitRate();

	long TotalOutput = FTSMultiplexer.get()->getOutputBitRate();

	long RestOutput = TotalOutput - (CurrentOutput - TmpStream.get()->getOutputBitRate());

	if (RestOutput < aNewOutputBitRate)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：新的输出带宽"+boost::lexical_cast<string>(aNewOutputBitRate)+"更改后，超过配置的总带宽"+boost::lexical_cast<string>(TotalOutput)+"！");
//		cout<<"刷新配置失败:通道"<<aChannelName<<"：新的输出带宽"<<aNewOutputBitRate<<"更改后，超过配置的总带宽"<<TotalOutput
//		<<"！"<<endl;
		return false;
	}

	if (TmpStream.get()->getOutputBitRate()!=aNewOutputBitRate)
	{
	    Log("刷新配置:通道"+aChannelName+"属性OutputBitRate从"+boost::lexical_cast<string>(TmpStream.get()->getOutputBitRate())+"改变为"+boost::lexical_cast<string>(aNewOutputBitRate));
//		cout<<"刷新配置:通道"<<aChannelName<<"属性OutputBitRate从"<<TmpStream.get()->getOutputBitRate() <<"改变为"<<aNewOutputBitRate<<endl;

		TmpStream.get()->setOutputBitRate(aNewOutputBitRate);

		SaveChannelConfig();
		Log("刷新配置:通道"+aChannelName+" OK!");
//		cout<<"刷新配置:通道"<<aChannelName<<" OK!"<<endl;
		return true;
	}
	return false;
}

bool MuxRuntimeConfigI::ModifyChannelName(const string& aChannelName, const string& aNewChannelName,
		const Ice::Current& _Current)
{
	if (aChannelName == NULLSTREAM_NAME)
		return false;
	ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();

	ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
	if (!TmpStream)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：输出通道不存在！");
//		cout<<"刷新配置失败:通道"<<aChannelName<<"：输出通道不存在！";
		return false;
	}
	ITSChannelStreamPtr TmpStream2=MuxChannelStreams.get()->GetTSChannelByName(aNewChannelName);
	if (TmpStream2)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：新的名称"+aNewChannelName+"已存在！");
//		cout<<"刷新配置失败:通道"<<aChannelName<<"：新的名称"<<aNewChannelName<<"已存在！";
		return false;
	}
	Log("刷新配置:通道"+aChannelName+"属性StreamName从"+TmpStream.get()->getStreamName()+"改变为"+aNewChannelName);
//	cout<<"刷新配置:通道"<<aChannelName<<"属性StreamName从"<<TmpStream.get()->getStreamName() <<"改变为"<<aNewChannelName;
	TmpStream.get()->setStreamName(aNewChannelName);
	SaveChannelConfig();
	Log("刷新配置:通道"+aChannelName+" OK!");
//	cout<<"刷新配置:通道"<<aChannelName<<" OK!";
	return true;
}
bool MuxRuntimeConfigI::ModifyChannelDataProvider(const string& aChannelName, const string& aNewDataProviderTypeID,
		const string& aNewDataProviderConfig, const Ice::Current& _Current)
{
	if (aChannelName == NULLSTREAM_NAME)
		return false;
	ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
	ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
	if (!TmpStream)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：输出通道不存在！");
//		cout<<"刷新配置失败:通道"<<aChannelName<<"：输出通道不存在！";
		return false;
	}

	if (FTSDataProviderFactoryTable.count(aNewDataProviderTypeID)==0)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：新数据提供者"+aNewDataProviderTypeID+"初始化失败！");
//		cout<<"刷新配置失败:通道"<<aChannelName<<"：新数据提供者"<<aNewDataProviderTypeID<<"初始化失败！";
		return false;
	}
	ITSDataProviderFactoryPtr Factory =FTSDataProviderFactoryTable[aNewDataProviderTypeID];
	ITSDataProviderPtr DataProvider = Factory.get()->CreateProvider(aNewDataProviderConfig);
	if (!DataProvider)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：新数据提供者"+aNewDataProviderTypeID+"初始化失败！");
//		cout<<"刷新配置失败:通道"<<aChannelName<<"：新数据提供者"<<aNewDataProviderTypeID<<"初始化失败！";
		return false;
	}
	Log("刷新配置:通道"+aChannelName+"属性DataProvider改变为"+aNewDataProviderTypeID);
//	cout<<"刷新配置:通道"<<aChannelName<<"属性DataProvider改变为"<<aNewDataProviderTypeID;
	TmpStream.get()->SwitchProvider(DataProvider);

	SaveChannelConfig();
	Log("刷新配置:通道"+aChannelName+" OK!");
//	cout<<"刷新配置:通道"<<aChannelName<<" OK!";
	return true;

}

bool MuxRuntimeConfigI::ModifyChannelDataProviderConfig(const string& aChannelName,
		const string& aNewDataProviderConfig, const Ice::Current& _Current)
{
	if (aChannelName == NULLSTREAM_NAME)
		return false;
	ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
	ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
	if (!TmpStream)
	{
		Log("刷新配置失败:通道"+aChannelName+"：输出通道不存在！");
//	    cout<<"刷新配置失败:通道"<<aChannelName<<"：输出通道不存在！";
		return false;
	}

	ITSDataProviderPtr DataProvider = TmpStream.get()->getDataProvider();
	if (!DataProvider)
	{
	    Log("刷新配置失败:通道"+aChannelName+"：数据提供者失败！");
//		cout<<"刷新配置失败:通道"<<aChannelName<<"：数据提供者失败！";
		return false;
	}
	Log("刷新配置:通道"+aChannelName+"属性DataProviderConfig从"+DataProvider->GetCurrentConfig()
		+"改变为"+aNewDataProviderConfig);
//	cout<<"刷新配置:通道"<<aChannelName<<"属性DataProviderConfig从"<<DataProvider->GetCurrentConfig()
//	<<"改变为"<<aNewDataProviderConfig;
	DataProvider->ConfigChanged(aNewDataProviderConfig);

	SaveChannelConfig();
	Log("刷新配置:通道"+aChannelName+" OK!");
//	cout<<"刷新配置:通道"<<aChannelName<<" OK!";
	return true;
}
