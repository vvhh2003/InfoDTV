#ifndef DEKTECTSBROADCASTTHREAD_H_
#define DEKTECTSBROADCASTTHREAD_H_

#define USE_POCO_THREAD
//#define DektecTRIAL

#include <boost/lexical_cast.hpp>
#include "../../Common/CircularBuffer.h"
#include "../../Common/TSPacketStruct.h"

#ifdef USE_ICE_THREAD
#include <IceUtil/Thread.h>
#endif
#ifdef USE_POCO_THREAD
#include "Poco/Activity.h"
#include "Poco/Thread.h"
#endif

#ifdef DektecTRIAL
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#endif

#include "DTAPI.h"


namespace MultiplexerCore_V1
{
	const int FifoSize=188*1024*80; //15M
//	const int TS_DataBuffer_Length=FifoSize;
#ifdef USE_ICE_THREAD
	class DektecTSBroadcastThread : public IceUtil::Thread
	{

		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}
			int FDeviceType;
			long FQAMHz;
			long FBitRate;
			bool FIsStoped;
			InfoDTV_Common_Buffer::CircularBufferPtr FCB;
			IceUtil::ThreadControl FThreadControl;

			DtDevice FDevice;
			//DtInpChannel InputChannel;
			DtOutpChannel FOutputChannel;
			bool FIsDeviceInited;//=false;
			bool FIsQAMDevice;//=false;
			bool FIsInputChannelInited;//=false;
			bool FIsOutputChannelInited;//=false;
			//			bool FIsSendBegined;//=false;
			//			__int64 QAMHz;//=400000000;

			int FLogCounter;//=0;
			int FCurrentSendBytes;//=0;
			bool FIsSendBegined;//=false;

			bool CheckResult(DTAPI_RESULT AResult, bool AIsNeedBreak, string AErrorStr)
			{
				if (AResult!=DTAPI_OK)
				{
					Log(AErrorStr+":"+AResult);
					if (AIsNeedBreak)
						return false;
				}
				return true;
			}

			virtual void run()
			{
				cout<<"BroadcastThread Thread Start Runing!"<<endl;
				initDevice();
				InitOutputPort(0, FBitRate);
				long BufferLength=FCB->getBufferLength();
				try
				{
					while(!FIsStoped)
					{
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

			bool InitOutputPort(int AiPortNum, int AiBitRate)
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

			bool initDevice()
			{
				DTAPI_RESULT Result=FDevice.AttachToType(FDeviceType);
				if (!CheckResult(Result, true, "InitDriverByType Error:"))
				{
					return false;
				}

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

			bool UnloadOutputPort(int AiPortNum)
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

			bool UnloadDriver()
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

			void OutputBuffer(int AiDevicePort, int AiBufferLength,
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

		public:

			DektecTSBroadcastThread(int aDeviceType, long aQAMHz, long aBitRate,
					InfoDTV_Common_Buffer::CircularBufferPtr aCB) :FLogger(),
					FDeviceType(aDeviceType), FQAMHz(aQAMHz), FBitRate(aBitRate), FIsStoped(true), FCB(aCB)
					{
				FLogger.setName("DektecTSBroadcastThread");
					}

			~DektecTSBroadcastThread()
			{
				if(FIsStoped)
				{
					Stop();
				}
			}
			void Start()
			{
				FThreadControl=this->start();
			}

			void Stop()
			{
				FIsStoped=true;
				if (FCB->IsBufferReaderBlocked())
				{
					//					RawBufferPtr TmpBuffer(new unsigned char[TS_DataBuffer_Length]);
					RawBufferPtr TmpBuffer((unsigned char *)std::malloc(TS_DataBuffer_Length),&free);
					FCB->setBuffer(TS_DataBuffer_Length, TmpBuffer);
				}

			}
	};
#endif
#ifdef USE_POCO_THREAD
	class DektecTSBroadcastThread
	{

		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			void Log(string ALogStr)
			{
				FLogger.information(ALogStr);
			}
			int FDeviceType;
			long FQAMHz;
			long FBitRate;
			bool FIsStoped;
			InfoDTV_Common_Buffer::CircularBufferPtr FCB;

			DtDevice FDevice;
			//DtInpChannel InputChannel;
			DtOutpChannel FOutputChannel;
			bool FIsDeviceInited;//=false;
			bool FIsQAMDevice;//=false;
			bool FIsInputChannelInited;//=false;
			bool FIsOutputChannelInited;//=false;
			//			bool FIsSendBegined;//=false;
			//			__int64 QAMHz;//=400000000;

			int FLogCounter;//=0;
			int FCurrentSendBytes;//=0;
			bool FIsSendBegined;//=false;
#ifdef DektecTRIAL
			Poco::DateTime FStartDateTime;
#endif
			Poco::Activity<DektecTSBroadcastThread> FActivity;
			bool CheckResult(DTAPI_RESULT AResult, bool AIsNeedBreak, string AErrorStr);

			virtual void run();

			bool InitOutputPort(int AiPortNum, int AiBitRate);

			bool initDevice();

			bool UnloadOutputPort(int AiPortNum);

			bool UnloadDriver();

			void OutputBuffer(int AiDevicePort, int AiBufferLength,const unsigned char* AiBuffer);

		public:

			DektecTSBroadcastThread(int aDeviceType, long aQAMHz, long aBitRate,
					InfoDTV_Common_Buffer::CircularBufferPtr aCB);

			~DektecTSBroadcastThread();
			void Start();
			void Stop();
	};
#endif
	typedef boost::shared_ptr<DektecTSBroadcastThread> DektecTSBroadcastThreadPtr;
}

#endif /*DEKTECTSBROADCASTTHREAD_H_*/
