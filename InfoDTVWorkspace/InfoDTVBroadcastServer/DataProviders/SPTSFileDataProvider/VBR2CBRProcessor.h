/*
 * VBR2CBRProcesser.h
 *
 *  Created on: 2009-3-19
 *      Author: victor
 */

#ifndef VBR2CBRPROCESSOR_H_
#define VBR2CBRPROCESSOR_H_
#include "../../Interface/ITSDataProvider.h"
#include "../../Interface/ITSDataProcessor.h"
#include "../../Common/Log/Log.h"
#include "../../Common/TSPacketStruct.h"
#include "../../Common/CircularBuffer.h"

#include "Poco/Activity.h"
#include "Poco/Thread.h"
#include <map>
#define TS_PACKET_SIZE 188
#define MAX_PID 8192
#define SYSTEM_CLOCK_FREQUENCY 27000000
#define OUTPUT_BUFFER_IN_PACKETS 2127 // 40mbps maximum dvb stream, pcr maximum 40ms -> 200Kbytes buffer, let's take 400K ;-)
#define READ_TIME_OUT 1000
const unsigned long VBR2CBRBufferLength=OUTPUT_BUFFER_IN_PACKETS*TS_PACKET_SIZE;
enum GetPacketStatus {GPS_SourcePacket,GPS_NullPacketFill};
struct VBR2CBR
{
	GetPacketStatus WriteStatus;
	unsigned long long int fcounter;
	unsigned long long int ucounter;
	unsigned long long int last_ucounter;
	unsigned long long int Total_ts_packet_output;
	unsigned long long int FinalWriteLength;

	unsigned long long int pcr_base;
	unsigned long long int pcr_ext;
	unsigned long long int out_ts_packet_count;
	unsigned long long int new_pcr;
	unsigned long long int new_pcr_index;
	std::map<unsigned short,unsigned long long> PID_PCR_TABLE;/* PCR table for the TS packets */
	std::map<unsigned short,unsigned long long> PID_PCR_INDEX_TABLE; /* PCR index table for the TS packets */
	unsigned long long InstantInputBits;
	TSPacketStructPtr TmpNULLPacketPtr;
	TSPacketStructPtr StackTSPacketPtr;
	VBR2CBR():
	WriteStatus(GPS_SourcePacket),
	fcounter(0),ucounter(0),last_ucounter(0),
	Total_ts_packet_output(0),FinalWriteLength(0),pcr_base(0),
	pcr_ext(0),out_ts_packet_count(0),new_pcr(0),new_pcr_index(0),
	PID_PCR_TABLE(),PID_PCR_INDEX_TABLE(),InstantInputBits(0),TmpNULLPacketPtr(TSPacketStruct::NewNullTSPacket()),
	StackTSPacketPtr()
	{

	}

