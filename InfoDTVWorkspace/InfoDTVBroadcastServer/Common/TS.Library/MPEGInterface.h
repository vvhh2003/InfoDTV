#ifndef MPEGINTERFACE_
#define MPEGINTERFACE_
#include <boost/shared_ptr.hpp>
#include "../TSPacketStruct.h"
namespace TSLibrary
{
	enum ISWriteDataResults
	{

		ISW_S_OK,//写入成功
		ISW_E_MEMORY,//内存分配出错
		ISW_E_OTHER//其他错误
	};


	/// <summary>
	/// 提供对ITSStream的计数器支持
	/// </summary>
	class ITSDataCounter
	{
		public:
			virtual ~ITSDataCounter()
			{
			}
			;
			/// <summary>
			/// 取得计数器当前数值
			/// </summary>
			/// <returns>计数器当前数值</returns>
			virtual unsigned char GetNextCounter()=0;
	};

	typedef boost::shared_ptr<ITSDataCounter> ITSDataCounterPtr;
	/// <summary>
	/// 负责对TS的原始字节数据进行操作，必须与TSDataManager配合使用
	/// </summary>
	class ITSPacketDataOperator
	{
		public:
			virtual ~ITSPacketDataOperator()
			{
			}
			;

			/// <summary>
			/// 根据TSConfig配置一个TS数据包，没有调整字段
			/// </summary>
			/// <param name="aTSConfig">TSConfig配置</param>
			/// <param name="aTSPacket">TS包的缓冲</param>
			/// <param name="aDataCounter">外部的计数器</param>
			/// <returns>该TS包中可以写入的大小，小于0为出错</returns>
			virtual int BuildTSPacket(TSPacketStructPtr aSrcTSPacket,TSPacketStructPtr aDestTSPacket, ITSDataCounterPtr aDataCounter)=0;

			/// <summary>
			/// 将来源数据写入一个没有调整字段TS包的数据区域（一共184字节或者183字节）
			/// </summary>
			/// <param name="aTSPacket">TS包</param>
			/// <param name="aSrcData">来源数据</param>
			/// <param name="aStartIndex">来源数据中起始的索引</param>
			/// <param name="aWriteSize">需要写入的大小</param>
			/// <returns>写入TS包的字节数，小于0为出错</returns>
			virtual int WriteTSData(TSPacketStructPtr aTSPacket, RawBufferPtr aSrcData,int aStartIndex, int aWriteSize)=0;
	};

	typedef boost::shared_ptr<ITSPacketDataOperator> ITSPacketDataOperatorPtr;
	/// <summary>
	/// 统一的TS流数据的内存管理器
	/// ITSStreamDataManager，管理N个188大小的vector<TSPacketStructPtr>缓冲区TSPacketStruct，
	/// 它将进行增加减少缓冲区操作
	/// </summary>
	class ITSStreamDataManager
	{
		public:
			virtual ~ITSStreamDataManager()
			{
			}
			;

			/// <summary>
			/// 返回用于内存管理器的数据操作器
			/// </summary>
			virtual ITSPacketDataOperatorPtr GetDataOperator()=0;
			/// <summary>
			/// 增加新包的内存区域
			/// </summary>
			/// <returns>小于0表示内存分配未成功。大于等于0表示内存块的索引</returns>
			virtual int AddDataPacket()=0;

			/// <summary>
			/// 通过索引得到一个188长度的TS数据包
			/// </summary>
			/// <param name="aIndex">索引</param>
			/// <returns>188长度的TS数据包</returns>
			virtual TSPacketStructPtr GetDataPacketByIndex(int aIndex)=0;

			/// <summary>
			/// 添加一个188长度的TS数据包到数据管理器中
			/// </summary>
			/// <returns>188长度的TS数据包,返回NULL为内存失败</returns>
			virtual TSPacketStructPtr GetNewDataPacket()=0;

			virtual TSPacketStructPtr GetNewNullDataPacket()=0;


			/// <summary>
			/// 从数据管理器中删除一个188长度的数据包
			/// </summary>
			/// <returns>小于0表示失败或其他意义，大于零表示成功</returns>
			/// virtual int DeleteDataPacketByIndex(int aIndex)=0;

