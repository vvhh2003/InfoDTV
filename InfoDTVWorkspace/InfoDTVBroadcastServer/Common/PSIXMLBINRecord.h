/*
 * XMLBINRecord.h
 *
 *  Created on: 2009-2-12
 *      Author: victor
 */

#ifndef PSIXMLBINRECORD_H_
#define PSIXMLBINRECORD_H_
#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace PSIXMLBIN
{
	using namespace std;
	const string PSIXMLBIN_IS_INCLUDE_ITEM_SIZE_STR="IS_INCLUDE_ITEM_SIZE";
	const string PSIXMLBIN_IS_SIZE_LIMITED_1024_STR="IS_SIZE_LIMITED_1024";
	const string PID_STR="PID";
	const string TABLE_ID_STR="TABLE_ID";
	const string TABLE_EXT_ID_STR="TABLE_EXT_ID";
	const string VERSION_NUMBER_STR="VERSION_NUMBER";
	const string IS_MPEG2_STR="IS_MPEG2";
	const string IS_CONTINUE_COUNTER_STR="IS_CONTINUE_COUNTER";
	const string REF_LAST_SECTION_NUMBER_POS_BYTE_STR="REF_LAST_SECTION_NUMBER_POS_BYTE";
	struct PSIXMLBINSectionRecord
	{
		public:

			boost::shared_ptr<unsigned char> HeaderBuffer;
			boost::shared_ptr<unsigned char> ItemBuffer;
			unsigned short HeaderBufferLength;
			unsigned short ItemBufferLength;
//			unsigned char SectionCount;
//			unsigned char CurrentSectionNum;
//			bool IsIncludeItemsSize; //reserve 4 Bit loop_length 12 Bit desc in ExtValueMap
			boost::shared_ptr< map<string,string> > ExtValueMapPtr;
			int SectionTableExtID;
			PSIXMLBINSectionRecord():HeaderBuffer(),ItemBuffer(),
			HeaderBufferLength(0),ItemBufferLength(0),ExtValueMapPtr(new std::map<string,string>()),SectionTableExtID(-1)
//			SectionCount(0),
//			CurrentSectionNum(0),
//			IsIncludeItemsSize(false) ,
			{

			}

			boost::shared_ptr<unsigned char> GetAllPSISectionDataBuffer()
			{
				bool IsIncludeItemsSize=false;
				unsigned int AllBufferSize=HeaderBufferLength+ItemBufferLength;
				if(ExtValueMapPtr->count(PSIXMLBIN_IS_INCLUDE_ITEM_SIZE_STR)!=0)
				{
					IsIncludeItemsSize=true;
					AllBufferSize+=1;
				}
				boost::shared_ptr<unsigned char> AllBuffer((unsigned char *)std::malloc(AllBufferSize),&free);

				unsigned char * TmpAllBuferPtr=AllBuffer.get();
				if(HeaderBufferLength>0)
					std::memcpy(TmpAllBuferPtr,HeaderBuffer.get(),HeaderBufferLength);
				TmpAllBuferPtr+=HeaderBufferLength;
				if(IsIncludeItemsSize)
				{
					TmpAllBuferPtr[0]=(ItemBufferLength>>8)&0xf;
					TmpAllBuferPtr[0]+=0xF0;
					TmpAllBuferPtr[1]=ItemBufferLength&0x00ff;
					TmpAllBuferPtr+=2;
				}
				std::memcpy(TmpAllBuferPtr,ItemBuffer.get(),ItemBufferLength);
				return AllBuffer;
			}
	};
	typedef boost::shared_ptr<PSIXMLBINSectionRecord> PSIXMLBINSectionRecordPtr;

	typedef vector<PSIXMLBINSectionRecordPtr > PSIXMLBINSectionRecordPtrList;
	struct PSIXMLBINRecord
	{
		public:
			PSIXMLBINSectionRecordPtrList  SectionRecordPtrList;
			unsigned int CurrentSectionRecordIndex;
			PSIXMLBINRecord():SectionRecordPtrList(),CurrentSectionRecordIndex(0)
			{

			}
			PSIXMLBINSectionRecordPtr GetNewSectionRecord()
			{
				PSIXMLBINSectionRecordPtr TmpPtr(new PSIXMLBINSectionRecord);
				SectionRecordPtrList.push_back(TmpPtr);
				CurrentSectionRecordIndex=SectionRecordPtrList.size()-1;
				return SectionRecordPtrList[SectionRecordPtrList.size()-1];
			}

	};

	typedef boost::shared_ptr<PSIXMLBINRecord> PSIXMLBINRecordPtr;

	typedef vector<PSIXMLBINRecordPtr > PSIXMLBINRecordPtrList;
}

#endif /* XMLBINRECORD_H_ */
