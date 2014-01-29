/*
 * XMLBINProcessor.cpp
 *
 *  Created on: 2009-2-1
 *      Author: victor
 */
#include "PSIXMLBINProcessor.h"
//#include "Poco/DOM/DOMParser.h"
//#include "Poco/DOM/NodeIterator.h"
//#include "Poco/DOM/NodeFilter.h"
//#include "Poco/SAX/InputSource.h"
//#include "Poco/Exception.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../RapidXML/rapidxml_print.hpp"
#include <boost/lexical_cast.hpp>
#include <vector>
#include "VBitStream.h"

	namespace PSIXMLBIN
	{
//		using Poco::XML::DOMParser;
//		using Poco::XML::InputSource;
//		using Poco::XML::NodeIterator;
//		using Poco::XML::NodeFilter;
//		using Poco::XML::Node;
//		using Poco::Exception;

		string LoadXMLFile(string aFileNameStr)
		{
			try
			{
				ifstream in(aFileNameStr.c_str());
				ostringstream os;
				os << in.rdbuf();
				return os.str();
			}
			catch(...)
			{
				return "";
			}
		}

		PSIXMLBINProcessor::PSIXMLBINProcessor(string aSrcXMLContent,bool aIsTextLoad):FTemplateFileName(""),FError(""),FSrcXMLDocumnetText(aSrcXMLContent),FSrcXmlDocument()
		{

		}

		PSIXMLBINProcessor::PSIXMLBINProcessor(string aSrcXMLName):FTemplateFileName(aSrcXMLName),FError(""),FSrcXMLDocumnetText(""),FSrcXmlDocument()
		{

		}
		PSIXMLBINProcessor::~PSIXMLBINProcessor()
		{

		}
		string PSIXMLBINProcessor::GetError() const
		{
			return FError;
		}

		inline string toUpper(string s)
		{
			if(s=="") return "";
			string upper(s);
			std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int)) std::toupper);
			//cout<<upper<<std::endl;
			return upper;
		}



		char * SetTargetXMLString(const boost::shared_ptr<rapidxml::xml_document<> > aDocPtr,const string aValue)
		{
			string NoteValue=aValue;
			char *node_value = aDocPtr->allocate_string(NoteValue.c_str(),NoteValue.size()+1);
			return node_value;
		}

		rapidxml::xml_node<> * SetTargetXMLRootNode(const boost::shared_ptr<rapidxml::xml_document<> > aDocPtr,const char *anode_name)
		{
			rapidxml::xml_node<> *TargetRootNode = aDocPtr->allocate_node(rapidxml::node_element, anode_name);
			aDocPtr->append_node(TargetRootNode);
			return TargetRootNode;
		}

		rapidxml::xml_node<> * SetTargetXMLNode(const boost::shared_ptr<rapidxml::xml_document<> > aDocPtr,rapidxml::xml_node<> * aParentNodePtr,const char *anode_name)
		{
			rapidxml::xml_node<> *TargetNodePtr = aDocPtr->allocate_node(rapidxml::node_element, anode_name);
			aParentNodePtr->append_node(TargetNodePtr);
			return TargetNodePtr;
		}

		void SetTargetXMLNodeValue(
				const boost::shared_ptr<rapidxml::xml_document<> > aDocPtr,
				rapidxml::xml_node<> * aParentNodePtr,
				const char *value,size_t size)
		{
			char *TargetValue = aDocPtr->allocate_string(value, size);
			aParentNodePtr->value(TargetValue,size);
		}

		rapidxml::xml_attribute<> * SetTargetXMLNodeAttr(
				const	boost::shared_ptr<rapidxml::xml_document<> > aDocPtr,
				rapidxml::xml_node<> * aParentNodePtr,
				const char *aAttr_name,const char *aAttr_value)
				{
			rapidxml::xml_attribute<> *attr = aDocPtr->allocate_attribute(aAttr_name, aAttr_value);
			aParentNodePtr->append_attribute(attr);
			return attr;
				}

		string GetXMLDocAttrValue(const rapidxml::xml_node<> *aSrcNode,const string aAttrName)
		{
			rapidxml::xml_attribute<> *TmpAttr =aSrcNode->first_attribute(aAttrName.c_str(),aAttrName.size(),false);
			if(!TmpAttr)
			{
				return "";
			}
			string TmpAttrValue = TmpAttr->value();
			return TmpAttrValue;
		}

		void ProductTargetXML(const rapidxml::xml_node<> *aSrcRootNode,const boost::shared_ptr<rapidxml::xml_document<> > aTargetXmlDocumentPtr,rapidxml::xml_node<> * aTargetRootNodePtr)
		{
			cout<<"ProductTargetXML"<<endl;
			rapidxml::xml_node<> *TmpSrcNode=aSrcRootNode->first_node();

			while(TmpSrcNode)
			{
				string SrcTagName = TmpSrcNode->name();
				SrcTagName = toUpper(SrcTagName);
				cout<<SrcTagName<<endl;

				string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
				cout<<TmpTargetNodeName<<endl;
				char *Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
				rapidxml::xml_node<> *TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,aTargetRootNodePtr,Tmp_Target_node_name);
				if (SrcTagName == "CONTENT")
				{
					string TmpSrcNValue=GetXMLDocAttrValue(TmpSrcNode,"VALUE");
					if(TmpSrcNValue=="")
					{
//						string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
//						char *Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
//						rapidxml::xml_node<> *TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,aTargetRootNodePtr,Tmp_Target_node_name);

						char* TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"TYPE");
						char* TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,"INT");
						SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);

						string TmpBitsString=GetXMLDocAttrValue(TmpSrcNode,"BITS");
						int aBits=boost::lexical_cast<int>(TmpBitsString);
						unsigned int MaxValue=0xFFFFFFFF>>(32-aBits);
						TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"VALUE");
						TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,boost::lexical_cast<string>(MaxValue));
						SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);
					}

				}
				else if (SrcTagName == "ITEM_EXT_VALUE")
				{
					char* TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"TYPE");
					char* TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,"INT");
					SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);
					int aBits=16;
					unsigned int MaxValue=0xFFFFFFFF>>(32-aBits);
					TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"VALUE");
					TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,boost::lexical_cast<string>(MaxValue));
					SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);
				}
				else if (SrcTagName == "SECTION_SPLITTER")
				{
					char* TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"TYPE");
					char* TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,"INT");
					SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);
					int aBits=8;
					unsigned int MaxValue=0xFFFFFFFF>>(32-aBits);
					TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"VALUE");
					TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,boost::lexical_cast<string>(MaxValue));
					SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);
				}
				else if (SrcTagName == "ITEM_EXT_VALUE")
				{
					char* TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"TYPE");
					char* TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,"INT");
					SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);
					int aBits=16;
					unsigned int MaxValue=0xFFFFFFFF>>(32-aBits);
					TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"VALUE");
					TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,boost::lexical_cast<string>(MaxValue));
					SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);
				}
				else if (SrcTagName == "STRCONTENT")
				{
//					string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
//					char *Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
//					rapidxml::xml_node<> *TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,aTargetRootNodePtr,Tmp_Target_node_name);

					char* TmpValueName=SetTargetXMLString(aTargetXmlDocumentPtr,"TYPE");
					char* TmpValue=SetTargetXMLString(aTargetXmlDocumentPtr,"CHAR");
					SetTargetXMLNodeAttr(aTargetXmlDocumentPtr,TmpTargetNode,TmpValueName,TmpValue);

					string Tmp="SimpleText";
					SetTargetXMLNodeValue(aTargetXmlDocumentPtr,TmpTargetNode,Tmp.c_str(),Tmp.size());

				}
				else if (SrcTagName == "PART")
				{
//					string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
//					char *Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
//					rapidxml::xml_node<> *TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,aTargetRootNodePtr,Tmp_Target_node_name);

					ProductTargetXML(TmpSrcNode,aTargetXmlDocumentPtr,TmpTargetNode);
				}
				else if (SrcTagName == "REPEATPART")
				{
//					string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
//					char *Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
//					rapidxml::xml_node<> *TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,aTargetRootNodePtr,Tmp_Target_node_name);

					TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"ITEMNAME");
					Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
					TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,TmpTargetNode,Tmp_Target_node_name);

					ProductTargetXML(TmpSrcNode,aTargetXmlDocumentPtr,TmpTargetNode);

