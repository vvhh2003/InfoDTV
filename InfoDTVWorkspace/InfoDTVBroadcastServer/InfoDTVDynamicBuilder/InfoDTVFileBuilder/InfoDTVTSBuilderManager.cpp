/*
 * InfoDTVTSBuilderManager.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "InfoDTVTSBuilderManager.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
//using namespace TSLibrary::InfoDTV;
using namespace InfoDTV::DynamicBuilder::FileBuilder;

InfoDTVTSBuilderManager::InfoDTVTSBuilderManager():FBuilderMap(),FBuilderParamsMap()
{

}

void InfoDTVTSBuilderManager::RegisterBuilder(string aUUID,ITSBuilder *aBuilder,string ParamsMap)
{
	FBuilderParamsMap[aUUID]=ParamsMap;
	FBuilderMap[aUUID]=aBuilder;
}

void InfoDTVTSBuilderManager::UnRegisterBuilder(string aUUID)
{
	if(FBuilderParamsMap.count(aUUID)!=0)
	{
		map<string,string>::iterator tt=FBuilderParamsMap.find(aUUID);
		FBuilderParamsMap.erase(tt);
	}
	if(FBuilderMap.count(aUUID)!=0)
	{
		map<string,ITSBuilder*>::iterator tt=FBuilderMap.find(aUUID);
		FBuilderMap.erase(tt);
	}
}

string InfoDTVTSBuilderManager::GetParamsFromBuilder(string aUUID)
{
	if(FBuilderParamsMap.count(aUUID)!=0)
	{
		return FBuilderParamsMap[aUUID];
	}
	else
	{
		return "";
	}
}

string InfoDTVTSBuilderManager::GetTargetIDFromBuilder(string aUUID,string aFileName)
{
	if(FBuilderMap.count(aUUID)!=0)
	{

		if(FBuilderMap[aUUID])
		{
			if(FBuilderMap[aUUID]->FileIDIndexer.count(aFileName)!=0)
			{
				string TmpResult=str(boost::format("%x")%FBuilderMap[aUUID]->FileIDIndexer[aFileName]);
				return TmpResult;
			}
		}
	}
	return "";
}
