/*
 * DektecTSBroadcastThread.cpp
 *
 *  Created on: 2009-4-10
 *      Author: victor
 */
#include "DektecTSBroadcastThread.h"

namespace MultiplexerCore_V1
{
	bool DektecTSBroadcastThread::CheckResult(DTAPI_RESULT AResult, bool AIsNeedBreak, string AErrorStr)
	{
		if (AResult!=DTAPI_OK)
		{
			Log(AErrorStr+":"+boost::lexical_cast<string>(AResult));
			if (AIsNeedBreak)
				return false;
		}
		return true;
	}

	void DektecTSBroadcastThread::run()
	{
		Log("BroadcastThread Thread Start Runing!");
#ifdef DektecTRIAL
		Log("体验模式");
		bool IsTrialInfoed=false;
		unsigned int TrialInfoed=0;
#else
	Log("锁定模式！！特征CPUID，MAC，硬盘ID DTAPI ID");
#endif
		if(!initDevice())
		{
			Log("初始化失败！请检查锁定状态");
			Log("Broadcast Ending...");
			UnloadDriver();
			Log("Broadcast Ended");
			return ;
		}
		InitOutputPort(0, FBitRate);
		long BufferLength=FCB->getBufferLength();
		try
		{

			while(!FIsStoped)
			{
#ifdef DektecTRIAL
				Poco::DateTime NowDateTime;
				if(FStartDateTime+Poco::Timespan(0,5,0,0,0)<NowDateTime)
				{
					if(!IsTrialInfoed&&TrialInfoed<5)
					{
						Log("体验模式-结束！");
						TrialInfoed++;
					}
					Poco::Thread::sleep(10000);
					continue;
				}
#endif
				RawBufferPtr TmpBuffer=FCB->getBuffer();

				//						int AiDevicePort, int AiBufferLength,
				//											const unsigned char* AiBuffer
				OutputBuffer(0,BufferLength,TmpBuffer.get());
				if(FIsStoped)
					break;

			}
		}
		catch(...)
		{
			Log("ERROR FIND!!");
			UnloadOutputPort(0);
			UnloadDriver();
		}
		Log("Broadcast Ending...");
		UnloadOutputPort(0);
		UnloadDriver();
		Log("Broadcast Ended");
	}


	bool DektecTSBroadcastThread::InitOutputPort(int AiPortNum, int AiBitRate)
	{
		if (!FIsDeviceInited)
		{
			Log("InitOutputPort  Driver not Init!");
			return false;
		}
		string Tstr1("InitOutputPort  BitRate Is:");
		Tstr1=Tstr1+boost::lexical_cast<std::string>(AiBitRate);
		Log(Tstr1.c_str());

		DTAPI_RESULT Result=FOutputChannel.Attach(&FDevice, 0);
		if (Result == DTAPI_OK_FAILSAFE)
		{
			Log("该设备具备故障保护能力！");
			FOutputChannel.SetFailsafeConfig(false);
			Log("故障保护关闭！");
			Result = DTAPI_OK;
		}
		if (!CheckResult(Result, true, "InitOutputPort Attach to Device Error:"))
		{
			return false;
		}
		Log("InitOutputPort  Attach OK");

		if (FIsQAMDevice)
		{
			Log("InitOutputPort  IsQAMDevice");
			Result=FOutputChannel.SetRfControl(FQAMHz);
			CheckResult(Result, false, "InitOutputPort SetRfControl Error:");

			string Tstr1("InitOutputPort  QAMSetting Is:");
			Tstr1=Tstr1+boost::lexical_cast<std::string>(FQAMHz);
			Log(Tstr1);
			Result =FOutputChannel.SetModControl(DTAPI_MOD_QAM64, DTAPI_MOD_J83_A,0,0);
			CheckResult(Result, false, "InitOutputPort SetModControl Error:");

			Log("InitOutputPort  QAMDevice Setting OK!");
		};
		Result=FOutputChannel.SetTsRateBps(AiBitRate);
		CheckResult(Result, false, "InitOutputPort SetTsRateBps Error:");
		Log("InitOutputPort  SetTsRateBps OK!");
		Result=FOutputChannel.SetTxControl(DTAPI_TXCTRL_IDLE);
		CheckResult(Result, false, "InitOutputPort SetTxControl1 Error:");
		Log("InitOutputPort  DTAPI_TXCTRL_IDLE OK!");

		Result=FOutputChannel.SetTxMode(DTAPI_TXMODE_188, DTAPI_TXSTUFF_MODE_OFF);
		CheckResult(Result, false, "InitOutputPort SetTxMode Error:");

		int TmpFifosize=0;
		Result=FOutputChannel.GetMaxFifoSize(TmpFifosize);
		CheckResult(Result, false, "InitOutputPort GetMaxFifoSize Error:");

		string str1("InitOutputPort  GetMaxFifoSize OK! Size Is:");
		str1=str1+boost::lexical_cast<std::string>(AiBitRate);
		Log(str1);
		Result=FOutputChannel.SetFifoSizeMax();
		CheckResult(Result, false, "InitOutputPort SetFifoSizeMax Error:");
		Log("InitOutputPort  SetMaxFifoSize OK!");

		Result=FOutputChannel.ClearFifo();
		CheckResult(Result, false, "InitOutputPort ClearFifo Error:");
		Result=FOutputChannel.SetTxControl(DTAPI_TXCTRL_HOLD);
		CheckResult(Result, false, "InitOutputPort SetTxControl2 Error:");

		FIsSendBegined=false;
		FIsOutputChannelInited=true;
		Log("InitOutputPort   OK!");
		return true;
	}

