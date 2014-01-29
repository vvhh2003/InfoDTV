#ifndef DEFAULTPSIDATASTREAM_H_
#define DEFAULTPSIDATASTREAM_H_
#include "PSIInterface.h"

namespace TSLibrary
{
	namespace DVB
	{
		class DefaultPSIDataStream : public IPSIDataStream
		{
			public:
				virtual ~DefaultPSIDataStream()
				{

				}

				virtual PSISectionWriteResultRecordPtr SmartCutSectionLength(int aDataSize, bool IsLimitBy10Bit);


				/// <summary>
				/// 根据PSIConfig配置写入，写入数据自动封包生成数个Section并配置相应的CRC32，
				/// 其他类只需要将PSIHeadConfig的一些关键属性设置好，将内部数据写入即可
				/// 对于来源数据大于于MaxSectionLength的将自动在后续的Section中配置相应的PSIHeadConfig
				/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
				/// </summary>
				///  <param name="aTSStream">ITSDataStream 流</param>
				///  <param name="aPSIConfig">TS包的配置</param>
				///  <param name="aData">来源数据区</param>
				/// <returns></returns>
				virtual PSISectionWriteResultRecordPtr WriteAllSectionDataToTSStream(ITSDataStreamPtr aTSStream,
				        PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter, bool aIsSectionLimitBy10Bit,unsigned int RefLastSectionNumPos=0);
				/// <summary>
				/// 根据PSIConfig配置写入，写入数据但是只生成一个Section并配置相应的CRC32，
				/// 注意不需要设置PSIConfig的SectionLength，只需要设置WriteLength就可以了
				/// 其他类需要将PSIHeadConfig的一些关键属性设置好并且需要设置好起始SectionNumber,LastSectionNumber，然后将内部数据写入即可
				/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
				/// </summary>
				///  <param name="aTSStream">ITSDataStream 流</param>
				///  <param name="aPSIConfig">TS包的配置</param>
				///  <param name="aSrcData">来源数据区</param>
				/// <param name="aSrcStartIndex">来源数据需要写入的开始的索引</param>
				/// <param name="aWriteLength">来源数据需要写入的长度</param>
				/// <returns>返回写入的Section数量</returns>
				virtual PSISectionWriteResultRecordPtr WriteSpecialSectionDataToTSStream(ITSDataStreamPtr aTSStream,
				        PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
				        int aSrcStartIndex, int aWriteLength, ITSDataCounterPtr aDataCounter,
				        IPSICrc32CounterPtr aCrc32Counter);

				/// <summary>
				//  根据PSIConfig配置写入，写入数据的第一个Section,但是只生成一个Section并配置相应的CRC32，
				/// 其他类需要将PSIHeadConfig的一些关键属性设置好，特别是需要制定aRestDataLength
				/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
				/// </summary>
				///  <param name="aTSStream">ITSDataStream 流</param>
				///  <param name="aPSIConfig">TS包的配置</param>
				///  <param name="aSrcData">来源数据区</param>
				/// <param name="aSrcStartIndex">来源数据需要写入的开始的索引</param>
				/// <param name="aWriteLength">来源数据需要写入的长度</param>
				/// <param name="aRestDataLength">余下数据的长度</param>
				/// <returns></returns>
				virtual PSISectionWriteResultRecordPtr WriteFirstSectionDataToTSStream(ITSDataStreamPtr aTSStream,
				        PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
				        int aSrcStartIndex, int aWriteLength, int aRestDataLength, ITSDataCounterPtr aDataCounter,
				        IPSICrc32CounterPtr aCrc32Counter, bool aIsSectionLimitBy10Bit);


				/// <summary>
				/// 根据PSIConfig配置写入，余下的数据Section,写入数据自动封包生成数个Section并配置相应的CRC32，
				/// 其他类只需要将PSIHeadConfig的一些关键属性设置好，将内部数据写入即可
				/// 对于来源数据大于于MaxSectionLength的将自动在后续的Section中配置相应的PSIHeadConfig
				/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
				/// </summary>
				///  <param name="aTSStream">ITSDataStream 流</param>
				///  <param name="aPSIConfig">TS包的配置</param>
				///  <param name="aSrcData">来源数据区</param>
				/// <returns></returns>
				virtual PSISectionWriteResultRecordPtr WriteRestSectionDataTSStream(ITSDataStreamPtr aTSStream,
				        PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter, bool aIsSectionLimitBy10Bit);
		};
	}
}
#endif /*TSPACKETSTRUCT_H_*/
