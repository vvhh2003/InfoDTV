/*
 * PSITableBuilder.cpp
 *
 *  Created on: 2009-2-12
 *      Author: victor
 */

#include "PSITableBuilder.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			using namespace XMLBIN;
			PSITableBuilder::PSITableBuilder():
				FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()),
				FXMLBINRecordPtr(),FPID(0),FTableID(0),FTableExtID(0),FVersion(0)
			{

			}
			PSITableBuilder::PSITableBuilder(ITSDataCounterPtr aDataCounter,IPSICrc32CounterPtr aCrc32Counter):
							FDataCounter(aDataCounter), FCrc32Counter(aCrc32Counter),
							FXMLBINRecordPtr(),FPID(0),FTableID(0),FTableExtID(0),FVersion(0)
			{

			}

			bool PSITableBuilder::setRecoder(XMLBINRecordPtr aXMLBINRecordPtr)
			{
				std::cout<<">>TableBuilder>> Start"<<std::endl;
				if(!aXMLBINRecordPtr)
				{
					std::cout<<"TableBuilder Empty Ptr"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->BufferLength==0)
				{
					std::cout<<"TableBuilder BufferLength=0"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->ExtValueMap.count(PID_STR)==0)
				{
					std::cout<<"TableBuilder NO PID"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->ExtValueMap.count(TABLE_ID_STR)==0)
				{
					std::cout<<"TableBuilder NO TABLE_ID"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->ExtValueMap.count(TABLE_EXT_ID_STR)==0)
				{
					std::cout<<"TableBuilder NO TABLE_EXT_ID"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->ExtValueMap.count(VERSION_NUMBER_STR)==0)
				{
					std::cout<<"TableBuilder NO VERSION_NUMBER"<<std::endl;
					return false;
				}

				try
				{
					FPID=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->ExtValueMap[PID_STR]);
					FTableID=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->ExtValueMap[TABLE_ID_STR]);
					FTableExtID=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->ExtValueMap[TABLE_EXT_ID_STR]);
					FVersion=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->ExtValueMap[VERSION_NUMBER_STR]);
					std::cout<<">>TableBuilder>> End"<<std::endl;
				}
				catch(...)
				{
					std::cout<<"TableBuilder HEAD Part with some error"<<std::endl;
					return false;
				}
				FXMLBINRecordPtr=aXMLBINRecordPtr;
				return true;
			}
			PSITableBuilder::~PSITableBuilder()
			{

			}
			void PSITableBuilder::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
					ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
			{


				bool IsDVB=true;
				unsigned int RefLastSectionNumPos=0;

				if(!FXMLBINRecordPtr)
					return ;

				if(FXMLBINRecordPtr->ExtValueMap.count(IS_MPEG2_STR)!=0)
				{
					IsDVB=false;
				}

				if(FXMLBINRecordPtr->ExtValueMap.count(REF_LAST_SECTION_NUMBER_POS_BYTE_STR)!=0)
				{
					RefLastSectionNumPos=boost::lexical_cast<unsigned int>(FXMLBINRecordPtr->ExtValueMap[REF_LAST_SECTION_NUMBER_POS_BYTE_STR]);
				}


				PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(FPID, FTableID,
						FTableExtID, true,IsDVB);
				PSIHeaderConfig->PSIHeader.version_number=FVersion;
				if(RefLastSectionNumPos==0)
					aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, FXMLBINRecordPtr->Buffer,
							FXMLBINRecordPtr->BufferLength, FDataCounter, FCrc32Counter, true);
				else
					aStream->WriteAllSectionDataToTSStream(aTSStream, PSIHeaderConfig, FXMLBINRecordPtr->Buffer,
							FXMLBINRecordPtr->BufferLength, FDataCounter, FCrc32Counter, false,RefLastSectionNumPos);
			}


		}
	}
}
