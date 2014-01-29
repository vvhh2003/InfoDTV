/*
 * DONE!
 */
#ifndef DEFAULTTSSTREAMDATAMANAGER_H_
#define DEFAULTTSSTREAMDATAMANAGER_H_
#include "MPEGInterface.h"
#include "DefaultTSPacketDataOperator.h"
#include <vector>

namespace TSLibrary
{

	/// <summary>
	/// 缺省TSStreamDataManager使用ArrayList作为分配项目,并且使用简单锁机制
	/// </summary>
	class DefaultTSStreamDataManager :public ITSStreamDataManager
	{
		/// <summary>
		/// 缺省数据池
		/// </summary>
		private:
		std::vector<TSPacketStructPtr> FDataPool;
		ITSPacketDataOperatorPtr FDataOperator;//=new DefaultTSPacketDataOperator();

		/// <summary>
		/// 返回用于内存管理器的数据操作器
		/// </summary>
		public:
		DefaultTSStreamDataManager():FDataPool(),FDataOperator(new DefaultTSPacketDataOperator)
		{

		}

		virtual ~DefaultTSStreamDataManager()
		{

		}

		virtual ITSPacketDataOperatorPtr GetDataOperator();

		/// <summary>
		/// 增加新包的内存区域
		/// </summary>
		/// <returns>小于0表示内存分配未成功。大于等于0表示内存块的索引</returns>
		virtual int AddDataPacket();
		/// <summary>
		/// 通过索引得到一个188长度的TS数据包
		/// </summary>
		/// <param name="aIndex">索引</param>
		/// <returns>188长度的TS数据包</returns>
		virtual TSPacketStructPtr GetDataPacketByIndex(int aIndex);

		/// <summary>
		/// 添加一个188长度的TS数据包到数据管理器中
		/// </summary>
		/// <returns>188长度的TS数据包</returns>
		virtual TSPacketStructPtr GetNewNullDataPacket();

		/// <summary>
		/// 添加一个188长度的TS数据包到数据管理器中
		/// </summary>
		/// <returns>188长度的TS数据包</returns>
		virtual TSPacketStructPtr GetNewDataPacket();
		/// <summary>
		/// 将数据管理器中全部数据写入一个缓冲区
		/// </summary>
		/// <param name="aDataBuffer">数据缓冲区</param>
		/// <returns>返回实际写入的字节数</returns>
		virtual int DumpToBuffer(RawBufferPtr aDataBuffer);

		/// <summary>
		/// 用于返回数据管理器中全部数据的长度
		/// </summary>
		/// <returns>数据管理器中全部数据的长度</returns>
		virtual int GetDataSize();

		/// <summary>
		/// 返回数据管理器中的TS包数量
		/// </summary>
		/// <returns>数据管理器中的TS包数量若不知道数量则返回-1</returns>
		virtual int GetPacketCounts();

		virtual void Clear();
	};
}
#endif /*DEFAULTTSSTREAMDATAMANAGER_H_*/
