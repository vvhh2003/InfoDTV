#ifndef DEKTECTSBROADCAST_H_
#define DEKTECTSBROADCAST_H_
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/cast.hpp"
#include <vector>
#include <Ice/Ice.h>


#include "../../Common/CircularBuffer.h"
#include "../../Common/TSPacketStruct.h"
#include "../../Interface/BroadcastInterface.h"
#include "../../Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/ICEBroadcastController.h"
#include "../../Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICERuntimeConfiger.h"

#include "../../Multiplexer/MuxRuntimeConfig.h"
#include "../../Multiplexer/SoftMultiplexer.h"
#include "DektecTSBroadcastThread.h"
#include "../TSDataPrepThread.h"
#include "../../Common/Log/Log.h"

using namespace std;
using namespace BroadcastCore;
using namespace InfoDTV_Common_Buffer;

namespace MultiplexerCore_V1
{

	class DektecTSBroadcast : virtual public ITSBroadcastControl, virtual public Ice::Application,
	        virtual public ITSBroadcastServer
	{

		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}
			bool FIsStopped;
			bool FIsBroadcasting;
			bool FIsQAMMode;
			int FDeviceType;
			long FQAMFreqHz;
			long FBitRate;
			string FHostIP;
			int FHostPort;
			//			Ice::CommunicatorPtr FCommunicator;

			Ice::ObjectAdapterPtr FICEAdapter;
			//boost::shared_ptr<InfoDTV::Broadcast::BroadcastControllerI> FBroadcastControllerPtr;
			InfoDTV::Broadcast::BroadcastControllerI* FBroadcastControllerPtr;
			string FDBPath;

			CircularBufferPtr FCircularBufferPtr;
			ISoftMultiplexerPtr FSoftMultiplexerPtr;
			TSDataPrepThreadPtr FTSDataPrepThreadPtr;
//			TSDataPrepThread * FTSDataPrepThreadPtr;
			DektecTSBroadcastThreadPtr FDektecTSBroadcastThreadPtr;
//			UDPTSBroadcastThread* FUDPTSBroadcastThreadPtr;

			//			InfoDTV::Multiplexer::RuntimeConfig::ICERuntimeConfigerPtr FICERuntimeConfigerPtr;

			string FCurrentDBFile;
			Ice::Identity FMuxConfigIdentity;
			string FDebugTSFile;
			GlobalConfigObjectPtr FGlobalConfigObjPtr;
			void CreatPath(string aConfigPath);

			void InitICEAdapter();

			string GetICEEndpointConfig();

			virtual void interruptCallback(int aInt);

			public:

			virtual ~DektecTSBroadcast();
			DektecTSBroadcast(bool aIsQAMMode,int aDeviceType,long aQAMFreqHz,string aHostIP,int aHostPort,string aDBPath);
			DektecTSBroadcast(GlobalConfigObjectPtr aGCO);
			DektecTSBroadcast(bool aIsQAMMode,int aDeviceType,long aQAMFreqHz,string aHostIP,int aHostPort,string aDBPath,string aDebugTSFile);
			virtual int run(int, char*[]);

			virtual bool StartBroadcast(::std::string aConfigDBName,long aOutputBitRate);
			virtual bool StopBroadcast();

			virtual bool RestartBroadcast();
			virtual bool IsInBroadcasting();

			virtual long GetBroadcastBitRate();

			virtual BroadcastCore::StringSeq GetRuntimeConfigDatabaseNameList();

			virtual string GetBroadcastConfigDBName();

			virtual int DeleteRuntimeConfigDB(::std::string aRuntimeConfigDB);

			virtual void StartServer();

			virtual void StopServer();
		};
		typedef boost::shared_ptr<DektecTSBroadcast> DektecTSBroadcastPtr;
		//
		                //		class UDPTSBroadcastApp : public IceUtil::Thread
		                //		{
		                //			private:
		                //				UDPTSBroadcastPtr FTSBroadcastControlPtr;
		                //			/*
		                //			 IceUtil::CtrlCHandler ctrCHandler(onCtrlC);
		                //			 static void onCtrlC(int)
		                //			 {
		                //			 dynamic_cast<UDPTSBroadcast*>(	this->FTSBroadcastControlPtr.get())->StopServer();
		                //			 }
		                //			 */
		                //			virtual void run()
		                //			{
		                //				cout<<"Start!"<<std::endl;
		                //				Ice::StringSeq Temp;
		                ////				FTSBroadcastControl.main(Temp);
		                //				FTSBroadcastControlPtr->main(Temp);
		                //				cout<<"End!"<<std::endl;
		                ////				FTSBroadcastControl
		                ////				dynamic_cast<MultiplexerCore_V1::UDPTSBroadcast*>(FTSBroadcastControlPtr.get())->main(0,NULL);
		                //			}
		                //			public:
		                //			UDPTSBroadcastApp(string aTargetIP, int aTargetPort, string aHostIP, int aHostPort, string aDBPath)
		                ////		:	FTSBroadcastControlPtr(UDPTSBroadcast::Create(aTargetIP,aTargetPort,aHostIP,aHostPort,aDBPath))
		                ////			:FTSBroadcastControl(aTargetIP,aTargetPort,aHostIP,aHostPort,aDBPath)
		                //					:	FTSBroadcastControlPtr(new UDPTSBroadcast(aTargetIP,aTargetPort,aHostIP,aHostPort,aDBPath))
		                //			{
		                ////				Ice::StringSeq Temp;
		                ////				FTSBroadcastControl.main(Temp);
		                //			}
		                //
		                //			void Stop()
		                //			{
		                ////				FTSBroadcastControl.StopServer();
		                //				FTSBroadcastControlPtr->StopServer();
		                ////				dynamic_cast<UDPTSBroadcast*>(FTSBroadcastControlPtr.get())->StopServer();
		                //			}
		                //
		                //		};
	                }



#endif /*DEKTECTSBROADCAST_H_*/
