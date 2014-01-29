#ifndef _H_UTFTOGB2312_
#define _H_UTFTOGB2312_

int GetUtf8ByteNumForWord(unsigned char firstCh);
unsigned short SearchCodeTable(unsigned short unicodeKey);
int Utf8ToGb2312(const char* utf8, int len, char *temp);
int GetGb2312Len(const char* utf8,int len);

#endif
