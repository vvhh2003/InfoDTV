/*
 * DynamicFileDataProviderGlobalConfig.h
 *
 *  Created on: 2009-3-6
 *      Author: victor
 */

#ifndef DYNAMICFILEDATAPROVIDERGLOBALCONFIG_H_
#define DYNAMICFILEDATAPROVIDERGLOBALCONFIG_H_

#include <string>
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/String.h"
#include "Poco/SingletonHolder.h"

//inline std::string& DynamicFileDataProvider_GlobalDBPath()
//{
//	static std::string GlobalPath;
//	return GlobalPath;
//}

namespace Multiplexer_DataProvider_V1
{

//	static Poco::SingletonHolder<std::string> DynamicFileDataProvider_GlobalDBPathSingleton;


	void ClearDynamicFileDataProviderDBPath(const std::string DynamicFileDataProvider_GlobalDBPath, const std::string aGDFDPServiceName);
	void CreateDynamicFileDataProviderDBPath(const std::string DynamicFileDataProvider_GlobalDBPath,const std::string aGDFDPServiceName);
	std::string GetDynamicFileDataProviderFileName(const std::string DynamicFileDataProvider_GlobalDBPath,const std::string aGDFDPServiceName,const std::string aGDFDPFileName);

	std::string GetDynamicFileDataProviderDBName(const std::string DynamicFileDataProvider_GlobalDBPath,const std::string aGDFDPServiceName);
}

#endif /* DYNAMICFILEDATAPROVIDERGLOBALCONFIG_H_ */
