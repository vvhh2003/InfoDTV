#ifndef SIMPLETSFILEDATAPROVIDER_H_
#define SIMPLETSFILEDATAPROVIDER_H_
#include "../Interface/ITSDataProvider.h"
#include "../Common/Log/Log.h"
#include "../eternity4/eternity/eternity.hpp"

#include "../Common/TS.Library/DefaultDataCounter.h"
namespace Multiplexer_DataProvider_V1
{

	const string SIMPLE_FILE_DATAPROVIDER_GUID="091FEEF9-2995-44d9-8988-43249FA3F9B4";
	struct SimpleTSFileConfigObject
	{

		string TSFileName;
		bool IsLockFile;
		bool IsFixCounter;
		SimpleTSFileConfigObject();
		void xml_serialize(eternity::xmlstring_archive &xml);

		void LoadConfig(string StringConfig);
		string SaveToString();
	};
	typedef boost::shared_ptr<SimpleTSFileConfigObject> SimpleTSFileConfigObjectPtr;
	using namespace MultiplexerCore;
	class SimpleTSFileDataProvider :public ITSDataProvider
	{
		SimpleTSFileConfigObjectPtr FConfigObject;
		bool FIsActived;
		long FFilePos;
		std::ifstream FFileStream;
		long FFileLength;
		TSLibrary::PIDDataCounterPtrMaps FPIDMaps;
		InfoDTV_Common_Log::InfoDTVLogger FLogger;
		void Log(string aMsg);
		public:
			SimpleTSFileDataProvider(SimpleTSFileConfigObjectPtr aCO);

			virtual ~SimpleTSFileDataProvider();
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
#endif /*SIMPLETSFILEDATAPROVIDER_H_*/
