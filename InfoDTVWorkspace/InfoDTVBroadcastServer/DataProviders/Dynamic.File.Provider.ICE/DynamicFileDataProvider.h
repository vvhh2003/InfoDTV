#ifndef DYNAMICFILEDATAPROVIDER_H_
#define DYNAMICFILEDATAPROVIDER_H_
#include "../../eternity4/eternity/eternity.hpp"


#include "../../Interface/ITSDataProvider.h"
#include "../../Common/TSPacketStruct.h"
#include "DynamicBufferReciver.h"
#include "../../Common/Log/Log.h"

#include "../../Common/GlobalConfig.hpp"

#include <iostream>
#include <fstream>
using namespace eternity;
using namespace MultiplexerCore;
namespace Multiplexer_DataProvider_V1
{
	const string DYNAMIC_FILE_DATAPROVIDER_GUID="0AA64432-00DB-40b3-A7B4-862DA0A91251";
	struct DynamicFileDataProviderConfigObject
	{

		string ChannelName;
		int ChannelIPPort;
		string ChannelIP;
		bool IsLogInfo;

		void xml_serialize(xmlstring_archive &xml);

		void LoadConfig(string StringConfig);

		string SaveToString();
	};

	typedef boost::shared_ptr<DynamicFileDataProviderConfigObject> DynamicFileDataProviderConfigObjectPtr;
	class DynamicFileDataProvider : public ITSDataProvider
	{
		private:
			DynamicFileDataProviderConfigObjectPtr FConfigObject;
			bool FIsActived;
//			RawBufferPtr FTSDataBuffer;
			FileManagerPtr FFileManager;
			ifstream FFileStream;
			uint FBufPosition;
			DynamicICEBufferReciverPtr FRBufferReciver;
			TSPacketStructPtr FTmpTsPacket;

			void CloseFile(const string aFileName);
			void SetInitProtectStream();
			void SetReciver();

			void ResetReciver();
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			GlobalConfigObjectPtr FGCOPtr;
			void Log(string ALogStr)
			{
				if(FConfigObject->IsLogInfo)
					FLogger.information(ALogStr);
			}
			void LogError(string ALogStr)
			{
				FLogger.error(ALogStr);
			}
		public:
			DynamicFileDataProvider(DynamicFileDataProviderConfigObjectPtr aConfigObject,GlobalConfigObjectPtr aGCOPtr);
			virtual ~DynamicFileDataProvider();
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
