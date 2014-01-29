#ifndef TSCHANNELSTREAM_H_
#define TSCHANNELSTREAM_H_
#include "../Interface/InterfaceCommon.h"
#include "../Interface/ITSChannelStream.h"
#include "../Interface/ITSDataProvider.h"

#include <map>
using namespace std;
using namespace MultiplexerCore;
namespace MultiplexerCore_V1
{
	class TSChannelStream : public ITSChannelStream
	{
		private:
			bool FIsNullStream;
			map<unsigned short, unsigned char> FOutputPIDTSCountTable;
			//1 输出带宽单位BPS 默认1M
			/// 188*664*8
			long FOutputBitRate;

			//1 输出优先级用于，控制流输出
			long FOutputPrority;
			//1 流名称
			string FStreamName;

			ITSDataProviderPtr FTSDataProvider;
			bool FIsFixOutputCounter;

			//1 用于从Provider读取TS，并提供修正输出PID与Counter的能力
			/// 若ITSCountFixer为空者不需要修正COUNTER
			/// 若aOutputPID为-1则不需要调整输出PID
			TSPacketStructPtr ReadTSPacket();


		public:
			virtual ~TSChannelStream();
			TSChannelStream(const string AFStreamName, long AFOutputBitRate);


			//			TSChannelStream(string AFStreamName, long AFOutputBitRate,	ITSDataProviderPtr AFTSDataProvider)
			//			{
			//				TSChannelStream(AFStreamName, AFOutputBitRate, AFTSDataProvider,	false);
			//			}

			TSChannelStream(string AFStreamName, long AFOutputBitRate,
			        ITSDataProviderPtr AFTSDataProvider,
			        bool AIsFixOutputCounter);
			virtual void DecOutputPrority(long aAverageBitRate);
			virtual TSPacketStructPtr GetTSPacket();

			virtual IntListPtr GetOutputPIDs();
			virtual void ResetCounter();
			virtual void InitOutputPrority();
			virtual bool IsNullTS();

			virtual void Reset();
			virtual void ResetOutputPrority();
			virtual void SwitchProvider(ITSDataProviderPtr aTSDataProvider);

			virtual ITSDataProviderPtr getDataProvider();

			virtual bool getIsFixOutputCounter();

			virtual void setIsFixOutputCounter(bool aIsFix);

			virtual long getOutputPrority();

			virtual long getOutputBitRate();

			virtual void setOutputBitRate(long aNewBitRate);

			virtual string getStreamName();

			virtual void setStreamName(string aStreamName);
	};

}

#endif /*TSCHANNELSTREAM_H_*/
