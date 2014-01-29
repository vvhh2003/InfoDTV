/*
 * SoftMultiplexer.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */
#include "SoftMultiplexer.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;

namespace MultiplexerCore_V1
{
	using boost::lexical_cast;
	void SoftMultiplexer::Log(string ALogStr)
	{
		FLogger.information(ALogStr);
	}

	void SoftMultiplexer::SetTSMuxChannelStreams(IMultiplexer* aMux)
	{
		FTSMuxChannelStreams.reset(new TSMuxChannelStreams(aMux));
	}


	 MultiplexerCore::ISoftMultiplexerPtr SoftMultiplexer::Create(long TotalOutputBitRate)
	{
		 ISoftMultiplexerPtr Result(new SoftMultiplexer(TotalOutputBitRate));
		 (dynamic_cast<SoftMultiplexer*>(Result.get()))->SetTSMuxChannelStreams( (dynamic_cast<IMultiplexer*>(Result.get())));
		return Result;
	}

	SoftMultiplexer::~SoftMultiplexer()
	{
		if (FTSMuxChannelStreams)
			FTSMuxChannelStreams.get()->ClearAllStream();
		Log("<MEM>已释放！");
	}
	SoftMultiplexer::SoftMultiplexer(long TotalOutputBitRate):FLogger()
	{
		FLogger.setName("复用器");
		Log("正在启动！");
		FOutputBitRate= TotalOutputBitRate;
		FOutputBufferLengthPreSec = TotalOutputBitRate/8;
		Log("启动完成！");
		//				FTotalOutputBitRate=TotalOutputBitRate;
	}

	void SoftMultiplexer::FillBuffer(int aBufferLength, RawBufferPtr aBuffer)
	{
		//				Log("FillBuffer Runing...");
		long NeedPackets=aBufferLength/188;
		//			if (FRuntimeConfig != null && FRefreshConfigCount>=MaxRefreshConfigCount)
		//			{
		//				FRuntimeConfig.RefreshConfig(this);
		//				FRefreshConfigCount = 0;
		//			}
		//			else
		//			{
		//				FRefreshConfigCount++;
		//			}

		if (FTSMuxChannelStreams)
		{
			for (int i=0; i<NeedPackets; i++)
			{
				TSPacketStructPtr TP=FTSMuxChannelStreams.get()->OutputPacket();
				//					TSPacketStruct.FastCopyToByteArray(ref TP,aBuffer,i*188);
				unsigned char * TmpBuffer=aBuffer.get()+i*188;
				TSPacketStruct::FastCopyToBuffer(TP, TmpBuffer);
			}
		}
		//				Log("FillBuffer End...");
	}// TSMultiplexer.FillBuffer


	void SoftMultiplexer::FillPreSecBuffer(int aBufferLength, RawBufferPtr aBuffer)
	{
		//	System.Diagnostics.Debug.Assert(aBuffer.Length<FOutputBufferLengthPreSec);
		//	assert()
		FillBuffer(aBufferLength, aBuffer);
		//			long NeedPackets=aBufferLength/188;
		//			if(FMuxChannelStreams!=null)
		//			{
		//				for(int i=0;i<NeedPackets;i++)
		//				{
		//					TSPacketStruct TP=FMuxChannelStreams.OutputPacket();
		//					TSPacketStruct.FastCopyToByteArray(ref TP,aBuffer,i*188);
		//				}
		//			}
		//
	}

	long SoftMultiplexer::GetOutputBitRateByName(string aStreamName)
	{
		if (FTSMuxChannelStreams)
			return FTSMuxChannelStreams.get()->GetOutputBitRateByName(aStreamName);
		else
			return -1;
	}

	StringListPtr SoftMultiplexer::GetOutputStreamNames()
	{
		if (FTSMuxChannelStreams)
			return FTSMuxChannelStreams.get()->GetOutputStreamNames();
		else
		{
			StringListPtr Tmp(new StringList);
			return Tmp;
		}

	}

	void SoftMultiplexer::Clear()
	{
		if (FTSMuxChannelStreams)
			FTSMuxChannelStreams.get()->ClearAllStream();
		FTSMuxChannelStreams.reset();
		return;
	}

	void SoftMultiplexer::Reset()
	{
		if (FTSMuxChannelStreams)
			FTSMuxChannelStreams.get()->ResetStreams();
		return;
	}

	ITSMuxChannelStreamsPtr SoftMultiplexer::getMuxChannelStreams()
	{
		return FTSMuxChannelStreams;
	}

	long SoftMultiplexer::getOutputBitRate()
	{
		return FOutputBitRate;
	}


	//感觉没什么用
	void SoftMultiplexer::setOutputBitRate(long aNewBitRate)
	{
		long TmpBitRate=(aNewBitRate/(8*188))*188; //保证为188的倍数BPS
		FOutputBufferLengthPreSec=TmpBitRate;
		FOutputBitRate=TmpBitRate;
		if (FTSMuxChannelStreams)
			FTSMuxChannelStreams.get()->ReCalculateMuxStreamsBitRate();
	}

	long SoftMultiplexer::getOutputBufferLengthPreSec()
	{
		return FOutputBufferLengthPreSec;
	}

	long SoftMultiplexer::GetCurrentTotalTSChannelBitRate()
	{
		if (FTSMuxChannelStreams)
			return FTSMuxChannelStreams.get()->GetCurrentTotalTSChannelBitRate();
		else
			return -1;
	}

	IntListPtr SoftMultiplexer::GetOutputPIDs()
	{
		if (FTSMuxChannelStreams)
			return FTSMuxChannelStreams.get()->GetOutputPIDs();
		else
		{
			IntListPtr TmpPtr;
			return TmpPtr;
		}
	}
}
