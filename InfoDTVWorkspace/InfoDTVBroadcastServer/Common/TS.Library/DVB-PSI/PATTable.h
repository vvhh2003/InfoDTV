#ifndef PATTABLE_H_
#define PATTABLE_H_
#include <vector>
#include <boost/shared_ptr.hpp>

#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"

#include <boost/serialization/list.hpp>

#include <boost/serialization/string.hpp>

#include <boost/serialization/nvp.hpp>

namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			struct PATDataRecord
			{
				private:
					friend class boost::serialization::access;
					template<class Archive> void serialize(Archive & ar, const unsigned int version)
					{
						using boost::serialization::make_nvp;
						ar & make_nvp("PROGRAM_NUMBER", Program_number);
						ar & make_nvp("PMT_PID", Program_map_PID);
					}
				public:
					unsigned short Program_number;
					unsigned short Program_map_PID;
			};

			typedef boost::shared_ptr<PATDataRecord> PATDataRecordPtr;

			using namespace TSLibrary::DVB;
			class PATTable : virtual public IPSIStreamWriteAble
			{
				private:
					ITSDataCounterPtr FDataCounter;
					IPSICrc32CounterPtr FCrc32Counter;
					int FTransport_ID;
					unsigned char FVersion;
					//					std::vector<PATDataRecordPtr> FPATDataRecords;
					std::vector<PATDataRecord *> FPATDataRecords;
					friend class boost::serialization::access;
					template<class Archive> void serialize(Archive & ar, const unsigned int version)
					{
						using boost::serialization::make_nvp;
						ar & make_nvp("Version", FVersion);
						ar & make_nvp("Transport_ID", FTransport_ID);
						ar & make_nvp("PAT_DATAS", FPATDataRecords);
					}
				public:
					PATTable();
					virtual ~PATTable();
					PATTable(int aTransport_ID) ;
					virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
					        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);
					void SetVersion(unsigned char aVersion );

					void AddProgram(int aProgram_number, int aProgram_map_PID);
			};
		}
	}
}

#endif /*PATTABLE_H_*/