	bool DektecTSBroadcastThread::initDevice()
	{
		DTAPI_RESULT Result=FDevice.AttachToType(FDeviceType);
		if (!CheckResult(Result, true, "InitDriverByType Error:"))
		{
			return false;
		}
#ifndef DektecTRIAL
		char TT[64];
		std::memset(TT,0,64);
//		string SN="2145000742";万州
//		string SN="2145000625"; //首页服务器
//		string SN="2145001018"; //川外服务器
//		string SN="2145001224"; //重大1
//		string SN="2145002131"; //重大2
//		string SN="2145002598"; //后工
		string SN="2145002597"; //川美
//		string SN="4145000631"; //ZMC设备1

		Result=FDevice.VpdRead("SN",TT);
		if (!CheckResult(Result, true, "Check Device Error:"))
		{
			return false;
		}
		string TmpStr=TT;

		if(TmpStr!=SN)
			return false;
#endif

		if (FDeviceType==110||FDeviceType==115)
		{
			FIsQAMDevice=true;
			string Tstr1("InitDriverByType  QAMSetting Is:");
			Tstr1=Tstr1+boost::lexical_cast<std::string>(FQAMHz);
			Log(Tstr1.c_str());
		};
		FIsDeviceInited=true;
		Log("Init Driver OK");
		return true;

	}

	bool DektecTSBroadcastThread::UnloadOutputPort(int AiPortNum)
	{
		if (!FIsDeviceInited||!FIsOutputChannelInited)
		{
			return false;
		}
		if (FIsOutputChannelInited)
		{
			DTAPI_RESULT Result= FOutputChannel.SetTxControl(DTAPI_TXCTRL_IDLE);
			CheckResult(Result, false, "UnloadOutputPort SetTxControl Error:");
			Result=FOutputChannel.Detach(DTAPI_INSTANT_DETACH);
			if (!CheckResult(Result, false, "UnloadOutputPort Detach Error:"))
			{
				return false;
			}
			FCurrentSendBytes=0;
			FIsOutputChannelInited=false;
			FIsSendBegined=false;
		}
		Log("UnloadOutputPort OK");
		return true;
	}

	bool DektecTSBroadcastThread::UnloadDriver()
	{

		if (FIsOutputChannelInited)
		{
			if (!UnloadOutputPort(0))
			{
				return false;
			}
			FIsOutputChannelInited=false;
		}
		if (FIsDeviceInited)
		{
			DTAPI_RESULT Result=FDevice.Detach();
			if (!CheckResult(Result, true, "UnloadDriver Error:"))
			{
				return false;
			}
			FIsDeviceInited=false;
		}
		Log("UnloadDriver OK");
		return true;
	}

	void DektecTSBroadcastThread::OutputBuffer(int AiDevicePort, int AiBufferLength,
			const unsigned char* AiBuffer)
	{
		if (!FIsOutputChannelInited)
			return;
		if (!FIsSendBegined)
		{
			FOutputChannel.SetTxControl(DTAPI_TXCTRL_SEND);
			Log("OutputBuffer Begin Send!");
			FIsSendBegined=true;
		}
		DTAPI_RESULT Result=FOutputChannel.Write((char *)AiBuffer, AiBufferLength);
		if (!CheckResult(Result, true, "OutputBuffer Write Error:"))
		{
			return;
		}
		FCurrentSendBytes+=AiBufferLength;
	}


	DektecTSBroadcastThread::DektecTSBroadcastThread(int aDeviceType, long aQAMHz, long aBitRate,
			InfoDTV_Common_Buffer::CircularBufferPtr aCB) :FLogger(),
			FDeviceType(aDeviceType), FQAMHz(aQAMHz), FBitRate(aBitRate), FIsStoped(false), FCB(aCB),
			FActivity(this,&DektecTSBroadcastThread::run)
			{
		FLogger.setName("DektecTSBroadcastThread");
			}

	DektecTSBroadcastThread::~DektecTSBroadcastThread()
	{
		if(!FIsStoped)
		{
			Stop();
		}
	}

	void DektecTSBroadcastThread::Start()
	{
		FIsStoped=false;
		FActivity.start();
	}

	void DektecTSBroadcastThread::Stop()
	{
		FIsStoped=true;
		Log("停止中.1..");
		if (FCB->IsBufferReaderBlocked())
		{
			Log("停止中..正在解决播出线程缓冲锁...");
			long BufferLength=FCB->getBufferLength();

			//					RawBufferPtr TmpBuffer(new unsigned char[BufferLength]);
			RawBufferPtr TmpBuffer((unsigned char *)std::malloc(BufferLength),&free);
			std::memset((void *)TmpBuffer.get(), 0, BufferLength);
			FCB->setBuffer(BufferLength, TmpBuffer);
			Log("停止中..播出线程缓冲锁已解决...");
		}
		Log("停止中.2..");
		FActivity.wait();
		Log("线程：播出线程 停止完成！");

	}
}
