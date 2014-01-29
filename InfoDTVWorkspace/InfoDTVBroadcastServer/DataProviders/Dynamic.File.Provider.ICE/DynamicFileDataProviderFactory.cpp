/*
 * DynamicFileDataProviderFactory.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */
#include "DynamicFileDataProviderFactory.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "DynamicFileDataProvider.h"

using namespace Multiplexer_DataProvider_V1;

using namespace std;
namespace fs = boost::filesystem;

DynamicFileDataProviderFactory::DynamicFileDataProviderFactory(GlobalConfigObjectPtr aGCOPtr ):
	FLogger(),FGCOPtr(aGCOPtr)
{
    FLogger.setName("DynamicFileDataProviderFactory");
}
DynamicFileDataProviderFactory::~DynamicFileDataProviderFactory()
{
	Log("<MEM>已释放");
}
ITSDataProviderPtr DynamicFileDataProviderFactory::CreateProvider(const string ProviderConfig)
{
	Log("正在建立DynamicFileDataProviderFactory");

	DynamicFileDataProviderConfigObjectPtr COPtr(new DynamicFileDataProviderConfigObject);


	string Tmp=CheckConfig(ProviderConfig);
	if (Tmp.empty())
	{

		COPtr->LoadConfig(ProviderConfig);

		ITSDataProviderPtr TmpPtr(new DynamicFileDataProvider(COPtr,FGCOPtr));

		return TmpPtr;
	}
	else
	{

		Log(Tmp);
	}
	ITSDataProviderPtr TmpPtr;
	return TmpPtr;
}

string DynamicFileDataProviderFactory::CheckConfig(const string aTmpConfig)
{
	string ResultStr;
	try
	{
		DynamicFileDataProviderConfigObjectPtr COPtr(new DynamicFileDataProviderConfigObject);
		COPtr->LoadConfig(aTmpConfig);
		//					fs::path FileName(COPtr->TSFileName);
		//					if(!fs::exists(FileName))
		//						return "File Not Exist!";
	}
	catch(...)
	{
		return "ERROR in Check Config";
	}

	return ResultStr;
}

string DynamicFileDataProviderFactory::GetProviderInfo()
{
	string Tmp= "根据配置文件对InfoDTVDynamic进行播放,需要指定相应的IP信息以及TS文件路径,例子如下：\r\n";
	DynamicFileDataProviderConfigObject CO;
	CO.IsLogInfo=true;
	CO.ChannelIP="127.0.0.1";
	CO.ChannelIPPort=10007;
	CO.ChannelName="测试通道";
	Tmp+=CO.SaveToString();
	return Tmp;
}

string DynamicFileDataProviderFactory::GetProviderName()
{
	return "InfoDTV Dynamic远程动态数据库数据提供器";
}

string DynamicFileDataProviderFactory::GetVersion()
{
	return "C++ V1";
}

string DynamicFileDataProviderFactory::getProviderTypeID()
{
	return DYNAMIC_FILE_DATAPROVIDER_GUID;
}

