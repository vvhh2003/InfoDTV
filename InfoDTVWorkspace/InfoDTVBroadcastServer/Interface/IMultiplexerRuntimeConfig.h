#ifndef IMULTIPLEXERRUNTIMECONFIG_H
#define IMULTIPLEXERRUNTIMECONFIG_H

#include <string>
#include <IceUtil/UUID.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "IMultiplexer.h"
#include "ITSDataProviderFactory.h"

/**
 * class IMultiplexerRuntimeConfig
 */

/******************************* Abstract Class ****************************
 IMultiplexerRuntimeConfig does not have any pure virtual methods, but its author
 defined it as an abstract class, so you should not use it directly.
 Inherit from it instead and create only objects from the derived classes
 *****************************************************************************/
using namespace std;
namespace MultiplexerCore
{
	class IMultiplexerRuntimeConfig;
	typedef boost::shared_ptr<IMultiplexerRuntimeConfig> IMultiplexerRuntimeConfigPtr;
	class IMultiplexerRuntimeConfig:public boost::enable_shared_from_this<IMultiplexerRuntimeConfig>
	{
		public:
			virtual ~IMultiplexerRuntimeConfig();
			/**
			 */
			virtual StringListPtr GetProviderInfos() =0;

			/**
			 */
			virtual StringListPtr GetProviderNames() =0;

			/**
			 */
			virtual StringListPtr GetProviderTypeIDs() =0;

			/**
			 */
			virtual StringListPtr GetProviderVers() =0;

			/**
			 * @return string
			 * @param  aProviderTypeID
			 * @param  aTmpConfig
			 */
			virtual string CheckDataProviderConfig(string aProviderTypeID, string aTmpConfig) =0;

			/**
			 * @param  ATSMultiplexer
			 */
			virtual void InitializeConfig(IMultiplexerPtr ATSMultiplexer) =0;

			/**
			 * @param  AMultiplexer
			 */
			virtual void RefreshConfig(IMultiplexerPtr AMultiplexer);

			/**
			 * @param  aProviderTypeID
			 * @param  aProviderFactory
			 */
			virtual void RegisterProviderFactory(string aProviderTypeID, ITSDataProviderFactoryPtr aProviderFactory);

	};
}

#endif // IMULTIPLEXERRUNTIMECONFIG_H
