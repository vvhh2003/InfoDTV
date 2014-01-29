/*
 * SPTSFileDataProviderFactory.cpp
 *
 *  Created on: 2009-3-23
 *      Author: victor
 */


#include "SPTSFileDataProviderFactory.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "../../eternity4/eternity/eternity.hpp"
#include "SPTSFileDataProvider.h"



using namespace std;
namespace fs = boost::filesystem;
using namespace Multiplexer_DataProvider_V1;

void SPTSFileDataProviderFactory::Log(string aMsg)
{
	FLogger.information(aMsg);
}

SPTSFileDataProviderFactory::~SPTSFileDataProviderFactory()
{
	Log("<MEM>已释放");
}
ITSDataProviderPtr SPTSFileDataProviderFactory::CreateProvider(const string ProviderConfig)
{
	Log("正在建立SPTSFileDataProviderFactory");
	 SPTSFileConfigObjectPtr COPtr(new  SPTSFileConfigObject);
	//SimpleTSFileDataProviderConfigObject CO();
	string Tmp=CheckConfig(ProviderConfig);
	if (Tmp.empty())
	{

		COPtr->LoadConfig(ProviderConfig);

		ITSDataProviderPtr TmpPtr(new SPTSFileDataProvider(COPtr,FGlobalSPTSFileDB));

		return TmpPtr;
	}
	else
	{
		Log(":"+Tmp);
	}
	ITSDataProviderPtr TmpPtr;
	return TmpPtr;
}

string SPTSFileDataProviderFactory::CheckConfig(const string aTmpConfig)
{
	string ResultStr;
	try
	{
		Log("正在检查配置");
		SPTSFileConfigObjectPtr COPtr(new SPTSFileConfigObject);
		Log("正在检查配置1");
		COPtr->LoadConfig(aTmpConfig);
		Log("正在检查配置2");
		fs::path FileName(FGlobalSPTSFileDB+COPtr->TSFileName);
		if(!fs::exists(FileName))
			return "File Not Exist!";
	}
	catch(eternity::exception *e)
	{
		return "ERROR in Check Config";
	}
	catch(...)
	{
		return "ERROR in Check Config";
	}

	return ResultStr;
}

string SPTSFileDataProviderFactory::GetProviderInfo()
{

	string Tmp= "对SPTS文件进行播放具备VBR调整与PCR PTS调整的功能,例子如下：\r\n";
	SPTSFileConfigObject CO;
	CO.TSFileName="文件名";
	CO.IsFixPCR_PTS=true;
	CO.IsVBRToCBR=false;
	CO.IsMapPID=true;
	CO.PIDMaps[1000]=1002;
	CO.PIDMaps[1001]=1003;
	CO.PcrPID=1000;
	Tmp+=CO.SaveToString();
	return Tmp;
}

string SPTSFileDataProviderFactory::GetProviderName()
{
	return "SPTS文件数据提供器";
}

string SPTSFileDataProviderFactory::GetVersion()
{
	return "C++ V1";
}

string SPTSFileDataProviderFactory::getProviderTypeID()
{
	return SPTS_FILE_DATAPROVIDER_GUID;
}
