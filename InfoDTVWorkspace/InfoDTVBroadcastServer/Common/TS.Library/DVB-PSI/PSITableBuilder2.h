/*
 * PSITableBuilder2.h
 *
 *  Created on: 2009-3-14
 *      Author: victor
 */

#ifndef PSITABLEBUILDER2_H_
#define PSITABLEBUILDER2_H_

#include <vector>
#include <boost/shared_ptr.hpp>

#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"

#include "../../PSIXMLBINRecord.h"

namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			using namespace std;

			using namespace TSLibrary::DVB;
			class PSITableBuilder2: virtual public IPSIStreamWriteAble
			{
				private:
					ITSDataCounterPtr FDataCounter;
					IPSICrc32CounterPtr FCrc32Counter;
					PSIXMLBIN::PSIXMLBINRecordPtr FXMLBINRecordPtr;
					unsigned short FPID;
					unsigned char FTableID;
					unsigned short FTableExtID;
					unsigned char FVersion;
				public:
					PSITableBuilder2();
					PSITableBuilder2(ITSDataCounterPtr aDataCounter,IPSICrc32CounterPtr aCrc32Counter);
					bool setRecoder(PSIXMLBIN::PSIXMLBINRecordPtr aXMLBINRecordPtr);
					~PSITableBuilder2();
					virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
							ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);
			};
		}
	}
}

#endif /* PSITABLEBUILDER2_H_ */