//					TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,TmpTargetNode,Tmp_Target_node_name);
				}
				else if (SrcTagName == "OPTIONPART")
				{
//					string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
//					char *Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
//					rapidxml::xml_node<> *TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,aTargetRootNodePtr,Tmp_Target_node_name);

					ProductTargetXML(TmpSrcNode,aTargetXmlDocumentPtr,TmpTargetNode);
				}

				else if (SrcTagName == "OPTIONITEM")
				{
//					string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"ITEMNAME");
//					char *Tmp_Target_node_name = SetTargetXMLString(aTargetXmlDocumentPtr,TmpTargetNodeName);
//					rapidxml::xml_node<> *TmpTargetNode = SetTargetXMLNode(aTargetXmlDocumentPtr,aTargetRootNodePtr,Tmp_Target_node_name);

					ProductTargetXML(TmpSrcNode,aTargetXmlDocumentPtr,TmpTargetNode);
				}

				TmpSrcNode=TmpSrcNode->next_sibling();
			}
		}

		string GetRootSample(rapidxml::xml_node<> *aRootNode)
		{
//			cout<<"GetRootSample"<<endl;
			boost::shared_ptr<rapidxml::xml_document<> > FTargetXmlDocument(new rapidxml::xml_document<>());
			rapidxml::xml_attribute<> *TmpAttr =aRootNode->first_attribute("NAME",4,false);
			if(!TmpAttr)
			{
//				FError="ERROR";
				return "";
			}
			string RootName = TmpAttr->value();
			char *Tmp_node_name = SetTargetXMLString(FTargetXmlDocument,RootName);
			rapidxml::xml_node<> *TargetRootNode = SetTargetXMLRootNode(FTargetXmlDocument,Tmp_node_name);
			ProductTargetXML(aRootNode,FTargetXmlDocument,TargetRootNode);

			std::string s;
			rapidxml::print(std::back_inserter(s), *FTargetXmlDocument, 0);
//			cout<<"GetRootSample End"<<endl;
			return s;
		}

		void PSIXMLBINProcessor::LoadXML()
		{
			FSrcXmlDocument.reset(new rapidxml::xml_document<> ());
			if(FSrcXMLDocumnetText=="")
				FSrcXMLDocumnetText=LoadXMLFile(FTemplateFileName);
			if(FSrcXMLDocumnetText=="")
			{
				FSrcXmlDocument.reset();
				FError+="\r\nCan't Load XMLFile";
				return;
			}
			char * content=const_cast<char *>(FSrcXMLDocumnetText.c_str());
			try
			{
				FSrcXmlDocument->parse<0> (content);
			}
			catch(rapidxml::parse_error &e)
			{
				cout<<e.what()<<endl;
				cout<<e.where<char>()<<endl;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return ;
			}
		}

		string PSIXMLBINProcessor::BuildSample()
		{
			FError="";
			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{
				FError+="\r\nLoad Source Bin XML Error!";
				return "";
			}


			rapidxml::xml_node<> *node=FSrcXmlDocument->first_node("ROOT",4,false);
			string ResltStr="";
			while (node)
			{
				string nodeString;
				try
				{
					nodeString=GetXMLDocAttrValue(node,"name");
					ResltStr+=GetRootSample(node);
				}
				catch(...)
				{
					FError+="\r\nProcess Source "+nodeString+"Error";
				}

				node=node->next_sibling("ROOT",4,false);
			}
			return ResltStr;
		}

		void SmartWriteIntToBitStream(const unsigned int aValue, const unsigned int aBits,VBitStreamPtr aVB)
		{
			if(!aVB)
			{
				cout<<"SmartWriteIntToBitStream Error!! VB is NULL"<<endl;
				return;
			}

			switch(aBits)
			{
				case 8:
				{
					aVB->WriteByte(aValue);
					break;
				}
				case 16:
				{
					aVB->WriteInt16(aValue);
					break;
				}
				case 32:
				{
					aVB->WriteInt32(aValue);
					break;
				}
				default:
				{
					aVB->WriteBits(aValue, aBits);
					break;
				}
			}
		}

		bool GetSrcNodeIsIncludeSizeField(const rapidxml::xml_node<> *aSrcNode)
		{
			string IsIncludeSizeStr=toUpper(GetXMLDocAttrValue(aSrcNode,"INCLUDESIZE"));
			bool IsIncludeSize=true;
			if(IsIncludeSizeStr==""||IsIncludeSizeStr!="TRUE")
			{
				IsIncludeSize=false;
			}
			return IsIncludeSize;
		}

		unsigned int GetSrcNodeBitSize(const rapidxml::xml_node<> *aSrcNode,const string aBitFieldName)
		{
			string TmpBitsStr=GetXMLDocAttrValue(aSrcNode,aBitFieldName);
			unsigned int Bits=0;
			if(TmpBitsStr!="")
			Bits=boost::lexical_cast<unsigned int>(TmpBitsStr);
			return Bits;
		}



		string GetHexString(string aValue)
		{
			if(aValue.size()%2==0)
			{
				string TmpResult="";
				for(unsigned int i=0;i<aValue.size()/2;i++)
				{
					string TmpHEX=aValue.substr(i*2,2);
					unsigned int TmpIntValue=0;
					sscanf(TmpHEX.c_str(),"%x",&TmpIntValue);
					unsigned char TmpByteValue=TmpIntValue;
					TmpResult+=TmpByteValue;
				}
				return TmpResult;
			}
			return "";
		}

		void SetExtValueMap(boost::shared_ptr< std::map<string,string> > aExtValueMapPtr,const string aKeyValue,const string aValue)
		{
			if(aExtValueMapPtr)
			{
				if(aExtValueMapPtr->count(aKeyValue)==0)
				{
//					*aExtValueMapPtr[aKeyValue]=aValue;
					std::pair<string,string> Tmp;
					Tmp.first=aKeyValue;
					Tmp.second=aValue;
					aExtValueMapPtr->insert(Tmp);
				}
			}
		}

		enum PSI_ProductTargetStatus {PS_INIT,PS_TEMP,PS_EXT,PS_PSI_HEAD,PS_PSI_ITEM};
		unsigned int ProductTargetBitStream(PSIXMLVBRecordPtr aPSIVBRecordPtr,const rapidxml::xml_node<> *aSrcRootNode,const rapidxml::xml_node<> * aTargetRootNodePtr,const PSI_ProductTargetStatus aStatus=PS_INIT)
			{
				cout<<"Product Target Bit Stream"<<endl;
				const rapidxml::xml_node<> *TargetRootNodePtr=aTargetRootNodePtr;
				unsigned int WriteBitsCount=0;
				rapidxml::xml_node<> *TmpSrcNode=aSrcRootNode->first_node();

				while(TmpSrcNode)
				{
					string SrcTagName = TmpSrcNode->name();
					SrcTagName = toUpper(SrcTagName);

					string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
					cout<<SrcTagName<<"->"<<TmpTargetNodeName<<"->"<<TargetRootNodePtr->name()<<endl;
					switch(aStatus)
					{
						case PS_TEMP:
							cout<<"Status:PS_TEMP"<<endl;
							break;
						case PS_EXT:
							cout<<"Status:PS_EXT"<<endl;
							break;
						case PS_PSI_HEAD:
							cout<<"Status:PS_PSI_HEAD"<<endl;
							break;
						case PS_PSI_ITEM:
							cout<<"Status:PS_PSI_ITEM"<<endl;
							break;
						case PS_INIT:
							cout<<"Status:PS_INIT"<<endl;
							break;
					}
					if (SrcTagName == "CONTENT")
					{
						if(aStatus==PS_INIT)
							return 0;
						unsigned int Bits=GetSrcNodeBitSize(TmpSrcNode,"BITS");
						string TmpSrcDefineValueStr=GetXMLDocAttrValue(TmpSrcNode,"VALUE");
						if(TmpSrcDefineValueStr!="")
						{
							unsigned int TmpSrcDefineValue=boost::lexical_cast<unsigned int>(TmpSrcDefineValueStr);
							switch(aStatus)
							{
								case PS_TEMP:
									SmartWriteIntToBitStream(TmpSrcDefineValue,Bits,aPSIVBRecordPtr->TmpVB);
									WriteBitsCount+=Bits;
									break;
								case PS_EXT:
									SetExtValueMap(aPSIVBRecordPtr->ExtValueMapPtr,TmpTargetNodeName,TmpSrcDefineValueStr);
									break;
								case PS_PSI_HEAD:
									SmartWriteIntToBitStream(TmpSrcDefineValue,Bits,aPSIVBRecordPtr->HeaderVB);
//									WriteBitsCount+=Bits;
									break;
								case PS_PSI_ITEM:
									SmartWriteIntToBitStream(TmpSrcDefineValue,Bits,aPSIVBRecordPtr->CurrentVB);
									WriteBitsCount+=Bits;
									break;
								case PS_INIT:
									break;
							}
						}
						else
						{
							rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
							if(TargetNode)
							{
								string TmpTargetValue=GetXMLDocAttrValue(TargetNode,"VALUE");
								string TmpTargetValueType=toUpper(GetXMLDocAttrValue(TargetNode,"TYPE"));
								if(TmpTargetValueType=="")
								{
									TmpTargetValueType="INT";
								}
								unsigned int TmpTargetIntValue=0;
								if(TmpTargetValueType=="INT")
								{
									TmpTargetIntValue=boost::lexical_cast<unsigned int>(TmpTargetValue);
								}
								else if(TmpTargetValueType=="CHAR")
								{

								}
								else if(TmpTargetValueType=="HEX")
								{
									sscanf(TmpTargetValue.c_str(),"%x",&TmpTargetIntValue);
								}
								switch(aStatus)
								{
									case PS_INIT:
										break;
									case PS_TEMP:
										SmartWriteIntToBitStream(TmpTargetIntValue,Bits,aPSIVBRecordPtr->TmpVB);
										break;
									case PS_EXT:
										SetExtValueMap(aPSIVBRecordPtr->ExtValueMapPtr,TmpTargetNodeName,boost::lexical_cast<string>(TmpTargetIntValue));
										break;
									case PS_PSI_HEAD:
										SmartWriteIntToBitStream(TmpTargetIntValue,Bits,aPSIVBRecordPtr->HeaderVB);
										break;
									case PS_PSI_ITEM:
										SmartWriteIntToBitStream(TmpTargetIntValue,Bits,aPSIVBRecordPtr->CurrentVB);
										break;
								}
							}
						}

					}
					else if (SrcTagName == "SECTION_SPLITTER")
					{
						if(aStatus!=PS_PSI_ITEM)
							return 0;
						rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
						if(TargetNode)
						{
//							string TmpTargetValue=GetXMLDocAttrValue(TargetNode,"VALUE");
//							string TmpTargetValueType=toUpper(GetXMLDocAttrValue(TargetNode,"TYPE"));
//							if(TmpTargetValueType=="")
//							{
//								TmpTargetValueType="INT";
//							}
//							unsigned int TmpTargetIntValue=0;
//							if(TmpTargetValueType=="INT")
//							{
//								TmpTargetIntValue=boost::lexical_cast<unsigned int>(TmpTargetValue);
//							}
//							else if(TmpTargetValueType=="CHAR")
//							{
//
//							}
//							else if(TmpTargetValueType=="HEX")
//							{
//								sscanf(TmpTargetValue.c_str(),"%x",&TmpTargetIntValue);
//							}
							if(aPSIVBRecordPtr->PSISectionSplitterMap.count(aPSIVBRecordPtr->CurrentVBIndex)==0)
							{
								std::pair<unsigned int,bool> Tmp;
								Tmp.first=aPSIVBRecordPtr->CurrentVBIndex;
								Tmp.second=true;
								aPSIVBRecordPtr->PSISectionSplitterMap.insert(Tmp);
							}
						}
					}
					else if (SrcTagName == "ITEM_EXT_VALUE")
					{
						if(aStatus!=PS_PSI_ITEM)
							return 0;
						rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
						if(TargetNode)
						{
							string TmpTargetValue=GetXMLDocAttrValue(TargetNode,"VALUE");
							string TmpTargetValueType=toUpper(GetXMLDocAttrValue(TargetNode,"TYPE"));
							if(TmpTargetValueType=="")
							{
								TmpTargetValueType="INT";
							}
							unsigned int TmpTargetIntValue=0;
							if(TmpTargetValueType=="INT")
							{
								TmpTargetIntValue=boost::lexical_cast<unsigned int>(TmpTargetValue);
							}
							else if(TmpTargetValueType=="CHAR")
							{

							}
							else if(TmpTargetValueType=="HEX")
							{
								sscanf(TmpTargetValue.c_str(),"%x",&TmpTargetIntValue);
							}
							if(aPSIVBRecordPtr->ExtTableExtIDMap.count(aPSIVBRecordPtr->CurrentVBIndex)==0)
							{
								std::pair<unsigned int,unsigned short> Tmp;
								Tmp.first=aPSIVBRecordPtr->CurrentVBIndex;
								Tmp.second=TmpTargetIntValue;
								aPSIVBRecordPtr->ExtTableExtIDMap.insert(Tmp);
							}
						}
					}
					else if (SrcTagName == "STRCONTENT")
					{
						if(aStatus==PS_INIT)
							return 0;
						bool IsIncludeSize=GetSrcNodeIsIncludeSizeField(TmpSrcNode);
						unsigned int sizeBits=GetSrcNodeBitSize(TmpSrcNode,"SIZEFIELDBITS");
						string TmpSrcDefineValueStr=GetXMLDocAttrValue(TmpSrcNode,"VALUE");
						string TargetStrValue="";
						string TmpTargetValueType="";
						if(TmpSrcDefineValueStr=="")
						{
							rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
							TargetStrValue=TargetNode->value();
							cout<<"string value:"<<TargetStrValue<<endl;
							TmpTargetValueType=toUpper(GetXMLDocAttrValue(TargetNode,"TYPE"));
							if(TmpTargetValueType=="")
							{
								TmpTargetValueType="CHAR";
							}
							if(TmpTargetValueType=="HEX")
							{
								TargetStrValue=GetHexString(TargetStrValue);
							}
						}
						else
						{
							TargetStrValue=TmpSrcDefineValueStr;
						}

						//TODO:UNICODE!!!CONVERT
						unsigned int strSize=TargetStrValue.size();
						switch(aStatus)
						{
							case PS_INIT:
								break;
							case PS_TEMP:
								if(IsIncludeSize)
								{
									aPSIVBRecordPtr->TmpVB->WriteBits(strSize,sizeBits);
								}
								aPSIVBRecordPtr->TmpVB->WriteData((unsigned char *)TargetStrValue.c_str(),strSize);
								break;
							case PS_PSI_HEAD:
								if(IsIncludeSize)
								{
									aPSIVBRecordPtr->HeaderVB->WriteBits(strSize,sizeBits);
								}
								aPSIVBRecordPtr->HeaderVB->WriteData((unsigned char *)TargetStrValue.c_str(),strSize);
								break;
							case PS_EXT:
								SetExtValueMap(aPSIVBRecordPtr->ExtValueMapPtr,TmpTargetNodeName,TargetStrValue);
								break;
							case PS_PSI_ITEM:
								if(IsIncludeSize)
								{
									aPSIVBRecordPtr->CurrentVB->WriteBits(strSize,sizeBits);
								}
								aPSIVBRecordPtr->CurrentVB->WriteData((unsigned char *)TargetStrValue.c_str(),strSize);
								break;
						}
					}
					else if (SrcTagName == "PART")
					{
						string TmpTargetValueTypeStr=toUpper(GetXMLDocAttrValue(TmpSrcNode,"TYPE"));
						if(TmpTargetValueTypeStr=="EXT")
						{
							rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
							PSI_ProductTargetStatus TmpStatus=PS_EXT;
							ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcNode,TargetNode,TmpStatus);
						}
						else if(TmpTargetValueTypeStr=="PSIHEADPART")
						{
							rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
							PSI_ProductTargetStatus TmpStatus=PS_PSI_HEAD;
							ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcNode,TargetNode,TmpStatus);
						}
						else
						{
							bool IsIncludeSize=GetSrcNodeIsIncludeSizeField(TmpSrcNode);
							if(IsIncludeSize)
							{
								unsigned int sizeBits=GetSrcNodeBitSize(TmpSrcNode,"SIZEFIELDBITS");

								VBitStreamPtr TmpSwapVB=aPSIVBRecordPtr->TmpVB;
								aPSIVBRecordPtr->TmpVB.reset(new VBitStream);
								PSI_ProductTargetStatus TmpStatus=PS_TEMP;
								rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
								if(TargetNode)
									ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcNode,TargetNode,TmpStatus);
								unsigned int TmpSize=aPSIVBRecordPtr->TmpVB->GetStreamTotalLength();

								switch(aStatus)
								{
									case PS_INIT:
										break;
									case PS_TEMP:
										TmpSwapVB->WriteBits(TmpSize,sizeBits);
										TmpSwapVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
										aPSIVBRecordPtr->TmpVB=TmpSwapVB;
										break;
									case PS_PSI_HEAD:
										aPSIVBRecordPtr->HeaderVB->WriteBits(TmpSize,sizeBits);
										aPSIVBRecordPtr->HeaderVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
										aPSIVBRecordPtr->TmpVB=TmpSwapVB;
										break;
									case PS_EXT:
										break;
									case PS_PSI_ITEM:
										aPSIVBRecordPtr->CurrentVB->WriteBits(TmpSize,sizeBits);
										aPSIVBRecordPtr->CurrentVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
										aPSIVBRecordPtr->TmpVB=TmpSwapVB;
										break;
								}

							}
							else
							{
								if(aStatus==PS_INIT)
									return 0;
								rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
								ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcNode,TargetNode,aStatus);
							}
						}


					}
					else if (SrcTagName == "REPEATPART")
					{
						string TmpTargetValueTypeStr=toUpper(GetXMLDocAttrValue(TmpSrcNode,"TYPE"));

						if(aStatus!=PS_EXT)
						{
//Add at 2009-8-16 Start
							if(TmpTargetValueTypeStr=="PSI_ITEM_PART")
							{
								bool IsIncludeSize=GetSrcNodeIsIncludeSizeField(TmpSrcNode);
								if(IsIncludeSize)
								{
									unsigned int sizeBits=GetSrcNodeBitSize(TmpSrcNode,"SIZEFIELDBITS");

									VBitStreamPtr TmpSwapVB=aPSIVBRecordPtr->TmpVB;
									aPSIVBRecordPtr->TmpVB.reset(new VBitStream);

									string TmpTargetRepeatItemNodeName = GetXMLDocAttrValue(TmpSrcNode,"ITEMNAME");
									cout<<"--->"<<SrcTagName<<"->"<<TmpTargetRepeatItemNodeName<<endl;
									rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
									if(TargetNode)
										TargetNode =TargetNode->first_node(TmpTargetRepeatItemNodeName.c_str(),TmpTargetRepeatItemNodeName.size(),false);
									while(TargetNode)
									{
										PSI_ProductTargetStatus TmpStatus=PS_TEMP;
										aPSIVBRecordPtr->GetNewItemVBToCurrent();

										ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcNode,TargetNode,TmpStatus);
										TargetNode=TargetNode->next_sibling();
									}
									unsigned int TmpSize=aPSIVBRecordPtr->TmpVB->GetStreamTotalLength();
									if(TmpSize>0)
									{
										switch(aStatus)
										{
											case PS_INIT:
												break;
											case PS_TEMP:
												TmpSwapVB->WriteBits(TmpSize,sizeBits);
												TmpSwapVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
												aPSIVBRecordPtr->TmpVB=TmpSwapVB;
												break;
											case PS_PSI_HEAD:
												aPSIVBRecordPtr->HeaderVB->WriteBits(TmpSize,sizeBits);
												aPSIVBRecordPtr->HeaderVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
												aPSIVBRecordPtr->TmpVB=TmpSwapVB;
												break;
											case PS_EXT:
												break;
											case PS_PSI_ITEM:
												aPSIVBRecordPtr->CurrentVB->WriteBits(TmpSize,sizeBits);
												aPSIVBRecordPtr->CurrentVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
												aPSIVBRecordPtr->TmpVB=TmpSwapVB;
												break;
										}
									}
								}
								else
								{
//Add at 2009-8-16 End
									string TmpTargetRepeatItemNodeName = GetXMLDocAttrValue(TmpSrcNode,"ITEMNAME");
									cout<<"--->"<<SrcTagName<<"->"<<TmpTargetRepeatItemNodeName<<endl;
									rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
									if(TargetNode)
										TargetNode =TargetNode->first_node(TmpTargetRepeatItemNodeName.c_str(),TmpTargetRepeatItemNodeName.size(),false);
									while(TargetNode)
									{
										PSI_ProductTargetStatus TmpStatus=PS_PSI_ITEM;
										aPSIVBRecordPtr->GetNewItemVBToCurrent();

										ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcNode,TargetNode,TmpStatus);
										TargetNode=TargetNode->next_sibling();
									}
								}
							}//Add at 2009-8-16
							else
							{

							}
						}

					}
					else if (SrcTagName == "OPTIONPART")
					{
						if(aStatus!=PS_EXT)
						{
							bool IsIncludeSize=GetSrcNodeIsIncludeSizeField(TmpSrcNode);
							if(IsIncludeSize)
							{
								unsigned int sizeBits=GetSrcNodeBitSize(TmpSrcNode,"SIZEFIELDBITS");

								VBitStreamPtr TmpSwapVB=aPSIVBRecordPtr->TmpVB;
								aPSIVBRecordPtr->TmpVB.reset(new VBitStream);
								PSI_ProductTargetStatus TmpStatus=PS_TEMP;
								/*
								 * 可以先将下面全部的OptionPartItem列出来到一个Map<Name,NodePtr>
								 * 再Target上循环，启用反向查找到对应的SrcNode用本函数递归
								 *
								 */


								map<string,rapidxml::xml_node<> * > TmpSrcOptionItemNodePtrMap;
								rapidxml::xml_node<> *TmpSrcOptionPartItemNodePtr=TmpSrcNode->first_node("OPTIONITEM",10,false);
								while(TmpSrcOptionPartItemNodePtr)
								{
									string TmpTargetNodeName = toUpper(GetXMLDocAttrValue(TmpSrcOptionPartItemNodePtr,"NAME"));
									if(TmpTargetNodeName!="")
										TmpSrcOptionItemNodePtrMap[TmpTargetNodeName]=TmpSrcOptionPartItemNodePtr;
									TmpSrcOptionPartItemNodePtr=TmpSrcOptionPartItemNodePtr->next_sibling();
								}

								rapidxml::xml_node<> *TargetOptionRootNodePtr =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);

								if(TargetOptionRootNodePtr)
								{
									rapidxml::xml_node<> *TargetOptionItemNodePtr =TargetOptionRootNodePtr->first_node();

									while(TargetOptionItemNodePtr)
									{

										string TargetOptionItemName = TargetOptionItemNodePtr->name();
										TargetOptionItemName = toUpper(TargetOptionItemName);
										if(TmpSrcOptionItemNodePtrMap.count(TargetOptionItemName)>0)
										{
											rapidxml::xml_node<> *TmpSrcOptionItemPtr=TmpSrcOptionItemNodePtrMap[TargetOptionItemName];
											ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcOptionItemPtr,TargetOptionItemNodePtr,TmpStatus);
										}
										TargetOptionItemNodePtr=TargetOptionItemNodePtr->next_sibling();
									}

								}
								unsigned int TmpSize=aPSIVBRecordPtr->TmpVB->GetStreamTotalLength();
								if(TmpSize>0)
								{
									switch(aStatus)
									{
										case PS_INIT:
											break;
										case PS_TEMP:
											TmpSwapVB->WriteBits(TmpSize,sizeBits);
											TmpSwapVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
											aPSIVBRecordPtr->TmpVB=TmpSwapVB;
											break;
										case PS_PSI_HEAD:
											aPSIVBRecordPtr->HeaderVB->WriteBits(TmpSize,sizeBits);
											aPSIVBRecordPtr->HeaderVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
											aPSIVBRecordPtr->TmpVB=TmpSwapVB;
											break;
										case PS_EXT:
											break;
										case PS_PSI_ITEM:
											aPSIVBRecordPtr->CurrentVB->WriteBits(TmpSize,sizeBits);
											aPSIVBRecordPtr->CurrentVB->AppendStream(*(aPSIVBRecordPtr->TmpVB));
											aPSIVBRecordPtr->TmpVB=TmpSwapVB;
											break;
									}
								}

							}
							else
							{
								map<string,rapidxml::xml_node<> * > TmpSrcOptionItemNodePtrMap;
								rapidxml::xml_node<> *TmpSrcOptionPartItemNodePtr=TmpSrcNode->first_node("OPTIONITEM",10,false);
								while(TmpSrcOptionPartItemNodePtr)
								{
									string TmpTargetNodeName = toUpper(GetXMLDocAttrValue(TmpSrcOptionPartItemNodePtr,"NAME"));
									if(TmpTargetNodeName!="")
										TmpSrcOptionItemNodePtrMap[TmpTargetNodeName]=TmpSrcOptionPartItemNodePtr;
									TmpSrcOptionPartItemNodePtr=TmpSrcOptionPartItemNodePtr->next_sibling();
								}

								rapidxml::xml_node<> *TargetOptionRootNodePtr =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);

								if(TargetOptionRootNodePtr)
								{
									rapidxml::xml_node<> *TargetOptionItemNodePtr =TargetOptionRootNodePtr->first_node();

									while(TargetOptionItemNodePtr)
									{

										string TargetOptionItemName = TargetOptionItemNodePtr->name();
										TargetOptionItemName = toUpper(TargetOptionItemName);
										if(TmpSrcOptionItemNodePtrMap.count(TargetOptionItemName)>0)
										{
											rapidxml::xml_node<> *TmpSrcOptionItemPtr=TmpSrcOptionItemNodePtrMap[TargetOptionItemName];
											ProductTargetBitStream(aPSIVBRecordPtr,TmpSrcOptionItemPtr,TargetOptionItemNodePtr,aStatus);
										}
										TargetOptionItemNodePtr=TargetOptionItemNodePtr->next_sibling();
									}

								}
							}
						}
					}

					else if (SrcTagName == "OPTIONITEM")
					{
						cout<<"OPTIONITEM in BIN it must be somewhere Error!"<<endl;
					}
					TmpSrcNode=TmpSrcNode->next_sibling();
				}
				unsigned int ResultCount=WriteBitsCount/8;
				return ResultCount;
			}

		void BuildRootBin(PSIXMLVBRecordPtr aPSIVBRecordPtr,const boost::shared_ptr<rapidxml::xml_document<> > aSrcDocPtr,const boost::shared_ptr<rapidxml::xml_document<> > aTargetDocPtr,rapidxml::xml_node<> *aSrcRootNode)
		{
			//			cout<<"GetRootSample"<<endl;
			rapidxml::xml_attribute<> *TmpAttr =aSrcRootNode->first_attribute("NAME",4,false);
			if(!TmpAttr)
			{
				return ;
			}
			string TargetRootTagName = TmpAttr->value();
			rapidxml::xml_node<> *TargetRootNode =aTargetDocPtr->first_node(TargetRootTagName.c_str(),TargetRootTagName.size(),false);
			if(!TargetRootNode)
			{
				return;
			}
			ProductTargetBitStream(aPSIVBRecordPtr,aSrcRootNode,TargetRootNode);
		}


		PSIXMLBINRecordPtrList BuildBinList(const boost::shared_ptr<rapidxml::xml_document<> > aSrcDocPtr,const boost::shared_ptr<rapidxml::xml_document<> > aTargetDocPtr)
		{

			PSIXMLBINRecordPtrList TmpRecList;

			rapidxml::xml_node<> *SrcRootNode=aSrcDocPtr->first_node("ROOT",4,false);

			while (SrcRootNode)
			{
				PSIXMLVBRecordPtr TmpVBRec(new PSIXMLVBRecord);
				PSIXMLBINRecordPtr TmpResult(new PSIXMLBINRecord);
				BuildRootBin(TmpVBRec,aSrcDocPtr,aTargetDocPtr,SrcRootNode);
				SrcRootNode=SrcRootNode->next_sibling("ROOT",4,false);
				cout<<"Result Header Size:"<<TmpVBRec->HeaderVB->GetStreamTotalLength()<<endl;
				cout<<"Result Item Cout:"<<TmpVBRec->ItemVBs.size()<<endl;

				//计算Section 容量 4093－9＝4084
				unsigned int MaxSectionLength=4080;
				if(TmpVBRec->ExtValueMapPtr->count(PSIXMLBIN_IS_SIZE_LIMITED_1024_STR))
				{
					MaxSectionLength=1021;
				}

				//采用尽力填充法填充Result

				//1 准备头数据
				PSIXMLBINSectionRecordPtr TmpSectionPtr=TmpResult->GetNewSectionRecord();
				const unsigned int TmpVBResHeaderSize=TmpVBRec->HeaderVB->GetStreamTotalLength();
				TmpSectionPtr->HeaderBufferLength=TmpVBResHeaderSize;

				if(TmpVBResHeaderSize>0)
				{
					TmpSectionPtr->HeaderBuffer.reset((unsigned char *)std::malloc(TmpVBResHeaderSize),&free);
					std::memcpy(TmpSectionPtr->HeaderBuffer.get(),TmpVBRec->HeaderVB->GetStream(),TmpVBResHeaderSize);
				}

				unsigned int CurrentSectionExtID=0;
				if(TmpVBRec->ExtValueMapPtr->count(TABLE_EXT_ID_STR)>0)
				{
					CurrentSectionExtID=boost::lexical_cast<unsigned short>(TmpVBRec->ExtValueMapPtr->at(TABLE_EXT_ID_STR));
				}
				unsigned int SectionCopyedSize=TmpVBResHeaderSize;
				unsigned char * TmpSectionItemBufferPtr=NULL;
				for(unsigned int i=0;i<TmpVBRec->ItemVBs.size();i++)
				{
					unsigned int TmpVBItemSize=TmpVBRec->ItemVBs[i]->GetStreamTotalLength();
					cout<<"TmpVBItemSize: "<<TmpVBItemSize<<endl;
					if(TmpVBItemSize==0)
					{
						cout<<"Error VB Item Size =0 "<<endl;
						continue;
					}
					//判断是否新建Section的条件变成了三个
					//1、尺寸不够
					//2、连续设置的ExtTableID与之前的不一样
					//3、设置了强制拆分标志
					bool IsNeedNewSection=false;
					if(TmpVBRec->PSISectionSplitterMap.count(i)>0)
					{
						if(TmpVBRec->PSISectionSplitterMap[i])
						{
							IsNeedNewSection=true;
						}
					}
					if(TmpVBRec->ExtTableExtIDMap.count(i)>0)
					{
						TmpSectionPtr->SectionTableExtID=TmpVBRec->ExtTableExtIDMap[i];
						if(TmpVBRec->ExtTableExtIDMap[i]!=CurrentSectionExtID)
						{
							//避免第一次就建两个Section
							if(i>0)
							{
								IsNeedNewSection=true;
							}
							CurrentSectionExtID=TmpVBRec->ExtTableExtIDMap[i];
						}
					}

					//注意这里有可能有BUG 因为可能TmpVBResHeaderSize直接就大于了MaxSectionLength
					if((SectionCopyedSize+TmpVBItemSize)>MaxSectionLength)
					{
						IsNeedNewSection=true;
					}
					if(IsNeedNewSection)
					{
						cout<<"Need a New Section"<<endl;

						//Save Current Section
						TmpSectionPtr->ItemBuffer.reset((unsigned char *)std::malloc(TmpSectionPtr->ItemBufferLength),&free);
						unsigned char * TmpPtr=TmpSectionPtr->ItemBuffer.get();
						std::memcpy(TmpPtr,TmpSectionItemBufferPtr,TmpSectionPtr->ItemBufferLength);
						std::free(TmpSectionItemBufferPtr);
						TmpSectionItemBufferPtr=NULL;
						TmpRecList.push_back(TmpResult);

						//Add New Section
						TmpSectionPtr=TmpResult->GetNewSectionRecord();
						TmpSectionPtr->HeaderBufferLength=TmpVBResHeaderSize;
						if(TmpVBResHeaderSize>0)
						{
							TmpSectionPtr->HeaderBuffer.reset((unsigned char *)std::malloc(TmpVBResHeaderSize),&free);
							std::memcpy(TmpSectionPtr->HeaderBuffer.get(),TmpVBRec->HeaderVB->GetStream(),TmpVBResHeaderSize);
						}
						SectionCopyedSize=TmpVBResHeaderSize;
					}

					if(TmpSectionItemBufferPtr==NULL)
					{
						TmpSectionItemBufferPtr=(unsigned char *)std::malloc(TmpVBItemSize);
						cout<<"malloc size: "<<TmpVBItemSize<<endl;
					}
					else
					{
						TmpSectionItemBufferPtr=(unsigned char *)std::realloc(TmpSectionItemBufferPtr,TmpSectionPtr->ItemBufferLength+TmpVBItemSize);
						cout<<"realloc size: "<<TmpSectionPtr->ItemBufferLength+TmpVBItemSize<<endl;
					}
					if(!TmpSectionItemBufferPtr)
					{
						cout<<"Error TmpSectionItemBufferPtr =0 "<<endl;
					}
					//						if(!TmpSectionPtr->ItemBuffer)
					//							TmpSectionPtr->ItemBuffer.reset((unsigned char *)std::malloc(TmpVBItemSize),&free);
					//						else
					//							TmpSectionPtr->ItemBuffer.reset((unsigned char *)std::realloc(TmpSectionPtr->ItemBuffer.get(),TmpSectionPtr->ItemBufferLength+TmpVBItemSize),&free);

					//					unsigned char * TmpPtr=TmpSectionPtr->ItemBuffer.get();
					//						TmpPtr+=TmpSectionPtr->ItemBufferLength;
					//						std::memcpy(TmpPtr,TmpVBRec->ItemVBs[i]->GetStream(),TmpVBItemSize);
					cout<<"Item Length:"<<TmpSectionPtr->ItemBufferLength<<" TmpVBItemSize:"<<TmpVBItemSize<<endl;
					unsigned char * TmpTmpSectionItemBufferPtr=TmpSectionItemBufferPtr+TmpSectionPtr->ItemBufferLength;
					std::memcpy(TmpTmpSectionItemBufferPtr,TmpVBRec->ItemVBs[i]->GetStream(),TmpVBItemSize);
					SectionCopyedSize+=TmpVBItemSize;
					TmpSectionPtr->ExtValueMapPtr=TmpVBRec->ExtValueMapPtr;


					TmpSectionPtr->ItemBufferLength+=TmpVBItemSize;
					cout<<"For ItemBufferLength Length:"<<TmpSectionPtr->ItemBufferLength<<endl;
				}
				cout<<"Total ItemBufferLength Length:"<<TmpSectionPtr->ItemBufferLength<<" SectionCopyedSize-TmpVBResHeaderSize:"<<SectionCopyedSize-TmpVBResHeaderSize<<endl;
				TmpSectionPtr->ItemBuffer.reset((unsigned char *)std::malloc(TmpSectionPtr->ItemBufferLength),&free);
				unsigned char * TmpPtr=TmpSectionPtr->ItemBuffer.get();
				std::memcpy(TmpPtr,TmpSectionItemBufferPtr,TmpSectionPtr->ItemBufferLength);
				std::free(TmpSectionItemBufferPtr);
				TmpSectionItemBufferPtr=NULL;
				TmpRecList.push_back(TmpResult);
			}

			return TmpRecList;
		}



		PSIXMLBINRecordPtr BuildBin(const boost::shared_ptr<rapidxml::xml_document<> > aSrcDocPtr,const boost::shared_ptr<rapidxml::xml_document<> > aTargetDocPtr)
		{
			PSIXMLVBRecordPtr TmpVBRec(new PSIXMLVBRecord);
			PSIXMLBINRecordPtr Result(new PSIXMLBINRecord);
//			XMLBINRecordPtr TmpRec(new XMLBINRecord);
			rapidxml::xml_node<> *SrcRootNode=aSrcDocPtr->first_node("ROOT",4,false);
			if(SrcRootNode)
				BuildRootBin(TmpVBRec,aSrcDocPtr,aTargetDocPtr,SrcRootNode);
//				BuildRootBin(VB,aSrcDocPtr,aTargetDocPtr,SrcRootNode,TmpRec->ExtValueMap);
			cout<<"Result Header Size:"<<TmpVBRec->HeaderVB->GetStreamTotalLength()<<endl;
			cout<<"Result Item Cout:"<<TmpVBRec->ItemVBs.size()<<endl;

			//计算Section 容量 4093－9＝4084
			unsigned int MaxSectionLength=4080;
			if(TmpVBRec->ExtValueMapPtr->count(PSIXMLBIN_IS_SIZE_LIMITED_1024_STR))
			{
				MaxSectionLength=1021;
			}

			//采用尽力填充法填充Result

			//1 准备头数据
			PSIXMLBINSectionRecordPtr TmpSectionPtr=Result->GetNewSectionRecord();
			unsigned int TmpVBResHeaderSize=TmpVBRec->HeaderVB->GetStreamTotalLength();

			TmpSectionPtr->HeaderBufferLength=TmpVBResHeaderSize;
			if(TmpVBResHeaderSize>0)
			{
				TmpSectionPtr->HeaderBuffer.reset((unsigned char *)std::malloc(TmpVBResHeaderSize),&free);
				std::memcpy(TmpSectionPtr->HeaderBuffer.get(),TmpVBRec->HeaderVB->GetStream(),TmpVBResHeaderSize);
			}
			unsigned int SectionCopyedSize=TmpVBResHeaderSize;
			for(unsigned int i=0;i<TmpVBRec->ItemVBs.size();i++)
			{
				unsigned int TmpVBItemSize=TmpVBRec->ItemVBs[i]->GetStreamTotalLength();
				//注意这里有可能有BUG 因为可能TmpVBResHeaderSize直接就大于了MaxSectionLength
				if((SectionCopyedSize+TmpVBItemSize)>MaxSectionLength)
				{
					TmpSectionPtr=Result->GetNewSectionRecord();
					TmpSectionPtr->HeaderBufferLength=TmpVBResHeaderSize;
					if(TmpVBResHeaderSize>0)
					{
						TmpSectionPtr->HeaderBuffer.reset((unsigned char *)std::malloc(TmpVBResHeaderSize),&free);
						std::memcpy(TmpSectionPtr->HeaderBuffer.get(),TmpVBRec->HeaderVB->GetStream(),TmpVBResHeaderSize);
					}
					SectionCopyedSize=TmpVBResHeaderSize;
				}

				if(!TmpSectionPtr->ItemBuffer)
					TmpSectionPtr->ItemBuffer.reset((unsigned char *)std::malloc(TmpVBItemSize),&free);
				else
					TmpSectionPtr->ItemBuffer.reset((unsigned char *)std::realloc(TmpSectionPtr->ItemBuffer.get(),TmpSectionPtr->ItemBufferLength+TmpVBItemSize),&free);


				unsigned char * TmpPtr=TmpSectionPtr->ItemBuffer.get();
				TmpPtr+=TmpSectionPtr->ItemBufferLength;
				TmpSectionPtr->ExtValueMapPtr=TmpVBRec->ExtValueMapPtr;
				std::memcpy(TmpPtr,TmpVBRec->ItemVBs[i]->GetStream(),TmpVBItemSize);
				SectionCopyedSize+=TmpVBItemSize;
				if(TmpVBRec->ExtTableExtIDMap.count(i)>0)
				{
					TmpSectionPtr->SectionTableExtID=TmpVBRec->ExtTableExtIDMap[i];
				}
				TmpSectionPtr->ItemBufferLength+=TmpVBItemSize;

			}



			return Result;
		}

		PSIXMLBINRecordPtr PSIXMLBINProcessor::ProcessXML(string aTargetXMLText,bool IsTextLoad)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				PSIXMLBINRecordPtr TmpBuff;
				return TmpBuff;
			}

			boost::shared_ptr<rapidxml::xml_document<> > TargetDocPtr(new rapidxml::xml_document<>());

			string TmpTargetXML=aTargetXMLText;
			boost::shared_ptr<char> TargetContent((char *)std::malloc(TmpTargetXML.size()+1),&free);
			memset(TargetContent.get(),0,TmpTargetXML.size()+1);
			memcpy(TargetContent.get(), TmpTargetXML.c_str(),TmpTargetXML.size());

			try
			{
				TargetDocPtr->parse<0> (TargetContent.get());
			}
			catch(rapidxml::parse_error &e)
			{
				cout<<"Target XML Error:"<<e.what()<<endl;
				cout<<e.where<char>()<<endl;
				PSIXMLBINRecordPtr TmpBuff;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuff;
			}

			PSIXMLBINRecordPtr TmpResult;
			try
			{
				TmpResult=BuildBin(FSrcXmlDocument,TargetDocPtr);
			}
			catch(...)
			{
				FError+="\r\n Build Bin Error!";
			}
			return TmpResult;
		}


		PSIXMLBINRecordPtr PSIXMLBINProcessor::ProcessXML(string aTargetXMLName)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				PSIXMLBINRecordPtr TmpBuff;
				return TmpBuff;
			}

			boost::shared_ptr<rapidxml::xml_document<> > TargetDocPtr(new rapidxml::xml_document<>());

			string TmpTargetXML=LoadXMLFile(aTargetXMLName);
			boost::shared_ptr<char> TargetContent((char *)std::malloc(TmpTargetXML.size()+1),&free);
			memset(TargetContent.get(),0,TmpTargetXML.size()+1);
			memcpy(TargetContent.get(), TmpTargetXML.c_str(),TmpTargetXML.size());

			try
			{
				TargetDocPtr->parse<0> (TargetContent.get());
			}
			catch(rapidxml::parse_error &e)
			{
				cout<<"Target XML Error:"<<e.what()<<endl;
				cout<<e.where<char>()<<endl;
				PSIXMLBINRecordPtr TmpBuff;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuff;
			}

			PSIXMLBINRecordPtr TmpResult;
			try
			{
				TmpResult=BuildBin(FSrcXmlDocument,TargetDocPtr);
			}
			catch(...)
			{
				FError+="\r\n Build Bin Error!";
			}
			return TmpResult;
		}




		PSIXMLBINRecordPtrList PSIXMLBINProcessor::ProcessMultiRootXML(string aTargetXMLText,bool IsTextLoad)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				PSIXMLBINRecordPtrList TmpBuffList;
				return TmpBuffList;
			}

			boost::shared_ptr<rapidxml::xml_document<> > TargetDocPtr(new rapidxml::xml_document<>());

			string TmpTargetXML=aTargetXMLText;
			boost::shared_ptr<char> TargetContent((char *)std::malloc(TmpTargetXML.size()+1),&free);
			memset(TargetContent.get(),0,TmpTargetXML.size()+1);
			memcpy(TargetContent.get(), TmpTargetXML.c_str(),TmpTargetXML.size());

			try
			{
				TargetDocPtr->parse<0> (TargetContent.get());
			}
			catch(rapidxml::parse_error &e)
			{
				cout<<"Target XML Error:"<<e.what()<<endl;
				cout<<e.where<char>()<<endl;
				PSIXMLBINRecordPtrList TmpBuffList;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuffList;
			}

			PSIXMLBINRecordPtrList TmpResult;
			try
			{
				TmpResult=BuildBinList(FSrcXmlDocument,TargetDocPtr);
			}
			catch(...)
			{
				FError+="\r\n Build Bin Error!";
			}
			return TmpResult;
		}


		PSIXMLBINRecordPtrList PSIXMLBINProcessor::ProcessMultiRootXML(string aTargetXMLName)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				PSIXMLBINRecordPtrList TmpBuffList;
				return TmpBuffList;
			}

			boost::shared_ptr<rapidxml::xml_document<> > TargetDocPtr(new rapidxml::xml_document<>());

			string TmpTargetXML=LoadXMLFile(aTargetXMLName);
			boost::shared_ptr<char> TargetContent((char *)std::malloc(TmpTargetXML.size()+1),&free);
			memset(TargetContent.get(),0,TmpTargetXML.size()+1);
			memcpy(TargetContent.get(), TmpTargetXML.c_str(),TmpTargetXML.size());

			try
			{
				TargetDocPtr->parse<0> (TargetContent.get());
			}
			catch(rapidxml::parse_error &e)
			{
				cout<<"Target XML Error:"<<e.what()<<endl;
				cout<<e.where<char>()<<endl;
				PSIXMLBINRecordPtrList TmpBuffList;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuffList;
			}

			PSIXMLBINRecordPtrList TmpResult;
			try
			{
				TmpResult=BuildBinList(FSrcXmlDocument,TargetDocPtr);
			}
			catch(...)
			{
				FError+="\r\n Build Bin Error!";
			}
			return TmpResult;
		}
	}



