/*
 * VBitStream.cpp
 *
 *  Created on: 2009-2-1
 *      Author: victor
 */
#include "VBitStream.h"
#include <iostream>
using namespace std;
VBitStream::VBitStream(void)
{
	// Init members
	m_lpStream = NULL;
	m_dwStreamLen = 0;
	m_dwStreamOffset = 0;
	m_dwCurrentPosition = 0;
	m_CurrentBit = 0;
}

VBitStream::~VBitStream(void)
{
	// Free stream
	if (m_lpStream != NULL)
	{
		free(m_lpStream);
		m_lpStream = NULL;
		m_dwStreamLen = 0;
	}
}

void VBitStream::_WriteByte(const unsigned char value)
{
	// Check for current bit offset
	if ((m_CurrentBit % 8) == 0)
	{
//		std::cout<<"_WriteByte if m_CurrentBit % 8"<<endl;
		// Check for valid stream
		if (m_lpStream == NULL)
		{
			m_lpStream = (unsigned char *)malloc(sizeof(unsigned char));
			m_dwStreamLen = 1;
			m_lpStream[m_dwStreamLen-1]=value;
			m_CurrentBit = 8;
			m_dwStreamOffset = 8;
			m_dwCurrentPosition = m_dwStreamOffset - 1;
		}
		else
		{
			m_CurrentBit = 8;
			m_dwStreamLen++;
			m_lpStream = (unsigned char *)realloc(m_lpStream, m_dwStreamLen*sizeof(unsigned char));
			m_lpStream[m_dwStreamLen-1] = value;
			m_dwStreamOffset+=8;
			m_dwCurrentPosition = m_dwStreamOffset - 1;
		}
	}
	else
	{
//		cout<<"_WriteByte else"<<endl;
		WriteByte(value);
	}
}

void VBitStream::_WriteBit(const unsigned char value)
{
	// Check for current bit offset
	if ((m_CurrentBit % 8) == 0)
	{
//		cout<<"_WriteBit if m_CurrentBit % 8"<<endl;
		// Check for valid stream
		if (m_lpStream == NULL)
		{
			m_lpStream = (unsigned char *)malloc(sizeof(unsigned char));
			m_dwStreamLen = 1;
			m_lpStream[m_dwStreamLen-1] = 0;
			m_CurrentBit = 0;
			m_dwStreamOffset = 0;
		}
		else
		{
//			cout<<"_WriteBit m_lpStream!=NULL"<<endl;
			m_CurrentBit = 0;
			m_dwStreamLen++;
			m_lpStream = (unsigned char *)realloc(m_lpStream, m_dwStreamLen*sizeof(unsigned char));
			m_lpStream[m_dwStreamLen-1] = 0;
		}
	}

	// Write single BIT
	m_lpStream[m_dwStreamLen-1] |= ((value & 0x80) >> m_CurrentBit);
	m_dwStreamOffset++;
	m_dwCurrentPosition = m_dwStreamOffset - 1;
	m_CurrentBit++;
}

void VBitStream::_ReadBit(unsigned char& value)
{
	// Check for valid position
	value = 0x00;
	if (m_dwCurrentPosition < m_dwStreamOffset)
	{
		// Read single BIT
		unsigned int currentByte = m_dwCurrentPosition >> 3;
		unsigned char currentBit = (unsigned char)(m_dwCurrentPosition % 8);
		value = ((unsigned char)(m_lpStream[currentByte] << currentBit) >> 7);
		m_dwCurrentPosition = max((unsigned int)0, (unsigned int)min(m_dwStreamOffset-1, m_dwCurrentPosition+1));
	}
}

void VBitStream::WriteBit(const unsigned char value)
{
	// Write single BIT
	unsigned char bitValue = ((value & 0x01) << 7);
	_WriteBit(bitValue);
}

void VBitStream::ReadBit(unsigned char& value)
{
	// Read single BIT
	_ReadBit(value);
}

void VBitStream::WriteByte(const unsigned char value)
{
	// Write single unsigned char
	if ((m_CurrentBit % 8) == 0)
	{
		_WriteByte(value);
		return ;
	}
	unsigned char currentOffset = 0;
	unsigned char mask = 0x80;
	unsigned char bitValue = 0;
	for (long i=0; i<8; i++)
	{
		bitValue = ((value & mask) << currentOffset);
		_WriteBit(bitValue);
		mask = mask >> 1;
		currentOffset++;
	}
}

