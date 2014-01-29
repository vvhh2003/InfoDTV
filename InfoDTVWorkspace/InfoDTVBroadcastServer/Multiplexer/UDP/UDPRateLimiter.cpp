/*
 * UDPRateLimiter.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "UDPRateLimiter.h"
namespace InfoDTV_UDP_Rate_Limit
{

#define MILLION 1000000
#define LLMILLION ((long long)1000000)





    static long long getLongLongDate(void)
    {
	long long date;
	struct timeval tv;
	gettimeofday(&tv, 0);
	date = (long long) tv.tv_sec;
	date *= LLMILLION;
	date += (long long) tv.tv_usec;
	return date;
    }


    int UDPRateLimiter::doRateLimit(rate_limitPtr rateLimit, int Sendsize)
    {
	int size=Sendsize;
	if (rateLimit)
	    {
		long long now = getLongLongDate();
		long long elapsed = now - rateLimit->date;
		long long bits = elapsed * ((long long)rateLimit->bitrate) / LLMILLION;
		int sleepTime;
		//		size += 28; /* IP header size */
		if(bits<0) bits=0;
		if (bits >= rateLimit->queueSize * 8)
		    {
			rateLimit->queueSize = size;
			rateLimit->date = now;
			return 0;
		    }

		rateLimit->queueSize -= bits / 8;
		rateLimit->date += bits * LLMILLION / rateLimit->bitrate;
		rateLimit->realDate = now;
		sleepTime = rateLimit->queueSize * 8 * LLMILLION / rateLimit->bitrate;
		//Start Victor 2009-1-17
		if(sleepTime >0)
#ifndef POCOSLEEP
		usleep(sleepTime);
#else
		Poco::Thread::sleep(sleepTime/1000);
#endif
		//End Victor 2009-1-17
//		if (sleepTime > 40000 || rateLimit->queueSize >= 100000)
//		    {
//			sleepTime -= 10000;
//			sleepTime -= sleepTime % 10000;
//			usleep(sleepTime);
//		    }
		/*flprintf(".");*/
		rateLimit->queueSize += size;
	    }
	return 0;
    }


    UDPRateLimiter::UDPRateLimiter(long bitrate)
    {
	FRate_limitP.reset(new rate_limit());
	FRate_limitP->bitrate=bitrate;
    }

    void	UDPRateLimiter::ToSendData(int SendSize)
    {
	doRateLimit(FRate_limitP,SendSize);
    }

}
