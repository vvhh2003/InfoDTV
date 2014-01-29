/*
 * TSChannelStream.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "TSChannelStream.h"

using namespace MultiplexerCore_V1;

TSPacketStructPtr TSChannelStream::ReadTSPacket()
{
	if (FTSDataProvider)
	{
		TSPacketStructPtr OutPutPacket = FTSDataProvider.get()->GetTSPacket();
		return OutPutPacket;
	}
	else
		return TSPacketStruct::NewNullTSPacket();
}// TSChannelStream.ReadTSPacket

TSChannelStream::~TSChannelStream()
{

}

TSChannelStream::TSChannelStream(const string AFStreamName, long AFOutputBitRate):
    FIsNullStream(false),FOutputPIDTSCountTable(),FOutputBitRate(AFOutputBitRate),
  		    FOutputPrority(AFOutputBitRate),FStreamName(AFStreamName),
  		    FTSDataProvider(),FIsFixOutputCounter(false)
{
	FIsNullStream=false;
	FOutputBitRate = AFOutputBitRate;
	FOutputPrority = AFOutputBitRate;
	//FStreamName ="";
	FIsFixOutputCounter = false;
	//FTSDataProvider.reset();
//	if (AFStreamName.empty())
//	{
//		FStreamName ="Empty";
//		FIsFixOutputCounter = false;
//
//		FIsNullStream = true;
//	}
//	else
//	{
//		FStreamName = AFStreamName;
//	}

	FIsNullStream = true;
	FIsFixOutputCounter = false;

	if (AFOutputBitRate != -1)
		FOutputBitRate = AFOutputBitRate;
}


//			TSChannelStream(string AFStreamName, long AFOutputBitRate,	ITSDataProviderPtr AFTSDataProvider)
//			{
//				TSChannelStream(AFStreamName, AFOutputBitRate, AFTSDataProvider,	false);
//			}

TSChannelStream::TSChannelStream(string AFStreamName, long AFOutputBitRate,
	ITSDataProviderPtr AFTSDataProvider,bool AIsFixOutputCounter):
		    FIsNullStream(false),FOutputPIDTSCountTable(),FOutputBitRate(AFOutputBitRate),
		    FOutputPrority(AFOutputBitRate),FStreamName(AFStreamName),
		    FTSDataProvider(AFTSDataProvider),FIsFixOutputCounter(false)
{
	FIsNullStream=false;
	FOutputBitRate = AFOutputBitRate;
	FOutputPrority = AFOutputBitRate;
	//FStreamName ="";
	FIsFixOutputCounter = false;

	if (AFStreamName.empty())
	{
		FStreamName ="Empty";
	}
	else
	{
		FStreamName = AFStreamName;
	}

	if (AIsFixOutputCounter)
		FIsFixOutputCounter = AIsFixOutputCounter;
	if (AFTSDataProvider)
	{
		FTSDataProvider = AFTSDataProvider;
		FTSDataProvider.get()->Active();
		FIsNullStream = false;
	}
	else
	{
		FIsNullStream = true;
	}
	if (AFOutputBitRate != -1)
		FOutputBitRate = AFOutputBitRate;

}
void TSChannelStream::DecOutputPrority(long aAverageBitRate)
{
	FOutputPrority -= aAverageBitRate;
}

TSPacketStructPtr TSChannelStream::GetTSPacket()
{
	TSPacketStructPtr TmpOut = ReadTSPacket();

	if (FIsFixOutputCounter)
	{
		unsigned short PID = TmpOut.get()->GetPID();
		//					lock(FOutputPIDTSCountTable)
		//					{
		if (PID != 0x1FFF)
		{


			//							if (!FOutputPIDTSCountTable.ContainsKey(PID))
			if (FOutputPIDTSCountTable.count(PID)==0)
			{
				FOutputPIDTSCountTable[PID]= 15;
			}
//			if (TmpOut.get()->IsCanFixCount())//TSPacketStruct.IsCanFixCount(ref TmpOut)

			{
				FOutputPIDTSCountTable[PID]++;
				if (FOutputPIDTSCountTable[PID] == 16)
				{
					FOutputPIDTSCountTable[PID] = 0;
				}
				//TSPacketStruct.FixNotNULLCount(TmpOut, FOutputPIDTSCountTable[PID]);
				TmpOut.get()->FixCount(FOutputPIDTSCountTable[PID]);
			}

			//							else
			//							{
			//								TSPacketStruct.FixNotNULLCount(TmpOut, FOutputPIDTSCountTable[PID]);
			//							}

		}
//		else
//		{
//			return TSPacketStruct::NewNullTSPacket();
//		}
	}
	//				}
	return TmpOut;
}

IntListPtr TSChannelStream::GetOutputPIDs()
{

	IntListPtr PIDs(new IntList());//FOutputPIDTSCountTable.size()
	//FOutputPIDTSCountTable.Keys.CopyTo(PIDs,0);
	map<unsigned short, unsigned char>::iterator iter;
	for (iter = FOutputPIDTSCountTable.begin(); iter
	!= FOutputPIDTSCountTable.end(); iter++)
	{
		//Cout<<iter->first<<”   ”<<iter->second<<end;
		PIDs.get()->push_back(iter->first);
	}
	return PIDs;
}
void TSChannelStream::ResetCounter()
{
	FOutputPIDTSCountTable.clear();
}

void TSChannelStream::InitOutputPrority()
{
	FOutputPrority = FOutputBitRate;
}
bool TSChannelStream::IsNullTS()
{
	return FIsNullStream;
}

void TSChannelStream::Reset()
{
	if (FTSDataProvider)
	{
		FTSDataProvider.get()->Reset();
	}
	FOutputPIDTSCountTable.clear();
	InitOutputPrority();
}
void TSChannelStream::ResetOutputPrority()
{
	FOutputPrority += FOutputBitRate;
}// TSChannelStream.ResetOutputPrority

void TSChannelStream::SwitchProvider(ITSDataProviderPtr aTSDataProvider)
{
	//FTSDataProvider.Dispose();
	FTSDataProvider = aTSDataProvider;

}// TSChannelStream.SwitchProvider

ITSDataProviderPtr TSChannelStream::getDataProvider()
{
	return FTSDataProvider;
}

bool TSChannelStream::getIsFixOutputCounter()
{
	return FIsFixOutputCounter;
}

void TSChannelStream::setIsFixOutputCounter(bool aIsFix)
{
	if (FIsFixOutputCounter != aIsFix)
	{
		FIsFixOutputCounter = aIsFix;
	}
}

long TSChannelStream::getOutputPrority()
{
	return FOutputPrority;
}

long TSChannelStream::getOutputBitRate()
{
	return FOutputBitRate;
}

void TSChannelStream::setOutputBitRate(long aNewBitRate)
{
	if (FOutputBitRate != aNewBitRate)
	{
		FOutputBitRate = aNewBitRate;
		FOutputPrority = FOutputBitRate;
	}
}

string TSChannelStream::getStreamName()
{
	return FStreamName;
}

void TSChannelStream::setStreamName(string aStreamName)
{
	if (FStreamName != aStreamName)
		FStreamName = aStreamName;
}
