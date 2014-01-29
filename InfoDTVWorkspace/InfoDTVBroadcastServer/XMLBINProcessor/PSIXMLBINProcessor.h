/*
 * XMLBINProcessor.h
 *
 *  Created on: 2009-2-1
 *      Author: victor
 */

#ifndef PSIXMLBINPROCESSOR_H_
#define PSIXMLBINPROCESSOR_H_


#include <string>
#include <boost/shared_ptr.hpp>
#include "../RapidXML/rapidxml.hpp"
#include "../Common/PSIXMLBINRecord.h"

#ifdef POCO
#include "Poco/SharedPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/Buffer.h"
using Poco::SharedPtr;
using Poco::Buffer;
#endif

	namespace PSIXMLBIN
	{
		class PSIXMLBINProcessor
		{
			private:
				string FTemplateFileName;
				string FError;

				string FSrcXMLDocumnetText;
				boost::shared_ptr<rapidxml::xml_document<> > FSrcXmlDocument;
//				boost::shared_ptr<Buffer<unsigned char> > BuildBin();
				void LoadXML();
			public:
				PSIXMLBINProcessor(string aSrcXMLName);
				PSIXMLBINProcessor(string aSrcXMLContent,bool aIsTextLoad);
				~PSIXMLBINProcessor();
//				void Init();
				string GetError() const;
				//返回 空 就需要检查错误位置
				PSIXMLBINRecordPtr ProcessXML(string aTargetXMLName);
				PSIXMLBINRecordPtr ProcessXML(string aTargetXMLContent,bool IsText);

				PSIXMLBINRecordPtrList ProcessMultiRootXML(string aTargetXMLName);
				PSIXMLBINRecordPtrList ProcessMultiRootXML(string aTargetXMLContent,bool IsText);
				string BuildSample();
		};
	}

#endif /* XMLBINPROCESSOR_H_ */
