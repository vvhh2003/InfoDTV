#ifndef DEFAULTPSICRC32COUNTER_H_
#define DEFAULTPSICRC32COUNTER_H_
#include <boost/shared_ptr.hpp>
//#include <boost/crc.hpp>
#include "PSIInterface.h"
//#include "../CCRC32.h"
namespace TSLibrary
{

	namespace DVB
	{

		class DefaultPSICrc32Counter : public IPSICrc32Counter
			{
				public:
					DefaultPSICrc32Counter()
					{
						//FCRC.Initialize();
					}
					virtual ~DefaultPSICrc32Counter()
					{

					}
					virtual unsigned long GetCrc32(RawBufferPtr aData, unsigned long uLength);
			};

		typedef boost::shared_ptr<DefaultPSICrc32Counter> DefaultPSICrc32CounterPtr;
	}
}
#endif /*DEFAULTPSICRC32COUNTER_H_*/
