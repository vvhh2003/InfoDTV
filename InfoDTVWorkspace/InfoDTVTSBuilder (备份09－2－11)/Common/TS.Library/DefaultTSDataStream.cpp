/*
 * DefaultTSDataStream.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */


#include "DefaultTSDataStream.h"
using namespace TSLibrary;

DefaultTSDataStream::DefaultTSDataStream() :FDataManager(ITSStreamDataManagerPtr(new DefaultTSStreamDataManager()))
{
	FTSOperator = FDataManager->GetDataOperator();
}


DefaultTSDataStream::DefaultTSDataStream(ITSStreamDataManagerPtr aStreamDataManager) :
	FDataManager(aStreamDataManager)
{
	FTSOperator = FDataManager->GetDataOperator();
}

DefaultTSDataStream::DefaultTSDataStream(ITSStreamDataManagerPtr aStreamDataManager, ITSPacketDataOperatorPtr aTSOperator) :
	FDataManager(aStreamDataManager), FTSOperator(aTSOperator)
{
}


 ISWriteDataResults DefaultTSDataStream::InsertNullPacket()
 {
	 TSPacketStructPtr TmpPacket=FDataManager->GetNewNullDataPacket();
	 if (!TmpPacket)
		 return ISW_E_MEMORY;
	 return ISW_S_OK;
 }

 /// <summary>
 /// 写入制定PID数据并指示第一个包采用新包IsPayLoadUnitStart=true即TSPacketConfig的缺省配置
 /// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
 /// 另外除了第一个包的IsPayLoadUnitStart为True外，后面的包该属性都将为False.
 /// </summary>
 ///  <param name="aPID">需要写入的PID</param>
 /// <param name="aSrcData">来源数据区</param>
 /// <returns></returns>
 ISWriteDataResults DefaultTSDataStream::WriteData(unsigned short aPID, RawBufferPtr aSrcData, int aSrcDataSize,
		 ITSDataCounterPtr aDataCounter)
 {
	 if (aSrcDataSize == 0)
		 return ISW_E_OTHER;
	 TSPacketStructPtr TSPacket=TSPacketStruct::NewTSPacket(aPID, true);
	 //				std::cout<<TSPacket->GetPID()<<std::endl;
	 return WriteData(TSPacket, aSrcData,aSrcDataSize, aDataCounter, true);
 }


 /// <summary>
 /// 根据TSConfig配置写入写入数据，并可以指定是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE
 /// 注意：该方法将忽略其配置中调整字段（AdaptationFieldControlType）的属性
 /// </summary>
 ///  <param name="aTSPacketConfig">TS包的配置</param>
 /// <param name="aSrcData">数据区</param>
 /// <param name="FixFollowPayLoadUnitStart">是否修正第一个TS包之后TS包的IsPayLoadUnitStart属性将它们设置为FALSE</param>
 /// <returns></returns>
 ISWriteDataResults DefaultTSDataStream::WriteData(TSPacketStructPtr aTSPacket, RawBufferPtr aSrcData, int aSrcDataSize,
		 ITSDataCounterPtr aDataCounter, bool aFixFollowPayLoadUnitStart)
 {

	 return WriteData(aTSPacket, aSrcData, aSrcDataSize, 0, aSrcDataSize, aDataCounter,
			 aFixFollowPayLoadUnitStart);
 }


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
 ISWriteDataResults DefaultTSDataStream::WriteData(TSPacketStructPtr aSrcTSPacket, RawBufferPtr aSrcData,
		 int aSrcDataSize, int aSrcStartIndex, int aSrcWriteLength, ITSDataCounterPtr aDataCounter,
		 bool FixFollowPayLoadUnitStart)
 {
	 if (aSrcDataSize == 0)
		 return ISW_E_OTHER;
	 if (aSrcWriteLength == 0)
		 return ISW_E_OTHER;
	 if ((aSrcDataSize- aSrcStartIndex) < aSrcWriteLength)
		 return ISW_E_OTHER;

	 int ToWriteSize = aSrcWriteLength;
	 int WritedSize = aSrcStartIndex;
	 int PakcetDataCount = 0;


#ifdef DEBUG
	 int TSPacketCount = 0;
#endif
	 while (ToWriteSize> 0)
	 {
		 TSPacketStructPtr TmpPacket = FDataManager->GetNewDataPacket();
#ifdef DEBUG
		 TSPacketCount++;
#endif
		 if (!TmpPacket)
			 return ISW_E_MEMORY;
		 PakcetDataCount = FTSOperator->BuildTSPacket(aSrcTSPacket, TmpPacket, aDataCounter);

		 if (ToWriteSize < PakcetDataCount)
			 FTSOperator->WriteTSData(TmpPacket, aSrcData, WritedSize, ToWriteSize);
		 else
			 FTSOperator->WriteTSData(TmpPacket, aSrcData, WritedSize, PakcetDataCount);
		 ToWriteSize -= PakcetDataCount;
		 WritedSize += PakcetDataCount;

		 if (FixFollowPayLoadUnitStart)
		 {
			 aSrcTSPacket->Header.payload_unit_start_indicator = 0;
		 }
	 }

	 return ISW_S_OK;
 }

 int DefaultTSDataStream::DumpToBuffer(RawBufferPtr aDataBuffer)
 {
	 return FDataManager->DumpToBuffer(aDataBuffer);
 }


 /// <parama name="aStartOffSet">数据流中的起始位置</param>, int aStartOffSet
 /// <summary>
 /// 用于返回数据管理器中全部数据的长度
 /// </summary>
 /// <returns>数据管理器中全部数据的长度</returns>
 int DefaultTSDataStream::GetDumpDataSize()
 {
	 return FDataManager->GetDataSize();
 }


 void DefaultTSDataStream::ClearData()
 {
	 return FDataManager->Clear();
 }
