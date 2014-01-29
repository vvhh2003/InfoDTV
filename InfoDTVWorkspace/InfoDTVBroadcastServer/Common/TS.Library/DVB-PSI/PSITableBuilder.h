/*
 * PSITableBuilder.h
 *
 *  Created on: 2009-2-12
 *      Author: victor
 */

#ifndef PSITABLEBUILDER_H_
#define PSITABLEBUILDER_H_
#include <vector>
#include <boost/shared_ptr.hpp>

#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"
#include "../../XMLBINRecord.h"


namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			using namespace std;

			using namespace TSLibrary::DVB;
			class PSITableBuilder: virtual public IPSIStreamWriteAble
			{
				private:
					ITSDataCounterPtr FDataCounter;
					IPSICrc32CounterPtr FCrc32Counter;
					XMLBIN::XMLBINRecordPtr FXMLBINRecordPtr;
					unsigned short FPID;
					unsigned char FTableID;
					unsigned short FTableExtID;
					unsigned char FVersion;
				public:
					PSITableBuilder();
					PSITableBuilder(ITSDataCounterPtr aDataCounter,IPSICrc32CounterPtr aCrc32Counter);
					bool setRecoder(XMLBIN::XMLBINRecordPtr aXMLBINRecordPtr);
					virtual ~PSITableBuilder();
					virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
							ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);
			};
		}
	}
}

#endif /* PSITABLEBUILDER_H_ */
