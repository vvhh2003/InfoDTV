/*
 * DefaultPSIDataStream.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "DefaultPSIDataStream.h"
using namespace TSLibrary::DVB;


PSISectionWriteResultRecordPtr DefaultPSIDataStream::SmartCutSectionLength(int aDataSize, bool IsLimitBy10Bit)
{
	/*
	 *   TSHead    PSIH1   PSIH2     Data(...n)          Crc32
	 * |---------|-------|-------|_____________________|------|
	 *      4        3      5             n               4
	 * |------------------------------------------------------|
	 *                      188
	 * the first TS Packet has a Point_field which has 1Byte
	 * so:
	 *       -4 (-1) -3    -5                             -4
	 *   TSHead    PSIH1   PSIH2     Data(...n)          Crc32
	 * |---------|-------|-------|_____________________|------|
	 *      4        4      4             n               4
	 * |------------------------------------------------------|
	 *
	 * 最优解：
	 * sn(184-4-1+184N-4)=DataSize
	 * sn(175+184N)=DataSize
	 * SectionLenght=175+184n+8
	 */
	///经验公式 1013 2035 4079
	PSISectionWriteResultRecordPtr ResultRec(new PSISectionWriteResultRecord());
	//int CountSize = 0;
	int SectionLength;// = 0;
	int SectionNums;// = 0;
	if (IsLimitBy10Bit)
	{
		//  SectionLength =778+9;//why ？ I don't know
		SectionLength = 1014 + 9;
		// SectionLength = 300 + 9;

	}
	else
	{


		//if (aDataSize < 3378)
		//    SectionLength = aDataSize + 9;
		//else
		SectionLength = 3378+9;

	}

	if (aDataSize < SectionLength - 9)
	{
		SectionLength = aDataSize + 9;
		SectionNums = 1;
	}
	else
	{
		SectionNums = aDataSize / (SectionLength-9);
		if (aDataSize % (SectionLength-9) > 0)
			SectionNums++;
	}
	ResultRec->SectionLength = SectionLength;
	ResultRec->SectionNums = SectionNums;
	ResultRec->Result = PSISW_S_OK;

	return ResultRec;
}


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
PSISectionWriteResultRecordPtr DefaultPSIDataStream::WriteAllSectionDataToTSStream(ITSDataStreamPtr aTSStream,
		PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter, bool aIsSectionLimitBy10Bit)
{
	unsigned short NeedSectionNums;
	unsigned short TmpSectionLength;
	PSISectionWriteResultRecordPtr ResultRec=SmartCutSectionLength(aSrcDataLength,
			aIsSectionLimitBy10Bit);
	if (ResultRec->Result != PSISW_S_OK)
		return ResultRec;

	NeedSectionNums = ResultRec->SectionNums;
	TmpSectionLength = ResultRec->SectionLength;
	//					aPSIConfig-SectionLength = TmpSectionLength;
	aPSIHeaderConfig->PSIHeader.SetSectionLength(TmpSectionLength);
	//					aPSIConfig.LastSectionNumber = (byte)(NeedSectionNums-1); 因为aSrcData为全部数据
	aPSIHeaderConfig->PSIHeader.last_section_number=(unsigned char)(NeedSectionNums-1);

	for (unsigned char i=0; i<NeedSectionNums; i++)
	{
		//						aPSIConfig.SectionNumber = i;
		aPSIHeaderConfig->PSIHeader.section_number=i;
		PSISectionWriteResultRecordPtr SResult;
		if (i < NeedSectionNums-1) //区分最后一个Section
		{


			//							SResult = WriteSpecialSectionDataToTSStream(aTSStream, aPSIConfig, aSrcData, i
			//							        * (TmpSectionLength-9), TmpSectionLength - 9, aDataCounter, aCrc32Counter);
			SResult = WriteSpecialSectionDataToTSStream(aTSStream, aPSIHeaderConfig, aSrcData,
					aSrcDataLength, i * (TmpSectionLength-9), TmpSectionLength - 9, aDataCounter,
					aCrc32Counter);
			aTSStream->InsertNullPacket();
			aTSStream->InsertNullPacket();
		}
		else
		{

			int LastSectionDataLength;
			if (aSrcDataLength > TmpSectionLength - 9)
				LastSectionDataLength = aSrcDataLength - i * (TmpSectionLength - 9);
			else
				LastSectionDataLength = aSrcDataLength + 9;
			//							aPSIConfig.SectionLength = LastSectionDataLength;
			aPSIHeaderConfig->PSIHeader.SetSectionLength(LastSectionDataLength);
			SResult = WriteSpecialSectionDataToTSStream(aTSStream, aPSIHeaderConfig, aSrcData,
					aSrcDataLength, i * (TmpSectionLength-9), LastSectionDataLength-9, aDataCounter,
					aCrc32Counter);
			aTSStream->InsertNullPacket();
			aTSStream->InsertNullPacket();
		}
		if (SResult->Result != PSISW_S_OK)
			return SResult;
	}

	ResultRec->SectionLength = TmpSectionLength;
	ResultRec->SectionNums = NeedSectionNums;
	ResultRec->WriteLength = aSrcDataLength;
	ResultRec->Result = PSISW_S_OK;
	return ResultRec;
}
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
PSISectionWriteResultRecordPtr DefaultPSIDataStream::WriteSpecialSectionDataToTSStream(ITSDataStreamPtr aTSStream,
		PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
		int aSrcStartIndex, int aWriteLength, ITSDataCounterPtr aDataCounter,
		IPSICrc32CounterPtr aCrc32Counter)
{
	PSISectionWriteResultRecordPtr ResultRec(new PSISectionWriteResultRecord());
	ResultRec->SectionNums = aPSIHeaderConfig->PSIHeader.last_section_number+1;
	if (aWriteLength > aSrcDataLength-aSrcStartIndex)
	{
		ResultRec->Result = PSISW_E_BUFFER_SIZE_NOT_ENOUGH;
		return ResultRec;
	}
	ResultRec->SectionLength = aWriteLength + 9; //（SectionLength 后面5Byte的与Crc32的4Byte）
	aPSIHeaderConfig->PSIHeader.SetSectionLength(ResultRec->SectionLength);

	RawBufferPtr PSIDataBuffer((unsigned char *)std::malloc(aWriteLength+8+4),&free);
	//					FPSIOperator->BuildPSIHead(aPSIConfig, PSIHeader);
	//					byte[] PSIDataBuffer = new byte[aWriteLength+8+4];

	std::memset(PSIDataBuffer.get(), 0, aWriteLength+8+4);
	std::memcpy(PSIDataBuffer.get(), &aPSIHeaderConfig->PSIHeader, 8);
	//					Buffer.BlockCopy(PSIHeader, 0, PSIDataBuffer, 0, 8);
	void * TmpPtr=aSrcData.get()+aSrcStartIndex;
	void * TmpPSIDataBuffer=PSIDataBuffer.get()+8;
	//					Buffer.BlockCopy(aSrcData, aSrcStartIndex, PSIDataBuffer, 8, aWriteLength);
	std::memcpy(TmpPSIDataBuffer, TmpPtr, aWriteLength);


	unsigned long TmpWriteLength=aWriteLength+8;

	unsigned long CRC32ints =0;
	CRC32ints=aCrc32Counter->GetCrc32(PSIDataBuffer, TmpWriteLength);


	//  CRC32Bytes.CopyTo(PSIDataBuffer, aWriteLength + 8);
	//					Buffer.BlockCopy(CRC32Bytes, 0, PSIDataBuffer, aWriteLength + 8, 4);

	//					TmpPtr=&CRC32ints;
	//					TmpPSIDataBuffer=PSIDataBuffer.get()+aWriteLength + 8;
	//					std::memcpy(TmpPSIDataBuffer, TmpPtr, 4);

	unsigned char * TmpCPtr=(unsigned char *)&CRC32ints;
	unsigned char * TmpCPSIDataBuffer=PSIDataBuffer.get()+aWriteLength + 8;
	TmpCPSIDataBuffer[0]=TmpCPtr[3];
	TmpCPSIDataBuffer[1]=TmpCPtr[2];
	TmpCPSIDataBuffer[2]=TmpCPtr[1];
	TmpCPSIDataBuffer[3]=TmpCPtr[0];



	aTSStream->WriteData(aPSIHeaderConfig->PID, PSIDataBuffer, aWriteLength+8+4, aDataCounter);

	ResultRec->Result = PSISW_S_OK;
	return ResultRec;
}


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
PSISectionWriteResultRecordPtr DefaultPSIDataStream::WriteFirstSectionDataToTSStream(ITSDataStreamPtr aTSStream,
		PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
		int aSrcStartIndex, int aWriteLength, int aRestDataLength, ITSDataCounterPtr aDataCounter,
		IPSICrc32CounterPtr aCrc32Counter, bool aIsSectionLimitBy10Bit)
{
	PSISectionWriteResultRecordPtr ResultRec;
	//计算全部Section数量
	ResultRec = SmartCutSectionLength(aRestDataLength, aIsSectionLimitBy10Bit);
	if (ResultRec->Result != PSISW_S_OK)
		return ResultRec;
	aPSIHeaderConfig->PSIHeader.section_number = 0;
	aPSIHeaderConfig->PSIHeader.last_section_number = (unsigned char)(ResultRec->SectionNums); ////因为计算的是aRestDataLength为剩余数据所以不同于ALLData的情况不用-1
	ResultRec = WriteSpecialSectionDataToTSStream(aTSStream, aPSIHeaderConfig, aSrcData,
			aSrcDataLength, aSrcStartIndex, aWriteLength, aDataCounter, aCrc32Counter);
	return ResultRec;
}


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
PSISectionWriteResultRecordPtr DefaultPSIDataStream::WriteRestSectionDataTSStream(ITSDataStreamPtr aTSStream,
		PSIHeaderConfigStructPtr aPSIHeaderConfig, RawBufferPtr aSrcData, int aSrcDataLength,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter, bool aIsSectionLimitBy10Bit)
{
	int NeedSectionNums;
	int TmpSectionLength;
	PSISectionWriteResultRecordPtr ResultRec;
	if(aSrcDataLength==0)
	{
		ResultRec->SectionLength=0;
		ResultRec->WriteLength=0;
		ResultRec->Result=PSISW_E_BUFFER_SIZE_NOT_ENOUGH;
		return ResultRec;
	}

	ResultRec = SmartCutSectionLength(aSrcDataLength, aIsSectionLimitBy10Bit);
	if (ResultRec->Result != PSISW_S_OK)
		return ResultRec;

	NeedSectionNums = ResultRec->SectionNums; //All Section Numbers
	TmpSectionLength = ResultRec->SectionLength;
	//					aPSIConfig.SectionLength = TmpSectionLength;
	aPSIHeaderConfig->PSIHeader.SetSectionLength(TmpSectionLength);


	//					aPSIConfig.LastSectionNumber = (unsigned char)(NeedSectionNums );//因为后续从1开始的

	aPSIHeaderConfig->PSIHeader.last_section_number=(unsigned char)(NeedSectionNums );//因为后续从1开始的
	for (unsigned char i = 0; i < NeedSectionNums; i++) //从0开始 因为aSrcData已经全部为剩余数据了所以从0开始
	{


		//						aPSIConfig.SectionNumber = (byte)(i+1);
		aPSIHeaderConfig->PSIHeader.section_number = (unsigned char)(i+1);
		PSISectionWriteResultRecordPtr SResult;
		if (i < NeedSectionNums - 1) //区分最后一个Section
		{

			SResult = WriteSpecialSectionDataToTSStream(aTSStream, aPSIHeaderConfig, aSrcData,
					aSrcDataLength, i * (TmpSectionLength-9), TmpSectionLength-9, aDataCounter,
					aCrc32Counter);
			aTSStream->InsertNullPacket();
			aTSStream->InsertNullPacket();

		}
		else
		{

			int LastSectionDataLength;
			if (aSrcDataLength > TmpSectionLength - 9)
				LastSectionDataLength = aSrcDataLength - i * (TmpSectionLength - 9)+9;
			else
				LastSectionDataLength = aSrcDataLength + 9;
			//							aPSIConfig.SectionLength = LastSectionDataLength;
			aPSIHeaderConfig->PSIHeader.SetSectionLength(LastSectionDataLength);
			SResult = WriteSpecialSectionDataToTSStream(aTSStream, aPSIHeaderConfig, aSrcData,
					aSrcDataLength, i * (TmpSectionLength-9), LastSectionDataLength-9, aDataCounter,
					aCrc32Counter);
			aTSStream->InsertNullPacket();
			aTSStream->InsertNullPacket();
		}
		if (SResult->Result != PSISW_S_OK)
			return SResult;
	}
	ResultRec->Result = PSISW_S_OK;
	return ResultRec;
}
