#ifndef TSFILTEROUTFILEDATAPROVIDERFACTORY_H_
#define TSFILTEROUTFILEDATAPROVIDERFACTORY_H_
#include "../Interface/ITSDataProviderFactory.h"
#include "../Common/Log/Log.h"

using namespace MultiplexerCore;
namespace Multiplexer_DataProvider_V1
{

	class TSFilterOutFileDataProviderFactory : public ITSDataProviderFactory
	{
	private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string aMsg);
		public:
			TSFilterOutFileDataProviderFactory();
			virtual ~TSFilterOutFileDataProviderFactory();
			virtual ITSDataProviderPtr CreateProvider(const string ProviderConfig);

			virtual string CheckConfig(const string aTmpConfig);

			virtual string GetProviderInfo();

			virtual string GetProviderName();

			virtual string GetVersion();

			virtual string getProviderTypeID();

	};
}
#endif /*TSFILTEROUTFILEDATAPROVIDERFACTORY_H_*/
