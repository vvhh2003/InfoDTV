#ifndef SIMPLETSFILEDATAPROVIDERFACTORY_H_
#define SIMPLETSFILEDATAPROVIDERFACTORY_H_
#include "../Interface/ITSDataProviderFactory.h"


using namespace MultiplexerCore;
namespace Multiplexer_DataProvider_V1
{

    class SimpleTSFileDataProviderFactory : public ITSDataProviderFactory
    {
	private:
	    InfoDTV_Common_Log::InfoDTVLogger FLogger;
	    void Log(string aMsg);
	public:
	    SimpleTSFileDataProviderFactory():FLogger(){FLogger.setName("SimpleTSFileDataProviderFactory");};
	    virtual ~SimpleTSFileDataProviderFactory();
	    virtual ITSDataProviderPtr CreateProvider(const string ProviderConfig);

	    virtual string CheckConfig(const string aTmpConfig);

	    virtual string GetProviderInfo();

	    virtual string GetProviderName();
	    virtual string GetVersion();

	    virtual string getProviderTypeID();

    };
}
#endif /*SIMPLETSFILEDATAPROVIDERFACTORY_H_*/
