#ifndef BUFFERRECIVER_H_
#define BUFFERRECIVER_H_
#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "../../Common/TSPacketStruct.h"
#include "ICEBufferSender.h"
#include "BufferTransferI.h"
#include "../../Common/Log/Log.h"
using namespace std;

namespace Multiplexer_DataProvider_V1
{
	class ICEBufferReciver
	{
		private:
			BufferManagerPtr FBufManager;
			Ice::CommunicatorPtr FCommunicator;
			Ice::ObjectAdapterPtr FICEAdapter;
			string FHostIP;
			int FIPPort;
			string FServiceName;
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr)
			{
			    FLogger.information(ALogStr);
			}
			void InitCommunicator();

			string GetICECommunicatorConfig();
			string GetICEEndpointConfig();
//			Ice::Identity FBufferTransferIdentity;
		public:
			ICEBufferReciver(BufferManagerPtr aBufManager,string aChannelName,string aChannelIP,int aChannelIPPort);
			void InitICEAdapter();
			void Start();

			void Stop();
	};

		    typedef boost::shared_ptr<ICEBufferReciver> ICEBufferReciverPtr;
	    }
#endif /*BUFFERRECIVER_H_*/