void VBitStream::ReadByte(unsigned char& value)
{
	// Read single unsigned char

	value = 0x00;
	unsigned char currentOffset = 7;
	unsigned char bitValue;
	for (long i=0; i<8; i++)
	{
		_ReadBit(bitValue);
		value |= (bitValue << currentOffset);
		currentOffset--;
	}
}

void VBitStream::WriteInt16(const unsigned short value)
{
	// Write single unsigned short
	if ((m_CurrentBit % 8) == 0)
	{
		unsigned char TmpValue=0;
		TmpValue=(value>>8);
		_WriteByte(TmpValue);
		TmpValue=value&0x00FF;
		_WriteByte(TmpValue);
		return ;
	}
	unsigned char currentOffset = 0;
	unsigned short mask = 0x8000;
	unsigned char bitValue = 0;
	for (long i=0; i<16; i++)
	{
		bitValue = (unsigned char)(((value & mask) << currentOffset) >> 8);
		_WriteBit(bitValue);
		mask = mask >> 1;
		currentOffset++;
	}
}

void VBitStream::ReadInt16(unsigned short& value)
{
	// Read single unsigned short
	value = 0x0000;
	unsigned char currentOffset = 15;
	unsigned char bitValue;
	for (long i=0; i<16; i++)
	{
		_ReadBit(bitValue);
		value |= (bitValue << currentOffset);
		currentOffset--;
	}
}

void VBitStream::WriteInt32(const unsigned int value)
{
	// Write single unsigned int
	if ((m_CurrentBit % 8) == 0)
	{
		unsigned char TmpValue=0;
		TmpValue=(value>>24);
		_WriteByte(TmpValue);
		TmpValue=(value>>16)&0x000000FF;
		_WriteByte(TmpValue);
		TmpValue=(value>>8)&0x000000FF;
		_WriteByte(TmpValue);
		TmpValue=value&0x00FF;
		_WriteByte(TmpValue);
		return ;
	}
	unsigned char currentOffset = 0;
	unsigned int mask = 0x80000000;
	unsigned char bitValue = 0;
	for (long i=0; i<32; i++)
	{
		bitValue = (unsigned char)(((value & mask) << currentOffset) >> 24);
		_WriteBit(bitValue);
		mask = mask >> 1;
		currentOffset++;
	}
}

void VBitStream::ReadInt32(unsigned int& value)
{
	// Read single unsigned int
	value = 0x00000000;
	unsigned char currentOffset = 31;
	unsigned char bitValue;
	for (long i=0; i<32; i++)
	{
		_ReadBit(bitValue);
		value |= (bitValue << currentOffset);
		currentOffset--;
	}
}

void VBitStream::WriteData(const unsigned char * lpData, long nLen)
{
	// Check for valid data
	if (lpData != NULL)
	{
		// Write variable-length data
		for (long i=0; i<nLen; i++)
		{
			// Write single unsigned char
			WriteByte(lpData[i]);
		}
	}
}

void VBitStream::ReadData(unsigned char * lpData, long nLen)
{
	// Check for valid data
	if (lpData != NULL)
	{
		// Read variable-length data
		for (long i=0; i<nLen; i++)
		{
			// Read single unsigned char
			ReadByte(lpData[i]);
		}
	}
}

void VBitStream::WriteBits(const unsigned int value, long nLen)
{
	// Write single BITs
	unsigned long _nLen = max((unsigned long)0, (unsigned long)min((long)32, nLen));
	unsigned char currentOffset = (unsigned char)(_nLen - 1);
	unsigned int mask = (0x00000001 << (_nLen - 1));
	unsigned char bitValue = 0;
	for (unsigned long i=0; i<_nLen; i++)
	{
		bitValue = ((unsigned char)((value & mask) >> currentOffset) << 7);
		_WriteBit(bitValue);
		mask = mask >> 1;
		currentOffset--;
	}
}

