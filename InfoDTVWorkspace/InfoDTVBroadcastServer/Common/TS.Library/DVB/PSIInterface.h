#ifndef PSIINTERFACE_H_
#define PSIINTERFACE_H_

#include <boost/shared_ptr.hpp>
#include "../../TSPacketStruct.h"
#include "../MPEGInterface.h"

namespace TSLibrary
{
	namespace DVB
	{
		inline unsigned char getBCDByte(const unsigned char value)
		{
			if(value>100)
				return 0;
			unsigned char Tmp8Bit=value/10;
			unsigned char Tmp10=Tmp8Bit*16;
			Tmp10=Tmp10+(value-(Tmp8Bit*10));
			return Tmp10;
		}

		enum PSISectionWriteResults
		{
			PSISW_S_OK,
			PSISW_E_MEMORY,
			/// <summary>
			/// 来源数据长度不够填充Section
			/// </summary>
			PSISW_E_BUFFER_SIZE_NOT_ENOUGH,
			/// <summary>
			/// 分配的Section长度能容纳来源数据的长度
			/// </summary>
			PSISW_E_SECTION_SIZE_NOT_ENOUGH
		};

		struct PSISectionWriteResultRecord
		{
				PSISectionWriteResults Result;
				unsigned short SectionLength;
				unsigned short SectionNums;
				/// <summary>
				/// 写入TS流中的长度
				/// </summary>
				unsigned long long WriteLength;
		};
		typedef boost::shared_ptr<PSISectionWriteResultRecord> PSISectionWriteResultRecordPtr;

		struct PSIHeaderStruct;
		typedef boost::shared_ptr<PSIHeaderStruct> PSIHeaderStructPtr;


		/// <summary>
		/// 使用时还须加上包头8个字节
		/// </summary>
		const int PSIMaxSectionLength = 4007;
		const int PSIFirtTSPacketLength=171;
		const int PSIRestTSPacketLength = 184;
		/// <summary>
		/// 使用时还须加上包头8个字节
		/// </summary>
		const int PSIMax10BitSectionLength = 1007;
		/// <summary>
		/// 符合ISO13818-1的PSI表的一些公用参数
		/// </summary>
		struct PSIHeaderStruct
		{

			public:
				unsigned table_id :8;

				unsigned section_length_Hi :4;
				unsigned reserved3BitFiled3 :1;
				unsigned reserved3BitFiled2 :1;
				unsigned reserved3BitFiled1 :1;
				unsigned section_syntax_indicator :1;

				unsigned section_length_Lo :8;

				/// <summary>
				/// 也就是PAT中的transport_stream_id； PMT中的program_number；CAT 中的reserved ;NIT中的network_id;
				/// SDT中的tran_stream_id;
				/// infoDTV中的Table_extension_id
				/// </summary>
				unsigned Special_ID_Field_Hi :8;
				unsigned Special_ID_Field_Lo :8;
				/// <summary>
				/// 私有段指示位置false表示后续全部为私有段，true表示私有段跟随PAT等规则表格段后面
				/// </summary>
				unsigned current_next_indicator :1;
				unsigned version_number :5;
				//保留的2个BIT
				unsigned reserved2BitFiled2 :1;
				unsigned reserved2BitFiled1 :1;

				unsigned section_number :8;
				unsigned last_section_number :8;


				/// <summary>
				/// 针对一个PID与TableID初始化一个PSI Section 头。
				/// </summary>
				/// <param name="aPID">使用该PID配置默认的TSPacketConfig</param>
				/// <param name="aTableID">使用的TableID</param>
				/// <param name="aSectionSyntaxIndicator">aSectionSyntaxIndicator</param>
				static PSIHeaderStructPtr NewPSIHeaderStruct(unsigned char aTableID, unsigned short aTableExtID,
				        bool aSectionSyntaxIndicator)
				{
					PSIHeaderStructPtr Result(new PSIHeaderStruct);
//					Result->PSIHeadLastPartData[0]=0;
//					Result->PSIHeadLastPartData[1]=0;
//					Result->PSIHeadLastPartData[2]=0;
//					Result->PSIHeadLastPartData[3]=0;
//					Result->PSIHeadLastPartData[4]=0;
					Result->table_id=aTableID;
					Result->Special_ID_Field_Hi = aTableExtID>>8;
					Result->Special_ID_Field_Lo = aTableExtID&0x00ff;
					if (aSectionSyntaxIndicator)
						Result->section_syntax_indicator = 1;
					else
						Result->section_syntax_indicator = 0;

					Result->reserved3BitFiled1 = 0;//"0"
					Result-> reserved3BitFiled2 = 1;
					Result->reserved3BitFiled3 = 1;

					Result->reserved2BitFiled1 = 1;
					Result->reserved2BitFiled2 = 1;

					Result->version_number = 0;
					Result->current_next_indicator = 1;
					//自动计算部分的初始化
					Result->section_length_Lo = 0;
					Result->section_length_Hi = 0;
					Result->last_section_number = 0;
					Result->section_number = 0;

					return Result;
				}

