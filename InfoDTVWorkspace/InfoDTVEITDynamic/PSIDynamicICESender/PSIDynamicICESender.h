/*
 * PSIDynamicICESender.h
 *
 *  Created on: 2009-3-3
 *      Author: victor
 */

#ifndef PSIDYNAMICICESENDER_H_
#define PSIDYNAMICICESENDER_H_
#include <string>
#include <Ice/Ice.h>
#include "Common/TSPacketStruct.h"
#include "DynICEBufferSender.h"
#include "Poco/SharedPtr.h"
using namespace std;

class PSIDynamicICESender
{
	private:
		string FHostIP;
		unsigned int FHostPort;
		string FServiceName;
		Ice::CommunicatorPtr FCommunicatorPtr;
		InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPrx FSendBufferPrx;
	public:
		PSIDynamicICESender(string aHostIP,unsigned int aHostPort,string aServiceName);
		~PSIDynamicICESender();
		bool Connect();
		void SendAllBuffer(RawBufferPtr aBuffer,unsigned int aBufferSize);
};

typedef Poco::SharedPtr<PSIDynamicICESender> PSIDynamicICESenderPtr;


#endif /* PSIDYNAMICICESENDER_H_ */
