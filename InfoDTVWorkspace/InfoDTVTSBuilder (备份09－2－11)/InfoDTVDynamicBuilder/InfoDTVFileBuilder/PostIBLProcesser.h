/*
 * PostIBLProcesser.h
 *
 *  Created on: 2008-12-21
 *      Author: victor
 */

#ifndef POSTIBLPROCESSER_H_
#define POSTIBLPROCESSER_H_
#include <map>
#include <deque>
//#include <IceUtil/IceUtil.h>

#include <boost/shared_ptr.hpp>
#include <string>
#include "../../Common/TS.Library/TSLibrary.h"
#include "../../Common/CodeConverter.h"
#include "InfoDTVObject.h"
#include "../../Common/Log/Log.h"
using namespace std;
namespace InfoDTV
{

	namespace DynamicBuilder
	{
		namespace FileBuilder
		{

			class PostIBLProcesser
			{
				private:
					CodeConverter FCodeConverter;
					InfoDTV_Common_Log::InfoDTVLogger FLogger;
					void Log(string ALogStr)
					{
						FLogger.information(ALogStr);
					}
					vector<InfoDTVObjectPtr>& FObjectList;
					map<string, unsigned short>& FFileIDIndexer;

					InfoDTVObjectPtr GetTargetObjectByName(string aFileName);
					inline string toUpper(string s);
					string& replace_all(string& str, const string& old_value, const string& new_value);
					string EncodeValue(string EncodeChar,const string aValue);


					string ProcessValue(string aValue);

					string RebuildXML(string aElementName,vector<string> &aKeyOrderList,map<string,string> &aAttributeMap,string aElementValue, bool IsNeedValue);

					string PostProcessXMLInstructionElement(string aTagName,string aTagValue,vector<string> &aKeyOrderList,map<string,string> &aAttributeMap);



					void PostGetImageLink(string aImgLinkName,map<string,string> &aAttributeMap);

					string PostProcessGroupAction(string aValue);
					void PostProcessAction(string aActionString,string aAsrcString,map<string,string>&aAttributeMap);
					void PostProcessIBL(InfoDTVObjectPtr aObject);
				public:
					PostIBLProcesser(vector<InfoDTVObjectPtr> &aObjectList, map<
							string, unsigned short> &aFileIDIndexer);

							void PostProcessAll();

			};
		}
	}
}
#endif /* POSTIBLPROCESSER_H_ */
