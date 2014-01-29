#include "CircularBuffer.h"

//#include "Log.h"
using namespace std;
//using namespace log4cplus;
//using namespace log4cplus::helpers;
//using namespace log4cplus::thread;
//using namespace InfoDTV_Common_Log;
namespace InfoDTV_Common_Buffer
{
	//bool FIsFirstSet=true;
	//bool FIsFirstGet=true;
	void CircularBuffer::Log(string ALogStr)
	{
		FLogger.information(ALogStr);
	}

	CircularBuffer::CircularBuffer(string aName, int aBufferCount, long aBufferlength):FLogger(),FInternalMonitor()
#ifdef POCO_SynchronizedObject
	,FReadNotifyEvent(true),FWriteNotifyEvent(true)
#endif
	//	FName(aName),BufferLength(aBufferlength),readLocation(0),writeLocation(0),occupiedBufferCount(0)
	{
		FName=aName;
		int i=0;
		FLogger.setName("数据缓冲区管理器:"+FName,false);
		BufferLength=aBufferlength;
		readLocation=0;
		writeLocation=0;
		occupiedBufferCount=0;
		//DefaultInitLoger("CircularBuffer:"+aName);
		//_logger=
		for (i=0; i<aBufferCount; i++)
		{
			//char *TmpPtr=(char *)std::malloc(aBufferlength);
			//boost::scoped_ptr<char> TT(((char *)std::malloc(aBufferlength)));

			//FBuffers.push_back(&TT);
			Log("初始化缓冲区: " +boost::lexical_cast<std::string>(i));
			RawBufferPtr TmpPtr((unsigned char *)std::malloc(aBufferlength),&free);
			FBuffers.push_back(TmpPtr);
			//LOG4CPLUS_DEBUG(_logger, "Init Buffer Index: " << i);
		}
		FReadNotifyEvent.set();
		FReadNotifyEvent.reset();
		FWriteNotifyEvent.set();
		FWriteNotifyEvent.reset();
	}

	void CircularBuffer::setBuffer(int aBufferSize, RawBufferPtr aBuffer)
	{
		if (aBufferSize!=BufferLength)
			return;
#ifndef POCO_SynchronizedObject
		FInternalMonitor.lock();
#endif
		if (occupiedBufferCount==FBuffers.size())
		{
			Log("缓冲区已满，等待读取... ");

#ifdef POCO_SynchronizedObject
			FReadNotifyEvent.wait();

#else
			FInternalMonitor.wait();
#endif
		}
		//		RawBufferPtr ResultBuffer((char *)malloc(BufferLength));
		Log("Buffer To write Index: " +boost::lexical_cast<std::string>(writeLocation));
		memcpy(FBuffers[writeLocation].get(), aBuffer.get(), BufferLength);
		occupiedBufferCount++;
		writeLocation = (writeLocation + 1 ) % FBuffers.size();
#ifdef POCO_SynchronizedObject
		//	if (occupiedBufferCount==1&&!FIsFirstSet)
		//	    {
		//		Log("缓冲区空解锁... ");
		//		FInternalMonitor.notify();
		//		Log("Event Set");
		//	    }
		//	FIsFirstSet=false;
		FWriteNotifyEvent.set();
		FReadNotifyEvent.reset();
#else
		FInternalMonitor.notify();
		FInternalMonitor.unlock();
#endif


		return;
	}

	RawBufferPtr CircularBuffer::getBuffer()
	{
#ifndef POCO_SynchronizedObject
		FInternalMonitor.lock();
#endif
		if (occupiedBufferCount==0)
		{
			Log("缓冲区已空，等待写入... ");

#ifdef POCO_SynchronizedObject
			FWriteNotifyEvent.wait();

#else
			FInternalMonitor.wait();
#endif
		}



		//		RawBufferPtr ResultBuffer(new unsigned char[BufferLength]);
		RawBufferPtr ResultBuffer((unsigned char*)std::malloc(BufferLength),&free);
		Log("Buffer To Read Index: " +boost::lexical_cast<std::string>(readLocation));
		std::memcpy(ResultBuffer.get(), FBuffers[readLocation].get(), BufferLength);
		occupiedBufferCount--;
		readLocation = (readLocation + 1 ) % FBuffers.size();
#ifdef POCO_SynchronizedObject
		//	if (occupiedBufferCount==FBuffers.size()-1&&!FIsFirstGet)
		//	    {
		//		Log("缓冲区满解锁... ");
		//		FInternalMonitor.notify();
		//		Log("Event Set");
		//	    }
		FReadNotifyEvent.set();
		FWriteNotifyEvent.reset();
#else
		FInternalMonitor.notify();
		FInternalMonitor.unlock();
#endif

		return ResultBuffer;
	}


	RawBufferPtr CircularBuffer::getBuffer(unsigned int aTimeOut)
	{
#ifndef POCO_SynchronizedObject
		FInternalMonitor.lock();
#endif
		if (occupiedBufferCount==0)
		{
			Log("缓冲区已空，等待写入... ");

#ifdef POCO_SynchronizedObject
			if(!FWriteNotifyEvent.tryWait(aTimeOut))
			{
				RawBufferPtr TmpResultBuffer;
				return TmpResultBuffer;
			}

#else
			FInternalMonitor.wait();
#endif
		}



		//		RawBufferPtr ResultBuffer(new unsigned char[BufferLength]);
		RawBufferPtr ResultBuffer((unsigned char*)std::malloc(BufferLength),&free);
		Log("Buffer To Read Index: " +boost::lexical_cast<std::string>(readLocation));
		std::memcpy(ResultBuffer.get(), FBuffers[readLocation].get(), BufferLength);
		occupiedBufferCount--;
		readLocation = (readLocation + 1 ) % FBuffers.size();
#ifdef POCO_SynchronizedObject
		//	if (occupiedBufferCount==FBuffers.size()-1&&!FIsFirstGet)
		//	    {
		//		Log("缓冲区满解锁... ");
		//		FInternalMonitor.notify();
		//		Log("Event Set");
		//	    }
		FReadNotifyEvent.set();
		FWriteNotifyEvent.reset();
#else
		FInternalMonitor.notify();
		FInternalMonitor.unlock();
#endif

		return ResultBuffer;
	}

	long CircularBuffer::getBufferLength() const
	{
		return BufferLength;
	}

	bool CircularBuffer::IsBufferWriterBlocked()
	{
		return occupiedBufferCount==FBuffers.size();
	}

	bool CircularBuffer::IsBufferReaderBlocked()
	{
		return occupiedBufferCount==0;
	}

	int CircularBuffer::getBufferCount()
	{
		return FBuffers.size();
	}
	CircularBuffer::~CircularBuffer()
	{
		//		int ti=0;
		//		for (vector<unsigned char * >::iterator i = FBuffers.begin(); i != FBuffers.end(); i++)
		//		{
		//			Log("释放缓冲区： "+boost::lexical_cast<std::string>(ti++));
		//			std::free(*i);
		//		}
		FBuffers.clear();
		std::vector<RawBufferPtr>(FBuffers).swap(FBuffers);
		Log("<MEM>已释放！");

	}
}
