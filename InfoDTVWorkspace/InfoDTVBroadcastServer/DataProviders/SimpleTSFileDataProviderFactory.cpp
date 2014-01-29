/*
 * SimpleTSFileDataProviderFactory.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "SimpleTSFileDataProviderFactory.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "../eternity4/eternity/eternity.hpp"
#include "SimpleTSFileDataProvider.h"



using namespace std;
namespace fs = boost::filesystem;
using namespace Multiplexer_DataProvider_V1;

void SimpleTSFileDataProviderFactory::Log(string aMsg)
{
	FLogger.information(aMsg);
}

SimpleTSFileDataProviderFactory::~SimpleTSFileDataProviderFactory()
{
	Log("<MEM>已释放");
}
ITSDataProviderPtr SimpleTSFileDataProviderFactory::CreateProvider(const string ProviderConfig)
{
	Log("正在建立SimpleTSFileDataProvider");
	SimpleTSFileConfigObjectPtr COPtr(new SimpleTSFileConfigObject);
	//SimpleTSFileDataProviderConfigObject CO();
	string Tmp=CheckConfig(ProviderConfig);
	if (Tmp.empty())
	{

		COPtr->LoadConfig(ProviderConfig);

		ITSDataProviderPtr TmpPtr(new SimpleTSFileDataProvider(COPtr));

		return TmpPtr;
	}
	else
	{
		Log(":"+Tmp);
	}
	ITSDataProviderPtr TmpPtr;
	return TmpPtr;
}

string SimpleTSFileDataProviderFactory::CheckConfig(const string aTmpConfig)
{
	string ResultStr;
	try
	{
		SimpleTSFileConfigObjectPtr COPtr(new SimpleTSFileConfigObject);
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

string SimpleTSFileDataProviderFactory::GetProviderInfo()
{

	string Tmp= "对TS文件进行简单播放,例子如下：\r\n";
	SimpleTSFileConfigObject CO;
	CO.TSFileName="文件名";
	CO.IsLockFile=false;
	Tmp+=CO.SaveToString();
	return Tmp;
}

string SimpleTSFileDataProviderFactory::GetProviderName()
{
	return "简单TS文件数据提供器";
}

string SimpleTSFileDataProviderFactory::GetVersion()
{
	return "C++ V1";
}

string SimpleTSFileDataProviderFactory::getProviderTypeID()
{
	return SIMPLE_FILE_DATAPROVIDER_GUID;
}
