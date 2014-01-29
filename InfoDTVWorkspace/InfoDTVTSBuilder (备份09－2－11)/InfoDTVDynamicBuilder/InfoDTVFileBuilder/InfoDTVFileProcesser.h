/*
 * FristPassFileProcesser.h
 *
 *  Created on: 2008-12-14
 *      Author: victor
 */

#ifndef FRISTPASSFILEPROCESSER_H_
#define FRISTPASSFILEPROCESSER_H_
#include <map>
#include <deque>
//#include <IceUtil/IceUtil.h>

//#include <strstream>
//#include "../TinyXML/tinyxml.h"
#include "../RapidXML/rapidxml.hpp"
#include <string>
#include "../../Common/TS.Library/TSLibrary.h"
#include "InfoDTVObject.h"
#include "PostIBLProcesser.h"
#include "../../Common/Log/Log.h"
using namespace std;

namespace InfoDTV
{

	namespace DynamicBuilder
	{
		namespace FileBuilder
		{

			//			typedef boost::shared_ptr<TiXmlDocument> TiXmlDocumentPtr;
			class InfoDTVFileProcesser
			{

				private:
					InfoDTV_Common_Log::InfoDTVLogger FLogger;
					void Log(string ALogStr)
					{
						FLogger.information(ALogStr);
					}

					unsigned short FPID;

					vector<InfoDTVObjectPtr>& FObjectList;
					map<string, unsigned short>& FFileIDIndexer;
					deque<string>& FProcessDeque; //需要处理的队列
					map<string,int> FTmpProcessedMap;//在处理过程中已经处理的队列
					TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter;
					string FRootPath;
					int FGlobalPassCount;
					PostIBLProcesser FPostProcesser;
					bool FObjectOverFlow;
					int FindEmptyInfoDTVScenarioIndex();

					int FindEmptyInfoDTVObjectIndex();
					void CleanObjectList(unsigned int aPassCount);

					void ProcessDeque();



					void ProcessIBL(string aFileName);


					//					inline bool HasLinkID(const vector<unsigned short>& aLinkIDs,const unsigned short aID)
					//					{
					//
					//					}

					inline string toUpper(string s);

					string& replace_all(string& str, const string& old_value, const string& new_value);
					void AddImageLink(InfoDTVObjectPtr aObject, string aImageName);
					void AddRemoteIBLLink(InfoDTVObjectPtr aObject, string aRLinkStr);

					void AddIBLLink(InfoDTVObjectPtr aObject, string aIBLName);

					void IBLProcessAction(InfoDTVObjectPtr aObject, rapidxml::xml_node<> *node, string AName,
					        string ASrcName);

					void IBLProcessGroupAction(InfoDTVObjectPtr aObject, string aGAValue);



					void IBLProcessImageLink(InfoDTVObjectPtr aObject, rapidxml::xml_node<> *node, int ImgType);

					void ProcessInfoDTVIBLObject(InfoDTVObjectPtr aObject, rapidxml::xml_document<> &aXmlDocument);
					void ReInitObjectList();
				public:
					InfoDTVFileProcesser(unsigned short aPID, vector<InfoDTVObjectPtr> &aObjectList, map<
					        string, unsigned short> &aFileIDIndexer, deque<string> &aProcessDeque,
					        TSLibrary::DVB::IPSICrc32CounterPtr aCrc32Counter) ;

					void BuildDefaultScenarioObject(InfoDTVObjectPtr aInfoDTVObject, unsigned short aIndex);

					void BuildDefaultIndexScenarioObject(InfoDTVObjectPtr aInfoDTVObject);

					void BuildDefaultImageObject(InfoDTVObjectPtr aInfoDTVObject);

					void Init();


					void Start( int aGlobalPassCount, string aRootPath);

			};
		}
	}
}

#endif /* FRISTPASSFILEPROCESSER_H_ */
