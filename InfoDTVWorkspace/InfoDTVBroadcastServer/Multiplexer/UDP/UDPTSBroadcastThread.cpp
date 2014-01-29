/*
 * UDPTSBroadcastThread.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "UDPTSBroadcastThread.h"

using namespace MultiplexerCore_V1;
#ifdef USE_ICE_THREAD

void UDPTSBroadcastThread::run()
{

	Log("线程：播出线程 开始运行！.");
	long BufferLength=FCB->getBufferLength();
	try
	{
		while(!FIsStoped)
		{
			RawBufferPtr TmpBuffer=FCB->getBuffer();
			if(FIsStoped)
				break;
			OutputBuffer(BufferLength,TmpBuffer);
		}
	}
	catch(...)
	{
		Log("线程：播出线程 ERROR FIND!!！.");

	}
	Log("线程：播出线程 结束运行...");
}

void UDPTSBroadcastThread::OutputBuffer(const int AiBufferLength, RawBufferPtr AiBuffer)
{
	if (!FIsSendBegined)
	{
		Log("线程：播出线程 开始播出.");
		FIsSendBegined=true;
	}
	//				DTAPI_RESULT Result=FOutputChannel.Write((char *)AiBuffer, AiBufferLength);


	int SendCount=AiBufferLength/(188*7);
	SendCount+=(AiBufferLength%(188*7)>0 ? 0 : 1);
	bool IsModBy188=AiBufferLength%(188*7)>0;
//	bool IsCountModBy7=SendCount%7>0;
	int RestCountModBy7=SendCount-SendCount%7;
//	FUDPRateLimiter.ToSendData(AiBufferLength);
	for (int i=0; i<SendCount; i++)
	{
		if (FIsStoped)
			return;
		void * TVBuffer=(void *)(AiBuffer.get()+i*188*7);
		if(i%7==0)
		    FUDPRateLimiter.ToSendData(7*188*7);
		if(i==RestCountModBy7)
		    {
			 FUDPRateLimiter.ToSendData(AiBufferLength-i*188*7);
		    }
		if(IsModBy188&&i==(SendCount-1))
		{


//			FUDPRateLimiter.ToSendData(AiBufferLength-i*188*7);
			sendto(FUdpsock, TVBuffer, AiBufferLength-i*188*7, MSG_DONTWAIT, (struct sockaddr *) &FSIPAddress,
					sizeof(FSIPAddress));
			if(FDebugFile.is_open())
			{
				FDebugFile.write((char *)TVBuffer, AiBufferLength-i*188*7);
			}
		}
		else
		{
//			FUDPRateLimiter.ToSendData(188*7);
			sendto(FUdpsock, TVBuffer, 188*7, MSG_DONTWAIT, (struct sockaddr *) &FSIPAddress,
					sizeof(FSIPAddress));
			if(FDebugFile.is_open())
			{
				FDebugFile.write((char *)TVBuffer, 188*7);
			}
		}

	}

	FCurrentSendBytes+=AiBufferLength;
}


UDPTSBroadcastThread::UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
		InfoDTV_Common_Buffer::CircularBufferPtr aReadCB) :
			FIPAddress(aIPAddress), FIPPort(aIPPort), FBitRate(aBitRate), FIsStoped(true), FIsNetworkReady(false),
			FCB(aReadCB), FUDPRateLimiter(aBitRate),FIsSendBegined(false),FDebugTSFileName(""),FLogger()
			{
	FLogger.setName("UDPTSBroadcastThread");
	Log("线程：播出线程 初始化中...");//<<std::endl;
			}


UDPTSBroadcastThread::UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
		InfoDTV_Common_Buffer::CircularBufferPtr aReadCB,std::string aDebugTSFile) :
			FIPAddress(aIPAddress), FIPPort(aIPPort), FBitRate(aBitRate), FIsStoped(true), FIsNetworkReady(false),
			FCB(aReadCB), FUDPRateLimiter(aBitRate),FIsSendBegined(false),FDebugTSFileName(aDebugTSFile),FLogger()
			{
	FLogger.setName("UDPTSBroadcastThread");
	Log("线程：播出线程 初始化中...");//<<std::endl;
	FDebugFile.open(FDebugTSFileName.c_str(),std::ios::out);
			}

void UDPTSBroadcastThread::InitNetwork()
{
	Log("线程：播出线程 正在初始化网络中..");
	FUdpsock = socket(AF_INET, SOCK_DGRAM, 0);
	FSIPAddress.sin_family = AF_INET;
	FSIPAddress.sin_addr.s_addr = inet_addr(FIPAddress.c_str());//inet_addr("192.168.0.1");
	FSIPAddress.sin_port = htons(FIPPort);
	const int on = 1; // option value for setsock
	/*  Clarify that we really want to do a broadcast and that this isn't
				 a mistake. The socket system makes this necessary just in case
				 we're a program that takes an IP address at the command line and
				 the user fooled us into making a broadcast.
	 */
	setsockopt(FUdpsock, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on));
	FIsNetworkReady=true;
}

