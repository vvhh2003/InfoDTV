#ifndef PMTTABLE_H_
#define PMTTABLE_H_
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

			struct PMTDataRecord
			{
				private:
				friend class boost::serialization::access;
				template<class Archive> void serialize(Archive & ar, const unsigned int version)
				{
					using boost::serialization::make_nvp;
					ar & make_nvp("Stream_Type", StreamType);
					ar & make_nvp("Elementary_PID", elementary_PID);
					//					ar & make_nvp("Elementary_PID", Program_map_PID);
				}
				public:
				unsigned char StreamType;
				//reserved 3Bit
				unsigned short elementary_PID;
				//reserved 4bit
				unsigned short ES_info_length;
				//List<DVBDescriptor> Descriptors;
			};

			typedef boost::shared_ptr<PMTDataRecord> PMTDataRecordPtr;

			using namespace TSLibrary::DVB;
			class PMTTable : public IPSIStreamWriteAble
			{
				private:
				ITSDataCounterPtr FDataCounter;
				IPSICrc32CounterPtr FCrc32Counter;

				unsigned short FPID;
				unsigned short FPcr_PID;
				unsigned short FProgram_number;
				unsigned char FVersion;
				//				std::vector<PMTDataRecordPtr> FPMTDataRecords;
				std::vector<PMTDataRecord *> FPMTDataRecords;
				unsigned short GetPMTBufferSize();

				friend class boost::serialization::access;
				template<class Archive> void serialize(Archive & ar, const unsigned int version)
				{
					using boost::serialization::make_nvp;
					ar & make_nvp("PID", FPID);
					ar & make_nvp("Version", FVersion);
					ar & make_nvp("PCR_PID", FPcr_PID);
					ar & make_nvp("Program_number", FProgram_number);
					ar & make_nvp("PMT_DATAS", FPMTDataRecords);
					//					ar & make_nvp("Elementary_PID", Program_map_PID);
				}
				public:
				virtual ~PMTTable();
				PMTTable();
				PMTTable(unsigned short aPID,unsigned short aProgram_number) ;
				PMTTable(unsigned short aPID,unsigned short aPcr_PID,unsigned short aProgram_number);
				virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
						ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);

				void SetVersion(unsigned char aVersion);
				void AddElementary(unsigned char aStreamType, unsigned short aElementary_PID);

			};
		}
	}
}

#endif /*PMTTABLE_H_*/
