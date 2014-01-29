#ifndef UDPTSBROADCASTTHREAD_H_
#define UDPTSBROADCASTTHREAD_H_

#define USE_POCO_THREAD
#define TRIAL

#include <boost/lexical_cast.hpp>
#include "../../Common/CircularBuffer.h"
#include "../../Common/TSPacketStruct.h"
#ifdef USE_ICE_THREAD
#include <IceUtil/Thread.h>
#endif
#ifdef USE_POCO_THREAD
#include "Poco/Activity.h"
#include "Poco/Thread.h"

#endif

#include "../../Common/AntiDebug.h"

#ifdef TRIAL
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"

#endif

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "UDPRateLimiter.h"
#include "../../Common/Log/Log.h"

namespace MultiplexerCore_V1
{
	//	const int FifoSize=188*1024*70; //15M
#ifdef USE_ICE_THREAD

	class UDPTSBroadcastThread : public IceUtil::Thread
	{

		private:
			std::string FIPAddress;
			int FIPPort;
			long int FBitRate;
			bool FIsStoped;
			bool FIsNetworkReady;
			InfoDTV_Common_Buffer::CircularBufferPtr FCB;
			IceUtil::ThreadControl FThreadControl;

			InfoDTV_UDP_Rate_Limit::UDPRateLimiter FUDPRateLimiter;

			int FUdpsock;
			struct sockaddr_in FSIPAddress;

			int FCurrentSendBytes;//=0;
			bool FIsSendBegined;//=false;



			std::string FDebugTSFileName;
			std::ofstream FDebugFile;
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}

			virtual void run();

			void OutputBuffer(const int AiBufferLength, RawBufferPtr AiBuffer);

		public:
			UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
			        InfoDTV_Common_Buffer::CircularBufferPtr aReadCB) ;


			UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
			        InfoDTV_Common_Buffer::CircularBufferPtr aReadCB,std::string aDebugTSFile);

			void InitNetwork();

			virtual ~UDPTSBroadcastThread();
			void Start();
			void Stop();
	};

	typedef boost::shared_ptr<UDPTSBroadcastThread> UDPTSBroadcastThreadPtr;

#endif


#ifdef USE_POCO_THREAD
	class UDPTSBroadcastThread
	{

		private:
			std::string FIPAddress;
			int FIPPort;
			long int FBitRate;
			bool FIsNetworkReady;
			InfoDTV_Common_Buffer::CircularBufferPtr FCB;
			InfoDTV_UDP_Rate_Limit::UDPRateLimiter FUDPRateLimiter;

			int FUdpsock;
			struct sockaddr_in FSIPAddress;

			int FCurrentSendBytes;//=0;
			bool FIsSendBegined;//=false;



			std::string FDebugTSFileName;
			std::ofstream FDebugFile;
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
#ifdef TRIAL
			Poco::DateTime FStartDateTime;
#endif
			Poco::Activity<UDPTSBroadcastThread> FActivity;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}

			virtual void run();

			void OutputBuffer(const int AiBufferLength, RawBufferPtr AiBuffer);

		public:
			UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
			        InfoDTV_Common_Buffer::CircularBufferPtr aReadCB) ;


			UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
			        InfoDTV_Common_Buffer::CircularBufferPtr aReadCB,std::string aDebugTSFile);

			void InitNetwork();

			virtual ~UDPTSBroadcastThread();
			void Start();
			void Stop();
	};

	typedef boost::shared_ptr<UDPTSBroadcastThread> UDPTSBroadcastThreadPtr;
#endif
}
#endif /*UDPTSBROADCASTTHREAD_H_*/
