#ifndef LOCATIONINFOTABLE_H_
#define LOCATIONINFOTABLE_H_
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
		const unsigned char DyIPInfoTableID=0xFC;
		class DyIPInfoTable : public IPSIStreamWriteAble
		{
			private:
				friend class boost::serialization::access;
				template<class Archive> void serialize(Archive & ar, const unsigned int version)
				{
					using boost::serialization::make_nvp;
					ar & make_nvp("PID", PID);
					ar & make_nvp("IPQAM_ID", IPQAM_ID);
					ar & make_nvp("DHCP_SrvName", DHCP_SrvName);
					ar & make_nvp("DHCP_ClientName", DHCP_ClientName);
				}

				unsigned int GetDyIPInfoTableSize();
				ITSDataCounterPtr FDataCounter;
				IPSICrc32CounterPtr FCrc32Counter;
			public:
				unsigned short PID;
				unsigned long IPQAM_ID;
				string DHCP_SrvName;
				string DHCP_ClientName;
				DyIPInfoTable();
				DyIPInfoTable(unsigned short aPID, unsigned long aIPQAM_ID, string aDHCP_SrvName, string aDHCP_ClientName) ;
				virtual ~DyIPInfoTable();
				virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
						ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);

			};
	}
}
#endif /*LOCATIONINFOTABLE_H_*/
