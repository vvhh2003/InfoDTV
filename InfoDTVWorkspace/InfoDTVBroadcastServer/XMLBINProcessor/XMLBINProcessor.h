/*
 * XMLBINProcessor.h
 *
 *  Created on: 2009-2-1
 *      Author: victor
 */

#ifndef XMLBINPROCESSOR_H_
#define XMLBINPROCESSOR_H_


#include <string>
#include <boost/shared_ptr.hpp>
#include "../RapidXML/rapidxml.hpp"
#include "../Common/XMLBINRecord.h"

#ifdef POCO
#include "Poco/SharedPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/Buffer.h"
using Poco::SharedPtr;
using Poco::Buffer;
using Poco::XML::Document;
using Poco::XML::AutoPtr;
#endif

	namespace XMLBIN
	{
		class XMLBINProcessor
		{
			private:
				string FTemplateFileName;
				string FError;

				string FSrcXMLDocumnetText;
				boost::shared_ptr<rapidxml::xml_document<> > FSrcXmlDocument;
//				boost::shared_ptr<Buffer<unsigned char> > BuildBin();
				void LoadXML();
			public:
				XMLBINProcessor(string aSrcXMLName);
				XMLBINProcessor(string aSrcXMLContent,bool aIsTextLoad);
				~XMLBINProcessor();
//				void Init();
				string GetError() const;
				//返回 空 就需要检查错误位置
				XMLBINRecordPtr ProcessXML(string aTargetXMLName);
				XMLBINRecordPtr ProcessXML(string aTargetXMLContent,bool IsText);

				XMLBINRecordPtrList ProcessMultiRootXML(string aTargetXMLName);
				XMLBINRecordPtrList ProcessMultiRootXML(string aTargetXMLContent,bool IsText);
				string BuildSample();
		};
	}

#endif /* XMLBINPROCESSOR_H_ */
