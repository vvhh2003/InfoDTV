/*
 * PSITableBuilder2.cpp
 *
 *  Created on: 2009-3-14
 *      Author: victor
 */


#include "PSITableBuilder2.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
namespace TSLibrary
{
	namespace DVB
	{
		namespace PSI
		{
			using namespace PSIXMLBIN;
			PSITableBuilder2::PSITableBuilder2():
				FDataCounter(new DefaultDataCounter()), FCrc32Counter(new DefaultPSICrc32Counter()),
				FXMLBINRecordPtr(),FPID(0),FTableID(0),FTableExtID(0),FVersion(0)
			{

			}
			PSITableBuilder2::PSITableBuilder2(ITSDataCounterPtr aDataCounter,IPSICrc32CounterPtr aCrc32Counter):
							FDataCounter(aDataCounter), FCrc32Counter(aCrc32Counter),
							FXMLBINRecordPtr(),FPID(0),FTableID(0),FTableExtID(0),FVersion(0)
			{

			}

			bool PSITableBuilder2::setRecoder(PSIXMLBINRecordPtr aXMLBINRecordPtr)
			{
				std::cout<<">>TableBuilder>> Start"<<std::endl;
				if(!aXMLBINRecordPtr)
				{
					std::cout<<"TableBuilder Empty Ptr"<<std::endl;
					return false;
				}

				if(!(aXMLBINRecordPtr->SectionRecordPtrList.size()>0))
				{
					std::cout<<"TableBuilder2 SectionRecordPtrList<=0"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->count(PID_STR)==0)
				{
					std::cout<<"TableBuilder NO PID"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->count(TABLE_ID_STR)==0)
				{
					std::cout<<"TableBuilder NO TABLE_ID"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->count(TABLE_EXT_ID_STR)==0)
				{
					std::cout<<"TableBuilder NO TABLE_EXT_ID"<<std::endl;
					return false;
				}

				if(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->count(VERSION_NUMBER_STR)==0)
				{
					std::cout<<"TableBuilder NO VERSION_NUMBER"<<std::endl;
					return false;
				}

				try
				{
					FPID=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->at(PID_STR));
					FTableID=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->at(TABLE_ID_STR));
					FTableExtID=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->at(TABLE_EXT_ID_STR));
					FVersion=boost::lexical_cast<unsigned short>(aXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->at(VERSION_NUMBER_STR));
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
			PSITableBuilder2::~PSITableBuilder2()
			{

			}
			void PSITableBuilder2::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
					ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
			{


				bool IsDVB=true;
				unsigned int RefLastSectionNumPos=0;

				if(!FXMLBINRecordPtr)
					return ;

				if(FXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->count(IS_MPEG2_STR)!=0)
				{
					IsDVB=false;
				}

				if(FXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->count(REF_LAST_SECTION_NUMBER_POS_BYTE_STR)!=0)
				{
					RefLastSectionNumPos=boost::lexical_cast<unsigned int>(FXMLBINRecordPtr->SectionRecordPtrList[0]->ExtValueMapPtr->at(REF_LAST_SECTION_NUMBER_POS_BYTE_STR));
				}

				PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(FPID, FTableID,
						FTableExtID, true,IsDVB);
				PSIHeaderConfig->PSIHeader.version_number=FVersion;

				unsigned TotalSectionNums=FXMLBINRecordPtr->SectionRecordPtrList.size()-1;

				for(unsigned int i=0;i<FXMLBINRecordPtr->SectionRecordPtrList.size();i++)
				{

					PSIHeaderConfig->PSIHeader.section_number=i;
					PSIHeaderConfig->PSIHeader.last_section_number=TotalSectionNums;
					PSIXMLBINSectionRecordPtr TmpSectionPtr=FXMLBINRecordPtr->SectionRecordPtrList[i];
					if(TmpSectionPtr->SectionTableExtID>-1)
						PSIHeaderConfig->PSIHeader.SetTableExtID(TmpSectionPtr->SectionTableExtID);
					unsigned int SrcDataLength=TmpSectionPtr->HeaderBufferLength+TmpSectionPtr->ItemBufferLength;
					RawBufferPtr TmpSrcBuffer=TmpSectionPtr->GetAllPSISectionDataBuffer();
					if(RefLastSectionNumPos>0)
					{
						unsigned char * TmpPtr=TmpSrcBuffer.get();
						TmpPtr[RefLastSectionNumPos]=TotalSectionNums;
					}
					aStream->WriteSpecialSectionDataToTSStream(aTSStream,
							PSIHeaderConfig,
							TmpSrcBuffer, SrcDataLength,
							0, SrcDataLength,FDataCounter,
							FCrc32Counter);
					aTSStream->InsertNullPacket();
					aTSStream->InsertNullPacket();
					aTSStream->InsertNullPacket();
				}



			}


		}
	}
}
