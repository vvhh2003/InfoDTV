/*
 * Test.h
 *
 *  Created on: 2009-2-24
 *      Author: victor
 */

#ifndef TEST_H_
#define TEST_H_
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include <iostream>
#include "Common/TS.Library/DVB-PSI/PATTable.h"
#include "Common/TS.Library/DefaultDataCounter.h"
#include "Common/TS.Library/DefaultTSDataStream.h"
#include "Common/TS.Library/DVB/DefaultPSICrc32Counter.h"
#include "Common/TS.Library/DVB/PSIInterface.h"
#include "Common/TS.Library/DVB/CommonPSIInclude.h"
#include "DataProviders/SPTSFileDataProvider/SPTSFileDataProvider.h"
#include <string>

#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"


inline void TESTProvider()
{
//	SPTSFileConfigObjectPtr COPtr(new  SPTSFileConfigObject);
//	ITSDataProviderPtr TmpPtr(new SPTSFileDataProvider(COPtr,FGlobalSPTSFileDB));
}

inline void TESTPocoPath()
{
	Poco::Path FP("/home/victor/tt.xe");

	cout<<Poco::toUpper(FP.getExtension())<<endl;
	cout<<FP.getFileName()<<endl;
}

inline void TESTStringToken()
{
	string tt="TT?192.168.1.1?2300";
	Poco::StringTokenizer ST(tt,"?",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	std::cout<<ST.count()<<endl;
	std::cout<<ST[0]<<endl;
	std::cout<<ST[1]<<endl;
	std::cout<<ST[2]<<endl;
	tt="TT";
	Poco::StringTokenizer ST1(tt,"?",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	std::cout<<ST1[0]<<endl;
}

inline void TESTSendBuffer()
{
	/*
	 * 1、计算长度拆分 是否能被188＊7整除 得到 SendCountBy188X7
	 * 2、若不能被188＊7整除 SendCountBy188X7＋＝1
	 * 3、循环开始
	 * 4、是否是最后一次循环＝＝SendCountBy188X7 ，若是构造一个188X7的缓冲区将最后部分复制到其中，然后发送
	 * 5、若否发送i*188*7位置的长度为188＊7的数据。
	 */
	unsigned int AiBufferLength=188*100*8;

	unsigned int SendCountBy188X7=AiBufferLength/(188*7);
	cout<<"  初始循环次数："<<SendCountBy188X7<<endl;
	unsigned int RestBytes=AiBufferLength-SendCountBy188X7*188*7;
	SendCountBy188X7+=(RestBytes>0 ? 1 : 0);
	unsigned int RepairePacketCount=(AiBufferLength-RestBytes)/188;
	cout<<"总长度："<<AiBufferLength<<"  循环次数："<<SendCountBy188X7<<" 整除188＊7剩余字节："<<RestBytes<<" 是否+1:"<<(RestBytes>0 ? 1 : 0)<<" 补充:"<<RepairePacketCount<<endl;

	for (unsigned int i=0; i<SendCountBy188X7; i++)
	{
		if(RestBytes>0&&i==(SendCountBy188X7-1))
		{

			cout<<"序号："<<i<<"最后输出:"<<RestBytes<<endl;
			cout<<"需要补充:"<<188*7-RestBytes<<endl;
		}
		else
		{

			cout<<"序号："<<i<<" 标准输出位置:"<<i*188*7<<" 输出："<<188*7<<endl;
		}
	}
}


inline void testInfoDTV()
{
	TSLibrary::DVB::PSI::PATTable PATA;

	TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
	TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());
	TSLibrary::ITSDataStreamPtr FTSStreamPtr(new TSLibrary::DefaultTSDataStream());

	TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
	PATA.TransferTo(FTSStreamPtr,FPSIStreamPtr,FDataCounter,FCrc32Counter);
}

inline unsigned char getBCDByte(const unsigned char value)
{
	if(value>100)
		return 0;
	unsigned char Tmp8Bit=value/10;
	unsigned char Tmp10=Tmp8Bit*16;
	Tmp10=Tmp10+(value-(Tmp8Bit*10));
	return Tmp10;
}

inline void TestCrcBug2()
{


	TSLibrary::ITSDataStreamPtr aTSStream(new TSLibrary::DefaultTSDataStream());
	TSLibrary::DVB::PSIHeaderConfigStructPtr aPSIHeaderConfig=TSLibrary::DVB::PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(0x14, 0x73,
			0, true);

   RawBufferPtr aSrcData((unsigned char *)std::malloc(17),&free);
   unsigned int aSrcDataLength=17;
   unsigned int aSrcStartIndex=0;
   unsigned int aWriteLength=17;
   TSLibrary::ITSDataCounterPtr aDataCounter(new TSLibrary::DefaultDataCounter());
   TSLibrary::DVB::IPSICrc32CounterPtr aCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());

		if (aWriteLength > aSrcDataLength-aSrcStartIndex)
		{
			return;
		}

//		if(aCrc32Counter)
//			ResultRec->SectionLength = aWriteLength + 9; //（SectionLength 后面5Byte的与Crc32的4Byte）
//		else
//			ResultRec->SectionLength = aWriteLength + 5;
		aPSIHeaderConfig->PSIHeader.SetSectionLength(aWriteLength + 9);


		cout<<"!!!!!!!!!Size:PSIHeaderStruct::"<<sizeof(TSLibrary::DVB::PSIHeaderStruct)<<endl;
		cout<<"!!!!!!!!!Size:"<<sizeof(TSPacketStruct)<<endl;
		aPSIHeaderConfig->PSIHeader.Special_ID_Field_Hi=8;

		if(aCrc32Counter)
		{
			RawBufferPtr PSIDataBuffer((unsigned char *)std::malloc(aWriteLength+8+4),&free);

			std::memset(PSIDataBuffer.get(), 0, aWriteLength+8+4);
			unsigned char * TmpPtr=(unsigned char *)&(aPSIHeaderConfig->PSIHeader);
			std::memcpy(PSIDataBuffer.get(), TmpPtr , 8);
//			void * TmpPtr=aSrcData.get()+aSrcStartIndex;
//			void * TmpPSIDataBuffer=PSIDataBuffer.get()+8;
//			if(aSrcData)
//			{
//				std::memcpy(TmpPSIDataBuffer, TmpPtr, aWriteLength);
//				cout<<"if src"<<endl;
//			}
			unsigned long TmpWriteLength=aWriteLength+8;

			unsigned long CRC32ints =0;
			CRC32ints=aCrc32Counter->GetCrc32(PSIDataBuffer, TmpWriteLength);

			unsigned char * TmpCPtr=(unsigned char *)&CRC32ints;
			unsigned char * TmpCPSIDataBuffer=PSIDataBuffer.get()+aWriteLength + 8;
			TmpCPSIDataBuffer[0]=TmpCPtr[3];
			TmpCPSIDataBuffer[1]=TmpCPtr[2];
			TmpCPSIDataBuffer[2]=TmpCPtr[1];
			TmpCPSIDataBuffer[3]=TmpCPtr[0];
			aTSStream->WriteData(aPSIHeaderConfig->PID, PSIDataBuffer, aWriteLength+8+4, aDataCounter);
		}
		else
		{
			RawBufferPtr PSIDataBuffer((unsigned char *)std::malloc(aWriteLength+8),&free);
			std::memset(PSIDataBuffer.get(), 0, aWriteLength+8);
			std::memcpy(PSIDataBuffer.get(), &aPSIHeaderConfig->PSIHeader, 8);
			if(aSrcData)
			{
				void * TmpPtr=aSrcData.get()+aSrcStartIndex;
				void * TmpPSIDataBuffer=PSIDataBuffer.get()+8;
				std::memcpy(TmpPSIDataBuffer, TmpPtr, aWriteLength);
			}
			aTSStream->WriteData(aPSIHeaderConfig->PID, PSIDataBuffer, aWriteLength+8, aDataCounter);
		}




//		ResultRec->Result = PSISW_S_OK;
//		return ResultRec;
//

}

