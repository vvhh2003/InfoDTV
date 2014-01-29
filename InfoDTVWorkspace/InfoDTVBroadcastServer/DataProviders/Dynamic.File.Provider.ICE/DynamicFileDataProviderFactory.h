#ifndef DYNAMICFILEPROVIDERFACTORY_H_
#define DYNAMICFILEPROVIDERFACTORY_H_
#include "../../Interface/ITSDataProviderFactory.h"

//#include "DynamicFileDataProvider.h"
#include "../../Common/Log/Log.h"

#include "../../Common/GlobalConfig.hpp"

using namespace MultiplexerCore;

namespace Multiplexer_DataProvider_V1
{

	class DynamicFileDataProviderFactory: public ITSDataProviderFactory
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			GlobalConfigObjectPtr FGCOPtr;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}
		public:
			DynamicFileDataProviderFactory(GlobalConfigObjectPtr aGCOPtr );
			virtual ~DynamicFileDataProviderFactory();
			virtual ITSDataProviderPtr CreateProvider(const string ProviderConfig);

			virtual string CheckConfig(const string aTmpConfig);

			virtual string GetProviderInfo();

			virtual string GetProviderName();
			virtual string GetVersion();
			virtual string getProviderTypeID();

	};
}
#endif /*DYNAMICPROVIDERFACTORY_H_*/
