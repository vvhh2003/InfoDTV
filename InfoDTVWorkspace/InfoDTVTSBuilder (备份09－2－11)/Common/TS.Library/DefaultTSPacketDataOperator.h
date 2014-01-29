/*
 * DONE!
 */

#ifndef DEFAULTTSPACKETDATAOPERATOR_H_
#define DEFAULTTSPACKETDATAOPERATOR_H_
#include "MPEGInterface.h"

namespace TSLibrary
{
	class DefaultTSPacketDataOperator :virtual public ITSPacketDataOperator
	{
		public:


			/// <summary>
			/// 根据TSConfig配置一个TS数据包，没有调整字段
			/// </summary>
			/// <param name="aTSConfig">TSConfig配置</param>
			/// <param name="aTSPacket">TS包的缓冲</param>
			/// <param name="aDataCounter">外部的计数器</param>
			/// <returns>该TS包中可以写入的大小,小于0为出错</returns>
			virtual int BuildTSPacket(TSPacketStructPtr aSrcTSPacket,TSPacketStructPtr aDestTSPacket, ITSDataCounterPtr aDataCounter);


			/// <summary>
			/// 将来源数据写入一个没有调整字段TS包的数据区域（一共184字节或者183字节）
			/// </summary>
			/// <param name="aTSPacket">TS包</param>
			/// <param name="aSrcData">来源数据</param>
			/// <param name="aStartIndex">来源数据中起始的索引</param>
			/// <param name="aWriteSize">需要写入的大小</param>
			/// <returns>写入TS包的字节数</returns>
			virtual int WriteTSData(TSPacketStructPtr aTSPacket, RawBufferPtr aSrcData, int aStartIndex,int aWriteSize);
	};
}
#endif /*DEFAULTTSPACKETDATAOPERATOR_H_*/
