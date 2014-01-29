/*
 * XMLBINProcessor.cpp
 *
 *  Created on: 2009-2-1
 *      Author: victor
 */
#include "XMLBINProcessor.h"
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

	namespace XMLBIN
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

		XMLBINProcessor::XMLBINProcessor(string aSrcXMLContent,bool aIsTextLoad):FTemplateFileName(""),FError(""),FSrcXMLDocumnetText(aSrcXMLContent),FSrcXmlDocument()
		{

		}

		XMLBINProcessor::XMLBINProcessor(string aSrcXMLName):FTemplateFileName(aSrcXMLName),FError(""),FSrcXMLDocumnetText(""),FSrcXmlDocument()
		{

		}
		XMLBINProcessor::~XMLBINProcessor()
		{

		}
		string XMLBINProcessor::GetError() const
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

		void XMLBINProcessor::LoadXML()
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

		string XMLBINProcessor::BuildSample()
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

		void SmartWriteIntToBitStream(const unsigned int aValue, const unsigned int aBits,VBitStream &aVB)
		{
			switch(aBits)
			{
				case 8:
				{
					aVB.WriteByte(aValue);
					break;
				}
				case 16:
				{
					aVB.WriteInt16(aValue);
					break;
				}
				case 32:
				{
					aVB.WriteInt32(aValue);
					break;
				}
				default:
				{
					aVB.WriteBits(aValue, aBits);
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

		void SetExtValueMap(map<string,string> * aExtValueMapPtr,const string aKeyValue,const string aValue)
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
		unsigned int ProductTargetBitStream(const rapidxml::xml_node<> *aSrcRootNode,const rapidxml::xml_node<> * aTargetRootNodePtr,VBitStream &aVB,const bool aIsExtMode,map<string,string> * aExtValueMapPtr)
			{
				cout<<"ProductTargetBitStream"<<endl;
				const rapidxml::xml_node<> *TargetRootNodePtr=aTargetRootNodePtr;
				bool FIsExtMode=aIsExtMode;
				unsigned int WriteBitsCount=0;
				rapidxml::xml_node<> *TmpSrcNode=aSrcRootNode->first_node();

				while(TmpSrcNode)
				{
					string SrcTagName = TmpSrcNode->name();
					SrcTagName = toUpper(SrcTagName);

					string TmpTargetNodeName = GetXMLDocAttrValue(TmpSrcNode,"NAME");
					cout<<SrcTagName<<"->"<<TmpTargetNodeName<<"->"<<TargetRootNodePtr->name()<<endl;

					if (SrcTagName == "CONTENT")
					{
						unsigned int Bits=GetSrcNodeBitSize(TmpSrcNode,"BITS");
						string TmpSrcDefineValueStr=GetXMLDocAttrValue(TmpSrcNode,"VALUE");
						if(TmpSrcDefineValueStr!="")
						{
							unsigned int TmpSrcDefineValue=boost::lexical_cast<unsigned int>(TmpSrcDefineValueStr);
							if(!FIsExtMode)
							{
								SmartWriteIntToBitStream(TmpSrcDefineValue,Bits,aVB);
								WriteBitsCount+=Bits;
							}
							else
							{
								SetExtValueMap(aExtValueMapPtr,TmpTargetNodeName,TmpSrcDefineValueStr);
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

								if(!FIsExtMode)
								{
									SmartWriteIntToBitStream(TmpTargetIntValue,Bits,aVB);
									WriteBitsCount+=Bits;
								}
								else
								{
									SetExtValueMap(aExtValueMapPtr,TmpTargetNodeName,boost::lexical_cast<string>(TmpTargetIntValue));
								}
							}
						}

					}
					else if (SrcTagName == "STRCONTENT")
					{

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

						if(!aIsExtMode)
						{
							//TODO:UNICODE!!!CONVERT
							unsigned int strSize=TargetStrValue.size();
							if(IsIncludeSize)
							{
								aVB.WriteBits(strSize,sizeBits);
								WriteBitsCount+=sizeBits;
							}
							aVB.WriteData((unsigned char *)TargetStrValue.c_str(),strSize);
							WriteBitsCount+=strSize*8;
						}
						else
						{
							SetExtValueMap(aExtValueMapPtr,TmpTargetNodeName,TargetStrValue);
						}
					}
					else if (SrcTagName == "PART")
					{
						string TmpTargetValueTypeStr=toUpper(GetXMLDocAttrValue(TmpSrcNode,"TYPE"));

						if(TmpTargetValueTypeStr!="EXT")
						{
							bool IsIncludeSize=GetSrcNodeIsIncludeSizeField(TmpSrcNode);
							if(IsIncludeSize)
							{
								unsigned int sizeBits=GetSrcNodeBitSize(TmpSrcNode,"SIZEFIELDBITS");

								VBitStream TmpVB;
								rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
								if(TargetNode)
									ProductTargetBitStream(TmpSrcNode,TargetNode,TmpVB,false,aExtValueMapPtr);
								unsigned int TmpSize=TmpVB.GetStreamTotalLength();
								aVB.WriteBits(TmpSize,sizeBits);
								aVB.AppendStream(TmpVB);
								WriteBitsCount+=sizeBits+TmpSize*8;
							}
							else
							{
								rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
								ProductTargetBitStream(TmpSrcNode,TargetNode,aVB,false,aExtValueMapPtr);
							}
						}
						else
						{
							rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
							ProductTargetBitStream(TmpSrcNode,TargetNode,aVB,true,aExtValueMapPtr);
						}

					}
					else if (SrcTagName == "REPEATPART")
					{
						if(!FIsExtMode)
						{
							string TmpTargetRepeatItemNodeName = GetXMLDocAttrValue(TmpSrcNode,"ITEMNAME");
							bool IsIncludeSize=GetSrcNodeIsIncludeSizeField(TmpSrcNode);
							if(IsIncludeSize)
							{
								unsigned int sizeBits=GetSrcNodeBitSize(TmpSrcNode,"SIZEFIELDBITS");

								VBitStream TmpVB;
								rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
								if(TargetNode)
									TargetNode =TargetNode->first_node(TmpTargetRepeatItemNodeName.c_str(),TmpTargetRepeatItemNodeName.size(),false);
								while(TargetNode)
								{

									ProductTargetBitStream(TmpSrcNode,TargetNode,TmpVB,FIsExtMode,aExtValueMapPtr);
									TargetNode=TargetNode->next_sibling();
								}
								unsigned int TmpSize=TmpVB.GetStreamTotalLength();
								aVB.WriteBits(TmpSize,sizeBits);
								aVB.AppendStream(TmpVB);
								WriteBitsCount+=sizeBits+TmpSize*8;
							}
							else
							{
								rapidxml::xml_node<> *TargetNode =TargetRootNodePtr->first_node(TmpTargetNodeName.c_str(),TmpTargetNodeName.size(),false);
								if(TargetNode)
									TargetNode =TargetNode->first_node(TmpTargetRepeatItemNodeName.c_str(),TmpTargetRepeatItemNodeName.size(),false);
								while(TargetNode)
								{
									ProductTargetBitStream(TmpSrcNode,TargetNode,aVB,FIsExtMode,aExtValueMapPtr);
									TargetNode=TargetNode->next_sibling();
								}
							}

						}
					}
					else if (SrcTagName == "OPTIONPART")
					{
						if(!FIsExtMode)
						{
							bool IsIncludeSize=GetSrcNodeIsIncludeSizeField(TmpSrcNode);
							if(IsIncludeSize)
							{
								unsigned int sizeBits=GetSrcNodeBitSize(TmpSrcNode,"SIZEFIELDBITS");

								VBitStream TmpVB;

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
											ProductTargetBitStream(TmpSrcOptionItemPtr,TargetOptionItemNodePtr,TmpVB,FIsExtMode,aExtValueMapPtr);
										}
										TargetOptionItemNodePtr=TargetOptionItemNodePtr->next_sibling();
									}

								}
								unsigned int TmpSize=TmpVB.GetStreamTotalLength();
								if(TmpSize>0)
								{
									aVB.WriteBits(TmpSize,sizeBits);
									aVB.AppendStream(TmpVB);
									WriteBitsCount+=sizeBits+TmpSize*8;
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
											ProductTargetBitStream(TmpSrcOptionItemPtr,TargetOptionItemNodePtr,aVB,FIsExtMode,aExtValueMapPtr);
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

		void BuildRootBin(VBitStream &aVB,const boost::shared_ptr<rapidxml::xml_document<> > aSrcDocPtr,const boost::shared_ptr<rapidxml::xml_document<> > aTargetDocPtr,rapidxml::xml_node<> *aSrcRootNode ,map<string,string> &aExtValueMap)
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
			ProductTargetBitStream(aSrcRootNode,TargetRootNode,aVB,false,&aExtValueMap);
		}


		XMLBINRecordPtrList BuildBinList(const boost::shared_ptr<rapidxml::xml_document<> > aSrcDocPtr,const boost::shared_ptr<rapidxml::xml_document<> > aTargetDocPtr)
		{

			XMLBINRecordPtrList TmpRecList;

			rapidxml::xml_node<> *SrcRootNode=aSrcDocPtr->first_node("ROOT",4,false);

			while (SrcRootNode)
			{
				VBitStream VB;
				XMLBINRecordPtr TmpRec(new XMLBINRecord);
				BuildRootBin(VB,aSrcDocPtr,aTargetDocPtr,SrcRootNode,TmpRec->ExtValueMap);
				SrcRootNode=SrcRootNode->next_sibling("ROOT",4,false);
				cout<<"VBitStream Size:"<<VB.GetStreamTotalLength()<<endl;
				TmpRec->Buffer.reset((unsigned char *)std::malloc(VB.GetStreamTotalLength()),&free);
				TmpRec->BufferLength=VB.GetStreamTotalLength();
				memcpy(TmpRec->Buffer.get(),VB.GetStream(),TmpRec->BufferLength);
				TmpRecList.push_back(TmpRec);
			}
			return TmpRecList;
		}



		XMLBINRecordPtr BuildBin(const boost::shared_ptr<rapidxml::xml_document<> > aSrcDocPtr,const boost::shared_ptr<rapidxml::xml_document<> > aTargetDocPtr)
		{
			VBitStream VB;
			XMLBINRecordPtr TmpRec(new XMLBINRecord);
			rapidxml::xml_node<> *SrcRootNode=aSrcDocPtr->first_node("ROOT",4,false);
			if(SrcRootNode)
				BuildRootBin(VB,aSrcDocPtr,aTargetDocPtr,SrcRootNode,TmpRec->ExtValueMap);
			cout<<"VBitStream Size:"<<VB.GetStreamTotalLength()<<endl;
			TmpRec->Buffer.reset((unsigned char *)std::malloc(VB.GetStreamTotalLength()),&free);
			TmpRec->BufferLength=VB.GetStreamTotalLength();
			memcpy(TmpRec->Buffer.get(),VB.GetStream(),TmpRec->BufferLength);
			return TmpRec;
		}

		XMLBINRecordPtr XMLBINProcessor::ProcessXML(string aTargetXMLText,bool IsTextLoad)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				XMLBINRecordPtr TmpBuff;
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
				XMLBINRecordPtr TmpBuff;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuff;
			}

			XMLBINRecordPtr TmpResult;
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


		XMLBINRecordPtr XMLBINProcessor::ProcessXML(string aTargetXMLName)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				XMLBINRecordPtr TmpBuff;
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
				XMLBINRecordPtr TmpBuff;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuff;
			}

			XMLBINRecordPtr TmpResult;
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




		XMLBINRecordPtrList XMLBINProcessor::ProcessMultiRootXML(string aTargetXMLText,bool IsTextLoad)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				XMLBINRecordPtrList TmpBuffList;
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
				XMLBINRecordPtrList TmpBuffList;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuffList;
			}

			XMLBINRecordPtrList TmpResult;
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


		XMLBINRecordPtrList XMLBINProcessor::ProcessMultiRootXML(string aTargetXMLName)
		{

			if(!FSrcXmlDocument)
			{
				LoadXML();
			}

			if(!FSrcXmlDocument)
			{

				XMLBINRecordPtrList TmpBuffList;
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
				XMLBINRecordPtrList TmpBuffList;
				string IError=e.what();
				FError+="\r\n Parse XML Error:"+IError;
				IError=e.where<char>();
				FError+="\r\n Where:"+IError;
				return TmpBuffList;
			}

			XMLBINRecordPtrList TmpResult;
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



