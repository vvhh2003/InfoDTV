#ifndef TSMUXCHANNELSTREAMS_H_
#define TSMUXCHANNELSTREAMS_H_
#include "../Interface/IMultiplexer.h"
#include "../Interface/ITSMuxChannelStreams.h"
#include "../Common/TSPacketStruct.h"
#include "../Common/Log/Log.h"
#include <vector>
#include "TSChannelStream.h"
#include <iostream>
#include "Poco/Mutex.h"
//#include <list>
using namespace std;
using namespace MultiplexerCore;

namespace MultiplexerCore_V1
{

	class TSMuxChannelStreams : public ITSMuxChannelStreams
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}

			//1 平均输出带宽BPS
			long FAverageBitRate;
			//1 全部输出通道列表
			// private ArrayList FChannelList = new ArrayList();
			vector<ITSChannelStreamPtr> FChannelList;
//			IMultiplexerPtr FMultiplexer;
			IMultiplexer* FMultiplexer;
			// ILog FLog = LogManager.GetLogger("InfoDTV.Multiplexer.Core.V1");
			ITSChannelStreamPtr FNullPacketChannelStream;

			Poco::FastMutex FMutex;
			//1 计算当前优先级，需要比较全部ChannelStream的优先级
			/// 若均小于平均值则返回-1
			int GetMaxProrityIndex(long aAverageBitRate);


			//1 重新计算平均码率并设置空包流输出码率
			void ReCalculateBitRate(long aCurrentTotalBitRate, bool aIsAddStream);


		public:
			virtual ~TSMuxChannelStreams();
//			TSMuxChannelStreams(IMultiplexerPtr aMultiplexer) :
			TSMuxChannelStreams(IMultiplexer* aMultiplexer) ;

			virtual long GetCurrentTotalTSChannelBitRate();
			virtual void ConfigChanged (string aStreamName,string aNewConfig );
			//1 增加输入流
			/// 需要重新计算平均码率以及空包流输出码率
			virtual ITSChannelStreamPtr AddChannelStream(string AFStreamName, long AFOutputBitRate,
			        ITSDataProviderPtr AFTSDataProvider, bool AIsFixOutputCounter);
			virtual ITSChannelStreamPtr AddChannelStream(string aStreamName, ITSChannelStreamPtr aStream);
			virtual void DeleteChannelStream(string aStreamName);

			virtual long GetOutputBitRateByName(string aStreamName);

			virtual StringListPtr GetOutputStreamNames();
			virtual IntListPtr GetOutputPIDs();


			virtual ITSChannelStreamPtr GetTSChannelByName(string aChannelName);

			//1 实现复用调度输出
			/// 具体步骤：
			/// 1、判断每一个TSChannelStream是否能够输出
			/// 2、输出该TSChannelStream的包
			virtual TSPacketStructPtr OutputPacket();

			virtual void ReCalculateMuxStreamsBitRate();

			virtual void ClearAllStream();

			virtual void ResetStreams();

		};
	}
;
#endif /*TSMUXCHANNELSTREAMS_H_*/
