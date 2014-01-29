/*
 * InfoDTVObject.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "InfoDTVObject.h"

using namespace InfoDTV::DynamicBuilder::FileBuilder;
void InfoDTVObject::LoadIBLFile(string aFileNameStr)
{
	ifstream in(aFileNameStr.c_str());
	ostringstream os;
	os << in.rdbuf();
	IBLFileContent = os.str();
}

void InfoDTVObject::LoadImageFile(string aFileName, unsigned char aObjectType)
{
	//TODO:LoadImageFile
	//						Log("LoadImageFile-1 :"+aFileName);
	std::ifstream IMGFileStream;
	string FileName=aFileName;
	IMGFileStream.open(aFileName.c_str(), ios::in | ios::binary);
	IMGFileStream.seekg(0, ios::end);
	int IMGFileSize = IMGFileStream.tellg();
	IMGFileStream.seekg(0, ios::beg);
	//						Log("FIleSize:"+boost::lexical_cast<string>(IMGFileSize));
	RawBufferPtr IMGBuffer((unsigned char *) std::malloc(IMGFileSize),&free);

	IMGFileStream.read((char *) IMGBuffer.get(), IMGFileSize);

	if (aObjectType == 0x23)
	{
		unsigned char * TmpPtr = IMGBuffer.get();
		if (TmpPtr[4] == 9)
			aObjectType = 0x27;
	}
	//						Log("LoadImageFile-2");

	Object->SetObjectContent(aObjectType, IMGBuffer, IMGFileSize);
	//						Log("LoadImageFile-3");
}

void InfoDTVObject::UpdateImageFileLinkFrom(vector<InfoDTVObjectPtr>& aObjectList)
{
	for (unsigned int i = 0; i < LinkFromIDs.size(); i++)
	{
		if (LinkFromIDs[i] > 254)
		{
			Log("Internal Error---ImageObject Link From ID ");
			continue;
		}
		ScenarioInfoTablePtr Scenario = aObjectList[LinkFromIDs[i]]->ScenarioInfo;
		if (Scenario)
		{
			Scenario->Version++;
		}
		else
		{
			Log("Internal Error---ImageObject Link From Object Scenario Empty! ");
		}
	}
}

bool InfoDTVObject::IsFileModifyed(boost::filesystem::path aFilePath)
{
	std::time_t TmpLastDateTime = boost::filesystem::last_write_time(aFilePath);
	if (TmpLastDateTime > LastFileDateTime)
		return true;
	else
		return false;
}


InfoDTVObject::InfoDTVObject(unsigned short aPID, unsigned short aID,
		TSLibrary::DVB::IPSICrc32CounterPtr aCrc32Counter) :FIsBinding(false),
		FPID(aPID), FCrc32Counter(aCrc32Counter),ID(aID),PassCount(0)
		{
//		FLogger.setName("InfoDTV对象 ID-"+boost::lexical_cast<string>(ID));
		}
//					InfoDTVObject(unsigned short aID,string aFileName):
//						FIsBinding(false),ID(aID),FileName(aFileName),PassCount(0)
//					{
//
//					}

void InfoDTVObject::BuildDefaultScenarioObject(unsigned short aIndex)
{
	//TODO:Check BuildDefaultScenarioObject
	//创建ScenarioTable以及ObjectTable

	//初始化 页面为"<>"，将LinkToIDs,LinkFromIDs 清空 各种大小调整,更新FileName

	assert(aIndex<=254);
	ScenarioInfo.reset(new ScenarioInfoTable(FPID, 0, aIndex + 1));
	unsigned short ObjectID = aIndex + 1 + 255;
	Object.reset(new ObjectInfoTable(FPID, ObjectID, FCrc32Counter));
	RawBufferPtr TmpBuf((unsigned char *)std::malloc(2),&free);
	unsigned char * TmpPtr = TmpBuf.get();
	TmpPtr[0] = '<';
	TmpPtr[1] = '>';
	Object->SetObjectContent(0x20, TmpBuf, 2);
	LastFileDateTime=0;
	FileName=boost::lexical_cast<string>(aIndex);
	ScenarioInfo->LinkedObjectIDs.push_back(ObjectID);
	//Log("BuildDefaultScenarioObject"+boost::lexical_cast<string>(ScenarioInfo->LinkedObjectIDs[0]));
}

void InfoDTVObject::BuildDefaultIndexScenarioObject()
{
	//TODO:Check BuildDefaultIndexScenarioObject
	//创建ScenarioTable以及ObjectTable
	//初始化 页面为"InfoDTV 正在启动...请稍后"，将LinkToIDs,LinkFromIDs 清空 尺寸调整,更新FileName
	ScenarioInfo.reset(new ScenarioInfoTable(FPID, 0, 1));
	unsigned short ObjectID = 1 + 255;
	Object.reset(new ObjectInfoTable(FPID, ObjectID, FCrc32Counter));
	string TmpStr = "<REGION SX=\"40\" SY=\"25\" EX=\"300\" EY=\"48\" Z=\"100\" />";
	TmpStr
	+= "<TEXT SX=\"40\" SY=\"25\" EX=\"300\" EY=\"48\" Z=\"100\">InfoDTV 服务正在启动...请稍后</TEXT>";

	RawBufferPtr TmpBuf((unsigned char *) std::malloc(TmpStr.size()+1),&free);
	unsigned char * TmpPtr = TmpBuf.get();
	strcpy((char *) TmpPtr, (char *) TmpStr.c_str());
	Object->SetObjectContent(0x20, TmpBuf, TmpStr.size());
	ScenarioInfo->LinkedObjectIDs.push_back(ObjectID);
	FileName="Index.IBL";
	LastFileDateTime=0;
}

void InfoDTVObject::BuildDefaultImageObject()
{
	//TODO: Check BuildDefaultImageObject
	//创建ObjectTable
	//将图片内容更新为58字节的BMP，将LinkToIDs,LinkFromIDs 清空 各种大小调整,更新FileName
	unsigned short ObjectID = ID + 1 + 255;
	Object.reset(new ObjectInfoTable(FPID, ObjectID, FCrc32Counter));
	RawBufferPtr TmpBuf((unsigned char *) std::malloc(58),&free);
	unsigned char * TmpPtr = TmpBuf.get();
	std::memcpy(TmpPtr, DefaultBMP, 58);
	Object->SetObjectContent(0x20, TmpBuf, 58);
	FIsBinding=false;
}
inline string InfoDTVObject::toUpper(string s)
{
	string upper(s);
	std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int)) std::toupper);
	//cout<<upper<<std::endl;
	return upper;
}

unsigned char InfoDTVObject::GetImageFileType(boost::filesystem::path &aFilePath)
{
	string FileExt = boost::filesystem::extension(aFilePath);

	FileExt = toUpper(FileExt);

	if (FileExt == ".BMP")
	{
		return 0x24;
	}
	else if (FileExt == ".GIF")
	{
		return 0x23;
	}
	else if (FileExt == ".JPEG")
	{
		return 0x26;
	}
	else if (FileExt == ".JPG")
	{
		return 0x26;
	}
	else if (FileExt == ".PCX")
	{
		return 0x25;
	}
	return 0;
}

void InfoDTVObject::SetLastFileDateTime(boost::filesystem::path aFilePath)
{
	std::time_t TmpLastDateTime = boost::filesystem::last_write_time(aFilePath);
	LastFileDateTime = TmpLastDateTime;

}

bool InfoDTVObject::SetBindingImage(string aRootPath, string aFileName, vector<InfoDTVObjectPtr>& aObjectList)
{
	//TODO: Check !!SetBindingImage
	//						Log("SetBindingImage-1");
	unsigned short ObjectID = ID + 1 + 255;
	boost::filesystem::path FilePath = aRootPath + aFileName;
	//						LinkFromIDs.clear();
	//						vector<unsigned short> (LinkFromIDs).swap(LinkFromIDs);


	if (!Object)
	{
		//							Log("SetBindingImage-2");
		Object.reset(new ObjectInfoTable(FPID, ObjectID, FCrc32Counter));
		//							Log("SetBindingImage-3");
		SetLastFileDateTime(FilePath);
	}
	else
	{
		bool FileModifyed = IsFileModifyed(FilePath);
		if (FileModifyed)
		{
			UpdateImageFileLinkFrom(aObjectList);
			SetLastFileDateTime(FilePath);
		}
		else
		{
			return true;

		}
	}

	unsigned char ObjectType = GetImageFileType(FilePath);
	if (ObjectType == 0)
	{
		Log("Image File Type Error!!");
		return false;
	}
	LoadImageFile(aRootPath+aFileName, ObjectType);

	FileName = aFileName;
	FIsBinding = true;
	return true;
}

void InfoDTVObject::PutScenarioContent(string aScenarioContent)
{
	if(!Object||ID>254)
	{
		Log("Internal Error:SetScenarioContent");
		return;
	}
	RawBufferPtr TmpBuf((unsigned char *) std::malloc(aScenarioContent.size()),&free);
	unsigned char * TmpPtr = TmpBuf.get();
	std::memcpy(TmpPtr,  aScenarioContent.c_str(),aScenarioContent.size());
	Object->SetObjectContent(0x20, TmpBuf, aScenarioContent.size());
}

void InfoDTVObject::PutScenarioContent(boost::shared_ptr<unsigned char> aScenarioContent,const unsigned int aContentLength)
{
	if(!Object||ID>254)
	{
		Log("Internal Error:SetScenarioContent");
		return;
	}
	Object->SetObjectContent(0x20, aScenarioContent, aContentLength);
}

bool InfoDTVObject::SetBindingIBL(string aRootPath, string aFileName)
{
	//						bool IsIBLObject = false;
	//						if (ID < 255)
	//							IsIBLObject = true;
	//						LinkFromIDs.clear();
	//						vector<unsigned short> (LinkFromIDs).swap(LinkFromIDs);
	boost::filesystem::path FilePath = aRootPath + aFileName;

	if (FileName != aFileName)
	{
		//属于新分配,需要释放原来的内容,版本,LastDatetime
		//因为每一个对象都是预先建立好的所以需要清除
		if (ScenarioInfo)
		{
			ScenarioInfo->CleanLinkedObjectIDs();
			ScenarioInfo->Version = 0;
		}
		else
		{
			Log("ERROR Scenario");
		}
		LinkToIDs.clear();
		vector<unsigned short> (LinkToIDs).swap(LinkToIDs);
		IBLFileContent = "";
		if (Object)
		{
			Object->ClearObjectContent();
		}
		else
		{
			Log("ERROR Object");
		}
		ScenarioInfo->LinkedObjectIDs.push_back(Object->ObjectID);
		SetLastFileDateTime(FilePath);
	}
	else
	{
		//属于原有对象,须判断是否更新如需要更新则载入文件,并扫描
		//如未更新,需要检测LinkTo的Image的图片对象是否存在.
		//如未更新,则将原有LinkTo的IBL对象压入Deque
		if (!boost::filesystem::exists(FilePath))
		{
			Log("File not exist!!!");
			return false;
		}

		bool FileModifyed = IsFileModifyed(FilePath);

		if (FileModifyed)
		{
			//已更新
			ScenarioInfo->Version++;
			SetLastFileDateTime(FilePath);
		}
		else
		{
			return true;
		}
	}
	LoadIBLFile(aRootPath + aFileName);

	FileName = aFileName;
	FIsBinding = true;
	return true;
}

void InfoDTVObject::ClearBinding()
{
	string TmpStr = "";
	IBLFileContent = TmpStr;
	FIsBinding = false;
}

bool InfoDTVObject::IsBinding()
{
	return FIsBinding;
}
