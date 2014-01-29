/*
 * PCRPTSProcessor.cpp
 *
 *  Created on: 2009-3-21
 *      Author: victor
 */

#include "PCRPTSProcessor.h"

#define TS_HEADER_SIZE 4
#define TS_PACKET_SIZE 188
#define MAX_PID 8192
#define SYSTEM_CLOCK_FREQUENCY 27000000
#define PACK_HEADER_SIZE 4
#define TIME_STAMP_SIZE 5
//const long long unsigned system_frequency = 27000000;

PCRPTSProcessor::PCRPTSProcessor(MultiplexerCore::ITSDataProcessorPtr aParentDataProcessorPtr) :
	FParentDataProcessorPtr(aParentDataProcessorPtr), FParentDataProviderPtr(),
	FIsActive(false), FParentIsDataProvider(false), FTSPacketCount(0),
	FPID_PCR_TABLE(),
	FPID_PCR_INDEX_TABLE(), FPTS_TABLE(), FPTS_DELTA_TABLE(), FPTS_INDEX_TABLE(),FLogger()
	{
	FLogger.setName("PCRPTSProcessor",false);

	}

PCRPTSProcessor::PCRPTSProcessor(MultiplexerCore::ITSDataProviderPtr aParentDataProviderPtr) :
	FParentDataProcessorPtr(), FParentDataProviderPtr(aParentDataProviderPtr),
	FIsActive(false),	FParentIsDataProvider(true),
	FTSPacketCount(0), FPID_PCR_TABLE(),
	FPID_PCR_INDEX_TABLE(), FPTS_TABLE(), FPTS_DELTA_TABLE(), FPTS_INDEX_TABLE(),FLogger()
	{
	FLogger.setName("PCRPTSProcessor",false);
	}

void PCRPTSProcessor::Active()
{
	FTSPacketCount = 0;
	FPID_PCR_TABLE.clear();
	FPID_PCR_INDEX_TABLE.clear();
	FPTS_TABLE.clear();
	FPTS_DELTA_TABLE.clear();
	FPTS_INDEX_TABLE.clear();
	FIsActive = true;
}

bool PCRPTSProcessor::getIsActived()
{
	return FIsActive;
}
void PCRPTSProcessor::DeActive()
{
	FIsActive = false;
}

void stamp_ts (unsigned long long int ts, unsigned char* buffer)
{
	if (buffer) {
		buffer[0] = ((ts >> 29) & 0x0F) | 0x01;
		buffer[1] = (ts >> 22) & 0xFF;
		buffer[2] = ((ts >> 14) & 0xFF ) | 0x01;
		buffer[3] = (ts >> 7) & 0xFF;
		buffer[4] = ((ts << 1) & 0xFF ) | 0x01;
	}
}

unsigned long long parse_timestamp(unsigned char *buf)
{
	unsigned long long a1;
	unsigned long long a2;
	unsigned long long a3;
	unsigned long long ts;

	a1 = (buf[0] & 0x0F) >> 1;
	a2 = ((buf[1] << 8) | buf[2]) >> 1;
	a3 = ((buf[3] << 8) | buf[4]) >> 1;
	ts = (a1 << 30) | (a2 << 15) | a3;

	return ts;
}