void VBitStream::ReadBits(unsigned int& value, long nLen)
{
	// Read single BITs
	value = 0x00000000;
	unsigned long _nLen = max((unsigned long)0, (unsigned long)min((long)32, nLen));
	unsigned char currentOffset = 31;
	unsigned char bitValue;
	for (unsigned long i=0; i<_nLen; i++)
	{
		_ReadBit(bitValue);
		value |= (bitValue << currentOffset);
		currentOffset--;
	}
}

bool VBitStream::AppendStream(VBitStream &aVB)
{
	if ((m_CurrentBit % 8) != 0)
		return false;
	//		std::cout<<"_WriteByte if m_CurrentBit % 8"<<endl;
			// Check for valid stream
	if (m_lpStream == NULL)
	{
		m_lpStream = (unsigned char *)malloc(aVB.GetStreamTotalLength());
		m_dwStreamLen = aVB.GetStreamTotalLength();
		memcpy(m_lpStream,aVB.GetStream(),m_dwStreamLen);
		m_CurrentBit = 8;
		m_dwStreamOffset = 8*m_dwStreamLen;
		m_dwCurrentPosition = m_dwStreamOffset - 1;
	}
	else
	{
		m_CurrentBit = 8;
		m_lpStream = (unsigned char *)realloc(m_lpStream, m_dwStreamLen+aVB.GetStreamTotalLength());
		unsigned char * TmpPtr=m_lpStream+m_dwStreamLen ;
		m_dwStreamLen+=aVB.GetStreamTotalLength();
		memcpy(TmpPtr,aVB.GetStream(),aVB.GetStreamTotalLength());
		m_dwStreamOffset+=8*aVB.GetStreamTotalLength();
		m_dwCurrentPosition = m_dwStreamOffset - 1;
	}
	return true;
}


void VBitStream::LoadStream(string lpszFileName)
{
	/*
	// Check for valid file name
	if (lpszFileName != NULL)
	{
		// Free stream
		if (m_lpStream != NULL)
		{
			free(m_lpStream);
			m_lpStream = NULL;
			m_dwStreamLen = 0;
		}

		// Read stream from file
		FILE* file = _tfopen(lpszFileName, _T("rb"));
		if (file != NULL)
		{
			m_dwStreamLen = filelength(file->_file);
			m_lpStream = (unsigned char *)malloc(m_dwStreamLen*sizeof(unsigned char));
			fread(m_lpStream, sizeof(unsigned char), m_dwStreamLen, file);
			fclose(file);
			m_dwStreamOffset = m_dwStreamLen << 3;
			m_dwCurrentPosition = m_dwStreamOffset - 1;
			m_CurrentBit = 0;
		}
	}
	*/
}

void VBitStream::SaveStream(string lpszFileName)
{
	/*
	// Check for valid file name
	if (lpszFileName != NULL)
	{
		// Check for valid stream
		if (m_lpStream != NULL)
		{
			// Write stream to file
			FILE* file = _tfopen(lpszFileName, _T("wb"));
			if (file != NULL)
			{
				fwrite(m_lpStream, sizeof(unsigned char), m_dwStreamLen, file);
				fclose(file);
			}
		}
	}
	*/
}


/*
void VBitStream::LoadStream(unsigned char * lpStream, long nLen)
{
	// Check for valid memory buffer
	if (lpStream != NULL)
	{
		// Free stream
		if (m_lpStream != NULL)
		{
			free(m_lpStream);
			m_lpStream = NULL;
			m_dwStreamLen = 0;
		}

		// Read stream from memory buffer
		m_dwStreamLen = nLen;
		m_lpStream = (unsigned char *)malloc(m_dwStreamLen*sizeof(unsigned char));
		memcpy(m_lpStream, lpStream, m_dwStreamLen*sizeof(unsigned char));
		m_dwStreamOffset = m_dwStreamLen << 3;
		m_dwCurrentPosition = m_dwStreamOffset - 1;
		m_CurrentBit = 0;
	}
}

void VBitStream::SaveStream(unsigned char * lpStream)
{
	// Check for valid memory buffer
	if (lpStream != NULL)
	{
		// Check for valid stream
		if (m_lpStream != NULL)
		{
			// Write stream to memory buffer
			memcpy(lpStream, m_lpStream, m_dwStreamLen*sizeof(unsigned char));
		}
	}
}
*/
