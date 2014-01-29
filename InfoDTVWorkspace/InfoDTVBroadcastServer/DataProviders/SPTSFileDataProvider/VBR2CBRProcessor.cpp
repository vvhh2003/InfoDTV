/*
 * VBR2CBRProcesser.cpp
 *
 *  Created on: 2009-3-19
 *      Author: victor
 */
#include "VBR2CBRProcessor.h"



//unsigned char null_ts_packet[TS_PACKET_SIZE];
//u_char ts_packet[TS_PACKET_SIZE];/* TS packet */
//unsigned char output_packet_buffer[OUTPUT_BUFFER_IN_PACKETS * TS_PACKET_SIZE]; OuputBufferPtr
//unsigned char* current_output_packet = 0;
//unsigned long long int ibits; unsigned long long InputBits;

//unsigned long long int obits; unsigned long long OuputBits;




//
//void VBR2CBRProcessor::run()
//{
//	unsigned long long int fcounter=0;
//	unsigned long long int ucounter=0;
//	unsigned long long int last_ucounter=0;
//	unsigned long long int ts_packet_output=0;
//	RawBufferPtr TmpOutputBufferPtr((unsigned char *)std::malloc(FCircularBufferPtr->getBufferLength()),&free);
//	RawBufferPtr FinalOutputBufferPtr((unsigned char *)std::malloc(FCircularBufferPtr->getBufferLength()),&free);
//
//	unsigned long long int FinalWriteLength=0;
//	unsigned char* current_output_packetPtr=TmpOutputBufferPtr.get();
//	unsigned long long int pcr_base = 0ll;
//	unsigned long long int pcr_ext = 0ll;
//	unsigned long long int ts_packet_count = 0ll;
//	unsigned long long int new_pcr = 0ll;
//	unsigned long long int new_pcr_index = 0ll;
//	std::map<unsigned short,unsigned long long> PID_PCR_TABLE;/* PCR table for the TS packets */
//	std::map<unsigned short,unsigned long long> PID_PCR_INDEX_TABLE; /* PCR index table for the TS packets */
//	unsigned long long InputBits=0;
//	TSPacketStructPtr TmpNULLPacket=TSPacketStruct::NewNullTSPacket();
//	if(FParentDataProviderPtr)
//	{
//		while(FIsActive)
//		{
//			TSPacketStructPtr TmpSrcTSPacketStruct=FParentDataProviderPtr->GetTSPacket();
//			unsigned short TmpSrcPID=TmpSrcTSPacketStruct->GetPID();
//			if(TmpSrcPID==FPcrPID) //<MAX_PID
//			{
//				//				if ((ts_packet[3] & 0x20) && (ts_packet[4] != 0) && (ts_packet[5] & 0x10)) {
//
//
//				if((TmpSrcTSPacketStruct->TSData[3]& 0x20) && (TmpSrcTSPacketStruct->TSData[4] != 0) && (TmpSrcTSPacketStruct->TSData[5] & 0x10))
//				{
//					/* there is a pcr field */
//					pcr_base = (TmpSrcTSPacketStruct->TSData[6] << 25) & 0x1FFFFFFFFll;
//					pcr_base += (TmpSrcTSPacketStruct->TSData[7] << 17) & 0x1FFFFFFll;
//					pcr_base += (TmpSrcTSPacketStruct->TSData[8] << 9) & 0x1FFFFll;
//					pcr_base += (TmpSrcTSPacketStruct->TSData[9] << 1) & 0x1FFll;
//					pcr_base += ((TmpSrcTSPacketStruct->TSData[10] & 0x80) >> 7) & 0x1ll;
//					pcr_ext = ((TmpSrcTSPacketStruct->TSData[10] & 0x01) << 8) & 0x1FFll;
//					pcr_ext += TmpSrcTSPacketStruct->TSData[11];
//
//					if(PID_PCR_TABLE.count(TmpSrcPID)==0)/* it's a new pcr pid */
//					{
//						PID_PCR_TABLE[TmpSrcPID] = pcr_base * 300ll + pcr_ext;
//						PID_PCR_INDEX_TABLE[TmpSrcPID] = (ts_packet_count * TS_PACKET_SIZE) + 10;
//					}
//					else   /* we can guess a bit rate comparing a previous pcr pid */
//					{
//						new_pcr = pcr_base * 300ll + pcr_ext;
//						new_pcr_index = (ts_packet_count * TS_PACKET_SIZE) + 10;
//						InputBits =	(((double)(new_pcr_index - PID_PCR_INDEX_TABLE[TmpSrcPID])) * 8 * SYSTEM_CLOCK_FREQUENCY) /  ((double)(new_pcr - PID_PCR_TABLE[TmpSrcPID]));
//						if(InputBits>FOutputBitRate)
//						{
//							//Overflow!
//							FIsActive=false;
//						}
//
//
//						unsigned char* output_packetPtr = TmpOutputBufferPtr.get();
//						for (; output_packetPtr < current_output_packetPtr; output_packetPtr += TS_PACKET_SIZE)
//						{
//
//							/* write input packet out */
////							write(STDOUT_FILENO, output_packetPtr, TS_PACKET_SIZE);
//							if((FinalWriteLength+TS_PACKET_SIZE)>(unsigned long)FCircularBufferPtr->getBufferLength())
//							{
//								FCircularBufferPtr->setBuffer(VBR2CBRBufferLength,FinalOutputBufferPtr);
//							}
//							unsigned char * TmpCurrentFinalOutputBufferPtr=FinalOutputBufferPtr.get()+FinalWriteLength;
//							std::memcpy(TmpCurrentFinalOutputBufferPtr,output_packetPtr,TS_PACKET_SIZE);
//							FinalWriteLength+=TS_PACKET_SIZE;
//							ts_packet_output++;
//
//							/* increase counters, every input packet generate free time and consume some*/
//							fcounter += TS_PACKET_SIZE * 8 * FOutputBitRate;
//							ucounter += TS_PACKET_SIZE * 8 * InputBits;
//
//							/* generate null packets if there's time */
//							while ( ucounter + (TS_PACKET_SIZE * 8 * InputBits) <= fcounter)
//							{
//
//								if((FinalWriteLength+TS_PACKET_SIZE)>(unsigned long)FCircularBufferPtr->getBufferLength())
//								{
//									FCircularBufferPtr->setBuffer(VBR2CBRBufferLength,FinalOutputBufferPtr);
//								}
//								/* write null packets */
////								write(STDOUT_FILENO, null_ts_packet, TS_PACKET_SIZE);
//								unsigned char * TmpCurrentFinalOutputBufferPtr=FinalOutputBufferPtr.get()+FinalWriteLength;
//								std::memcpy(TmpCurrentFinalOutputBufferPtr,TmpNULLPacket->TSData,TS_PACKET_SIZE);
//								FinalWriteLength+=TS_PACKET_SIZE;
//								ts_packet_output++;
//
//								/* increase output bit counter */
//								last_ucounter = ucounter;
//								ucounter += TS_PACKET_SIZE * 8 * InputBits;
//								if (last_ucounter > ucounter)
//								{ /* manage zeroed counter */
//									last_ucounter = last_ucounter - fcounter;
//									fcounter = 0;
//									ucounter = last_ucounter + TS_PACKET_SIZE * 8 * InputBits;
//								}
//							}
//						}
//						current_output_packetPtr = TmpOutputBufferPtr.get();
//						fcounter = fcounter - ucounter;
//						ucounter = 0;
//						last_ucounter = 0;
//
//
//						PID_PCR_TABLE[TmpSrcPID] = new_pcr;
//						PID_PCR_INDEX_TABLE[TmpSrcPID] = new_pcr_index;
//					}
//				}
//
//			}
//			if(current_output_packetPtr+TS_PACKET_SIZE>TmpOutputBufferPtr.get() + VBR2CBRBufferLength)
//			{
//				//Overflow!
//				FIsActive=false;
//			}
//			else
//			{
//				std::memcpy(current_output_packetPtr, TmpSrcTSPacketStruct->TSData, TS_PACKET_SIZE);
//				current_output_packetPtr += TS_PACKET_SIZE;
//			}
//			ts_packet_count++;
//		}
//
//
//	}
//
//}