UDPTSBroadcastThread::~UDPTSBroadcastThread()
{
    //				cout<<"<MEM>线程：播出线程  释放中..."<<std::endl;
    if(FDebugFile.is_open())
	FDebugFile.close();
    Log("<MEM>释放中...");
    if (!FIsStoped)
	{
	    Stop();
	}

    if(isAlive())
	FThreadControl.join();
    Log("停止中.2..");
    if (FIsNetworkReady)
	close(FUdpsock);
    FIsNetworkReady=false;
    Log("线程：播出线程 停止完成！");
    Log("<MEM>已释放...");
    //				cout<<"<MEM>线程：播出线程  已释放..."<<std::endl;
}

void UDPTSBroadcastThread::Start()
{
	InitNetwork();
	FIsStoped=false;
	FThreadControl=this->start();
}

void UDPTSBroadcastThread::Stop()
{
	Log("线程：播出线程 停止中...");
	FIsStoped=true;
	Log("停止中.1..");


}
#endif
#ifdef USE_POCO_THREAD

bool CheckID()
{
	unsigned char eth0[]={0x0,0x21,0x5A,0xD3,0xD9,0xF0};
	unsigned char eth1[]={0x0,0x21,0x5A,0xD3,0xD9,0xF1};
	unsigned char eth2[]={0x0,0x21,0x5A,0xD3,0xD9,0xF2};
	bool eth0OK=false;
	bool eth1OK=false;
	bool eth2OK=false;
	for(unsigned int i=0;i<3;i++)
	{
		if(CheckMAC(i,eth0))
			eth0OK=true;
	}
	for(unsigned int i=0;i<3;i++)
	{
		if(CheckMAC(i,eth1))
			eth1OK=true;
	}
	for(unsigned int i=0;i<3;i++)
	{
		if(CheckMAC(i,eth2))
			eth2OK=true;
	}
	if(eth0OK||eth1OK||eth2OK)
		return true;
	else
		return false;

}
void UDPTSBroadcastThread::run()
{

	Log("线程：播出线程 开始运行！.");
#ifdef TRIAL
	Log("体验模式");
	bool IsTrialInfoed=false;
	unsigned int TrialInfoed=0;
#else

	Log("锁定模式！！特征CPUID，MAC，硬盘ID");
	if(!CheckID())
	{
		Log("锁定模式！！终止");
		Log("线程：播出线程 结束运行...");
		return;
	}
#endif

	long BufferLength=FCB->getBufferLength();
	try
	{
		while(!FActivity.isStopped())
		{
#ifdef TRIAL
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
			if(FActivity.isStopped())
				break;
			OutputBuffer(BufferLength,TmpBuffer);
		}
	}

	catch(...)
	{
		Log("线程：播出线程 ERROR FIND!!！.");

	}
	Log("线程：播出线程 结束运行...");
}
/*
void UDPTSBroadcastThread::OutputBuffer(const int AiBufferLength, RawBufferPtr AiBuffer)
{
	if (!FIsSendBegined)
	{
		Log("线程：播出线程 开始播出.");
		FIsSendBegined=true;
	}
	//				DTAPI_RESULT Result=FOutputChannel.Write((char *)AiBuffer, AiBufferLength);



	int SendCount=AiBufferLength/(188*7);
	SendCount+=(AiBufferLength%(188*7)>0 ? 0 : 1);
	bool IsModBy188=AiBufferLength%(188*7)>0;
//	bool IsCountModBy7=SendCount%7>0;
	int RestCountModBy7=SendCount-SendCount%7;
//	FUDPRateLimiter.ToSendData(AiBufferLength);
	for (int i=0; i<SendCount; i++)
	{
		if (FActivity.isStopped())
			return;
		void * TVBuffer=(void *)(AiBuffer.get()+i*188*7);
		if(i%7==0)
		    FUDPRateLimiter.ToSendData(7*188*7);
		if(i==RestCountModBy7)
		    {
			 FUDPRateLimiter.ToSendData(AiBufferLength-i*188*7);
		    }
		if(IsModBy188&&i==(SendCount-1))
		{


//			FUDPRateLimiter.ToSendData(AiBufferLength-i*188*7);
			sendto(FUdpsock, TVBuffer, AiBufferLength-i*188*7, MSG_DONTWAIT, (struct sockaddr *) &FSIPAddress,
					sizeof(FSIPAddress));
			if(FDebugFile.is_open())
			{
				FDebugFile.write((char *)TVBuffer, AiBufferLength-i*188*7);
			}
		}
		else
		{
//			FUDPRateLimiter.ToSendData(188*7);
			sendto(FUdpsock, TVBuffer, 188*7, MSG_DONTWAIT, (struct sockaddr *) &FSIPAddress,
					sizeof(FSIPAddress));
			if(FDebugFile.is_open())
			{
				FDebugFile.write((char *)TVBuffer, 188*7);
			}
		}

	}

	FCurrentSendBytes+=AiBufferLength;
}

*/