TSPacketStructPtr PCRPTSProcessor::GetTSPacket()
{

	if (!FIsActive)
	{
		return TSPacketStruct::NewNullTSPacket();
	}
	TSPacketStructPtr TmpSrcPacketStructPtr;
	if (FParentIsDataProvider)
		TmpSrcPacketStructPtr = FParentDataProviderPtr->GetTSPacket();
	else
		TmpSrcPacketStructPtr = FParentDataProcessorPtr->GetTSPacket();
	if (!TmpSrcPacketStructPtr)
	{
		return TSPacketStruct::NewNullTSPacket();
	}
	unsigned short SrcPID = TmpSrcPacketStructPtr->GetPID();

	if (SrcPID < MAX_PID && (TmpSrcPacketStructPtr->TSData[3] & 0x20) && (TmpSrcPacketStructPtr->TSData[4] != 0) && (TmpSrcPacketStructPtr->TSData[5] & 0x10))
	{
		/* there is PCR */
		/* Check pcr */
		unsigned long long int new_pcr_index = (FTSPacketCount * TS_PACKET_SIZE) + 10;
		unsigned long long int trbits = 0;
		if (FPID_PCR_TABLE.count(SrcPID) > 0)
		{
			unsigned long long int new_pcr = new_pcr_index - FPID_PCR_INDEX_TABLE[SrcPID];
			new_pcr *= 8;
			new_pcr *= SYSTEM_CLOCK_FREQUENCY;
			new_pcr /= trbits;
			new_pcr += FPID_PCR_TABLE[SrcPID];

			unsigned long long int pcr_base = new_pcr / 300;
			unsigned long long int pcr_ext = new_pcr % 300;
			TmpSrcPacketStructPtr->TSData[6] = (0xFF & (pcr_base >> 25));
			TmpSrcPacketStructPtr->TSData[7] = (0xFF & (pcr_base >> 17));
			TmpSrcPacketStructPtr->TSData[8] = (0xFF & (pcr_base >> 9));
			TmpSrcPacketStructPtr->TSData[9] = (0xFF & (pcr_base >> 1));
			TmpSrcPacketStructPtr->TSData[10] = ((0x1 & pcr_base) << 7) | 0x7E | ((0x100 & pcr_ext) >> 8);
			TmpSrcPacketStructPtr->TSData[11] = (0xFF & pcr_ext);
			FPID_PCR_TABLE[SrcPID] = new_pcr;
		}
		FPID_PCR_INDEX_TABLE[SrcPID] = new_pcr_index;

		/* check PTS and DTS */
		int ts_header_size = 0;
		unsigned char adapt = (TmpSrcPacketStructPtr->TSData[3] >> 4) & 0x03;
		if (adapt == 0)
		{
			ts_header_size = TS_PACKET_SIZE; /* the packet is invalid ?*/
		}
		else if (adapt == 1)
		{
			ts_header_size = TS_HEADER_SIZE; /* only payload */
		}
		else if (adapt == 2)
		{
			ts_header_size = TS_PACKET_SIZE; /* only adaptation field */
		}
		else if (adapt == 3)
		{
			ts_header_size = TS_HEADER_SIZE + TmpSrcPacketStructPtr->TSData[4] + 1; /* jump the adaptation field */
		}
		else
		{
			ts_header_size = TS_PACKET_SIZE; /* not managed */
		}

		unsigned char pes_header_size = 0;
		unsigned long long time = 0;

		if (ts_header_size + 20 < TS_PACKET_SIZE && SrcPID < MAX_PID)
		{
			if ((TmpSrcPacketStructPtr->TSData[ts_header_size] == 0x00) && (TmpSrcPacketStructPtr->TSData[ts_header_size + 1] == 0x00)
					&& (TmpSrcPacketStructPtr->TSData[ts_header_size + 2] == 0x01))
			{
				unsigned char timestamp[TIME_STAMP_SIZE];
				pes_header_size = TmpSrcPacketStructPtr->TSData[ts_header_size + 8];
				if ((TmpSrcPacketStructPtr->TSData[ts_header_size + 3] >> 4) == 0x0E)
				{ /* PES video stream */
					memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
					time = parse_timestamp(timestamp);

					if (pes_header_size > 5)
					{
						memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 14, TIME_STAMP_SIZE);
						time = parse_timestamp(timestamp);

					}

					if (FPTS_INDEX_TABLE.count(SrcPID) == 0)
					{
						FPTS_INDEX_TABLE[SrcPID]=0;
						if (pes_header_size > 5)
						{ /* if there are both dts and pts, get dts */
							memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 14, TIME_STAMP_SIZE);
							time = parse_timestamp(timestamp);
						}
						else
						{ /* othewise they are the same */
							memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
							time = parse_timestamp(timestamp);
						}
						FPTS_INDEX_TABLE[SrcPID] = 1;
						FPTS_TABLE[SrcPID] = time;
					}
					else if (FPTS_INDEX_TABLE[SrcPID] == 1)
					{
						if (pes_header_size > 5)
						{ /* if there are both dts and pts, get dts */
							memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 14, TIME_STAMP_SIZE);
							time = parse_timestamp(timestamp);
						}
						else
						{ /* othewise they are the same */
							memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
							time = parse_timestamp(timestamp);
						}
						FPTS_INDEX_TABLE[SrcPID] = 2;
						FPTS_DELTA_TABLE[SrcPID] = time - FPTS_TABLE[SrcPID];
						FPTS_TABLE[SrcPID] = time;
					}
					else
					{
						if (pes_header_size > 5)
						{ /* if there are both dts and pts */
							memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
							time = parse_timestamp(timestamp);
							memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 14, TIME_STAMP_SIZE);
							time -= parse_timestamp(timestamp);
							FPTS_TABLE[SrcPID] += FPTS_DELTA_TABLE[SrcPID]; /* dts goes up 1 step */
							stamp_ts(FPTS_TABLE[SrcPID], TmpSrcPacketStructPtr->TSData + ts_header_size + 14);
							TmpSrcPacketStructPtr->TSData[ts_header_size + 14] &= 0x0F;
							TmpSrcPacketStructPtr->TSData[ts_header_size + 14] |= 0x10;
							/* pts goes up the same gap there was before */
							stamp_ts(FPTS_TABLE[SrcPID] + time, TmpSrcPacketStructPtr->TSData + ts_header_size + 9);
							TmpSrcPacketStructPtr->TSData[ts_header_size + 9] &= 0x0F;
							TmpSrcPacketStructPtr->TSData[ts_header_size + 9] |= 0x20;
						}
						else
						{
							FPTS_TABLE[SrcPID] += FPTS_DELTA_TABLE[SrcPID];
							stamp_ts(FPTS_TABLE[SrcPID], TmpSrcPacketStructPtr->TSData + ts_header_size + 9);
							TmpSrcPacketStructPtr->TSData[ts_header_size + 9] &= 0x0F;
							TmpSrcPacketStructPtr->TSData[ts_header_size + 9] |= 0x20;
						}
					}

					memcpy(timestamp,  TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
					time = parse_timestamp(timestamp);

					if (pes_header_size > 5)
					{
						memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 14, TIME_STAMP_SIZE);
						time = parse_timestamp(timestamp);
					}

				}
				else if ((TmpSrcPacketStructPtr->TSData[ts_header_size + 3] >> 5) == 0x06)
				{ /* PES audio stream */

					memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
					time = parse_timestamp(timestamp);
					// fprintf(stderr, "Pid %d old Audio Presentation Time Stamp is: %llu, %llu.%04llu sec.\n", pid, time,  time / (system_frequency / 300), (time % (system_frequency / 300)) / ((system_frequency / 300) / 10000));

					if (FPTS_INDEX_TABLE.count(SrcPID)==0)
					{
						FPTS_INDEX_TABLE[SrcPID] = 1;
						memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
						time = parse_timestamp(timestamp);
						FPTS_TABLE[SrcPID] = time;
					}
					else if (FPTS_INDEX_TABLE[SrcPID] == 1)
					{
						FPTS_INDEX_TABLE[SrcPID] = 2;
						memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
						time = parse_timestamp(timestamp);
						FPTS_DELTA_TABLE[SrcPID] = time - FPTS_TABLE[SrcPID];
						FPTS_TABLE[SrcPID] = time;
					}
					else
					{
						FPTS_TABLE[SrcPID] += FPTS_DELTA_TABLE[SrcPID];
						stamp_ts(FPTS_TABLE[SrcPID], TmpSrcPacketStructPtr->TSData + ts_header_size + 9);
						TmpSrcPacketStructPtr->TSData[ts_header_size + 9] &= 0x0F;
						TmpSrcPacketStructPtr->TSData[ts_header_size + 9] |= 0x20;
					}

					memcpy(timestamp, TmpSrcPacketStructPtr->TSData + ts_header_size + 9, TIME_STAMP_SIZE);
					time = parse_timestamp(timestamp);
				}
			}
		}

	}
	FTSPacketCount++;
	return TmpSrcPacketStructPtr;

}

