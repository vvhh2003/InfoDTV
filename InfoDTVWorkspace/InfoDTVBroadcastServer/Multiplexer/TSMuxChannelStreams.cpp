/*
 * TSMuxChannelStreams.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "TSMuxChannelStreams.h"
#include <boost/lexical_cast.hpp>

using namespace MultiplexerCore_V1;


void  TSMuxChannelStreams::ConfigChanged (string aStreamName,string aNewConfig )
{
	ITSChannelStreamPtr TmpStream=GetTSChannelByName(aStreamName);
	ITSDataProviderPtr DataProvider = TmpStream.get()->getDataProvider();
	{
		Poco::FastMutex::ScopedLock lock(FMutex);
		DataProvider->ConfigChanged(aNewConfig);
	}
}
int TSMuxChannelStreams::GetMaxProrityIndex(long aAverageBitRate)
{
	//				cout<<"GetMaxProrityIndex Runing..."<<std::endl;
	int MaxIndex = -1;
	//				cout<<"GetMaxProrityIndex Runing. Size "<<FChannelList.size()<<std::endl;
	//判断最大值算法
	for (unsigned int i = 0; i < FChannelList.size(); i++)
	{
		ITSChannelStreamPtr CS = FChannelList[i];
		//					cout<<"GetMaxProrityIndex Runing. "<<i<<std::endl;
		long CurrentPrority = CS.get()->getOutputPrority();
		bool isMax = true;
		for (unsigned int ii = 0; ii < FChannelList.size(); ii++)
		{
			ITSChannelStreamPtr CS2 = FChannelList[ii];
			if (CurrentPrority < CS2.get()->getOutputPrority())
			{
				isMax = false;
			}
		}
		if (isMax)
		{
			MaxIndex = i;
			break;
		}
	}
	ITSChannelStreamPtr CS3 = FChannelList[MaxIndex];
	if (CS3.get()->getOutputPrority() < aAverageBitRate)
		return -1; //比较是否大于平均值
	//				cout<<"GetMaxProrityIndex End.."<<std::endl;
	return MaxIndex;
}// TSMuxChannelStreams.GetMaxProrityIndex


//1 重新计算平均码率并设置空包流输出码率
void TSMuxChannelStreams::ReCalculateBitRate(long aCurrentTotalBitRate, bool aIsAddStream)
{
	//需要重新计算平均码率
	if (aIsAddStream)
		//需要先调用本函数再添加

	{


		//减去NullStream 加上待加入的TSStream
		FAverageBitRate = aCurrentTotalBitRate / (FChannelList.size() - 1 + 1);

	}
	else
	{
		//需要先删除再调用本函数
		if ((FChannelList.size() - 1) > 0)
			FAverageBitRate = aCurrentTotalBitRate / (FChannelList.size() - 1);//减去NullStream 减去待删除的TSStream已经先被删除掉了

		else
			//极端情况：码流全被删除
			FAverageBitRate = 0;

	}


	//空包流输出码率
	FNullPacketChannelStream.get()->setOutputBitRate(FMultiplexer->getOutputBitRate() - aCurrentTotalBitRate);
}// TSMuxChannelStreams.ReCalculateBitRate


TSMuxChannelStreams::~TSMuxChannelStreams()
{
	ClearAllStream();
	Log("<MEM>已释放！");
}
//			TSMuxChannelStreams(IMultiplexerPtr aMultiplexer) :
TSMuxChannelStreams::TSMuxChannelStreams(IMultiplexer* aMultiplexer) :FLogger(),FMutex()
{
	FLogger.setName("复用通道管理器");

	FAverageBitRate = 0;
	FMultiplexer=aMultiplexer;
	//在适当时候可以调整为纯接口
	FNullPacketChannelStream.reset(new TSChannelStream(NULLSTREAM_NAME,aMultiplexer->getOutputBitRate()));
	FChannelList.push_back(FNullPacketChannelStream);
	Log("已启动");
}

long TSMuxChannelStreams::GetCurrentTotalTSChannelBitRate()
{
	long TotalBitRate = 0;
	vector<ITSChannelStreamPtr>::iterator iter;
	for (iter = FChannelList.begin(); iter!= FChannelList.end(); iter++)
	{
		ITSChannelStreamPtr CS = *iter;
		if (!CS.get()->IsNullTS())
			TotalBitRate += CS.get()->getOutputBitRate();
	}

	return TotalBitRate;
}// TSMuxChannelStreams.GetCurrentTotalTSChannelBitRate


//1 增加输入流
/// 需要重新计算平均码率以及空包流输出码率
ITSChannelStreamPtr TSMuxChannelStreams::AddChannelStream(string AFStreamName, long AFOutputBitRate,
		ITSDataProviderPtr AFTSDataProvider, bool AIsFixOutputCounter)
{
	ITSChannelStreamPtr aStream(new TSChannelStream(AFStreamName, AFOutputBitRate, AFTSDataProvider, AIsFixOutputCounter));
	long TotalBitRate = GetCurrentTotalTSChannelBitRate();
	if ((aStream.get()->getOutputBitRate() + TotalBitRate)> FMultiplexer->getOutputBitRate())
	{
		aStream.reset();
		return aStream;
	}
	else
	{
		TotalBitRate = aStream.get()->getOutputBitRate() + TotalBitRate;
		//重新计算平均码率并设置空包流输出码率
		ReCalculateBitRate(TotalBitRate, true);
		//需要先调用函数再添加
		//lock (FChannelList.SyncRoot)
		//					lock(FChannelList)
		//					{
		Poco::FastMutex::ScopedLock lock(FMutex);
		FChannelList.push_back(aStream); //aStreamName

		//					}
	}
	return aStream;
}
ITSChannelStreamPtr TSMuxChannelStreams::AddChannelStream(string aStreamName, ITSChannelStreamPtr aStream)
{
	long TotalBitRate = GetCurrentTotalTSChannelBitRate();
	Log("Add Stream>>Total BitRate:"+boost::lexical_cast<string>(TotalBitRate));

	if ((aStream.get()->getOutputBitRate() + TotalBitRate) > FMultiplexer->getOutputBitRate())
	{
		Log("Add Stream>>Stream BitRate:"+boost::lexical_cast<string>(aStream.get()->getOutputBitRate()));
		ITSChannelStreamPtr TmpStream;
		return TmpStream;
	}

	else
	{
		TotalBitRate = aStream.get()->getOutputBitRate() + TotalBitRate;
		//重新计算平均码率并设置空包流输出码率
		ReCalculateBitRate(TotalBitRate, true);
		//需要先调用函数再添加
		//lock (FChannelList.SyncRoot)
		//				lock (FChannelList)
		//				{
		Poco::FastMutex::ScopedLock lock(FMutex);
		FChannelList.push_back(aStream); //aStreamName
		//				}
	}
	return aStream;
}

void TSMuxChannelStreams::DeleteChannelStream(string aStreamName)
{
	//if(!FChannelList.Contains(aStreamName)) return;
	if (aStreamName == NULLSTREAM_NAME)
		return;

	long TotalBitRate = GetCurrentTotalTSChannelBitRate();

	ITSChannelStreamPtr CS = GetTSChannelByName(aStreamName);
	if (!CS)
		return;
	TotalBitRate = TotalBitRate - CS.get()->getOutputBitRate();
	//需要先删除再调用计算函数
	//lock (FChannelList.SyncRoot)
	//				lock(FChannelList)
	//				{
	vector<ITSChannelStreamPtr>::iterator iter;
	Poco::FastMutex::ScopedLock lock(FMutex);
	for (iter = FChannelList.begin(); iter!= FChannelList.end(); iter++)
	{
		if ((*iter).get()->getStreamName()==aStreamName)
		{
			FChannelList.erase(iter);
			break;
		}
	}
	//	FChannelList(CS);
	//					CS.Dispose();
	//				}
	//重新计算平均码率并设置空包流输出码率
	ReCalculateBitRate(TotalBitRate, false);
}// TSMuxChannelStreams.DeleteChannelStream


long TSMuxChannelStreams::GetOutputBitRateByName(string aStreamName)
{
	ITSChannelStreamPtr CS = GetTSChannelByName(aStreamName);
	if (CS)
		return CS.get()->getOutputBitRate();
	else
		return -1;
}// TSMuxChannelStreams.GetOutputRitRateByName


StringListPtr TSMuxChannelStreams::GetOutputStreamNames()
{
//	Log("GetOutputStreamNames Stream");
	StringListPtr Names(new StringList());
	//lock (FChannelList.SyncRoot)
	//				lock (FChannelList)
	//				{
	vector<ITSChannelStreamPtr>::iterator iter;
	for (iter = FChannelList.begin(); iter!= FChannelList.end(); iter++)
	{
		Names.get()->push_back((*iter).get()->getStreamName());
	}
	//					for (int i = 0; i < FChannelList.Count; i++)
	//					{
	//						ITSChannelStream CS = (ITSChannelStream)FChannelList[i];
	//						Names[i] = CS.StreamName;
	//					}
	//				}
//	Log("GetOutputStreamNames Stream End");
	return Names;
}// TSMuxChannelStreams.GetOutputStreamNames

IntListPtr TSMuxChannelStreams::GetOutputPIDs()
{
	IntListPtr PIDsPtr(new IntList());
	//  ArrayList PIDs =new ArrayList();
	// lock (FChannelList.SyncRoot)
	//				lock(FChannelList)
	//				{

	vector<ITSChannelStreamPtr>::iterator iter;
	for (iter = FChannelList.begin(); iter!= FChannelList.end(); iter++)
	{
		IntListPtr TmpPIDsPtr=(*iter).get()->GetOutputPIDs();
		IntList::iterator Tmpiter;
		for (Tmpiter=TmpPIDsPtr.get()->begin(); Tmpiter !=TmpPIDsPtr.get()->end(); Tmpiter++)
			PIDsPtr.get()->push_back(*Tmpiter);
	}
	//					for (int i = 0; i < FChannelList.Count; i++)
	//					{
	//						ITSChannelStream CS = (ITSChannelStream)FChannelList[i];
	//						int[] SPIDs = CS.GetOutputPIDs();
	//						for (int PI=0; PI<SPIDs.Length; PI++)
	//						{
	//							PIDs.Add(SPIDs[PI]);
	//						}
	//					}
	//				}
	return PIDsPtr;
}// TSMuxChannelStreams.GetOutputStreamPIDs


ITSChannelStreamPtr TSMuxChannelStreams::GetTSChannelByName(string aChannelName)
{
	//lock (FChannelList.SyncRoot)
	//				lock(FChannelList)
	//				{
	vector<ITSChannelStreamPtr>::iterator iter;
	for (iter = FChannelList.begin(); iter!= FChannelList.end(); iter++)
	{
		ITSChannelStreamPtr CS=*iter;
		if (CS.get()->getStreamName() == aChannelName)
			return CS;
	}
	//					for (int i = 0; i < FChannelList.Count; i++)
	//					{
	//						ITSChannelStream CS = (ITSChannelStream)FChannelList[i];
	//						if (CS.StreamName == aChannelName)
	//							return CS;
	//					}
	//				}
	ITSChannelStreamPtr CS;
	return CS;
}// TSMuxChannelStreams.GetTSChannelByName


//1 实现复用调度输出
/// 具体步骤：
/// 1、判断每一个TSChannelStream是否能够输出
/// 2、输出该TSChannelStream的包
TSPacketStructPtr TSMuxChannelStreams::OutputPacket()
{
	//				cout<<"OutputPacket Runing..."<<std::endl;
	TSPacketStructPtr OTSP = TSPacketStruct::NewNullTSPacket();
	//				cout<<"OutputPacket Runing. 1.."<<std::endl;
	//需要锁住List
	//lock (FChannelList.SyncRoot)
	//			lock (FChannelList)
	//			{
	/// 若当前FPrority大于aAverageBitRate且在TotalBitRates等于最大
	/// 则FPrority减去aAverageBitRate返回True
	/// 若当前FPrority小于aAverageBitRate或在TotalBitRates不等于最大
	/// 则FPrority加上aAverageBitRate返回False
	int MaxIndex =-1;
	{
		Poco::FastMutex::ScopedLock lock(FMutex);
		MaxIndex = GetMaxProrityIndex(FAverageBitRate);//
	}
	//FLog.Debug(String.Format("TSMuxChannelStreams.OutputStream:{0}", MaxIndex));
	//				cout<<"OutputPacket Runing. 1.."<<std::endl;
	if (MaxIndex == -1) //不满足平均大于条件

	{
		vector<ITSChannelStreamPtr>::iterator iter;
		for (iter = FChannelList.begin(); iter!= FChannelList.end(); iter++)
		{
			ITSChannelStreamPtr CS=*iter;
			CS.get()->ResetOutputPrority();
		}
		//					for (int i = 0; i < FChannelList.Count; i++)
		//					{
		//						ITSChannelStream CS = FChannelList[i] as ITSChannelStream;
		//						CS.ResetOutputPrority();
		//					}
		{
			Poco::FastMutex::ScopedLock lock(FMutex);
			MaxIndex = GetMaxProrityIndex(FAverageBitRate);
		}

	}
	//				cout<<"OutputPacket Runing. 2.."<<std::endl;
	ITSChannelStreamPtr MaxProrityCS = FChannelList[MaxIndex];
	//	FLog.Debug(String.Format("TSMuxChannelStreams.OutputStream:Output {0}", MaxProrityCS.StreamName));
	//这种情况从算法数学上不可能出现if(MaxProrityCS.OuputPrority<FAverageBitRate){}
	//System.Diagnostics.Debug.Assert(MaxProrityCS.OuputPrority<FAverageBitRate);
	//				cout<<"OutputPacket Runing. 3.."<<std::endl;
	{
		Poco::FastMutex::ScopedLock lock(FMutex);
		OTSP = MaxProrityCS.get()->GetTSPacket();
	}
	MaxProrityCS.get()->DecOutputPrority(FAverageBitRate);
	//			}
	//				cout<<"OutputPacket Ending..."<<std::endl;
	return OTSP;
}// TSMuxChannelStreams.OutputPacket


void TSMuxChannelStreams::ReCalculateMuxStreamsBitRate()
{
	long TotalBitRate = GetCurrentTotalTSChannelBitRate();
	ReCalculateBitRate(TotalBitRate, false);
}

void TSMuxChannelStreams::ClearAllStream()
{
	//				lock(FChannelList)
	//				{
	//				while (FChannelList.Count>0)
	//				{
	//					FChannelList.Remove(FChannelList[0]);
	//				}
	//				}
	FChannelList.clear();
}

void TSMuxChannelStreams::ResetStreams()
{
	//				lock(FChannelList)
	//				{
	vector<ITSChannelStreamPtr>::iterator iter;
	for (iter = FChannelList.begin(); iter!= FChannelList.end(); iter++)
	{
		ITSChannelStreamPtr CS=*iter;
		CS.get()->Reset();
	}
	//					for (int i = 0; i < FChannelList.Count; i++)
	//					{
	//						ITSChannelStream CS = FChannelList[i];
	//						CS.Reset();
	//					}
	//				}
}