				static void FastCopyToBuffer(PSIHeaderStructPtr aTmpPSIHeader, unsigned char * aBuffer)
				{
					std::memcpy((void *)aBuffer, (void *)aTmpPSIHeader.get(), 8);
				}

				static void FastClone(PSIHeaderStructPtr aSrcPSIHeader, PSIHeaderStructPtr aDestPSIHeader)
				{
					std::memcpy((void *)aDestPSIHeader.get(), (void *)aSrcPSIHeader.get(), 8);
				}

				inline void SetSectionLength(unsigned short aSectionLength)
				{
					section_length_Hi=aSectionLength>>8;
					section_length_Lo=aSectionLength&0x00ff;
				}

				inline void SetTableExtID(unsigned short aTableID)
				{
					Special_ID_Field_Hi=aTableID>>8;
					Special_ID_Field_Lo=aTableID&0x00ff;
				}

		};

		struct PSIHeaderConfigStruct;
		typedef boost::shared_ptr<PSIHeaderConfigStruct> PSIHeaderConfigStructPtr;
		struct PSIHeaderConfigStruct
		{
			public:
				unsigned short PID;
				PSIHeaderStruct PSIHeader;
				static PSIHeaderConfigStructPtr NewPSIHeaderConfigStruct(unsigned short aPID, unsigned char aTableID,
				        unsigned short aTableExtID, bool aSectionSyntaxIndicator,bool aIsDVB=true)
				{
					PSIHeaderConfigStructPtr Result(new PSIHeaderConfigStruct);
					Result->PID=aPID;
//					std::memset(&Result->PSIHeader, 0, 8);
					Result->PSIHeader.table_id=aTableID;
					Result->PSIHeader.Special_ID_Field_Hi = aTableExtID>>8;
					Result->PSIHeader.Special_ID_Field_Lo = aTableExtID&0x00ff;
					if (aSectionSyntaxIndicator)
						Result->PSIHeader.section_syntax_indicator = 1;
					else
						Result->PSIHeader.section_syntax_indicator = 0;

					if(aIsDVB)
						Result->PSIHeader.reserved3BitFiled1 = 1;//0; //"0"
					else
						Result->PSIHeader.reserved3BitFiled1 = 0;
					Result->PSIHeader.reserved3BitFiled2 = 1;
					Result->PSIHeader.reserved3BitFiled3 = 1;

					Result->PSIHeader.reserved2BitFiled1 = 1;
					Result->PSIHeader.reserved2BitFiled2 = 1;

					Result->PSIHeader.version_number = 0;
					Result->PSIHeader.current_next_indicator = 1;
					//自动计算部分的初始化
					Result->PSIHeader.section_length_Lo = 0;
					Result->PSIHeader.section_length_Hi = 0;
					Result->PSIHeader.last_section_number = 0;
					Result->PSIHeader.section_number = 0;
					return Result;
				}

