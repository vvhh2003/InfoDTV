/*
 * CodeConvet.h
 *
 *  Created on: 2008-12-23
 *      Author: victor
 */

#ifndef CODECONVET_H_
#define CODECONVET_H_

//#include <iconv.h>
#include <boost/shared_ptr.hpp>
#include <string>
//#include <iostream>
#include "./LanguageCode/UTFTOGB2312.h"



using namespace std;

// 代码转换操作类
//class CodeConverter {
//	private:
//		iconv_t cd;
//		// 转换输出
//		int Internalconvert(char *inbuf,int inlen,char *outbuf,int outlen) {
//			char **pin = &inbuf;
//			char **pout = &outbuf;
//
//			memset(outbuf,0,outlen);
//
//			return iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen);
//		}
//	public:
//		// 构造
//		CodeConverter(string from_charset,string to_charset) {
//			cd = iconv_open(to_charset.c_str(),from_charset.c_str());
//		}
//
//		// 析构
//		~CodeConverter() {
//			iconv_close(cd);
//		}
//
//		string convert(string aStr)
//		{
//			int size=aStr.size();
//			boost::shared_ptr<char> Buffer((char*)std::malloc(size),&free);
//			int insize=strlen(aStr.c_str());
//			char * SrcStrPtr =(char * )aStr.c_str();
//			char * TmpBufferPtr=Buffer.get();
//			Internalconvert(SrcStrPtr,insize,TmpBufferPtr,size);
//			string Result=Buffer.get();
//			return Result;
//		}
//
//};


class CodeConverter {
	public:

		string convert(string aStr);

		boost::shared_ptr<unsigned char> convert(const string aStr,int* aOutStrLength);

};
#endif /* CODECONVET_H_ */
