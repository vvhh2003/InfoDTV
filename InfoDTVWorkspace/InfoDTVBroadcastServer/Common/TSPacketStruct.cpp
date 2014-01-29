/*
 * TSPacketStruct.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "TSPacketStruct.h"
using namespace std;

TSPacketStruct::TSPacketStruct():TSData()
{
}
const TSPacketStruct & TSPacketStruct::operator=(const TSPacketStruct &aTSPSrc)
{
	if (&aTSPSrc!=this)
	{
		//Header=aTSPSrc.Header;
		std::memcpy(TSData, aTSPSrc.TSData, 188);
	}
	return *this;
}

TSPacketStructPtr TSPacketStruct::NewNullTSPacket()
{
	//			cout<<"NewNullTSPacket Runing..."<<std::endl;
	TSPacketStructPtr TmpTSPacket(new TSPacketStruct());
	std::memset(TmpTSPacket.get(),0xFF,188);
	TmpTSPacket.get()->Header.payload_unit_start_indicator=0;
	TmpTSPacket.get()->Header.transport_error_indicator=0;
	TmpTSPacket.get()->Header.transport_priority=0;
	TmpTSPacket.get()->Header.sync_byte=0x47;
	TmpTSPacket.get()->Header.PID_Hi=0x1F;
	TmpTSPacket.get()->Header.PID_Lo=0xFF;
	TmpTSPacket.get()->Header.adaptation_field_control=0x01;
//			TmpTSPacket.get()->Header.payload_unit_start_indicator=0;
	TmpTSPacket.get()->Header.transport_scrambling_control=0;
	TmpTSPacket.get()->Header.continuity_counter=0;
//			TmpTSPacket.get()->Header.transport_error_indicator=0;
	//			cout<<"NewNullTSPacket Ending..."<<std::endl;
	return TmpTSPacket;
}

TSPacketStructPtr TSPacketStruct::NewTSPacket(unsigned short aPID)
{
	TSPacketStructPtr TmpTSPacket(new TSPacketStruct());
	std::memset(TmpTSPacket.get(),0xFF,188);
	TmpTSPacket.get()->Header.sync_byte=0x47;
	TmpTSPacket.get()->Header.payload_unit_start_indicator=0;
	TmpTSPacket.get()->Header.transport_error_indicator=0;
	TmpTSPacket.get()->Header.transport_priority=0;
	TmpTSPacket.get()->Header.PID_Hi=GetPIDHi(aPID);
	TmpTSPacket.get()->Header.PID_Lo=GetPIDLo(aPID);
	TmpTSPacket.get()->Header.adaptation_field_control=0x01;
	TmpTSPacket.get()->Header.transport_scrambling_control=0;

	return TmpTSPacket;
}


void TSPacketStruct::FastCopyToBuffer(TSPacketStructPtr aTmpTP, unsigned char * aBuffer)
{
	std::memcpy((void *)aBuffer, (void *)aTmpTP.get(), 188);
	//	memcpy((void *)aBuffer, (void *)aTmpTP->TSData, 188);
}

TSPacketStructPtr TSPacketStruct::NewTSPacket(unsigned short aPID, bool aIsStartPacket,
        TSPacketAdaptationFieldControlTypes aAdaptField)
{
	TSPacketStructPtr TmpTSPacket(new TSPacketStruct());
	std::memset(TmpTSPacket.get(),0xFF,188);
	TmpTSPacket.get()->Header.sync_byte=0x47;
	TmpTSPacket.get()->Header.PID_Hi=GetPIDHi(aPID);
	TmpTSPacket.get()->Header.PID_Lo=GetPIDLo(aPID);
	TmpTSPacket.get()->Header.adaptation_field_control=aAdaptField;
	if (aIsStartPacket)
		{
			TmpTSPacket.get()->Header.payload_unit_start_indicator=1;
			TmpTSPacket.get()->Data[0]=0;
		}
	else
		TmpTSPacket.get()->Header.payload_unit_start_indicator=0;
	TmpTSPacket.get()->Header.transport_scrambling_control=0;
	TmpTSPacket.get()->Header.transport_priority=0;
	TmpTSPacket.get()->Header.transport_error_indicator=0;
	return TmpTSPacket;
}

TSPacketStructPtr TSPacketStruct::NewTSPacket(unsigned short aPID, bool aIsStartPacket)
{
	TSPacketStructPtr TmpTSPacket(new TSPacketStruct());
	std::memset(TmpTSPacket.get(),0xFF,188);
	TmpTSPacket.get()->Header.sync_byte=0x47;
	TmpTSPacket.get()->Header.PID_Hi=GetPIDHi(aPID);
	TmpTSPacket.get()->Header.PID_Lo=GetPIDLo(aPID);
	TmpTSPacket.get()->Header.adaptation_field_control=0x01;
	if (aIsStartPacket)
	{
		TmpTSPacket.get()->Header.payload_unit_start_indicator=1;
		TmpTSPacket.get()->Data[0]=0;
	}
	else
		TmpTSPacket.get()->Header.payload_unit_start_indicator=0;
	TmpTSPacket.get()->Header.transport_scrambling_control=0;
	TmpTSPacket.get()->Header.transport_priority=0;
	TmpTSPacket.get()->Header.transport_error_indicator=0;
	return TmpTSPacket;
}
