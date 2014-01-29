#ifndef TSDATAPREPTHREAD_H_
#define TSDATAPREPTHREAD_H_
//#define USE_ICE_THREAD
#define USE_POCO_THREAD
#include "../Common/CircularBuffer.h"
#include "../Common/TSPacketStruct.h"
#include "../Common/Log/Log.h"
#ifdef USE_ICE_THREAD
#include <IceUtil/Thread.h>
#endif
#ifdef USE_POCO_THREAD
#include "Poco/Activity.h"
#include "Poco/Thread.h"
#endif

#include "SoftMultiplexer.h"
namespace MultiplexerCore_V1
{
	const int TS_DataBuffer_Length=188 * 1024 * 10 * 7;
#ifdef USE_ICE_THREAD
	class TSDataPrepThread : public IceUtil::Thread
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}

			MultiplexerCore::ISoftMultiplexerPtr FMultiplexer;
			InfoDTV_Common_Buffer::CircularBufferPtr FCB;
			bool FIsStoped;
			IceUtil::ThreadControl FThreadControl;

			virtual void run();

			void PreBuildBuffer();
		public:

			TSDataPrepThread(MultiplexerCore::ISoftMultiplexerPtr aMultiplexer,
			        InfoDTV_Common_Buffer::CircularBufferPtr aCB);

			virtual ~TSDataPrepThread();

			virtual void Start();

			virtual void Stop();
	};
	typedef boost::shared_ptr<TSDataPrepThread> TSDataPrepThreadPtr;
#endif
#ifdef USE_POCO_THREAD


	class TSDataPrepThread
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			Poco::Activity<TSDataPrepThread> FActivity;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}

			MultiplexerCore::ISoftMultiplexerPtr FMultiplexer;
			InfoDTV_Common_Buffer::CircularBufferPtr FCB;
			virtual void run();
			void PreBuildBuffer();

		public:

			TSDataPrepThread(MultiplexerCore::ISoftMultiplexerPtr aMultiplexer,
			        InfoDTV_Common_Buffer::CircularBufferPtr aCB);

			virtual ~TSDataPrepThread();

			virtual void Start();

			virtual void Stop();
	};
	typedef boost::shared_ptr<TSDataPrepThread> TSDataPrepThreadPtr;
#endif
}
#endif /*DEKTECTSDATAPREPTHREAD_H_*/
