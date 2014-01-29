/*
 * InfoDTVFileProcesser.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include "InfoDTVFileProcesser.h"

#include "Poco/StringTokenizer.h"
#include "InfoDTVTSBuilderManager.h"

using namespace InfoDTV::DynamicBuilder::FileBuilder;
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
int InfoDTVFileProcesser::FindEmptyInfoDTVScenarioIndex()
{
	for (unsigned short i = 0; i < 255; i++)
	{
		if (!FObjectList[i]->IsBinding())
			return i;
	}
	return -1;
}

int InfoDTVFileProcesser::FindEmptyInfoDTVObjectIndex()
{
	//注意此处对象回收
	unsigned short TotalSize=FObjectList.size();
	if(TotalSize>=65020)
		return 65021;
	if(TotalSize>254)
	{
		for (unsigned short i = 255; i < TotalSize; i++)
		{
			if (!FObjectList[i]->IsBinding())
				return i;
		}
	}
	unsigned short Index=FObjectList.size();
	FObjectList.push_back(InfoDTVObjectPtr(new InfoDTVObject(FPID, Index, FCrc32Counter)));
	return Index;
}

void InfoDTVFileProcesser::CleanObjectList(unsigned int aPassCount)
{
	for(unsigned int i=0;i<FObjectList.size();i++)
	{
		if(FObjectList[i]->PassCount!=aPassCount)
		{
			//删除没有PASSCOUNT的对象在FFileIDIndexer中
			if(FFileIDIndexer.count(FObjectList[i]->FileName)!=0)
			{
				map<string,unsigned short>::iterator tt=FFileIDIndexer.find(FObjectList[i]->FileName);
				FFileIDIndexer.erase(tt);
			}

			//删除没有PASSCOUNT对象的FileName在FObjectList中


			if(i<=255)
			{
				if(i==0)
				{
					BuildDefaultIndexScenarioObject(FObjectList[i]);
				}
				else
				{
					if(FObjectList[i]->FileName!=boost::lexical_cast<string>(i))
						BuildDefaultScenarioObject(FObjectList[i],i);
				}
			}
			else
			{
				if(FObjectList[i]->FileName!=boost::lexical_cast<string>(i))
					BuildDefaultImageObject(FObjectList[i]);
			}
			FObjectList[i]->FileName=boost::lexical_cast<string>(i);

		}
	}
}

void InfoDTVFileProcesser::ProcessDeque()
{
	if (FProcessDeque.size() == 0)
		return;
	Log("全部队列有:\t"+boost::lexical_cast<string>(FProcessDeque.size()));
	unsigned int Count=0;
	do
	{

		string FileName = FProcessDeque[0];
		Log("正在处理:\t"+FileName);
		if(FTmpProcessedMap.count(FileName)==0)
		{
			ProcessIBL(FileName);
//			if(FObjectOverFlow)
//			{
//				FProcessDeque.pop_front();
//				Log("处理已经溢出:\t"+FileName);
//				break ;
//			}
		}
		Log("处理完成:\t"+FileName);
		FProcessDeque.pop_front();
		Log("队列剩余:\t"+boost::lexical_cast<string>(FProcessDeque.size()));
		Count=FProcessDeque.size();
	}
	while (Count > 0);
	//						std::cout<<"!!!!!!!!!!!"<<std::endl;
	CleanObjectList(FGlobalPassCount);
	FPostProcesser.PostProcessAll();

	FTmpProcessedMap.clear();
	FProcessDeque.clear();
	deque<string>(FProcessDeque).swap(FProcessDeque);
	FObjectOverFlow=false;
}




void InfoDTVFileProcesser::ProcessIBL(string aFileName)
{


	//TiXmlDocumentPtr  XmlDocument(new TiXmlDocument());

	rapidxml::xml_document<> XmlDocument;

	boost::filesystem::path TmpPath = FRootPath + aFileName;
	if (!boost::filesystem::exists(TmpPath))
	{
		Log("未找到文件：" + FRootPath + aFileName);
		return;
	}
	int ObjectIndex = -1;

	if (FFileIDIndexer.count(aFileName) == 0)
	{
		ObjectIndex = FindEmptyInfoDTVScenarioIndex();
		if(ObjectIndex==-1)
		{
			FObjectOverFlow=true;

		}
		else
		{
			FFileIDIndexer[aFileName] = ObjectIndex;
		}

	}
	else
	{
		ObjectIndex = FFileIDIndexer[aFileName];
	}

	if (ObjectIndex < 0 || ObjectIndex > (int) FObjectList.size())
	{
		LogError("场景对象数量超过255，溢出！");
		FTmpProcessedMap[aFileName]=1;
	}
	else
	{
		FObjectList[ObjectIndex]->SetBindingIBL(FRootPath, aFileName);
		//SetBinding 载入IBL文件
		FObjectList[ObjectIndex]->PassCount = FGlobalPassCount;
		ProcessInfoDTVIBLObject(FObjectList[ObjectIndex], XmlDocument);
		FTmpProcessedMap[aFileName]=1;
	}


	//						}
}


//					inline bool HasLinkID(const vector<unsigned short>& aLinkIDs,const unsigned short aID)
//					{
//
//					}

inline string InfoDTVFileProcesser::toUpper(string s)
{
	string upper(s);
	std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int)) std::toupper);
	//cout<<upper<<std::endl;
	return upper;
}

string& InfoDTVFileProcesser::replace_all(string& str, const string& old_value, const string& new_value)
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

void InfoDTVFileProcesser::AddImageLink(InfoDTVObjectPtr aObject, string aImageName)
{
	//就地增加图片
	int ImgIndex = -1;

	aImageName=replace_all(aImageName,"\\","/");

	boost::filesystem::path FilePath = FRootPath + aImageName;
	if (!boost::filesystem::exists(FilePath))
	{
		Log("未找到图片文件：" + FRootPath + aImageName);
		return;
	}

	if (FFileIDIndexer.count(aImageName) == 0)
	{
		ImgIndex = FindEmptyInfoDTVObjectIndex();
		if(ImgIndex>65020)
		{
			FObjectOverFlow=true;
			ImgIndex=-1;
		}
		else
		{
			FFileIDIndexer[aImageName] = ImgIndex;
		}
	}
	else
	{
		ImgIndex = FFileIDIndexer[aImageName];
	}

	if (ImgIndex > -1)
	{
		InfoDTVObjectPtr ImgObject = FObjectList[ImgIndex];
		ImgObject->SetBindingImage(FRootPath, aImageName, FObjectList);

		bool HasLinkID = false;
		for (unsigned int i = 0; i < ImgObject->LinkFromIDs.size(); i++)
		{
			if (ImgObject->LinkFromIDs[i] == aObject->ID)
			{
				HasLinkID = true;
				break;
			}
		}
		if (!HasLinkID)
			ImgObject->LinkFromIDs.push_back(aObject->ID);
		ImgObject->PassCount = FGlobalPassCount;

		bool IBLHasImageLinkID=false;
		for (unsigned int i = 0; i <aObject->ScenarioInfo->LinkedObjectIDs.size(); i++)
		{
			if (aObject->ScenarioInfo->LinkedObjectIDs[i] ==ImgObject->Object->ObjectID)
			{
				IBLHasImageLinkID = true;
				break;
			}
		}
		if(!IBLHasImageLinkID)
			aObject->ScenarioInfo->LinkedObjectIDs.push_back(ImgObject->Object->ObjectID);
	}
	else
	{
		Log("图片对象超出限制!");
	}
}

void InfoDTVFileProcesser::AddRemoteIBLLink(InfoDTVObjectPtr aObject, string aRLinkStr)
{

	Poco::StringTokenizer ST(aRLinkStr,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	if(ST.count()==2)
	{
		if(GlobalBuilderManager.GetParamsFromBuilder( ST[0])!="")
			Log("Find RemoteIBLLink" + ST[0] + " IBL Name: " + ST[1] + "!");
	}
}

void InfoDTVFileProcesser::AddIBLLink(InfoDTVObjectPtr aObject, string aIBLName)
{
	if (FFileIDIndexer.count(aIBLName) == 0)
	{
		//暂时没有想到这时可以干什么
	}
	FProcessDeque.push_back(aIBLName);
}

void InfoDTVFileProcesser::IBLProcessAction(InfoDTVObjectPtr aObject, rapidxml::xml_node<> *node, string AName,
		string ASrcName)
{

	rapidxml::xml_attribute<> *attr = node->first_attribute(AName.c_str(), AName.size(), false);

	if (attr)
	{
		string ActionName = attr->value();
		ActionName = toUpper(ActionName);
		if (ActionName == "LINK")
		{
			attr = node->first_attribute(ASrcName.c_str(), ASrcName.size(), false);
			if (attr)
			{
				string IBLName = attr->value();
				AddIBLLink(aObject, IBLName);
			}
			else
			{
				Log("IBL ERROR! has " + AName + " no " + ASrcName + "!");
			}
		}
		else if (ActionName == "RLINK")
		{
			attr = node->first_attribute(ASrcName.c_str(), ASrcName.size(), false);
			if (attr)
			{
				string RLinkString = attr->value();
				AddRemoteIBLLink(aObject, RLinkString);
			}
		}
		else if (ActionName == "DLINK")
		{
			attr = node->first_attribute(ASrcName.c_str(), ASrcName.size(), false);
			if (attr)
			{
				string RLinkString = attr->value();
				AddRemoteIBLLink(aObject, RLinkString);
			}
		}
		else if (ActionName == "VODLINK")
		{
			attr = node->first_attribute(ASrcName.c_str(), ASrcName.size(), false);
			if (attr)
			{
				string RLinkString = attr->value();
				AddRemoteIBLLink(aObject, RLinkString);
			}
		}
	}
}



void InfoDTVFileProcesser::IBLProcessLinkResourceInfo(InfoDTVObjectPtr aObject, rapidxml::xml_node<> *node)
{

	rapidxml::xml_attribute<> *attr = node->first_attribute("TYPE", 4, false);

	if (attr)
	{
		string ActionName = attr->value();
		ActionName = toUpper(ActionName);
		if (ActionName == "DVB")
		{
			attr = node->first_attribute("URL", 3, false);
			if (attr)
			{

				string IBLName = attr->value();
				Poco::StringTokenizer ST(IBLName,":",Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
				if(ST.count()==1)
					AddIBLLink(aObject, IBLName);
				else
					AddRemoteIBLLink(aObject, IBLName);
			}
			else
			{
				Log("IBL ERROR! LinkResourceInfo no URL !");
			}
		}
	}
}

void InfoDTVFileProcesser::IBLProcessGroupAction(InfoDTVObjectPtr aObject, string aGAValue)
{
	boost::char_separator<char> sep("#");

	tokenizer tokens(aGAValue, sep);
	string TmpXML;
	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
	{
		TmpXML += "<ACONTENT " + *tok_iter + "/>";
	}
	rapidxml::xml_document<> TmpXmlDocument;
	//boost::shared_array<char> Content(new char[TmpXML.size() + 1]);
	boost::shared_ptr<char> Content((char*)std::malloc(TmpXML.size() + 1),&free);
	strcpy(Content.get(), TmpXML.c_str());
	//aXmlDocument->Parse(aObject->IBLFileContent.c_str());
	TmpXmlDocument.parse<0> (Content.get());
	rapidxml::xml_node<> *node = TmpXmlDocument.first_node();
	while (node)
	{
		IBLProcessAction(aObject, node, "action", "asrc");
		node = node->next_sibling();
	}
}




void InfoDTVFileProcesser::IBLProcessImageLink(InfoDTVObjectPtr aObject, rapidxml::xml_node<> *node, int ImgType)
//ImgType 0 : img ; 1 : region
{

	if (ImgType == 0)
	{

		rapidxml::xml_attribute<> *attr = node->first_attribute("src", 3, false);

		if (attr)
		{
			string ImageName = attr->value();
			AddImageLink(aObject, ImageName);
		}
		attr = node->first_attribute("fsrc", 4, false);
		if (attr)
		{
			string ImageName = attr->value();
			AddImageLink(aObject, ImageName);
		}
	}
	else
	{

		rapidxml::xml_attribute<> *attr = node->first_attribute("bkimg", 5, false);

		if (attr)
		{
			string ImageName = attr->value();
			AddImageLink(aObject, ImageName);
		}
	}

}

void InfoDTVFileProcesser::ProcessInfoDTVIBLObject(InfoDTVObjectPtr aObject, rapidxml::xml_document<> &aXmlDocument)
{

	aXmlDocument.clear();

	//						boost::shared_array<char> Content(new char[aObject->IBLFileContent.size() + 1]);
	boost::shared_ptr<char> Content((char *)std::malloc(aObject->IBLFileContent.size() + 1),&free);//new char[aObject->IBLFileContent.size() + 1]);
	strcpy(Content.get(), aObject->IBLFileContent.c_str());
	//aXmlDocument->Parse(aObject->IBLFileContent.c_str());
	aXmlDocument.parse<0> (Content.get());

	rapidxml::xml_node<> *node = aXmlDocument.first_node();

	while (node)
	{
		//								cout << "Name of  node is: " << node->name() << "\n";
		//								cout << "Node  has value " << node->value() << "\n";
		string TagName = node->name();

		TagName = toUpper(TagName);
		if (TagName == "IMG")
		{
			IBLProcessImageLink(aObject, node, 0);
			IBLProcessAction(aObject, node, "laction", "lasrc");
			IBLProcessAction(aObject, node, "faction", "fasrc");
			IBLProcessAction(aObject, node, "action", "asrc");
			//								attr = node->first_attribute("laction", 7, false);
			//								attr = node->first_attribute("lasrc", 5, false);
			//								attr = node->first_attribute("faction", 7, false);
			//								attr = node->first_attribute("fasrc", 5, false);
			//								for (xml_attribute<> *attr = node->first_attribute(); attr; attr
			//								        = attr->next_attribute())
			//								{
			//								    cout << "Node has attribute " << attr->name() << " ";
			//								    cout << "with value " << attr->value() << "\n";
			//								}

		}
		else if (TagName == "STBAD")
		{
			IBLProcessImageLink(aObject, node, 0);
		}
		else if (TagName == "TEXTLINK")
		{
			IBLProcessAction(aObject, node, "laction", "lasrc");
			IBLProcessAction(aObject, node, "faction", "fasrc");
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		else if (TagName == "REGION")
		{
			IBLProcessImageLink(aObject, node, 1);
		}
		else if (TagName == "GROUPACTION")
		{
			//xml_attribute<> *attr = node->first_attribute("bkimg", 6, false);
			string Value = node->value();
			IBLProcessGroupAction(aObject, Value);
		}
		else if(TagName=="KEYACTION")
		{
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		else if (TagName == "FORCEACTION")
		{
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		else if (TagName == "CARDID")
		{
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		else if (TagName == "BOUQUETID")
		{
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		else if (TagName == "STBID")
		{
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		else if (TagName == "NUMINPUT")
		{
			//								string Value = node->value();
			//								IBLProcessGroupAction(aObject, Value);
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		else if (TagName == "VCHANNEL")
		{
			string Value = node->value();
			IBLProcessGroupAction(aObject, Value);
		}
		else if (TagName == "CODEINPUT")
		{
			IBLProcessAction(aObject, node, "laction", "lasrc");
			IBLProcessAction(aObject, node, "faction", "fasrc");
			string Value = node->value();
			IBLProcessGroupAction(aObject, Value);
		}
		else if (TagName == "SLOT")
		{
			string Value = node->value();
			IBLProcessGroupAction(aObject, Value);
		}
		else if (TagName == "LINKRESOURCEINFO")
		{
			IBLProcessLinkResourceInfo(aObject,node);
			//								string Value = node->value();
			//								IBLProcessGroupAction(Value);
		}
		else if(TagName=="SELECTFILE")
		{
			IBLProcessAction(aObject, node, "action", "asrc");
		}
		node = node->next_sibling();
	}

}
void InfoDTVFileProcesser::ReInitObjectList()
{
	FObjectList.clear();
	vector<InfoDTVObjectPtr>(FObjectList).swap(FObjectList);
	FProcessDeque.clear();
	deque<string>(FProcessDeque).swap(FProcessDeque);
	FTmpProcessedMap.clear();
	map<string,int>(FTmpProcessedMap).swap(FTmpProcessedMap);
	FFileIDIndexer.clear();
	map<string, unsigned short>(FFileIDIndexer).swap(FFileIDIndexer);
	Init();
}



InfoDTVFileProcesser::InfoDTVFileProcesser(unsigned short aPID,  vector<InfoDTVObjectPtr> &aObjectList, map<
		string, unsigned short> &aFileIDIndexer, deque<string> &aProcessDeque,
		TSLibrary::DVB::IPSICrc32CounterPtr aCrc32Counter) :FLogger(),FPID(aPID),
		FObjectList(aObjectList), FFileIDIndexer(aFileIDIndexer),
		FProcessDeque(aProcessDeque),FTmpProcessedMap(), FCrc32Counter(aCrc32Counter),
		FRootPath(""),FGlobalPassCount(0),FPostProcesser(FObjectList,FFileIDIndexer),FObjectOverFlow(false)
		{
			FLogger.setName("InfoDTV文档处理器 PID-"+boost::lexical_cast<string>(aPID));
		}

		void InfoDTVFileProcesser::BuildDefaultScenarioObject(InfoDTVObjectPtr aInfoDTVObject, unsigned short aIndex)
		{
			//TODO:Check BuildDefaultScenarioObject
			//初始化 页面为"<>"，将LinkToIDs,LinkFromIDs 清空 各种大小调整,更新FileName
			aInfoDTVObject->BuildDefaultScenarioObject(aIndex);
		}

		void InfoDTVFileProcesser::BuildDefaultIndexScenarioObject(InfoDTVObjectPtr aInfoDTVObject)
		{
			//TODO:BuildDefaultIndexScenarioObject
			//初始化 页面为"InfoDTV 正在启动...请稍后"，将LinkToIDs,LinkFromIDs 清空 尺寸调整,更新FileName
			aInfoDTVObject->BuildDefaultIndexScenarioObject();
		}

		void InfoDTVFileProcesser::BuildDefaultImageObject(InfoDTVObjectPtr aInfoDTVObject)
		{
			//TODO:BuildDefaultImageObject
			//将图片内容更新为58字节的BMP，将LinkToIDs,LinkFromIDs 清空 各种大小调整,更新FileName
			aInfoDTVObject->BuildDefaultImageObject();
		}

		void InfoDTVFileProcesser::Init()
		{
			FObjectOverFlow=false;
			//建立对象255个
			for (int i = 0; i < 255; i++)
			{
				//							FFileNameList.push_back(boost::lexical_cast<string>(i));
				FObjectList.push_back(
						// InfoDTVObjectPtr(new InfoDTVObject(i, boost::lexical_cast<string>(i))));
						InfoDTVObjectPtr(new InfoDTVObject(FPID,i,FCrc32Counter)));

				if (i == 0)
				{
					BuildDefaultIndexScenarioObject(FObjectList[i]);
				}
				else
				{
					BuildDefaultScenarioObject(FObjectList[i], i);
				}
				//FPProcesser.BuildDefaultScenarioObject(FObjectList[i], boost::lexical_cast<string>(i));
			}

			//设置默认Index
			//						FFileNameList[0] = "Index.IBL";
			//默认Index
			FFileIDIndexer["Index.IBL"] = 0;
			Log("内部初始化完成");
		}


		void InfoDTVFileProcesser::Start(int aGlobalPassCount, string aRootPath)
		{
//			FPID = aPID;
			boost::filesystem::path RPath = aRootPath;

			if (!boost::filesystem::exists(RPath))
			{
				Log("给出的路径并不存在：" + aRootPath);
				return;
			}
			RPath = aRootPath + "Index.IBL";
			if (!boost::filesystem::exists(RPath))
			{
				Log("Index.IBL并不存在：" + aRootPath);
				return;
			}
			FRootPath = aRootPath;
			FGlobalPassCount= aGlobalPassCount;

			FProcessDeque.push_back("Index.IBL");

			ProcessDeque();
//			if(FObjectOverFlow)
//			{
//				ReInitObjectList();
//				Start(aGlobalPassCount, aRootPath);
//			}
		}

