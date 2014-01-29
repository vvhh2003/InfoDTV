#include <stdio.h>
#include <string.h>
#include "codeTable.h"

#define APP_PRINT
#define u8 unsigned char
#define u16 unsigned short

int GetUtf8ByteNumForWord(u8 firstCh)
{
	u8 temp = 0x80;
	int num = 0;

	while (temp & firstCh)
	{
		num++;
		temp = (temp >> 1);
	}

	//    APP_PRINT("the num is: %d", num);
	return num;
}

#define CODE_TABLE_SIZE 21791

u16 SearchCodeTable(u16 unicodeKey)
{
	int first = 0;
	int end = CODE_TABLE_SIZE - 1;
	int mid = 0;

	while (first <= end)
	{
		mid = (first + end) / 2;

		if (code_table[mid].unicode == unicodeKey)
		{
			return code_table[mid].gb;
		}
		else if (code_table[mid].unicode > unicodeKey)
		{
			end = mid - 1;
		}
		else
		{
			first = mid + 1;
		}
	}
	return 0;
}

int GetGb2312Len(const char* utf8,int len)
{
	int byteCount = 0;
	int i = 0;
	int j = 0;
//	u16 unicodeKey = 0;
//	u16 gbKey = 0;

	while (i < len)
	{
		switch(GetUtf8ByteNumForWord((u8)utf8[i]))
		{
			case 0:
				byteCount = 1;
				break;
			case 2:
				byteCount = 2;
				break;
			case 3:
				byteCount = 3;
				break;
			case 4:
				byteCount = 4;
				break;
			case 5:
				byteCount = 5;
				break;
			case 6:
				byteCount = 6;
				break;
			default:
				//                APP_PRINT("the len is more than 6\n");
				break;
		}

		i += byteCount;
		if (byteCount == 1)
		{
			j++;
		}
		else
		{
			j += 2;
		}
	}
	return j;


}


int Utf8ToGb2312(const char* utf8, int len, char *temp)
{
	//    APP_PRINT("utf8->unicode: \n");
	//    APP_PRINT("utf8: [");
	//
	//    for (int k = 0; k < len; k++)
	//    {
	//      APP_PRINT("%02x ", utf8[k]);
	//    }
	//    APP_PRINT("]\n");

	int byteCount = 0;
	int i = 0;
	int j = 0;

	u16 unicodeKey = 0;
	u16 gbKey = 0;


	while (i < len)
	{
		switch(GetUtf8ByteNumForWord((u8)utf8[i]))
		{
			case 0:
				temp[j] = utf8[i];
				byteCount = 1;
				break;

			case 2:
				temp[j] = utf8[i];
				temp[j + 1] = utf8[i + 1];
				byteCount = 2;
				break;

			case 3:

				temp[j + 1] = ((utf8[i] & 0x0F) << 4) | ((utf8[i + 1] >> 2) & 0x0F);
				temp[j] = ((utf8[i + 1] & 0x03) << 6) + (utf8[i + 2] & 0x3F);


				memcpy(&unicodeKey, (temp + j), 2);
				//                 APP_PRINT("unicode key is: 0x%04X\n", unicodeKey);
				gbKey = SearchCodeTable(unicodeKey);
				//                APP_PRINT("gb2312 key is: 0x%04X\n", gbKey);

				if (gbKey != 0)
				{
					//here change the byte

					gbKey = (gbKey >> 8) | (gbKey << 8);
					memcpy((temp + j), &gbKey, 2);
				}

				byteCount = 3;
				break;

			case 4:
				byteCount = 4;
				break;

			case 5:
				byteCount = 5;
				break;

			case 6:
				byteCount = 6;
				break;

			default:
				//                APP_PRINT("the len is more than 6\n");
				break;
		}

		i += byteCount;
		if (byteCount == 1)
		{
			j++;
		}
		else
		{
			j += 2;
		}
	}
	return j;

	//    APP_PRINT("utf8: [");
	//    for (int k = 0; k < j; k++)
	//    {
	//      APP_PRINT("%02x ", temp[k]);
	//    }
	//    APP_PRINT("]\n");
}