	TSPacketStructPtr GetPacket(MultiplexerCore::ITSDataProviderPtr aParentDataProviderPtr,const unsigned long aOutputBitRate,const unsigned short aPcrPID)
	{

		TSPacketStructPtr TmpSrcTSPacketStructPtr;
		if(WriteStatus==GPS_SourcePacket)
		{
			TmpSrcTSPacketStructPtr=aParentDataProviderPtr->GetTSPacket();
			unsigned short TmpSrcPID=TmpSrcTSPacketStructPtr->GetPID();
			//是否属于PCR PID
			if(TmpSrcPID==aPcrPID)
			{
				if((TmpSrcTSPacketStructPtr->TSData[3]& 0x20) && (TmpSrcTSPacketStructPtr->TSData[4] != 0) && (TmpSrcTSPacketStructPtr->TSData[5] & 0x10))
				{
					/* there is a pcr field */
					pcr_base = (TmpSrcTSPacketStructPtr->TSData[6] << 25) & 0x1FFFFFFFFll;
					pcr_base += (TmpSrcTSPacketStructPtr->TSData[7] << 17) & 0x1FFFFFFll;
					pcr_base += (TmpSrcTSPacketStructPtr->TSData[8] << 9) & 0x1FFFFll;
					pcr_base += (TmpSrcTSPacketStructPtr->TSData[9] << 1) & 0x1FFll;
					pcr_base += ((TmpSrcTSPacketStructPtr->TSData[10] & 0x80) >> 7) & 0x1ll;
					pcr_ext = ((TmpSrcTSPacketStructPtr->TSData[10] & 0x01) << 8) & 0x1FFll;
					pcr_ext += TmpSrcTSPacketStructPtr->TSData[11];

					if(PID_PCR_TABLE.count(TmpSrcPID)==0)/* it's a new pcr pid */
					{
						PID_PCR_TABLE[TmpSrcPID] = pcr_base * 300ll + pcr_ext;
						PID_PCR_INDEX_TABLE[TmpSrcPID] = (Total_ts_packet_output * TS_PACKET_SIZE) + 10;
					}
					else
					{
						new_pcr = pcr_base * 300ll + pcr_ext;
						new_pcr_index = (Total_ts_packet_output * TS_PACKET_SIZE) + 10;
						InstantInputBits =	(((double)(new_pcr_index - PID_PCR_INDEX_TABLE[TmpSrcPID])) * 8 * SYSTEM_CLOCK_FREQUENCY) /  ((double)(new_pcr - PID_PCR_TABLE[TmpSrcPID]));
						if(InstantInputBits>aOutputBitRate)
						{
							//Overflow!
						}
						//原Flush_buffer()逻辑开始
						//主要计算fcounter 和 ucounter 来设置状态
						ucounter = out_ts_packet_count*TS_PACKET_SIZE *8 * InstantInputBits;
						if(ucounter+(TS_PACKET_SIZE *8 * InstantInputBits)<=fcounter)
						{
							WriteStatus=GPS_NullPacketFill;
							//将当前PCR包压入临时缓冲返回空包
							StackTSPacketPtr=TmpSrcTSPacketStructPtr;
							TmpSrcTSPacketStructPtr=TmpNULLPacketPtr;
						}
						//原Flush_buffer()逻辑结束

						PID_PCR_TABLE[TmpSrcPID] = new_pcr;
						PID_PCR_INDEX_TABLE[TmpSrcPID] = new_pcr_index;
					}

				}


			}
		}
		else if(WriteStatus==GPS_NullPacketFill)
		{
			TmpSrcTSPacketStructPtr=TmpNULLPacketPtr;
			//判断是否完成填充数量
			if(ucounter+(TS_PACKET_SIZE *8* InstantInputBits )>fcounter)
			{
				//在完成填充数量后更改状态
				fcounter=fcounter-ucounter;
				ucounter=0;
				last_ucounter=0;
				out_ts_packet_count=0;
				WriteStatus=GPS_SourcePacket;
				if(StackTSPacketPtr)
				{
					TmpSrcTSPacketStructPtr=StackTSPacketPtr;
					pcr_base = (TmpSrcTSPacketStructPtr->TSData[6] << 25) & 0x1FFFFFFFFll;
					pcr_base += (TmpSrcTSPacketStructPtr->TSData[7] << 17) & 0x1FFFFFFll;
					pcr_base += (TmpSrcTSPacketStructPtr->TSData[8] << 9) & 0x1FFFFll;
					pcr_base += (TmpSrcTSPacketStructPtr->TSData[9] << 1) & 0x1FFll;
					pcr_base += ((TmpSrcTSPacketStructPtr->TSData[10] & 0x80) >> 7) & 0x1ll;
					pcr_ext = ((TmpSrcTSPacketStructPtr->TSData[10] & 0x01) << 8) & 0x1FFll;
					pcr_ext += TmpSrcTSPacketStructPtr->TSData[11];
					new_pcr = (((Total_ts_packet_output * TS_PACKET_SIZE) + 10) * 8 * SYSTEM_CLOCK_FREQUENCY) / aOutputBitRate;
					pcr_base = new_pcr / 300;
					pcr_ext = new_pcr % 300;
					TmpSrcTSPacketStructPtr->TSData[6] = (0xFF & (pcr_base >> 25));
					TmpSrcTSPacketStructPtr->TSData[7] = (0xFF & (pcr_base >> 17));
					TmpSrcTSPacketStructPtr->TSData[8] = (0xFF & (pcr_base >> 9));
					TmpSrcTSPacketStructPtr->TSData[9] = (0xFF & (pcr_base >> 1));
					TmpSrcTSPacketStructPtr->TSData[10] = ((0x1 & pcr_base) << 7) | 0x7E | ((0x100 & pcr_ext) >> 8);
					TmpSrcTSPacketStructPtr->TSData[11] = (0xFF & pcr_ext);
					StackTSPacketPtr.reset();
				}
			}
			else
			{
//				out_ts_packet_count++;
				/* increase output bit counter */
				last_ucounter = ucounter;
				ucounter += TS_PACKET_SIZE * 8 * InstantInputBits;
				if (last_ucounter > ucounter) { /* manage zeroed counter */
					last_ucounter = last_ucounter - fcounter;
					fcounter = 0;
					ucounter = last_ucounter + TS_PACKET_SIZE * 8 * InstantInputBits;
					//fprintf(stderr, "manage zeroed counter\r\n");
				}
			}
		}

		 if(WriteStatus!=GPS_NullPacketFill)
		 {
			 fcounter += TS_PACKET_SIZE* 8 * aOutputBitRate;
		 }


		out_ts_packet_count++;
		Total_ts_packet_output++;
		return TmpSrcTSPacketStructPtr;
	}
};


class VBR2CBRProcessor:public MultiplexerCore::ITSDataProcessor
{
	private:
		MultiplexerCore::ITSDataProviderPtr FParentDataProviderPtr;
		bool FIsActive;
//		InfoDTV_Common_Buffer::CircularBufferPtr FCircularBufferPtr;
//		Poco::Activity<VBR2CBRProcessor> FActivity;
		RawBufferPtr FCurrentBufferPtr;
		unsigned int FBufPosition;
		unsigned long long FOutputBitRate;
		unsigned short FPcrPID;
//		virtual void run();
		VBR2CBR FVBR2CBR;
		InfoDTV_Common_Log::InfoDTVLogger FLogger;
		void Log(string aMsg)
		{
			FLogger.information(aMsg);
		}
	public:
		VBR2CBRProcessor(MultiplexerCore::ITSDataProviderPtr aDataProviderPtr,unsigned short aPcrPID,unsigned long long aOutputBitRate);
		virtual ~VBR2CBRProcessor()
		{
			Log("<MEM>已释放");
		};
		virtual void Active ( );
		virtual void DeActive ( );
		/**
		 * @return TSPacketStruct
		 */
		virtual TSPacketStructPtr GetTSPacket ( );

		/**
		 * @return bool
		 */
		virtual bool getIsActived ( ) ;

};



#endif /* VBR2CBRPROCESSER_H_ */
