#ifndef DYNAMICPROVIDER_H_
#define DYNAMICPROVIDER_H_
#include "../../eternity4/eternity/eternity.hpp"


#include "../../Interface/ITSDataProvider.h"
#include "../../Common/TSPacketStruct.h"
#include "BufferReciver.h"
#include "../../Common/Log/Log.h"

using namespace eternity;
using namespace MultiplexerCore;
namespace Multiplexer_DataProvider_V1
{
    const string DYNAMIC_IP_DATAPROVIDER_GUID="18779755-7A58-4d04-A745-F0EC6FF5B12F";
    struct DynamicIPDataProviderConfigObject
    {

	string ChannelName;
	int ChannelIPPort;
	string ChannelIP;
	string ProtectedTSFileName;

	void xml_serialize(xmlstring_archive &xml);

	void LoadConfig(string StringConfig);

	string SaveToString();
    };

    typedef boost::shared_ptr<DynamicIPDataProviderConfigObject> DynamicIPDataProviderConfigObjectPtr;
    class DynamicIPDataProvider : public ITSDataProvider
    {
	private:
	    DynamicIPDataProviderConfigObjectPtr FConfigObject;
	    bool FIsActived;
	    RawBufferPtr FTSDataBuffer;
	    BufferManagerPtr FBufManager;
	    uint FBufPosition;
	    ICEBufferReciverPtr FRBufferReciver;


	    void SetInitProtectStream();
	    void SetReciver();

	    void ResetReciver();
	    InfoDTV_Common_Log::InfoDTVLogger FLogger;
	    void Log(string ALogStr)
	    {
		FLogger.information(ALogStr);
	    }
	public:
	    DynamicIPDataProvider(DynamicIPDataProviderConfigObjectPtr aConfigObject);
	    virtual ~DynamicIPDataProvider();
	    virtual void Active();

	    virtual void DeActive();

	    virtual TSPacketStructPtr GetTSPacket();

	    virtual void ConfigChanged(string aNewConfig);
	    virtual string GetProviderInfo();

	    virtual string GetProviderStateInfo();
	    virtual string getTypeID();
	    virtual bool getIsActived();
	    virtual void Reset();

	    virtual string GetCurrentConfig();
    };

}
#endif /*DYNAMICPROVIDER_H_*/
