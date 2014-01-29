/*
 * TOTTable.h
 *
 *  Created on: 2009-2-25
 *      Author: victor
 */

#ifndef TOTTABLE_H_
#define TOTTABLE_H_
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
			class TOTTable : virtual public IPSIStreamWriteAble
			{
				private:
					ITSDataCounterPtr FDataCounter;
					IPSICrc32CounterPtr FCrc32Counter;
				public:
					TOTTable();
					TOTTable(ITSDataCounterPtr aDataCounter,IPSICrc32CounterPtr aCrc32Counter);
					virtual ~TOTTable();
					virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
									        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);
			};
		}
	}
}

#endif /* TOTTABLE_H_ */
