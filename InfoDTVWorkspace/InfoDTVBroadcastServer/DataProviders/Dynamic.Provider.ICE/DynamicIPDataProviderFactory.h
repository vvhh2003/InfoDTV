#ifndef DYNAMICPROVIDERFACTORY_H_
#define DYNAMICPROVIDERFACTORY_H_
#include "../../Interface/ITSDataProviderFactory.h"

//#include "DynamicIPDataProvider.h"
#include "../../Common/Log/Log.h"

using namespace MultiplexerCore;

namespace Multiplexer_DataProvider_V1
{

    class DynamicIPDataProviderFactory: public ITSDataProviderFactory
    {
	private:
	    InfoDTV_Common_Log::InfoDTVLogger FLogger;
	    void Log(string ALogStr)
	    {
		FLogger.information(ALogStr);
	    }
	public:
	    DynamicIPDataProviderFactory();
	    virtual ~DynamicIPDataProviderFactory();
	    virtual ITSDataProviderPtr CreateProvider(const string ProviderConfig);

	    virtual string CheckConfig(const string aTmpConfig);

	    virtual string GetProviderInfo();

	    virtual string GetProviderName();
	    virtual string GetVersion();
	    virtual string getProviderTypeID();

    };
}
#endif /*DYNAMICPROVIDERFACTORY_H_*/
