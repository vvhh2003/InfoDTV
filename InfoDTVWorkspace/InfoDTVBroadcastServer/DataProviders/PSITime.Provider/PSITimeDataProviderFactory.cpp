/*
 * PSITimeDataProviderFactory.cpp
 *
 *  Created on: 2009-2-28
 *      Author: victor
 */


#include "PSITimeDataProviderFactory.h"

#include "PSITimeDataProvider.h"



using namespace std;
using namespace Multiplexer_DataProvider_V1;

void PSITimeDataProviderFactory::Log(string aMsg)
{
	FLogger.information(aMsg);
}

PSITimeDataProviderFactory::~PSITimeDataProviderFactory()
{
	Log("<MEM>已释放");
}
ITSDataProviderPtr PSITimeDataProviderFactory::CreateProvider(const string ProviderConfig)
{
	Log("正在建立PSITimeDataProvider");

	ITSDataProviderPtr TmpPtr(new PSITimeDataProvider());

	return TmpPtr;

}

string PSITimeDataProviderFactory::CheckConfig(const string aTmpConfig)
{
	string ResultStr;
	return ResultStr;
}

string PSITimeDataProviderFactory::GetProviderInfo()
{

	string Tmp= "提供TDT TOT时间，没有配置，可以乱写";
	return Tmp;
}

string PSITimeDataProviderFactory::GetProviderName()
{
	return "时钟数据提供器";
}

string PSITimeDataProviderFactory::GetVersion()
{
	return "C++ V1";
}

string PSITimeDataProviderFactory::getProviderTypeID()
{
	return PSI_TIME_DATAPROVIDER_GUID;
}
