/*
 * TDTTable.h
 *
 *  Created on: 2009-2-24
 *      Author: victor
 */

#ifndef TDTTABLE_H_
#define TDTTABLE_H_
#include <boost/shared_ptr.hpp>

#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"
namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			using namespace TSLibrary::DVB;
			class TDTTable : virtual public IPSIStreamWriteAble
			{
				private:
					ITSDataCounterPtr FDataCounter;
					IPSICrc32CounterPtr FCrc32Counter;
				public:
					TDTTable();
					TDTTable(ITSDataCounterPtr aDataCounter);
					virtual ~TDTTable();
					virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
									        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);
			};
		}
	}
}
#endif /* TDTTABLE_H_ */
