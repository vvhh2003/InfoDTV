/*
 * XMLBINRecord.h
 *
 *  Created on: 2009-2-12
 *      Author: victor
 */

#ifndef XMLBINRECORD_H_
#define XMLBINRECORD_H_
#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>


using namespace std;
namespace XMLBIN
{
	const string PID_STR="PID";
	const string TABLE_ID_STR="TABLE_ID";
	const string TABLE_EXT_ID_STR="TABLE_EXT_ID";
	const string VERSION_NUMBER_STR="VERSION_NUMBER";
	const string IS_MPEG2_STR="IS_MPEG2";
	const string IS_CONTINUE_COUNTER_STR="IS_CONTINUE_COUNTER";
	const string REF_LAST_SECTION_NUMBER_POS_BYTE_STR="REF_LAST_SECTION_NUMBER_POS_BYTE";
	struct XMLBINRecord
	{
		public:
			boost::shared_ptr<unsigned char> Buffer;
			unsigned int BufferLength;
			map<string,string> ExtValueMap;
			XMLBINRecord():Buffer(),BufferLength(0),ExtValueMap()
			{

			}
	};




	typedef boost::shared_ptr<XMLBINRecord> XMLBINRecordPtr;

	typedef vector<XMLBINRecordPtr > XMLBINRecordPtrList;
}

#endif /* XMLBINRECORD_H_ */
