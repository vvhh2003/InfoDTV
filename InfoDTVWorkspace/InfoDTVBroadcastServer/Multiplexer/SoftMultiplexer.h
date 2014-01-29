#ifndef SOFTMULTIPLEXER_H_
#define SOFTMULTIPLEXER_H_
#include <boost/shared_ptr.hpp>
#include "../Common/Log/Log.h"
//#include <boost/enable_shared_from_this.hpp>
#include "../Interface/ISoftMultiplexer.h"
#include "TSMuxChannelStreams.h"
using namespace std;


namespace MultiplexerCore_V1
{
	class SoftMultiplexer ;
	typedef boost::shared_ptr<SoftMultiplexer> SoftMultiplexerPtr;
	class SoftMultiplexer : public ISoftMultiplexer//,public boost::enable_shared_from_this<SoftMultiplexer>
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr);
//			long FTotalOutputBitRate;
			ITSMuxChannelStreamsPtr FTSMuxChannelStreams;
			long FOutputBitRate;
			long FOutputBufferLengthPreSec;
			void SetTSMuxChannelStreams(IMultiplexer* aMux);
		public:
			static  MultiplexerCore::ISoftMultiplexerPtr Create(long TotalOutputBitRate);
			virtual ~SoftMultiplexer();
			SoftMultiplexer(long TotalOutputBitRate);

			void FillBuffer(int aBufferLength, RawBufferPtr aBuffer);


			void FillPreSecBuffer(int aBufferLength, RawBufferPtr aBuffer);

			long GetOutputBitRateByName(string aStreamName);

			StringListPtr GetOutputStreamNames();

			void Clear();

			void Reset();

			ITSMuxChannelStreamsPtr getMuxChannelStreams();

			long getOutputBitRate();
			//感觉没什么用
			void setOutputBitRate(long aNewBitRate);

			long getOutputBufferLengthPreSec();

			long GetCurrentTotalTSChannelBitRate();

			IntListPtr GetOutputPIDs();
	};

}


#endif /*SOFTMULTIPLEXER_H_*/