inline void TestCrcFun()
{
	RawBufferPtr TmpBufferPtr((unsigned char *)std::malloc(29),&free);
	unsigned char * TOTData=TmpBufferPtr.get();
	std::memset(TmpBufferPtr.get(), 0, 29);
	TOTData[0]=0xF0; //reserved 4 Bit
	TOTData[1]=0x0F; //descriptors_loop_length 12 bit
	TOTData[2]= 0x58;//descriptor_tag
	TOTData[3]=13;//descriptor_length
	TOTData[4]=0x43;//country_code 1 Byte C
	TOTData[5]=0x48;//country_code 1 Byte H
	TOTData[6]=0x4E;//country_code 1 Byte N
	TOTData[7]=0x02; //country_region_id 6 bslbf	reserved 1 bslbf 	local_time_offset_polarity 1 bslbf
	TOTData[8]=0x08; //local_time_offset 16Bit Hi
	TOTData[9]=0x00; //local_time_offset 16Bit Lo
	TOTData[10]=0xCD; //time_of _change
	TOTData[11]=0xEF; //time_of _change
	TOTData[12]=0x08; //time_of _change
	TOTData[13]=0x33; //time_of _change
	TOTData[14]=0x36; //time_of _change
	TOTData[15]=0x08; //next_time_offset
	TOTData[16]=0x00; //next_time_offset
	TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());
	unsigned long CRC32ints =0;
	CRC32ints=FCrc32Counter->GetCrc32(TmpBufferPtr, 25);
}
inline void TestCrcBug()
{
	TSLibrary::DVB::PSIHeaderConfigStructPtr PSIHeaderConfig=TSLibrary::DVB::PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(0x14, 0x73,
				0, true);

//		Poco::LocalDateTime PLD;
//		Poco::DateTime LDT=PLD.utc();
//
//		unsigned short L=0;
//		if(LDT.month()==1||LDT.month()==2) L=1;
//		unsigned short MJD=14956+LDT.day()+int((LDT.year()-1900-L)* 365.25) +int((LDT.month() + 1 + L * 12) * 30.6001);
//		PSIHeaderConfig->PSIHeader.PSIData[0]=(MJD>>8);
//		PSIHeaderConfig->PSIHeader.PSIData[1]=MJD&0x00FF;
//		PSIHeaderConfig->PSIHeader.PSIData[2]=getBCDByte(LDT.hour());
//		PSIHeaderConfig->PSIHeader.PSIData[3]=getBCDByte(LDT.minute());
//		PSIHeaderConfig->PSIHeader.PSIData[4]=getBCDByte(LDT.second());

		RawBufferPtr TmpBufferPtr((unsigned char *)std::malloc(17),&free);
		unsigned char * TOTData=TmpBufferPtr.get();
		TOTData[0]=0xF0; //reserved 4 Bit
		TOTData[1]=0x0F; //descriptors_loop_length 12 bit
		TOTData[2]= 0x58;//descriptor_tag
		TOTData[3]=13;//descriptor_length
		TOTData[4]=0x43;//country_code 1 Byte C
		TOTData[5]=0x48;//country_code 1 Byte H
		TOTData[6]=0x4E;//country_code 1 Byte N
		TOTData[7]=0x02; //country_region_id 6 bslbf	reserved 1 bslbf 	local_time_offset_polarity 1 bslbf
		TOTData[8]=0x08; //local_time_offset 16Bit Hi
		TOTData[9]=0x00; //local_time_offset 16Bit Lo
		TOTData[10]=0xCD; //time_of _change
		TOTData[11]=0xEF; //time_of _change
		TOTData[12]=0x08; //time_of _change
		TOTData[13]=0x33; //time_of _change
		TOTData[14]=0x36; //time_of _change
		TOTData[15]=0x08; //next_time_offset
		TOTData[16]=0x00; //next_time_offset


		TSLibrary::ITSDataCounterPtr FDataCounter(new TSLibrary::DefaultDataCounter());
		TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter());

		TSLibrary::ITSDataCounterPtr CounterPtr=FDataCounter;
		TSLibrary::DVB::IPSICrc32CounterPtr Crc32Ptr=FCrc32Counter;

		TSLibrary::ITSDataStreamPtr FTSStreamPtr(new TSLibrary::DefaultTSDataStream());
		TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream());
		FPSIStreamPtr->WriteSpecialSectionDataToTSStream(FTSStreamPtr, PSIHeaderConfig,TmpBufferPtr ,
				17,0,17, CounterPtr, Crc32Ptr);
}

