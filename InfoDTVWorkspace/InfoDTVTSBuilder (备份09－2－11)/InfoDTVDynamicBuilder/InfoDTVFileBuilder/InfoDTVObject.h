/*
 * InfoDTVObject.h
 *
 *  Created on: 2008-12-11
 *      Author: victor
 */

#ifndef INFODTVOBJECT_H_
#define INFODTVOBJECT_H_

#include "../../Common/TS.Library/InfoDTV/ObjectInfoTable.h"
#include "../../Common/TS.Library/InfoDTV/ScenarioInfoTable.h"
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem/convenience.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "../../Common/Log/Log.h"
using namespace std;
using namespace TSLibrary::InfoDTV;
namespace InfoDTV
{
	namespace DynamicBuilder
	{
		namespace FileBuilder
		{

			const unsigned char DefaultBMP[58] = { 0x42, 0x4d, 0x3a, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x36, 0x0, 0x0, 0x0,
			        0x28, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0,
			        0x0, 0x4, 0x0, 0x0, 0x0, 0xc4, 0xe, 0x0, 0x0, 0xc4, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
			        0x0, 0x0, 0xff, 0xff, 0xff, 0x0 };
			class InfoDTVObject;
			typedef boost::shared_ptr<InfoDTVObject> InfoDTVObjectPtr;
			class InfoDTVObject
			{
				private:
					bool FIsBinding;//在第一次分析时使用，一旦绑定只能在该文件上更新，除非解除绑定
					unsigned short FPID;
					TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter;
//					InfoDTV_Common_Log::InfoDTVLogger FLogger;
					void Log(string ALogStr)
					{
//						FLogger.information(ALogStr);
						cout<<"InfoDTV对象"<<ID<<":"<<ALogStr<<endl;
					}

					void LoadIBLFile(string aFileNameStr);

					void LoadImageFile(string aFileName, unsigned char aObjectType);
					void UpdateImageFileLinkFrom(vector<InfoDTVObjectPtr>& aObjectList);

					bool IsFileModifyed(boost::filesystem::path aFilePath);
				public:
					unsigned short ID;
					string FileName;
					ScenarioInfoTablePtr ScenarioInfo;
					ObjectInfoTablePtr Object;
					time_t LastFileDateTime;

					unsigned int PassCount;//由外部修改
					string IBLFileContent;
					vector<unsigned short> LinkToIDs;
					vector<unsigned short> LinkFromIDs;

					InfoDTVObject(unsigned short aPID, unsigned short aID,
					        TSLibrary::DVB::IPSICrc32CounterPtr aCrc32Counter);
					//					InfoDTVObject(unsigned short aID,string aFileName):
					//						FIsBinding(false),ID(aID),FileName(aFileName),PassCount(0)
					//					{
					//
					//					}

					void BuildDefaultScenarioObject(unsigned short aIndex);

					void BuildDefaultIndexScenarioObject();

					void BuildDefaultImageObject();
					inline string toUpper(string s);

					unsigned char GetImageFileType(boost::filesystem::path &aFilePath);
					void SetLastFileDateTime(boost::filesystem::path aFilePath);

					bool SetBindingImage(string aRootPath, string aFileName, vector<InfoDTVObjectPtr>& aObjectList);

					void PutScenarioContent(string aScenarioContent);

					void PutScenarioContent(boost::shared_ptr<unsigned char> aScenarioContent,const unsigned int aContentLength);

					bool SetBindingIBL(string aRootPath, string aFileName);

					void ClearBinding();
					bool IsBinding();
			};

		}
	}
}
#endif /* INFODTVOBJECT_H_ */
