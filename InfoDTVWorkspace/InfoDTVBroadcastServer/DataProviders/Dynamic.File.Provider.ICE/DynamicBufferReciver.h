#ifndef DYNAMICBUFFERRECIVER_H_
#define DYNAMICBUFFERRECIVER_H_
#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "../../Common/TSPacketStruct.h"
#include "DynICEBufferSender.h"
#include "DynamicBufferTransferI.h"
#include "../../Common/Log/Log.h"
using namespace std;

namespace Multiplexer_DataProvider_V1
{
	class DynamicICEBufferReciver
	{
		private:
			FileManagerPtr FFileManager;
			Ice::CommunicatorPtr FCommunicator;
			Ice::ObjectAdapterPtr FICEAdapter;
			string FHostIP;
			int FIPPort;
			string FServiceName;
			bool FIsLogInfo;
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			string FDynamicFileDataProvider_GlobalDBPath;
			void Log(string ALogStr)
			{
				if(FIsLogInfo)
			    FLogger.information(ALogStr);
			}
			void InitCommunicator();

			string GetICECommunicatorConfig();
			string GetICEEndpointConfig();
//			Ice::Identity FBufferTransferIdentity;
		public:
			DynamicICEBufferReciver(FileManagerPtr aFileManager,string aChannelName,string aChannelIP,int aChannelIPPort,bool aIsLogInfo,string aDynamicFileDataProvider_GlobalDBPath);
			void InitICEAdapter();
			void Start();

			void Stop();
	};

		    typedef boost::shared_ptr<DynamicICEBufferReciver> DynamicICEBufferReciverPtr;
	    }
#endif /*BUFFERRECIVER_H_*/