VBR2CBRProcessor::VBR2CBRProcessor(MultiplexerCore::ITSDataProviderPtr aDataProviderPtr,unsigned short aPcrPID,unsigned long long aOutputBitRate):
	FParentDataProviderPtr(aDataProviderPtr),FIsActive(false),
	/*FCircularBufferPtr(),	FActivity(this,&VBR2CBRProcessor::run),*/
	FCurrentBufferPtr(),FBufPosition(0),
	FOutputBitRate(aOutputBitRate),FPcrPID(aPcrPID),FVBR2CBR(),FLogger()

{
	FLogger.setName("VBR2CBRProcessor",false);
//	FCircularBufferPtr.reset(new InfoDTV_Common_Buffer::CircularBuffer("VBR2CBRProcessor",3,VBR2CBRBufferLength));
}

void VBR2CBRProcessor::Active()
{
//	FActivity.start();
	FIsActive=true;
}


void VBR2CBRProcessor::DeActive()
{
//	FActivity.stop();
//	if (FCircularBufferPtr->IsBufferWriterBlocked())
//	{
////		Log("停止中..正在解决数据准备缓冲锁...");
//		FCircularBufferPtr->getBuffer();
////		Log("停止中..数据准备缓冲锁已解决...");
//	}
//	FActivity.wait();
	FIsActive=false;
}

TSPacketStructPtr VBR2CBRProcessor::GetTSPacket ( )
{
/*	if(!FIsActive)
		return TSPacketStruct::NewNullTSPacket();
	if(!FCurrentBufferPtr)
	{
		FCurrentBufferPtr=FCircularBufferPtr->getBuffer(READ_TIME_OUT);
		if(!FCurrentBufferPtr)
			return TSPacketStruct::NewNullTSPacket();
		FBufPosition=0;
	}
	if(FBufPosition+188>(unsigned long)FCircularBufferPtr->getBufferLength())
	{
		FCurrentBufferPtr=FCircularBufferPtr->getBuffer(READ_TIME_OUT);
		if(!FCurrentBufferPtr)
			return TSPacketStruct::NewNullTSPacket();
		FBufPosition=0;
	}
	TSPacketStructPtr FTmpTsPacket(new TSPacketStruct);
	if(FActivity.isStopped())
		return TSPacketStruct::NewNullTSPacket();
	void * Buf = FCurrentBufferPtr.get() + FBufPosition;
	std::memcpy((void *) FTmpTsPacket.get(), Buf, 188);
	FBufPosition += 188;

	 return FTmpTsPacket;*/

	if(!FIsActive)
			return TSPacketStruct::NewNullTSPacket();

		TSPacketStructPtr FTmpTsPacket=FVBR2CBR.GetPacket(FParentDataProviderPtr,FOutputBitRate,FPcrPID);


		 return FTmpTsPacket;


}

bool VBR2CBRProcessor::getIsActived ( )
{
	return FIsActive;
}