			/// <summary>
			/// 将数据管理器中全部数据写入一个缓冲区,该缓冲区需要事先分配好，必须大于等于数据管理器的数据的长度
			/// </summary>
			/// <param name="aDataBuffer">数据缓冲区</param>
			/// <returns>返回实际写入的字节数</returns>
			virtual int DumpToBuffer(RawBufferPtr aDataBuffer)=0;

			/// <summary>
			/// 将数据管理器中全部数据写入一个数据流
			/// </summary>
			/// <param name="aStream">数据流</param>
			/// void DumpToStream(Stream aStream); /// <parama name="aStartOffSet">数据流中的起始位置</param>,int aStartOffSet

			/// <summary>
			/// 用于返回数据管理器中全部数据的长度
			/// </summary>
			/// <returns>数据管理器中全部数据的长度</returns>
			virtual int GetDataSize()=0;

			/// <summary>
			/// 返回数据管理器中的TS包数量
			/// </summary>
			/// <returns>数据管理器中的TS包数量若不知道数量则返回-1</returns>
			virtual int GetPacketCounts()=0;


			virtual void Clear()=0;
	};

	typedef boost::shared_ptr<ITSStreamDataManager> ITSStreamDataManagerPtr;


	/// <summary>
	/// 提供对于TS层访问的封装
	/// 对于其他需要打包到TS的类而言，只需要对ITSStream接口进行相应操作即可
	/// </summary>
	class ITSDataStream
	{
		public:

			virtual ~ITSDataStream()
			{
			}
			;
			/// <summary>
			/// 插入空包
			/// </summary>
			/// <returns></returns>
			virtual ISWriteDataResults InsertNullPacket()=0;

			/// <summary>
			/// 写入指定PID数据并指示第一个包采用新包IsPayLoadUnitStart=true即TSPacketConfig的缺省配置
			/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
			/// 另外除了第一个包的IsPayLoadUnitStart为True外，后面的包该属性都将为False.
			/// </summary>
			///  <param name="aPID">需要写入的PID</param>
			/// <param name="aSrcData">来源数据区</param>
			///
			/// <returns></returns>
			virtual ISWriteDataResults WriteData(unsigned short aPID, RawBufferPtr aSrcData, int aSrcDataSize,
			        ITSDataCounterPtr aDataCounter)=0;

			/// <summary>
			/// 根据TSConfig配置写入写入数据，并可以指定是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE
			/// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
			/// </summary>
			///  <param name="aTSPacketConfig">TS包的配置</param>
			/// <param name="aSrcData">来源数据区</param>
			/// <param name="FixFollowPayLoadUnitStart">是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE</param>
			/// <returns></returns>
			virtual ISWriteDataResults WriteData(TSPacketStructPtr aTSPacketHeadConfig, RawBufferPtr aSrcData,
			        int aSrcDataSize, ITSDataCounterPtr aDataCounter, bool FixFollowPayLoadUnitStart)=0;

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
			virtual ISWriteDataResults WriteData(TSPacketStructPtr aTSPacketHeaderConfig, RawBufferPtr aSrcData,
			        int aSrcDataSize, int aSrcStartIndex, int aSrcWriteLength, ITSDataCounterPtr aDataCounter,
			        bool FixFollowPayLoadUnitStart)=0;

			/// <summary>
			/// 将数据管理器中全部数据写入一个缓冲区,该缓冲区需要事先分配好，必须大于等于数据管理器的数据的长度
			/// </summary>
			/// <param name="aDataBuffer">数据缓冲区</param>
			/// <returns>返回实际写入的字节数</returns>
			virtual int DumpToBuffer(RawBufferPtr aDataBuffer)=0;

			/// <summary>
			/// 用于返回数据管理器中全部数据的长度
			/// </summary>
			/// <returns>数据管理器中全部数据的长度</returns>
			virtual int GetDumpDataSize()=0;

			virtual void ClearData()=0;

	};

	typedef boost::shared_ptr<ITSDataStream> ITSDataStreamPtr;
}
#endif /*MPEGINTERFACE_*/
