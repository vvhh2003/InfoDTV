#ifndef ITSDATAPROVIDERFACTORY_H
#define ITSDATAPROVIDERFACTORY_H

#include <string>
#include "ITSDataProvider.h"
/**
 * class ITSDataProviderFactory
 */
using namespace std;
namespace MultiplexerCore
{
	class ITSDataProviderFactory
	{

		public:
			ITSDataProviderFactory()
			{
			};
			virtual ~ITSDataProviderFactory()
			{
			};
			/**
			 * @return ITSDataProviders
			 * @param  ProviderConfig
			 */
			virtual ITSDataProviderPtr CreateProvider(const string ProviderConfig) =0;

			/**
			 * @return bool
			 * @param  aTmpConfig
			 * @param  aResult
			 */
			virtual string CheckConfig(const string aTmpConfig) =0; //, string aResult

			/**
			 * @return string
			 */
			virtual string GetProviderInfo() =0;

			/**
			 * @return string
			 */
			virtual string GetProviderName() =0;

			/**
			 * @return string
			 */
			virtual string GetVersion() =0;

			/**
			 * @return long
			 */
			virtual string getProviderTypeID() =0;

	};

	typedef boost::shared_ptr< ITSDataProviderFactory > ITSDataProviderFactoryPtr;

}
;
#endif // ITSDATAPROVIDERFACTORY_H
