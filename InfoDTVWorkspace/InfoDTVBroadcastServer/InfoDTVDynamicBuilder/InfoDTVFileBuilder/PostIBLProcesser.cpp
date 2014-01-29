/*
 * PostIBLProcesser.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include "../../RapidXML/rapidxml.hpp"
#include "../../Common/CodeConverter.h"
#include "PostIBLProcesser.h"

#include "Poco/StringTokenizer.h"
#include "InfoDTVTSBuilderManager.h"

using namespace InfoDTV::DynamicBuilder::FileBuilder;


InfoDTVObjectPtr PostIBLProcesser::GetTargetObjectByName(string aFileName)
{
	InfoDTVObjectPtr  EmptyResult;
	if(FFileIDIndexer.count(aFileName)!=0)
	{
		//							map<string,unsigned short>::iterator   it=FFileIDIndexer.find(aFileName);
		unsigned short ObjectID=FFileIDIndexer[aFileName];
		return FObjectList[ObjectID];
	}
	else
		return EmptyResult;
}
inline string PostIBLProcesser::toUpper(string s)
{
	string upper(s);
	std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int)) std::toupper);
	//cout<<upper<<std::endl;
	return upper;
}
string& PostIBLProcesser::replace_all(string& str, const string& old_value, const string& new_value)
{
	while (true)
	{
		string::size_type pos(0);
		if ((pos = str.find(old_value)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else
			break;
	}
	return str;
}
string PostIBLProcesser::EncodeValue(string EncodeChar,const string aValue)
{
	vector< string > TmpXMLs;
	boost::split( TmpXMLs, aValue, boost::is_any_of(EncodeChar) );
	if(TmpXMLs.size()==1)
		return aValue;
	for(unsigned int i=0;i<TmpXMLs.size()-1;i++)
	{

		TmpXMLs[i]+="^"+EncodeChar;
	}
	string Result;
	for(unsigned int i=0;i<TmpXMLs.size();i++)
	{
		Result+=TmpXMLs[i];
	}
	return Result;
}


string PostIBLProcesser::ProcessValue(string aValue)
{
	//TODO: PostProcessValue;
	if(aValue.empty())
		return "";
	string TmpXML;

	string TmpChar="^";
	TmpXML=EncodeValue(TmpChar,aValue);
	TmpChar="<";
	TmpXML=EncodeValue(TmpChar,TmpXML);
	TmpChar=">";
	TmpXML=EncodeValue(TmpChar,TmpXML);

	return TmpXML;
}


string PostIBLProcesser::RebuildXML(string aElementName,vector<string> &aKeyOrderList,map<string,string> &aAttributeMap,string aElementValue, bool IsNeedValue)
{
	string Result="<"+aElementName+" ";
	for(unsigned int i=0;i<aKeyOrderList.size();i++)
	{
		Result+=aKeyOrderList[i]+"=\""+aAttributeMap[aKeyOrderList[i]]+"\" ";
	}
	if(IsNeedValue)
	{
		Result+=">";
		Result+=aElementValue;
		Result+="</"+aElementName+">";
	}
	else
	{
		Result+="/>";
	}
	return Result;
}

string PostIBLProcesser::PostProcessXMLInstructionElement(string aTagName,string aTagValue,vector<string> &aKeyOrderList,map<string,string> &aAttributeMap)
{
	//					string TagName=toUpper(aTagName);
	//string Result;
	if(aTagName=="AV"||aTagName=="COPYRIGHT"||aTagName=="STBIDTEXT"||aTagName=="CARDIDTEXT")
	{
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="SCROLLTEXT"||aTagName=="TEXT")
	{
		string TmpValue=ProcessValue(aTagValue);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,TmpValue,true);
	}
	else if(aTagName=="KEYACTION")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="REGION")
	{
		PostGetImageLink("BKIMG",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="IMG")
	{
		PostGetImageLink("SRC",aAttributeMap);
		PostGetImageLink("FSRC",aAttributeMap);

		PostProcessAction("ACTION","ASRC",aAttributeMap);
		PostProcessAction("LACTION","LASRC",aAttributeMap);
		PostProcessAction("FACTION","FASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if (aTagName == "STBAD")
	{
		PostGetImageLink("SRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="TEXTLINK")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		PostProcessAction("LACTION","LASRC",aAttributeMap);
		PostProcessAction("FACTION","FASRC",aAttributeMap);
		string TmpValue=ProcessValue(aTagValue);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,TmpValue,true);
	}
	else if(aTagName=="FORCEACTION")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="CARDID")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,true);
	}
	else if (aTagName == "BOUQUETID")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,true);
	}
	else if(aTagName=="STBID")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,true);
	}
	else if(aTagName=="VCHANNEL")
	{
		string TmpValue=PostProcessGroupAction(aTagValue);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,TmpValue,true);
	}
	else if(aTagName=="SLOT")
	{
		string TmpValue=PostProcessGroupAction(aTagValue);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,TmpValue,true);
	}
	else if(aTagName=="CODEINPUT")
	{
		string TmpValue=PostProcessGroupAction(aTagValue);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,TmpValue,true);
	}
	else if(aTagName=="NUMINPUT")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="GROUPACTION")
	{
		string TmpValue=PostProcessGroupAction(aTagValue);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,TmpValue,true);
	}
	else if(aTagName=="LINKRESOURCEINFO")
	{
		PostProcessAction("TYPE","URL",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="SELECTFILE")
	{
		PostProcessAction("ACTION","ASRC",aAttributeMap);
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	else if(aTagName=="REM")
	{
		return "";
	}
	else
	{
		return RebuildXML(aTagName,aKeyOrderList,aAttributeMap,aTagValue,false);
	}
	//					else if(TagName=="LINKRESOURCEINFO")
	//					{
	//
	//					}
}



void PostIBLProcesser::PostGetImageLink(string aImgLinkName,map<string,string> &aAttributeMap)
{
	if(aAttributeMap.count(aImgLinkName)!=0)
	{
		string aImageName=aAttributeMap[aImgLinkName];
		aImageName=replace_all(aImageName,"\\","/");
		InfoDTVObjectPtr TargetObject=GetTargetObjectByName(aImageName);
		unsigned short TmpInt=0;
		if(TargetObject)
		{
			if(TargetObject->Object)
				TmpInt=TargetObject->Object->ObjectID;
			else
				Log("Internal Error:PostProcessXMLInstructionElement-PostGetImageLinkString ");
		}
		string HexStr=str(boost::format("%x")%TmpInt);
		aAttributeMap[aImgLinkName]=HexStr;
	}
}

string PostIBLProcesser::PostProcessGroupAction(string aValue)
{
	string Result;
	boost::char_separator<char> sep("#");
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	tokenizer tokens(aValue, sep);
	string TmpXML;
	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
	{
		TmpXML += "<ACONTENT " + *tok_iter + "/>";
	}
	rapidxml::xml_document<> TmpXmlDocument;
	//boost::shared_array<char> Content(new char[TmpXML.size() + 1]);
	boost::shared_ptr<char> Content((char*)std::malloc(TmpXML.size() + 1),&free);
	strcpy(Content.get(), TmpXML.c_str());
	TmpXmlDocument.parse<0> (Content.get());
	rapidxml::xml_node<> *node = TmpXmlDocument.first_node();
	map<string,string> AttributeMap;
	//vector<string> KeyOrderList;

	while (node)
	{
		for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr= attr->next_attribute())
		{
			string AttrName=attr->name();
			AttrName=toUpper(AttrName);
			string AttrValue= attr->value();
			//								KeyOrderList.push_back(AttrName);
			AttributeMap[AttrName]=AttrValue;
			if(AttrName!="ACTION"&&AttrName!="ASRC")
				Result+=AttrName+"=\""+AttrValue+"\" ";
		}
		PostProcessAction("ACTION","ASRC",AttributeMap);
		Result+="ACTION=\""+AttributeMap["ACTION"]+"\" ASRC=\""+AttributeMap["ASRC"]+"\"#";
		//KeyOrderList.clear();
		AttributeMap.clear();
		node = node->next_sibling();
	}
	AttributeMap.clear();
	return Result;
}
enum LinkType {LT_RLINK,LT_DLINK,LT_DLINKS,LT_VODLINK,LT_VODLINKS,LT_DVBLINK1,LT_DVBLINK2,LT_DVBLINK3};
string GenTSParams(const string aSetTSParams,const LinkType aType,const string aObjectIDStr)
{
	//aSetTSParams 频点:符号率:QAMType:TSID:NetworkID:ServiceID:PID:timeout 均直接写成16进制

	Poco::StringTokenizer ST(aSetTSParams,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	if(ST.count()!=8)
		return aObjectIDStr;
	switch(aType)
	{
		case LT_RLINK:
		{
			string Tmp=ST[4]+":"+ST[3]+":"+ST[5]+":"+ST[6]+":"+aObjectIDStr;
			return Tmp;
		}
		case LT_DLINK:
		case LT_VODLINK:
		{
			string Tmp=ST[0]+":"+ST[1]+":"+ST[2]+":"+ST[6]+":"+aObjectIDStr+":"+ST[7];
			return Tmp;
		}
		case LT_DLINKS:
		case LT_VODLINKS:
		{
			string Tmp=ST[0]+":"+ST[1]+":"+ST[2]+":"+ST[5]+":0:"+aObjectIDStr+":"+ST[7];
			return Tmp;
		}
		case LT_DVBLINK1:
		{
			string Tmp="DVB1:"+ST[4]+":"+ST[3]+":"+ST[5]+":"+ST[6]+":"+aObjectIDStr;
			return Tmp;
		}
		case LT_DVBLINK2:
		{
			string Tmp="DVB2:"+ST[0]+":"+ST[1]+":"+ST[2]+":"+ST[6]+":"+aObjectIDStr;
			return Tmp;
		}
		case LT_DVBLINK3:
		{
			string Tmp="DVB3:"+ST[0]+":"+ST[1]+":"+ST[2]+":"+ST[5]+aObjectIDStr;
			return Tmp;
		}
	}
	return aObjectIDStr;
}

void PostIBLProcesser::PostProcessAction(string aActionString,string aAsrcString,map<string,string>&aAttributeMap)
{
	//						Log(">>"+aActionString);
	//						Log(">>"+aAsrcString);
	if(aAttributeMap.count(aActionString)!=0&&aAttributeMap.count(aAsrcString)!=0)
	{
		string TmpA=aAttributeMap[aActionString];
		TmpA=toUpper(TmpA);
		aAttributeMap[aActionString]=TmpA;
		if(TmpA=="LINK")
		{
			InfoDTVObjectPtr TargetObject=GetTargetObjectByName(aAttributeMap[aAsrcString]);
			unsigned short TmpInt=0;
			if(TargetObject)
			{

				if(TargetObject->ScenarioInfo)
					TmpInt=TargetObject->ScenarioInfo->ScenarioID;
				else
					Log("Internal Error:PostProcessXMLInstructionElement-PostProcessAction ");
			}
			string HexStr=str(boost::format("%x")%TmpInt);
			aAttributeMap[aAsrcString]=HexStr;
		}
		else if(TmpA=="RLINK")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_RLINK,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find RLINK " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}

		}
		else if(TmpA=="DLINK")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_DLINK,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find DLINK " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
		else if(TmpA=="VODLINK")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_VODLINK,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find VODLINK " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
		else if(TmpA=="DLINKS")
		{
			aAttributeMap[aActionString]="DLINK";
			string RLinkStr=aAttributeMap[aAsrcString];
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_DLINKS,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find DLINKS " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
		else if(TmpA=="VODLINKS")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			aAttributeMap[aActionString]="VODLINK";
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_VODLINKS,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find VODLINKS " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
		else if(TmpA=="DVB")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			aAttributeMap[aActionString]="DVB";
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_DVBLINK1,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find DVBLINK1 " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
		else if(TmpA=="DVB1")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			aAttributeMap[aActionString]="DVB";
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_DVBLINK1,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find DVBLINK1 " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
		else if(TmpA=="DVB2")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			aAttributeMap[aActionString]="DVB";
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_DVBLINK2,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find DVBLINK2 " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
		else if(TmpA=="DVB3")
		{
			string RLinkStr=aAttributeMap[aAsrcString];
			aAttributeMap[aActionString]="DVB";
			Poco::StringTokenizer ST(RLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			if(ST.count()==2)
			{
				if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
				{
					aAttributeMap[aAsrcString]=GenTSParams(GlobalBuilderManager.GetParamsFromBuilder( ST[0]),
							LT_DVBLINK3,GlobalBuilderManager.GetTargetIDFromBuilder(ST[0],ST[1]));
					Log("Find DVBLINK3 " + ST[0] + " IBL Name: " + ST[1] + "Final Params="+aAttributeMap[aAsrcString]);
				}
			}
		}
	}
	//						else
	//						{
	//							Log("Internal Error--PostProcessAction no ASRCString or ActionString");
	//						}
}


void PostIBLProcesser::PostProcessIBL(InfoDTVObjectPtr aObject)
{
	if(aObject->IBLFileContent.size()==0)
		return;
	rapidxml::xml_document<> XmlDocument;
	boost::shared_ptr<char> Content((char *)std::malloc(aObject->IBLFileContent.size() + 1),&free);//new char[aObject->IBLFileContent.size() + 1]);
	strcpy(Content.get(), aObject->IBLFileContent.c_str());
	XmlDocument.parse<0> (Content.get());
	rapidxml::xml_node<> *node = XmlDocument.first_node();
	string Result="";
	map<string,string> AttributeMap;
	vector<string> KeyOrderList;
	while (node)
	{
		//								cout << "Name of  node is: " << node->name() << "\n";
		//								cout << "Node  has value " <<  << "\n";
		string TagName = node->name();
		TagName=toUpper(TagName);
		string TagValue=node->value();// can Empty()

		for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr= attr->next_attribute())
		{
			string AttrName=attr->name();
			AttrName=toUpper(AttrName);
			string AttrValue= attr->value();
			KeyOrderList.push_back(AttrName);
			AttributeMap[AttrName]=AttrValue;
			//Log(AttrName);
		}
		Result+=PostProcessXMLInstructionElement(TagName,TagValue,KeyOrderList,AttributeMap);
		KeyOrderList.clear();
		AttributeMap.clear();
		node = node->next_sibling();
	}

	int TmpSize=0;
	boost::shared_ptr<unsigned char> ResultBuf=FCodeConverter.convert(Result,&TmpSize);
	//						Log("Convert Size:"+boost::lexical_cast<string>(TmpSize));
	//
	//						Log("Orgin Size:"+boost::lexical_cast<string>(strlen(Result.c_str())));
	if(ResultBuf&&(TmpSize!=0))
		aObject->PutScenarioContent(ResultBuf,TmpSize);
	else
	{
		Log("Internal Error ---ResultBuf nil or size zero");
	}
}



PostIBLProcesser::PostIBLProcesser(vector<InfoDTVObjectPtr> &aObjectList, map<
		string, unsigned short> &aFileIDIndexer):FCodeConverter(),FLogger(),FObjectList(aObjectList),FFileIDIndexer(aFileIDIndexer)
		{
			FLogger.setName("InfoDTV文档后处理器");
		}

		void PostIBLProcesser::PostProcessAll()
		{
			map<string,unsigned short>::iterator   it=FFileIDIndexer.begin();
			for(;it!=FFileIDIndexer.end();++it)
			{

				unsigned short InfoDTVObjectID=it->second;
				if(InfoDTVObjectID<=254)
				{
					Log("后处理阶段－正在处理文件:"+FObjectList[InfoDTVObjectID]->FileName);
					PostProcessIBL(FObjectList[InfoDTVObjectID]);
					Log("后处理阶段－处理文件完成:"+FObjectList[InfoDTVObjectID]->FileName);
				}
			}
		}
