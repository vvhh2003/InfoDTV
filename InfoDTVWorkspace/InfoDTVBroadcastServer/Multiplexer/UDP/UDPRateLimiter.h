#ifndef UDPRATELIMITER_H_
#define UDPRATELIMITER_H_
#define POCOSLEEP
#include <boost/shared_ptr.hpp>
	#include <sys/types.h>
	#include <sys/time.h>

#ifndef POCOSLEEP
	#include <unistd.h>
#else
	#include"Poco/Thread.h"
#endif
namespace InfoDTV_UDP_Rate_Limit
{
	struct rate_limit
	{
		long long date;
		long long realDate;
		long bitrate;
		int queueSize;
	};

	typedef boost::shared_ptr<rate_limit> rate_limitPtr;

	class UDPRateLimiter
	{
		private:
			rate_limitPtr FRate_limitP;
			int doRateLimit(rate_limitPtr rateLimit, int Sendsize);
		public:
			UDPRateLimiter(long bitrate);

			void	ToSendData(int SendSize);
	};
}
#endif /*UDPRATELIMITER_H_*/
