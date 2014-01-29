/*
 * VBitStream.h
 *
 *  Created on: 2009-2-1
 *      Author: victor
 */

#ifndef VBITSTREAM_H_
#define VBITSTREAM_H_
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

using namespace std;
class VBitStream
{
public:
	// Public methods
	VBitStream(void);

	virtual ~VBitStream(void);
	void WriteBit(const unsigned char value);
	void ReadBit(unsigned char& value);

	void WriteByte(const unsigned char value);
	void ReadByte(unsigned char& value);

	void WriteInt16(const unsigned short value);
	void ReadInt16(unsigned short& value);

	void WriteInt32(const unsigned int value);
	void ReadInt32(unsigned int& value);

	void WriteData(const unsigned char * lpData, const long nLen);
	void ReadData(unsigned char * lpData, long nLen);

	void WriteBits(const unsigned int value, const long nLen=32);
	void ReadBits(unsigned int& value, long nLen=32);

	void LoadStream(string lpszFileName);
	void SaveStream(string lpszFileName);
//	void LoadStream(unsigned char * lpStream, long nLen);
//	void SaveStream(unsigned char * lpStream);
	bool AppendStream(VBitStream &aVB);
	unsigned char * GetStream()	{return m_lpStream;}
	unsigned int GetStreamLength()	{return m_dwStreamOffset;}
	unsigned int GetStreamTotalLength()	{return m_dwStreamLen;}
	unsigned int GetCurrentPosition()	{return m_dwCurrentPosition;}
	void SetCurrentPosition(unsigned int dwCurrentPosition)	{m_dwCurrentPosition = max((unsigned int)0, (unsigned int)min(m_dwStreamOffset-1, dwCurrentPosition));}

private:
	// Private methods
	void _WriteBit(unsigned char value);
	void _WriteByte(unsigned char value);
	void _ReadBit(unsigned char& value);

private:
	// Private members
	unsigned char * m_lpStream;
	unsigned int m_dwStreamLen;
	unsigned int m_dwStreamOffset;
	unsigned int m_dwCurrentPosition;
	unsigned char m_CurrentBit;

};

typedef boost::shared_ptr<VBitStream> VBitStreamPtr;
typedef std::vector<VBitStreamPtr > VBitStreamPtrList;

struct PSIXMLVBRecord
	{
		public:

			VBitStreamPtr HeaderVB;
			VBitStreamPtrList ItemVBs;
			boost::shared_ptr<std::map<string,string> > ExtValueMapPtr;
			std::map<unsigned int,unsigned short> ExtTableExtIDMap;
			std::map<unsigned int,bool> PSISectionSplitterMap;
			VBitStreamPtr CurrentVB;
			unsigned int CurrentVBIndex;
			VBitStreamPtr TmpVB; //用于表述临时VB
			PSIXMLVBRecord():HeaderVB(new VBitStream()),ItemVBs(),ExtValueMapPtr(new std::map<string,string>()),ExtTableExtIDMap(),
			PSISectionSplitterMap(),CurrentVB(),CurrentVBIndex(0),TmpVB()
			{

			}
			void GetNewItemVBToCurrent()
			{
				VBitStreamPtr TmpPtr(new VBitStream());
				ItemVBs.push_back(TmpPtr);
				CurrentVBIndex=ItemVBs.size()-1;
				CurrentVB=ItemVBs[ItemVBs.size()-1];
			}
	};
typedef boost::shared_ptr<PSIXMLVBRecord> PSIXMLVBRecordPtr;

#endif /* VBITSTREAM_H_ */
