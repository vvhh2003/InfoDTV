#ifndef DEFAULTTSDATASTREAM_H_
#define DEFAULTTSDATASTREAM_H_
#include "MPEGInterface.h"
#include "DefaultTSStreamDataManager.h"
#include "DefaultTSPacketDataOperator.h"

namespace TSLibrary
{
	class DefaultTSDataStream : public ITSDataStream
	{
		private:
			ITSStreamDataManagerPtr FDataManager;

			ITSPacketDataOperatorPtr FTSOperator;
		public:
			DefaultTSDataStream() ;
			DefaultTSDataStream(ITSStreamDataManagerPtr aStreamDataManager);
			DefaultTSDataStream(ITSStreamDataManagerPtr aStreamDataManager, ITSPacketDataOperatorPtr aTSOperator);


			/// <summary>
			/// 插入空包
			/// </summary>
			/// <returns></returns>
			virtual ISWriteDataResults InsertNullPacket();


			/// <summary>
			/// 写入制定PID数据并指示第一个包采用新包IsPayLoadUnitStart=true即TSPacketConfig的缺省配置
			/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
			/// 另外除了第一个包的IsPayLoadUnitStart为True外，后面的包该属性都将为False.
			/// </summary>
			///  <param name="aPID">需要写入的PID</param>
			/// <param name="aSrcData">来源数据区</param>
			/// <returns></returns>
			virtual ISWriteDataResults WriteData(unsigned short aPID, RawBufferPtr aSrcData, int aSrcDataSize,
			        ITSDataCounterPtr aDataCounter);


			/// <summary>
			/// 根据TSConfig配置写入写入数据，并可以指定是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE
			/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
			/// </summary>
			///  <param name="aTSPacketConfig">TS包的配置</param>
			/// <param name="aSrcData">数据区</param>
			/// <param name="FixFollowPayLoadUnitStart">是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE</param>
			/// <returns></returns>
			virtual ISWriteDataResults WriteData(TSPacketStructPtr aTSPacket, RawBufferPtr aSrcData, int aSrcDataSize,
			        ITSDataCounterPtr aDataCounter, bool aFixFollowPayLoadUnitStart);


			/// <summary>
			/// 根据TSConfig配置写入写入数据，并可以指定是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE
			/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
			/// </summary>
			///  <param name="aTSPacketConfig">TS包的配置</param>
			/// <param name="aSrcData">来源数据区</param>
			/// <param name="aSrcStartIndex">来源数据区开始索引</param>
			/// <param name="aSrcWriteLength">来源数据区写入长度</param>
			/// <param name="FixFollowPayLoadUnitStart">是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE</param>
			/// <returns></returns>
			virtual ISWriteDataResults WriteData(TSPacketStructPtr aSrcTSPacket, RawBufferPtr aSrcData,
			        int aSrcDataSize, int aSrcStartIndex, int aSrcWriteLength, ITSDataCounterPtr aDataCounter,
			        bool FixFollowPayLoadUnitStart);

			virtual int DumpToBuffer(RawBufferPtr aDataBuffer);


			/// <parama name="aStartOffSet">数据流中的起始位置</param>, int aStartOffSet
			/// <summary>
			/// 用于返回数据管理器中全部数据的长度
			/// </summary>
			/// <returns>数据管理器中全部数据的长度</returns>
			virtual int GetDumpDataSize();


			virtual void ClearData();
	};
}
#endif /*DEFAULTTSDATASTREAM_H_*/
