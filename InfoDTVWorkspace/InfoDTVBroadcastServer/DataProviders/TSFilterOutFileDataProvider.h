#ifndef TSFILTEROUTFILEDATAPROVIDER_H_
#define TSFILTEROUTFILEDATAPROVIDER_H_
#include "../eternity4/eternity/eternity.hpp"
#include <map>
#include <iostream>
#include <fstream>
#include "../Interface/ITSDataProvider.h"
#include "../Common/TSPacketStruct.h"
#include "../Common/TS.Library/DefaultDataCounter.h"
#include "../Common/Log/Log.h"

using namespace eternity;
using namespace MultiplexerCore;
namespace Multiplexer_DataProvider_V1
{

	const string TS_FILTER_OUT_FILE_DATAPROVIDER_GUID="4D5E25FD-8600-4077-923F-E23D74694C72";
	struct TSFilterOutFileConfigObject
	{

		string TSFileName;
		bool IsLockFile;
		bool IsFixCounter;
		map<int ,int > PIDMaps;
		TSFilterOutFileConfigObject();
		void xml_serialize(xmlstring_archive &xml);

		void AddPidmap(unsigned short aOrgPID,unsigned short aOutPID);

		void LoadConfig(string StringConfig);

		string SaveToString();
	};

	typedef boost::shared_ptr<TSFilterOutFileConfigObject> TSFilterOutFileConfigObjectPtr;

	class TSFilterOutFileDataProvider : public ITSDataProvider
	{
		private:
			TSFilterOutFileConfigObjectPtr FConfigObject;
			bool FIsActived;
			long FFilePos;
			std::ifstream FFileStream;
			long FFileLength;
			TSLibrary::PIDDataCounterPtrMaps FPIDMaps;

			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string aMsg);
		public:
			TSFilterOutFileDataProvider(TSFilterOutFileConfigObjectPtr aCO) ;

			virtual ~TSFilterOutFileDataProvider();
			void Active();
			void ConfigChanged(string aNewConfig);

			void DeActive();

			string GetProviderInfo();
			string GetProviderStateInfo();

			TSPacketStructPtr GetTSPacket();

			void Reset();
			bool getIsActived();

			string getTypeID();

			string GetCurrentConfig();
		};
	}
#endif /*TSFILTEROUTFILEDATAPROVIDER_H_*/
