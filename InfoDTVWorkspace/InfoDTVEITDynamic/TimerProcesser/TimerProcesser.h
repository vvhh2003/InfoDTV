/*
 * TimerProcesser.h
 *
 *  Created on: 2009-3-3
 *      Author: victor
 */

#ifndef TIMERPROCESSER_H_
#define TIMERPROCESSER_H_

#include "Poco/Thread.h"
#include "Poco/Timer.h"
#include "Common.h"
#include <string>
using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;

using namespace std;
class TimerProcesser
{
	private :

		const string FDefineFile;
		const string FValueFile;
		const unsigned int FTimerInterval;
		Timer FTimer;
		TimerCallback<TimerProcesser> FTimerCallback;
		const SendBufferFunction FSendBufferFnPtr;
		void onTimer(Poco::Timer& atimer);
	public:
		TimerProcesser(const string aDefineFile,const string aValueFile,const unsigned int aTimerInterval,const SendBufferFunction SendBufferFnPtr);
		void start();
		void stop();
};

#endif /* TIMERPROCESSER_H_ */
