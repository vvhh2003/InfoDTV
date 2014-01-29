/*
 * ObjectInfoTable.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "ObjectInfoTable.h"
#include <iostream>
using namespace std;
using namespace TSLibrary::DVB;
using namespace TSLibrary::InfoDTV;

unsigned short ObjectInfoTable::GetObjectInfoLength()
{
	return 14+FObject.Original_size;
}
ObjectInfoTable::ObjectInfoTable(IPSICrc32CounterPtr aCrc32Counter) :
	FCrc32Counter(aCrc32Counter)
	{

	}
ObjectInfoTable::ObjectInfoTable(unsigned short aPID, unsigned short aObjectID, IPSICrc32CounterPtr aCrc32Counter) :
	FCrc32Counter(aCrc32Counter),PID(aPID), ObjectID(aObjectID)
	{
	FObject.Object_type=0;
	}
ObjectInfoTable::~ObjectInfoTable()
{

}
//				void SetObjectType(unsigned char aObjectType)
//				{
//					 FObject.Object_type=aObjectType;
//				}
unsigned char ObjectInfoTable::GetObjectType()
{
	return FObject.Object_type;
}

void ObjectInfoTable::ClearObjectContent()
{
	FObject.Original_size=0;
	FObject.Original_Crc32=0;
	FObject.Compressed_size=0;
	FObject.ObjectContent.reset();
}

RawBufferPtr ObjectInfoTable::GetObjectContentPtr()
{
	return FObject.ObjectContent;
}

unsigned long ObjectInfoTable::GetObjectSize()
{
	return FObject.Original_size;
}

void ObjectInfoTable::SetObjectContent(unsigned char aObjectType, RawBufferPtr aObjectContent,
		unsigned long aObjectContentLength)
{
	FObject.Object_type=aObjectType;
	FObject.Original_size=aObjectContentLength;
	FObject.ObjectContent=aObjectContent;
	if(!aObjectContentLength)
		std::cout<<"!!SetObjectContent!!";
	FObject.Original_Crc32=FCrc32Counter->GetCrc32(aObjectContent, aObjectContentLength);

	FObject.Compressed_size=aObjectContentLength;
	FObject.Compressed_flag=0;
}
void ObjectInfoTable::TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	TransferHeadTo(aTSStream,aStream,aDataCounter,aCrc32Counter);
	TransferRestPartTo(aTSStream,aStream,aDataCounter,aCrc32Counter);
}

void ObjectInfoTable::TransferHeadTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(PID,
			ObjectInfoTableID, ObjectID, true);
	PSIHeaderConfig->PSIHeader.version_number=0x1F;
	PSIHeaderConfig->PSIHeader.reserved2BitFiled1=0x1;
	PSIHeaderConfig->PSIHeader.reserved2BitFiled1=0x1;
	//					if (!aDataCounter)
		//					{
		//						if (!FDataCounter)
	//							FDataCounter.reset(new DefaultDataCounter());
	//					}
	//					else
	//					{
	//						FDataCounter=aDataCounter;
	//					}

	RawBufferPtr TmpBufferPtr((unsigned char *)std::malloc(14),&free);
	unsigned char * TmpPtr=TmpBufferPtr.get();
	TmpPtr[0]=FObject.Object_type;
	TmpPtr[1]=(unsigned char)(FObject.Original_size>>24);
	TmpPtr[2]=(unsigned char)(FObject.Original_size>>16);
	TmpPtr[3]=(unsigned char)(FObject.Original_size>>8);
	TmpPtr[4]=(unsigned char)(FObject.Original_size);

	TmpPtr[5]=(unsigned char)(FObject.Original_Crc32>>24);
	TmpPtr[6]=(unsigned char)(FObject.Original_Crc32>>16);
	TmpPtr[7]=(unsigned char)(FObject.Original_Crc32>>8);
	TmpPtr[8]=(unsigned char)(FObject.Original_Crc32);
	TmpPtr[9]=0;
	TmpPtr[10]=(unsigned char)(FObject.Compressed_size>>24);
	TmpPtr[11]=(unsigned char)(FObject.Compressed_size>>16);
	TmpPtr[12]=(unsigned char)(FObject.Compressed_size>>8);
	TmpPtr[13]=(unsigned char)(FObject.Compressed_size);
	aStream->WriteFirstSectionDataToTSStream(aTSStream, PSIHeaderConfig, TmpBufferPtr, 14, 0, 14,
			FObject.Original_size, aDataCounter, FCrc32Counter, false);
}

void ObjectInfoTable::TransferRestPartTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
		ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter)
{
	if (!FObject.ObjectContent)
		return;
	PSIHeaderConfigStructPtr PSIHeaderConfig=PSIHeaderConfigStruct::NewPSIHeaderConfigStruct(PID,
			ObjectInfoTableID, ObjectID, true);
	PSIHeaderConfig->PSIHeader.version_number=0x1F;

	aStream->WriteRestSectionDataTSStream(aTSStream, PSIHeaderConfig, FObject.ObjectContent,FObject.Original_size,
			aDataCounter, FCrc32Counter, false);
}
