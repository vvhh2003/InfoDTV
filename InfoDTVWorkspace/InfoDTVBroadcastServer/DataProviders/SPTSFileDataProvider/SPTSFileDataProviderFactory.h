/*
 * SPTSFileDataProviderFactory.h
 *
 *  Created on: 2009-3-23
 *      Author: victor
 */

#ifndef SPTSFILEDATAPROVIDERFACTORY_H_
#define SPTSFILEDATAPROVIDERFACTORY_H_
#include "../../Interface/ITSDataProviderFactory.h"

using namespace MultiplexerCore;
namespace Multiplexer_DataProvider_V1
{

	class SPTSFileDataProviderFactory : public ITSDataProviderFactory
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			string FGlobalSPTSFileDB;
			void Log(string aMsg);
		public:
			SPTSFileDataProviderFactory(string aGlobalSPTSFileDB):FLogger(),FGlobalSPTSFileDB(aGlobalSPTSFileDB){FLogger.setName("SPTSFileDataProviderFactory");};
			virtual ~SPTSFileDataProviderFactory();
			virtual ITSDataProviderPtr CreateProvider(const string ProviderConfig);

			virtual string CheckConfig(const string aTmpConfig);

			virtual string GetProviderInfo();

			virtual string GetProviderName();
			virtual string GetVersion();

			virtual string getProviderTypeID();

	};
}

#endif /* SPTSFILEDATAPROVIDERFACTORY_H_ */
