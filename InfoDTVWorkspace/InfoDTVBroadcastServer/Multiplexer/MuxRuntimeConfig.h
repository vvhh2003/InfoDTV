#ifndef MUXRUNTIMECONFIG_H_
#define MUXRUNTIMECONFIG_H_
#include <Ice/Ice.h>
#include <boost/shared_ptr.hpp>
#include "../Interface/InterfaceCommon.h"
#include "../Interface/ITSChannelStream.h"
#include "../Interface/ITSDataProvider.h"
#include "../Interface/IMultiplexer.h"

//#include "../Interface/IMultiplexerRuntimeConfig.h"
//#include "ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICERuntimeConfiger.h"
#include <boost/cast.hpp>

#include <vector>

using namespace std;
using namespace MultiplexerCore;
using namespace InfoDTV::Multiplexer::RuntimeConfig;
namespace MultiplexerCore_V1
{
	class MuxRuntimeConfig;
	typedef boost::shared_ptr<MuxRuntimeConfig> MuxRuntimeConfigPtr;
	//typedef	boost::shared_ptr< MuxRuntimeConfigI > ICERuntimeConfigerPtr;
	typedef vector<ITSDataProviderPtr> ProviderPtrList;
	class MuxRuntimeConfig
	{
		private:
			ProviderPtrList FProviderPtrs;
			string FDBPath;
			ICERuntimeConfigerPtr FConfiger;
		public:
			MuxRuntimeConfig(string aDBPath,Ice::CommunicatorPtr aICECommunicator,string aHostIP,int aServerPort)
			{
				FDBPath=aDBPath;
				//FConfiger.reset(new MuxRuntimeConfigI(boost::polymorphic_cast<MultiplexerCore::IMultiplexerRuntimeConfig*>(this)));
			//	FConfiger.reset(new MuxRuntimeConfigI(this));
			}
//			virtual StringListPtr GetProviderInfos()
//			{
//				StringListPtr ProviderInfos(new StringList());
//				ProviderPtrList::iterator iter;
//				for(iter=FProviderInfoPtrs.begin();iter!=FProviderInfoPtrs.end();iter++)
//				{
//					ProviderInfos.get()->push_back(iter.get()->get);
//				}
//				//ProviderInfos.get()->push_back();
//				return ProviderInfos;
//			}
	};

}
#endif /*MUXRUNTIMECONFIG_H_*/
