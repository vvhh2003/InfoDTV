/*
 * DynamicIPDataProviderFactory.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */
#include "DynamicIPDataProviderFactory.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "DynamicIPDataProvider.h"
using namespace Multiplexer_DataProvider_V1;

using namespace std;
namespace fs = boost::filesystem;

DynamicIPDataProviderFactory::DynamicIPDataProviderFactory():FLogger()
{
    FLogger.setName("DynamicIPDataProviderFactory");
}
DynamicIPDataProviderFactory::~DynamicIPDataProviderFactory()
{
	Log("<MEM>已释放");
}
ITSDataProviderPtr DynamicIPDataProviderFactory::CreateProvider(const string ProviderConfig)
{
	Log("正在建立DynamicIPDataProviderFactory");

	DynamicIPDataProviderConfigObjectPtr COPtr(new DynamicIPDataProviderConfigObject);


	string Tmp=CheckConfig(ProviderConfig);
	if (Tmp.empty())
	{

		COPtr->LoadConfig(ProviderConfig);

		ITSDataProviderPtr TmpPtr(new DynamicIPDataProvider(COPtr));

		return TmpPtr;
	}
	else
	{

		Log(Tmp);
	}
	ITSDataProviderPtr TmpPtr;
	return TmpPtr;
}

string DynamicIPDataProviderFactory::CheckConfig(const string aTmpConfig)
{
	string ResultStr;
	try
	{
		DynamicIPDataProviderConfigObjectPtr COPtr(new DynamicIPDataProviderConfigObject);
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

string DynamicIPDataProviderFactory::GetProviderInfo()
{
	string Tmp= "根据配置文件对InfoDTV进行播放,需要指定相应的IP信息以及保护TS流文件,例子如下：\r\n";
	DynamicIPDataProviderConfigObject CO;
	CO.ProtectedTSFileName="PROTECTFILENAME.TS";
	CO.ChannelIP="127.0.0.1";
	CO.ChannelIPPort=10007;
	CO.ChannelName="测试通道";
	Tmp+=CO.SaveToString();
	return Tmp;
}

string DynamicIPDataProviderFactory::GetProviderName()
{
	return "InfoDTV 远程动态数据库数据提供器";
}

string DynamicIPDataProviderFactory::GetVersion()
{
	return "C++ V1";
}

string DynamicIPDataProviderFactory::getProviderTypeID()
{
	return DYNAMIC_IP_DATAPROVIDER_GUID;
}

