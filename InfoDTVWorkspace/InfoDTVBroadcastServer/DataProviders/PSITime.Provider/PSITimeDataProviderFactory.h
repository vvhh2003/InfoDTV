/*
 * PSITimeDataProviderFactory.h
 *
 *  Created on: 2009-2-28
 *      Author: victor
 */

#ifndef PSITIMEDATAPROVIDERFACTORY_H_
#define PSITIMEDATAPROVIDERFACTORY_H_

#include "../../Interface/ITSDataProviderFactory.h"


using namespace MultiplexerCore;
namespace Multiplexer_DataProvider_V1
{

	class PSITimeDataProviderFactory : public ITSDataProviderFactory
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string aMsg);
		public:
			PSITimeDataProviderFactory():FLogger(){FLogger.setName("PSITimeDataProviderFactory");};
			virtual ~PSITimeDataProviderFactory();
			virtual ITSDataProviderPtr CreateProvider(const string ProviderConfig);

			virtual string CheckConfig(const string aTmpConfig);

			virtual string GetProviderInfo();

			virtual string GetProviderName();
			virtual string GetVersion();

			virtual string getProviderTypeID();

	};
}
#endif /* PSITIMEDATAPROVIDERFACTORY_H_ */