void UDPTSBroadcastThread::OutputBuffer(const int AiBufferLength, RawBufferPtr AiBuffer)
{
	if (!FIsSendBegined)
	{
		Log("线程：播出线程 开始播出.");
		FIsSendBegined=true;
	}
	//				DTAPI_RESULT Result=FOutputChannel.Write((char *)AiBuffer, AiBufferLength);

/*
 * 1、计算长度拆分 是否能被188＊7整除 得到 SendCountBy188X7
 * 2、若不能被188＊7整除 SendCountBy188X7＋＝1
 * 3、循环开始
 * 4、是否是最后一次循环＝＝SendCountBy188X7 ，若是构造一个188X7的缓冲区将最后部分复制到其中，然后发送
 * 5、若否发送i*188*7位置的长度为188＊7的数据。
 */

	unsigned int SendCountBy188X7=AiBufferLength/(188*7);
	unsigned int RestBytes=AiBufferLength-SendCountBy188X7*188*7;
	SendCountBy188X7+=(RestBytes>0 ? 1 : 0);
	unsigned int RepairePacketCount=(AiBufferLength-RestBytes)/188;
	RawBufferPtr LastBuffer;
	if(RestBytes>0)
	{
		TSPacketStructPtr TmpTSPacketPtr= TSPacketStruct::NewNullTSPacket();
		void * TVBuffer=(void *)(AiBuffer.get()+(SendCountBy188X7-1)*188*7);

		LastBuffer.reset((unsigned char *)std::malloc(188*7),&free);
		std::memcpy(LastBuffer.get(),(unsigned char*)TVBuffer,RestBytes);
		unsigned char * TmpTargetPtr=LastBuffer.get()+RestBytes;
		for(unsigned int TmpI=0;TmpI<RepairePacketCount;TmpI++)
		{
			std::memcpy(TmpTargetPtr,TmpTSPacketPtr.get(),188);
			TmpTargetPtr+=188;
		}
	}

	for (unsigned int i=0; i<SendCountBy188X7; i++)
	{
		if (FActivity.isStopped())
			return;


		if(i%4==0)
			FUDPRateLimiter.ToSendData(4*188*7);


		if(RestBytes>0&&i==(SendCountBy188X7-1)&&LastBuffer)
		{

			//			FUDPRateLimiter.ToSendData(AiBufferLength-i*188*7);
			sendto(FUdpsock, LastBuffer.get(), 188*7, MSG_DONTWAIT, (struct sockaddr *) &FSIPAddress,
					sizeof(FSIPAddress));
			if(FDebugFile.is_open())
			{
				FDebugFile.write((char *)LastBuffer.get(), 188*7);
			}
		}
		else
		{
			void * TVBuffer=(void *)(AiBuffer.get()+i*188*7);
//			FUDPRateLimiter.ToSendData(188*7);
			sendto(FUdpsock, TVBuffer, 188*7, MSG_DONTWAIT, (struct sockaddr *) &FSIPAddress,
					sizeof(FSIPAddress));
			if(FDebugFile.is_open())
			{
				FDebugFile.write((char *)TVBuffer, 188*7);
			}
		}

	}

	FCurrentSendBytes+=AiBufferLength;
}


