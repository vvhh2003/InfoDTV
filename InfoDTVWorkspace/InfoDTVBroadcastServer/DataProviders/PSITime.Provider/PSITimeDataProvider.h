/*
 * PSITimeDataProvider.h
 *
 *  Created on: 2009-2-27
 *      Author: victor
 */

#ifndef PSITIMEDATAPROVIDER_H_
#define PSITIMEDATAPROVIDER_H_
#include "../../Interface/ITSDataProvider.h"
#include "../../Common/Log/Log.h"
#include "../../eternity4/eternity/eternity.hpp"

#include "../../Common/TS.Library/DVB/PSIInterface.h"
#include "../../Common/TS.Library/MPEGInterface.h"
#include "../../Common/TS.Library/DVB-PSI/TDTTable.h"
#include "../../Common/TS.Library/DVB-PSI/TOTTable.h"
namespace Multiplexer_DataProvider_V1
{

	const string PSI_TIME_DATAPROVIDER_GUID="981FEEF7-2995-44d9-8988-43249FA3F9B5";
	using namespace MultiplexerCore;
	class PSITimeDataProvider :public ITSDataProvider
	{
		private:
			bool FIsActived;
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			int FGetCount;
			TSLibrary::DVB::PSI::TDTTable FTDTTable;
			TSLibrary::DVB::PSI::TOTTable FTOTTable;
			TSLibrary::ITSDataCounterPtr FDataCounter;
			TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter;
			void Log(string aMsg);
		public:
			PSITimeDataProvider();

			virtual ~PSITimeDataProvider();
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
#endif /* PSITIMEDATAPROVIDER_H_ */
