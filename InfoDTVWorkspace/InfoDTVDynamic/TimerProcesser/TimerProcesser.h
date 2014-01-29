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
#include <boost/shared_ptr.hpp>
#include <string>
#include "../Main/DynamicGlobalConfig.hpp"
#include "InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.h"
using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;

using namespace std;
class InfoDTVTimerProcesser
{
	private :


		const string FHostIP;
		const int FHostIPPort;
		const string FChannelName;
		const unsigned short FPID;
		const string FTSParams;
		const string FIBLPath;
		const string FPathGuid;
		const int FTimerInterval;
		const int FRunMode;
		const string FDebugPath;
		Timer FTimer;
		TimerCallback<InfoDTVTimerProcesser> FTimerCallback;
		const SendBufferFunction FSendBufferFnPtr;
		InfoDTV::DynamicBuilder::FileBuilder::InfoDTVTSBuilder FBuilder;
		void onTimer(Poco::Timer& atimer);
	public:
		InfoDTVTimerProcesser(const string aHostIP,const int aHostIPPort,
				const string aChannelName,const unsigned short aPID,
				const string aTSParams,const string aIBLPath,
				const string aPathGuid,const int aTimerInt,const int aRunMode,
				const string aDebugPath,
				const SendBufferFunction SendBufferFnPtr);
		void start();
		void stop();
};
typedef boost::shared_ptr<InfoDTVTimerProcesser> InfoDTVTimerProcesserPtr;
#endif /* TIMERPROCESSER_H_ */
