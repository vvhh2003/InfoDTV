#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_
#define POCO_SynchronizedObject
//#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>

#ifdef POCO_SynchronizedObject
#include "Poco/SynchronizedObject.h"
#include "Poco/Event.h"
#else
#include <IceUtil/Mutex.h>
#include <IceUtil/Monitor.h>
#endif

//#include "../Common/Log.h"
#include "../Common/TSPacketStruct.h"
#include "../Common/Log/Log.h"
using namespace std;

namespace InfoDTV_Common_Buffer
{

class CircularBuffer
{
private:
	volatile uint occupiedBufferCount ;
	 long BufferLength;
	 InfoDTV_Common_Log::InfoDTVLogger FLogger;
	 volatile int readLocation ;
	 volatile int writeLocation ;
	 string FName;
#ifdef POCO_SynchronizedObject
	 Poco::SynchronizedObject FInternalMonitor;
	 Poco::Event FReadNotifyEvent;
	 Poco::Event FWriteNotifyEvent;
#else
	 IceUtil::Monitor<IceUtil::Mutex> FInternalMonitor;
#endif


	 //vector< boost::scoped_ptr<char> > FBuffers;
	 vector<RawBufferPtr> FBuffers;
	 //Logger _logger ;
	 void Log(string ALogStr);
public:
	CircularBuffer(string aName,int aBufferCount,long aBufferlength);
	RawBufferPtr getBuffer();
	RawBufferPtr getBuffer(unsigned int aTimeOut);
	long getBufferLength() const;
	void setBuffer(int aBufferSize,RawBufferPtr aBuffer);
	bool IsBufferReaderBlocked();
	bool IsBufferWriterBlocked();
	int getBufferCount();
	virtual ~CircularBuffer();
};
typedef boost::shared_ptr<CircularBuffer> CircularBufferPtr;
}

#endif /*CIRCULARBUFFER_H_*/
