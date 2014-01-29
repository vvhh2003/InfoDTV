#ifndef BUFFERREVICER_H_
#define BUFFERREVICER_H_
#include <IceUtil/IceUtil.h>
#include "ICEBufferSender.h"
#include "../../Common/TSPacketStruct.h"
#include "../../Common/Log/Log.h"
using namespace std;
namespace Multiplexer_DataProvider_V1
{

	class BufferManager
	{
		private:
			RawBufferPtr FBuffer;
			RawBufferPtr FBackupBuffer;
			bool FHasNewBuffer;
			uint FBackupBufferLength;
			uint FBufferLength;
			IceUtil::Mutex FMutex;
		public:
			BufferManager();

			uint GetBackupBufferLength();

			uint GetBufferLength();

			RawBufferPtr BeginRead();

			void EndRead();

			void SetNewBuffer(RawBufferPtr aBuffer,int aBufferLength);

	};
	typedef boost::shared_ptr<BufferManager> BufferManagerPtr;
}

namespace InfoDTV
{

	namespace Multiplexer
	{

		namespace Dynamic
		{

			namespace Provider
			{
				class BufferTransferI : virtual public InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer
				{
				    private:
						Multiplexer_DataProvider_V1::BufferManagerPtr FBufferManager;
						string FServiceName;
						string FSessionID;
						long FTotalRecvLength;
						long  FTotalToBeRecvedLength;
						RawBufferPtr FBuffer;
						InfoDTV_Common_Log::InfoDTVLogger FLogger;
						void Log(string ALogStr)
						{
						    FLogger.information(ALogStr);
						}
					public:
						BufferTransferI(Multiplexer_DataProvider_V1::BufferManagerPtr aBufferManager,
						        string aServiceName) ;

						virtual ~BufferTransferI();
						virtual void Login(const Ice::Current & _Current);
						virtual void SendBuffer(const string& aServiceName, ::Ice::Int aBufferLength,
						        const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq,
						        const ::Ice::Current& _Current);

						virtual void SendBuffer2(const string& aServiceName, const string& aBufferGuid,
						        ::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength,
						        const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&aSeq,
						        const ::Ice::Current& _Current);
				};
			}
		}
	}
}
#endif /*BUFFERREVICER_H_*/