inline void testPocoFile()
{
	Poco::File TT("/home/victor/TTTTTTTTT/TT/");
	TT.createDirectories();
}
inline void TestPocoTime()
{
	Poco::LocalDateTime PLD;
	std::string str = Poco::DateTimeFormatter::format(PLD, Poco::DateTimeFormat::HTTP_FORMAT);
	std::cout<<str<<std::endl;
	str = Poco::DateTimeFormatter::format(PLD.utc(), Poco::DateTimeFormat::HTTP_FORMAT);
	std::cout<<str<<std::endl;
}


struct USStruct
{
	union
	{
		struct
		{
			unsigned char ULo;
			unsigned char UHi;

		};
		unsigned short UINT;
	};
};
inline unsigned short getMJD(unsigned short aYear,unsigned char aMonth,unsigned char aDay)
{
	unsigned short L=0;
	if(aMonth==1||aMonth==2)
		L=1;
	USStruct TT;
	TT.UINT=14956+aDay+int((aYear-1900-L)* 365.25) +int((aMonth + 1 + L * 12) * 30.6001);

	unsigned short MJD=TT.UHi;
	MJD=MJD<<8;
	MJD+=TT.ULo;
	return TT.UINT;
}


inline void GetTDTData()
{
	unsigned char TDTData[5];
	Poco::LocalDateTime PLD;
	Poco::DateTime LDT=PLD.utc();
//	Poco::DateTime LDT(2009,2,5,4,24,59);
	unsigned short L=0;
	if(LDT.month()==1||LDT.month()==2) L=1;
	unsigned short MJD=14956+LDT.day()+int((LDT.year()-1900-L)* 365.25) +int((LDT.month() + 1 + L * 12) * 30.6001);
	TDTData[0]=(MJD>>8);
	TDTData[1]=MJD&0x00FF;
	TDTData[2]=getBCDByte(LDT.hour());
	TDTData[3]=getBCDByte(LDT.minute());
	TDTData[4]=getBCDByte(LDT.second());
	for(int i=0;i<5;i++)
	std::cout<<(int)TDTData[i]<<std::endl;
}

inline void TestMJD()
{
	std::cout<<(int)getMJD(2009,2,5)<<std::endl;
}
inline void TestBCDConvert()
{
	unsigned char TT=getBCDByte(59);
	std::cout<<(int)TT<<std::endl;
}
inline void TestUTCConvert()
{
	Poco::LocalDateTime PLD;
	int hour=PLD.hour();
	std::cout<<(int)hour<<std::endl;

}

#endif /* TEST_H_ */
