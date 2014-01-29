/*
 * SDTable.h
 *
 *  Created on: 2009-1-23
 *      Author: victor
 */

#ifndef SDTABLE_H_
#define SDTABLE_H_

namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			struct SDTDataRecord
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

		}
	}
}
#endif /* SDTABLE_H_ */