UDPTSBroadcastThread::UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
		InfoDTV_Common_Buffer::CircularBufferPtr aReadCB) :
			FIPAddress(aIPAddress), FIPPort(aIPPort), FBitRate(aBitRate), FIsNetworkReady(false),
			FCB(aReadCB), FUDPRateLimiter(aBitRate),FIsSendBegined(false),FDebugTSFileName(""),FLogger(),
#ifdef TRIAL
			FStartDateTime(),
#endif
			FActivity(this,&UDPTSBroadcastThread::run)
			{
	FLogger.setName("UDPTSBroadcastThread");
	Log("线程：播出线程 初始化中...");//<<std::endl;
			}


UDPTSBroadcastThread::UDPTSBroadcastThread(std::string aIPAddress, int aIPPort, long int aBitRate,
		InfoDTV_Common_Buffer::CircularBufferPtr aReadCB,std::string aDebugTSFile) :
			FIPAddress(aIPAddress), FIPPort(aIPPort), FBitRate(aBitRate),  FIsNetworkReady(false),
			FCB(aReadCB), FUDPRateLimiter(aBitRate),FIsSendBegined(false),FDebugTSFileName(aDebugTSFile),FLogger(),
			FActivity(this,&UDPTSBroadcastThread::run)
			{
	FLogger.setName("UDPTSBroadcastThread");
	Log("线程：播出线程 初始化中...");//<<std::endl;
	FDebugFile.open(FDebugTSFileName.c_str(),std::ios::out);
			}

void UDPTSBroadcastThread::InitNetwork()
{
	Log("线程：播出线程 正在初始化网络中..");
	FUdpsock = socket(AF_INET, SOCK_DGRAM, 0);
	FSIPAddress.sin_family = AF_INET;
	FSIPAddress.sin_addr.s_addr = inet_addr(FIPAddress.c_str());//inet_addr("192.168.0.1");
	FSIPAddress.sin_port = htons(FIPPort);
	const int on = 1; // option value for setsock
	/*  Clarify that we really want to do a broadcast and that this isn't
				 a mistake. The socket system makes this necessary just in case
				 we're a program that takes an IP address at the command line and
				 the user fooled us into making a broadcast.
	 */
	setsockopt(FUdpsock, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on));
	FIsNetworkReady=true;
}

UDPTSBroadcastThread::~UDPTSBroadcastThread()
{
    //				cout<<"<MEM>线程：播出线程  释放中..."<<std::endl;
    if(FDebugFile.is_open())
	FDebugFile.close();
    Log("<MEM>释放中...");
    if (!FActivity.isStopped())
	{
	    Stop();
	}



    if (FIsNetworkReady)
	close(FUdpsock);
    FIsNetworkReady=false;

    Log("<MEM>已释放...");
    //				cout<<"<MEM>线程：播出线程  已释放..."<<std::endl;
}

void UDPTSBroadcastThread::Start()
{
	InitNetwork();

	FActivity.start();

}

void UDPTSBroadcastThread::Stop()
{
    Log("线程：播出线程 停止中...");
    FActivity.stop();
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

#endif
