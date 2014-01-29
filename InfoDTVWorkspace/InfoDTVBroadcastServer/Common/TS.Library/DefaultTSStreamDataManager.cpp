/*
 * DefaultTSStreamDataManager.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */


#include "DefaultTSStreamDataManager.h"
using namespace TSLibrary;
ITSPacketDataOperatorPtr DefaultTSStreamDataManager:: GetDataOperator()
{
	return FDataOperator;
}

/// <summary>
/// 增加新包的内存区域
/// </summary>
/// <returns>小于0表示内存分配未成功。大于等于0表示内存块的索引</returns>
int DefaultTSStreamDataManager::AddDataPacket()
{
	FDataPool.push_back(TSPacketStructPtr(new TSPacketStruct));
	//FDataPool.push_back(TSPacketStruct::NewNullTSPacket());
	return FDataPool.size()-1;
}


/// <summary>
/// 通过索引得到一个188长度的TS数据包
/// </summary>
/// <param name="aIndex">索引</param>
/// <returns>188长度的TS数据包</returns>
TSPacketStructPtr DefaultTSStreamDataManager::GetDataPacketByIndex(int aIndex)
{
	return FDataPool[aIndex];
}


/// <summary>
/// 添加一个188长度的TS数据包到数据管理器中
/// </summary>
/// <returns>188长度的TS数据包</returns>
TSPacketStructPtr DefaultTSStreamDataManager::GetNewNullDataPacket()
{
	FDataPool.push_back(TSPacketStructPtr(TSPacketStruct::NewNullTSPacket()));
	return FDataPool[FDataPool.size() - 1];
}


/// <summary>
/// 添加一个188长度的TS数据包到数据管理器中
/// </summary>
/// <returns>188长度的TS数据包</returns>
TSPacketStructPtr DefaultTSStreamDataManager::GetNewDataPacket()
{
	FDataPool.push_back(TSPacketStructPtr(new TSPacketStruct));
	return FDataPool[FDataPool.size() - 1];
}

/// <summary>
/// 将数据管理器中全部数据写入一个缓冲区
/// </summary>
/// <param name="aDataBuffer">数据缓冲区</param>
/// <returns>返回实际写入的字节数</returns>
int DefaultTSStreamDataManager::DumpToBuffer(RawBufferPtr aDataBuffer)
{
	int Count;
	for (unsigned int i = 0; i < FDataPool.size(); i++)
	{
		//Buffer.BlockCopy(FDataPool[i],0,aDataBuffer, i * 188,188);
		TSPacketStructPtr Tmp=FDataPool[i];
		unsigned char * TmpBufferPtr=aDataBuffer.get()+i*188;
		TSPacketStruct::FastCopyToBuffer(Tmp,TmpBufferPtr);
	}
	Count = FDataPool.size();
	return Count * 188;
}


/// <summary>
/// 用于返回数据管理器中全部数据的长度
/// </summary>
/// <returns>数据管理器中全部数据的长度</returns>
int DefaultTSStreamDataManager::GetDataSize()
{
	return FDataPool.size()*188;
}

/// <summary>
/// 返回数据管理器中的TS包数量
/// </summary>
/// <returns>数据管理器中的TS包数量若不知道数量则返回-1</returns>
int DefaultTSStreamDataManager::GetPacketCounts()
{
	return FDataPool.size();
}

void DefaultTSStreamDataManager::Clear()
{
	FDataPool.clear();
	std::vector<TSPacketStructPtr>(FDataPool).swap(FDataPool);
}
