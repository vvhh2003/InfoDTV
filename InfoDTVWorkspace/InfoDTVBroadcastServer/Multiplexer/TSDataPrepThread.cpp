/*
 * TSDataPrepThread.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "TSDataPrepThread.h"
#include <IceUtil/Thread.h>
using namespace MultiplexerCore_V1;

#ifdef USE_ICE_THREAD

void TSDataPrepThread::run()
{
	Log("线程运行开始！");
	RawBufferPtr TmpBuffer((unsigned char *)std::malloc(TS_DataBuffer_Length),&free);
	//RawBufferPtr TmpBuffer(new unsigned char[TS_DataBuffer_Length]);
	while (!FIsStoped)
	{
		try
		{
			FMultiplexer->FillBuffer(TS_DataBuffer_Length,TmpBuffer);
			if(FIsStoped)
			{
				break;
			}
			FCB->setBuffer(TS_DataBuffer_Length,TmpBuffer);
			if(FIsStoped)
			{
				break;
			}
		}
		catch(void *e)
		{
			Log("TSDataPrepThread Thread Erroring");
		}
	}
	Log("线程运行结束！");
}



TSDataPrepThread::TSDataPrepThread(MultiplexerCore::ISoftMultiplexerPtr aMultiplexer,
		InfoDTV_Common_Buffer::CircularBufferPtr aCB) :FLogger(),
		FMultiplexer(aMultiplexer), FCB(aCB), FIsStoped(false)
		{
	FLogger.setName("数据准备线程对象");
	Log("初始化...");
		}

TSDataPrepThread::~TSDataPrepThread()
{

	if (!FIsStoped)
	{
		Stop();
	}
	if(isAlive())
	    FThreadControl.join();
	Log("停止完成..");
	Log("<MEM> 已释放...");
}

void TSDataPrepThread::PreBuildBuffer()
{
    RawBufferPtr TmpBuffer((unsigned char *)std::malloc(TS_DataBuffer_Length),&free);
    	//RawBufferPtr TmpBuffer(new unsigned char[TS_DataBuffer_Length]);
    int PreBuildBufferCount=FCB->getBufferCount()-1;
    	for(int i=0;i<PreBuildBufferCount;i++)
    	{
    		try
    		{
    			FMultiplexer->FillBuffer(TS_DataBuffer_Length,TmpBuffer);
    			if(FIsStoped)
    			{
    				break;
    			}
    			FCB->setBuffer(TS_DataBuffer_Length,TmpBuffer);
    			if(FIsStoped)
    			{
    				break;
    			}
    		}
    		catch(void *e)
    		{
    			Log("TSDataPrepThread PreBuildBuffer Erroring");
    		}
    	}
}

void TSDataPrepThread::Start()
{
	Log("正在启动...");
	Log("正在准备数据...");
	PreBuildBuffer();
	FThreadControl=start();
	FIsStoped=false;
	Log("启动完成...");
}

void TSDataPrepThread::Stop()
{
	Log("停止中...");
	FIsStoped=true;
	Log("停止中.1..");

}
#endif

#ifdef USE_POCO_THREAD

void TSDataPrepThread::run()
{
	Log("线程运行开始！");
	RawBufferPtr TmpBuffer((unsigned char *)std::malloc(TS_DataBuffer_Length),&free);
	//RawBufferPtr TmpBuffer(new unsigned char[TS_DataBuffer_Length]);
	while (!FActivity.isStopped())
	{
		try
		{
			FMultiplexer->FillBuffer(TS_DataBuffer_Length,TmpBuffer);
			if(FActivity.isStopped())
			{
				break;
			}
			FCB->setBuffer(TS_DataBuffer_Length,TmpBuffer);
			if(FActivity.isStopped())
			{
				break;
			}
		}
		catch(void *e)
		{
			Log("TSDataPrepThread Thread Erroring");
		}
	}
	Log("线程运行结束！");
}



TSDataPrepThread::TSDataPrepThread(MultiplexerCore::ISoftMultiplexerPtr aMultiplexer,
		InfoDTV_Common_Buffer::CircularBufferPtr aCB) :FLogger(),
		FActivity(this,&TSDataPrepThread::run),
		FMultiplexer(aMultiplexer), FCB(aCB)
		{
	FLogger.setName("数据准备线程对象");
	Log("初始化...");
		}

TSDataPrepThread::~TSDataPrepThread()
{
	if (!FActivity.isStopped())
	{
		Stop();
	}
	Log("<MEM> 已释放...");
}

void TSDataPrepThread::PreBuildBuffer()
{
    RawBufferPtr TmpBuffer((unsigned char *)std::malloc(TS_DataBuffer_Length),&free);
    	//RawBufferPtr TmpBuffer(new unsigned char[TS_DataBuffer_Length]);
    int PreBuildBufferCount=FCB->getBufferCount()-1;
    	for(int i=0;i<PreBuildBufferCount;i++)
    	{
    		try
    		{
    			FMultiplexer->FillBuffer(TS_DataBuffer_Length,TmpBuffer);
    			FCB->setBuffer(TS_DataBuffer_Length,TmpBuffer);
    		}
    		catch(void *e)
    		{
    			Log("TSDataPrepThread PreBuildBuffer Erroring");
    		}
    	}
}

void TSDataPrepThread::Start()
{
	Log("正在启动...");
	Log("正在准备数据...");
	PreBuildBuffer();
	FActivity.start();
	Log("启动完成...");
}

void TSDataPrepThread::Stop()
{
	Log("停止中...");
	FActivity.stop();
	Log("停止中.1..");
	if (FCB->IsBufferWriterBlocked())
	    {
		//					RawBufferPtr TmpBuffer(new unsigned char[TS_DataBuffer_Length]);
		Log("停止中..正在解决数据准备缓冲锁...");
		FCB->getBuffer();
		Log("停止中..数据准备缓冲锁已解决...");
	    }
	FActivity.wait();
	Log("停止完成..");
}
#endif
