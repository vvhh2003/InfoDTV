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

typedef bool (*SendBufferFunction)(const unsigned char * Buffer,const unsigned int BufferLength);

typedef void (*SetSendBufferCallBackFunction)(SendBufferFunction);

typedef void (*LogFunction)(const char *);

typedef void (*MainFunction)(const char * DefineXMLFile,const char * ValueXMLFile,const int aTimerInt,const SendBufferFunction aSendBufferFunction);
#endif /* COMMON_H_ */
