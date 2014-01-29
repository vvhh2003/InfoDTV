/*
 * TSFilterOutFileDataProviderFactory.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "TSFilterOutFileDataProviderFactory.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "TSFilterOutFileDataProvider.h"


using namespace std;
namespace fs = boost::filesystem;
using namespace Multiplexer_DataProvider_V1;
void TSFilterOutFileDataProviderFactory::Log(string aMsg)
{
    FLogger.information(aMsg);
}
TSFilterOutFileDataProviderFactory::TSFilterOutFileDataProviderFactory():FLogger()
{
    FLogger.setName("TSFilterOutFileDataProviderFactory");
}
TSFilterOutFileDataProviderFactory::~TSFilterOutFileDataProviderFactory()
{
	Log("<MEM>已释放");
}
ITSDataProviderPtr TSFilterOutFileDataProviderFactory::CreateProvider(const string ProviderConfig)
{
	Log("正在建立TSFilterOutFileDataProvider");

	TSFilterOutFileConfigObjectPtr COPtr(new TSFilterOutFileConfigObject);

	string Tmp=CheckConfig(ProviderConfig);
	if (Tmp.empty())
	{

		COPtr->LoadConfig(ProviderConfig);

		ITSDataProviderPtr TmpPtr(new TSFilterOutFileDataProvider(COPtr));

		return TmpPtr;
	}
	else
	{

		Log(":"+Tmp);
	}
	ITSDataProviderPtr TmpPtr;
	return TmpPtr;
}

string TSFilterOutFileDataProviderFactory::CheckConfig(const string aTmpConfig)
{
	string ResultStr;
	try
	{
		TSFilterOutFileConfigObjectPtr COPtr(new TSFilterOutFileConfigObject);
		COPtr->LoadConfig(aTmpConfig);
		fs::path FileName(COPtr->TSFileName);
		if(!fs::exists(FileName))
			return "File Not Exist!";
	}
	catch(...)
	{
		return "ERROR in Check Config";
	}

	return ResultStr;
}

string TSFilterOutFileDataProviderFactory::GetProviderInfo()
{
	string Tmp= "对TS文件过滤后同时修改输出PID进行播放，不是直接播放,需要指定用于过滤后输出的PID以及更改PID,例子如下：\r\n";
	TSFilterOutFileConfigObject CO;
	CO.TSFileName="文件名";
	CO.IsLockFile=false;
	CO.AddPidmap(1000,2000);
	CO.AddPidmap(1000,2000);
	Tmp+=CO.SaveToString();
	return Tmp;
}

string TSFilterOutFileDataProviderFactory::GetProviderName()
{
	return "能够过滤同时更改输出PID的TS文件数据提供器";
}

string TSFilterOutFileDataProviderFactory::GetVersion()
{
	return "C++ V1";
}

string TSFilterOutFileDataProviderFactory::getProviderTypeID()
{
	return TS_FILTER_OUT_FILE_DATAPROVIDER_GUID;
}
