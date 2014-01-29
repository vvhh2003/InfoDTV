#ifndef DOOWAYINFOTABLE_H_
#define DOOWAYINFOTABLE_H_
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/string.hpp>

#include <boost/serialization/nvp.hpp>
#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"

namespace TSLibrary
{
	namespace InfoDTV
	{
		using namespace TSLibrary::DVB;
		using namespace std;
		const unsigned char DyDoorwayInfoTableID=0xFB;
		class DyDoorwayInfoTable : public IPSIStreamWriteAble
		{
			private:
				friend class boost::serialization::access;
				template<class Archive> void serialize(Archive & ar, const unsigned int version)
				{
					using boost::serialization::make_nvp;
					ar & make_nvp("PID", PID);
					ar & make_nvp("VODDoorway_IP", VODDoorway_IP);
					ar & make_nvp("StatusDoorway_IP", StatusDoorway_IP);
				}


				ITSDataCounterPtr FDataCounter;
				IPSICrc32CounterPtr FCrc32Counter;
			public:
				unsigned short PID;
				unsigned long VODDoorway_IP;
				unsigned long StatusDoorway_IP;
				DyDoorwayInfoTable();
				DyDoorwayInfoTable(unsigned short aPID, unsigned long aVODDoorway_IP, unsigned long aStatusDoorway_IP) ;
				virtual ~DyDoorwayInfoTable();
				virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
						ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);

			};
	}
}
#endif /*DOOWAYINFOTABLE_H_*/
