/*
 * DynamicFileDataProviderGlobalConfig.cpp
 *
 *  Created on: 2009-3-6
 *      Author: victor
 */
#include "DynamicFileDataProviderGlobalConfig.h"
namespace Multiplexer_DataProvider_V1
{
	void ClearDynamicFileDataProviderDBPath(const std::string DynamicFileDataProvider_GlobalDBPath,const std::string aGDFDPServiceName)
	{
		Poco::Path FP(DynamicFileDataProvider_GlobalDBPath+aGDFDPServiceName);
		try
		{
			Poco::DirectoryIterator it(FP);
			Poco::DirectoryIterator end;
			while (it != end)
			{
				Poco::Path p(it->path());
				if(it->isFile())
				{
					if(Poco::toUpper(p.getExtension())=="MEMTS")
					{
						it->remove(true);
					}
				}
				++it;
			}
		}
		catch(...)
		{

		}
	}
	void CreateDynamicFileDataProviderDBPath(const std::string DynamicFileDataProvider_GlobalDBPath,const std::string aGDFDPServiceName)
	{
		Poco::File FF(DynamicFileDataProvider_GlobalDBPath+aGDFDPServiceName);
		if(!FF.exists())
		{
			FF.createDirectories();
		}
	}
	std::string GetDynamicFileDataProviderFileName(const std::string DynamicFileDataProvider_GlobalDBPath,const std::string aGDFDPServiceName,const std::string aGDFDPFileName)
	{
		return DynamicFileDataProvider_GlobalDBPath+aGDFDPServiceName+Poco::Path::separator()+aGDFDPFileName+".MEMTS";
	}

	std::string GetDynamicFileDataProviderDBName(const std::string DynamicFileDataProvider_GlobalDBPath,const std::string aGDFDPServiceName)
	{
		return DynamicFileDataProvider_GlobalDBPath+aGDFDPServiceName;
	}
}
