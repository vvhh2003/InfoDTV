/*
 * PSITable.h
 *
 *  Created on: 2009-1-24
 *      Author: victor
 */

#ifndef PSITABLE_H_
#define PSITABLE_H_
#include "PATTable.h"
#include "PMTTable.h"



namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			struct PSIDataRecord
			{
				private:
					friend class boost::serialization::access;
					template<class Archive> void serialize(Archive & ar, const unsigned int version)
					{
						using boost::serialization::make_nvp;
						ar & make_nvp("PATTable", FPATTable);
						ar & make_nvp("PMTTables", FPMTTables);
						//					ar & make_nvp("Elementary_PID", Program_map_PID);
					}
					PATTable FPATTable;
					std::vector<PMTTable *> FPMTTables;
				public:

			};

		}
	}
}
#endif /* PSITABLE_H_ */
