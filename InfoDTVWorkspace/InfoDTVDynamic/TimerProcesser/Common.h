/*
 * Common.h
 *
 *  Created on: 2009-3-3
 *      Author: victor
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <string>
using namespace std;

typedef bool (*SendBufferFunction)(const char * aGUIDName,const unsigned char * Buffer,const unsigned int BufferLength);

typedef void (*SetSendBufferCallBackFunction)(SendBufferFunction);

typedef void (*BuildSendBufferFunction)(const char * aGUIDName,const char * aHostIP,const int aHostIPPort,
		const char * aChannelName);

typedef void (*LogFunction)(const char *);

/*
 * string HostIP;
	int HostIPPort;
	string ChannelName;
	string TSParams;
	string IBLPath;
	string PathGuid;
	int TimerInterval;
	int RunMode;
 */
typedef void (*MainFunction)(const char * aConfigFileName,const BuildSendBufferFunction aBuildSendBufferFunction,const SendBufferFunction aSendBufferFunction);

/*
typedef void (*MainFunction)(const char * aHostIP,const int aHostIPPort,
		const char * aChannelName,const char * aTSParams,const char * aIBLPath,
		const char *aPathGuid,const int aTimerInt,const int aRunMode,
		const SendBufferFunction aSendBufferFunction);
*/

#endif /* COMMON_H_ */
