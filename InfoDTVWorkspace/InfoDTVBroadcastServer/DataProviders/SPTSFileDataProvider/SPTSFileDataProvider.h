/*
 * SPTSFileDataProvider.h
 *
 *  Created on: 2009-3-19
 *      Author: victor
 */

#ifndef SPTSFILEDATAPROVIDER_H_
#define SPTSFILEDATAPROVIDER_H_
#include "../../Interface/ITSDataProvider.h"
#include "../../Interface/ITSDataProcessor.h"
#include "../../Common/Log/Log.h"
#include "../../eternity4/eternity/eternity.hpp"
#include "../../Common/TS.Library/DefaultDataCounter.h"


namespace Multiplexer_DataProvider_V1
{
	using namespace eternity;
	const string SPTS_FILE_DATAPROVIDER_GUID="83B752F5-DB50-45c5-BC3D-7781C6A132C5";
	struct SPTSFileConfigObject
	{

		string TSFileName;
		unsigned short PcrPID;
		unsigned long long int CBRPIDBitRate;
		bool IsVBRToCBR;
		bool IsFixPCR_PTS;
		bool IsMapPID;
		map<int ,int > PIDMaps;
		SPTSFileConfigObject();
		void xml_serialize(eternity::xmlstring_archive &xml);

		void LoadConfig(string StringConfig);
		string SaveToString();
	};
	typedef boost::shared_ptr<SPTSFileConfigObject> SPTSFileConfigObjectPtr;
//	typedef boost::shared_ptr<SimpleTSFileDataProvider> SimpleTSFileDataProviderPtr;
	using namespace MultiplexerCore;
	class SPTSFileDataProvider :public ITSDataProvider
	{
		private:
			SPTSFileConfigObjectPtr FConfigObject;
			ITSDataProviderPtr FSimpleTSFileDataProviderPtr;
			ITSDataProcessorPtr FVBR2CRBProcessorPtr;
			ITSDataProcessorPtr FPCRPTSProcessorPtr;
			bool FIsActived;
//			map<unsigned short,unsigned short> FPIDMaps;
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			TSPacketStructPtr FNullPacketPtr;
			string FGlobalSPTSFileDB;
			void Log(string aMsg);
		public:
			SPTSFileDataProvider(SPTSFileConfigObjectPtr aCO,string aGlobalSPTSFileDB);

			virtual ~SPTSFileDataProvider();
			virtual void Active();
			virtual	void ConfigChanged(string aNewConfig);
			virtual	void DeActive();
			virtual	string GetProviderInfo();
			virtual	string GetProviderStateInfo();

			virtual TSPacketStructPtr GetTSPacket();

			virtual	void Reset();

			virtual bool getIsActived();

			virtual	string getTypeID();

			virtual	string GetCurrentConfig();
	};
}
#endif /* SPTSFILEDATAPROVIDER_H_ */