				static PSIHeaderConfigStructPtr NewPSIHeaderConfigStruct(unsigned short aPID, unsigned char aTableID,
						unsigned char aTableExtIDHi,unsigned char aTableExtIDLo, bool aSectionSyntaxIndicator,bool aIsDVB=true)
				{
					PSIHeaderConfigStructPtr Result(new PSIHeaderConfigStruct);
					Result->PID=aPID;
					Result->PSIHeader.table_id=aTableID;
					Result->PSIHeader.Special_ID_Field_Hi =aTableExtIDHi;
					Result->PSIHeader.Special_ID_Field_Lo = aTableExtIDLo;
					if (aSectionSyntaxIndicator)
						Result->PSIHeader.section_syntax_indicator = 1;
					else
						Result->PSIHeader.section_syntax_indicator = 0;

					if(aIsDVB)
						Result->PSIHeader.reserved3BitFiled1 = 1;//0; //"0"
					else
						Result->PSIHeader.reserved3BitFiled1 = 0;
					Result->PSIHeader.reserved3BitFiled2 = 1;
					Result->PSIHeader.reserved3BitFiled3 = 1;

					Result->PSIHeader.reserved2BitFiled1 = 1;
					Result->PSIHeader.reserved2BitFiled2 = 1;

					Result->PSIHeader.version_number = 0;
					Result->PSIHeader.current_next_indicator = 1;
					//自动计算部分的初始化
					Result->PSIHeader.section_length_Lo = 0;
					Result->PSIHeader.section_length_Hi = 0;
					Result->PSIHeader.last_section_number = 0;
					Result->PSIHeader.section_number = 0;
					return Result;
				}
		};


		/// <summary>
		/// IPSICrc32Counter 提供MPEG的CRC32计算。
		/// </summary>
		class IPSICrc32Counter
		{

			public:
				virtual ~IPSICrc32Counter()
				{
				}
				;
				/// <summary>
				/// 计算数据的MPEG CRC32值
				/// </summary>
				/// <param name="aData">数据块区域</param>
				/// <param name="uLength">数据块从索引0开始的长度</param>
				/// <returns></returns>
				virtual unsigned long GetCrc32(RawBufferPtr aData, unsigned long uLength) =0;
		};

		typedef boost::shared_ptr<IPSICrc32Counter> IPSICrc32CounterPtr;

		class IPSIDataStream
		{

			public:
				virtual ~IPSIDataStream()
				{
				}
				;
				/// <summary>
				/// 返回一个优化后的Section长度，主要是用于对其188个TS包，尽力避免TS包中出现空字节
				/// </summary>
				/// <param name="aDataSize">实际数据长度</param>
				/// <returns></returns>
				virtual PSISectionWriteResultRecordPtr SmartCutSectionLength(int aDataSize, bool IsLimitBy10Bit)=0;

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
				virtual PSISectionWriteResultRecordPtr
				        WriteAllSectionDataToTSStream(ITSDataStreamPtr aTSStream,
				                PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aData, int aSrcDataLength,
				                ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter,
				                bool aIsSectionLimitBy10Bit,unsigned int RefLastSectionNumPos=0)=0;

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
				        PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aData, int aSrcDataLength,
				        int aSrcStartIndex, int aWriteLength, ITSDataCounterPtr aDataCounter,
				        IPSICrc32CounterPtr aCrc32Counter)=0;

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
				        PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aData, int aSrcDataLength,
				        int aSrcStartIndex, int aWriteLength, int aRestDataLength, ITSDataCounterPtr aDataCounter,
				        IPSICrc32CounterPtr aCrc32Counter, bool aIsSectionLimitBy10Bit)=0;

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
				virtual PSISectionWriteResultRecordPtr
				        WriteRestSectionDataTSStream(ITSDataStreamPtr aTSStream,
				                PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aData, int aSrcDataLength,
				                ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter,
				                bool aIsSectionLimitBy10Bit)=0;
		};

		typedef boost::shared_ptr<IPSIDataStream> IPSIDataStreamPtr;


		/// <summary>
		/// 该接口提供一次性写入到PSIStream中的能力
		/// </summary>
		class IPSIStreamWriteAble
		{

			public:
				virtual ~IPSIStreamWriteAble()
				{
				}
				;
				/// <summary>
				/// 将属性数据全部发送到相应的流中
				/// </summary>
				/// <param name="aTSStream">ITSDataStream</param>
				/// <param name="aStream">IPSIDataStream</param>
				/// <param name="aDataCounter">aDataCounter</param>
				virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)=0;

		};


		/// <summary>
		/// 提供分此写入到PSIStream中的能力
		/// </summary>
		class IPSIStreamPartWriteAble : virtual public IPSIStreamWriteAble
		{

			public:
				virtual void TransferHeadTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)=0;
				virtual void TransferRestPartTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)=0;
		};
	}
}

#endif /*PSIINTERFACE_H_*/
