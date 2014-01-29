/*
 * CodeConverter.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "CodeConverter.h"

string CodeConverter::convert(string aStr)
{
	int size=GetGb2312Len(aStr.c_str(),aStr.size());
	boost::shared_ptr<char> Buffer((char*)std::malloc(size+1),&free);
	char * TmpBufferPtr=Buffer.get();
	std::memset(TmpBufferPtr,0,size+1);
	Utf8ToGb2312(aStr.c_str(),size,TmpBufferPtr);
	string Result=Buffer.get();
	return Result;
}

boost::shared_ptr<unsigned char> CodeConverter::convert(const string aStr,int* aOutStrLength)
{
	int OgrSize=strlen(aStr.c_str());
	int size=GetGb2312Len(aStr.c_str(),OgrSize);
	boost::shared_ptr<unsigned char> Buffer((unsigned char*)std::malloc(size),&free);
	char * TmpBufferPtr=(char*)Buffer.get();
	std::memset(TmpBufferPtr,0,size);
	Utf8ToGb2312(aStr.c_str(),OgrSize,TmpBufferPtr);
	*aOutStrLength=size;
	return Buffer;
}
