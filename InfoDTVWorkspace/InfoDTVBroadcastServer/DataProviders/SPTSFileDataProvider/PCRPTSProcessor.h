/*
 * PCRPTSProcessor.h
 *
 *  Created on: 2009-3-21
 *      Author: victor
 */

#ifndef PCRPTSPROCESSOR_H_
#define PCRPTSPROCESSOR_H_

#include "../../Interface/ITSDataProvider.h"
#include "../../Interface/ITSDataProcessor.h"
#include "../../Common/Log/Log.h"
#include "../../Common/TSPacketStruct.h"
#include "../../Common/CircularBuffer.h"
#include <map>


class PCRPTSProcessor:public MultiplexerCore::ITSDataProcessor
{
	private:
		MultiplexerCore::ITSDataProcessorPtr FParentDataProcessorPtr;
		MultiplexerCore::ITSDataProviderPtr FParentDataProviderPtr;
		bool FIsActive;
		bool FParentIsDataProvider;

		unsigned long long int FTSPacketCount;
		std::map<unsigned short,unsigned long long> FPID_PCR_TABLE;/* PCR table for the TS packets */
		std::map<unsigned short,unsigned long long> FPID_PCR_INDEX_TABLE; /* PCR index table for the TS packets */
		std::map<unsigned short,unsigned long long> FPTS_TABLE; /* PTS last value */
		std::map<unsigned short,unsigned long long> FPTS_DELTA_TABLE; /* PTS delta increment */
		std::map<unsigned short,unsigned char> FPTS_INDEX_TABLE;/* PTS index table for the TS packets */
		InfoDTV_Common_Log::InfoDTVLogger FLogger;
		void Log(string aMsg)
		{
			FLogger.information(aMsg);
		}
	public:
		PCRPTSProcessor(MultiplexerCore::ITSDataProcessorPtr aParentDataProcessorPtr);
		PCRPTSProcessor(MultiplexerCore::ITSDataProviderPtr aParentDataProviderPtr);
		virtual ~PCRPTSProcessor()
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
		virtual bool getIsActived ( );
};
#endif /* PCRPTSPROCESSOR_H_ */
