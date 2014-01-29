#ifndef TSPACKETSTRUCT_H_
#define TSPACKETSTRUCT_H_

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include <vector>

inline unsigned char GetPIDHi(unsigned short aPID)
{
	return (unsigned char)(aPID>>8&0x001F);
}

inline unsigned char GetPIDLo(unsigned short aPID)
{
	return (unsigned char)(aPID&0x00FF);
}

struct TSPacketHeadStruct
{
	public:
		unsigned sync_byte :8;
		unsigned PID_Hi :5;
		unsigned transport_priority :1;
		unsigned payload_unit_start_indicator :1;
		unsigned transport_error_indicator :1;
		unsigned PID_Lo :8;
		unsigned continuity_counter :4;
		unsigned adaptation_field_control :2;
		unsigned transport_scrambling_control :2;
		inline void SetPID(unsigned short NewPID)
		{
			PID_Hi=NewPID>>8;
			PID_Lo=NewPID&0x00ff;
		}

		inline unsigned short GetPID()
		{
			unsigned short Tmp=PID_Hi<<8;
			Tmp+=PID_Lo;
			return Tmp;
		}


		//		const TSPacketHeadStruct & operator=(const TSPacketHeadStruct &aTSPSrc)
		//		{
		//			if(&aTSPSrc!=this)
		//			{
		//				sync_byte=0x47;//aTSPSrc.sync_byte;
		//				PID_Hi=aTSPSrc.PID_Hi;
		//				PID_Lo=aTSPSrc.PID_Lo;
		//				transport_priority=aTSPSrc.transport_priority;
		//				payload_unit_start_indicator=aTSPSrc.payload_unit_start_indicator;
		//				transport_error_indicator=aTSPSrc.transport_error_indicator;
		//				continuity_counter=aTSPSrc.continuity_counter;
		//				adaptation_field_control=aTSPSrc.adaptation_field_control;
		//				transport_scrambling_control=aTSPSrc.transport_scrambling_control;
		//			}
		//			return *this;
		//		}
};
struct TSPacketStruct;
typedef boost::shared_ptr<TSPacketStruct> TSPacketStructPtr;
//typedef boost::shared_ptr<unsigned char[188]> RawTSPacketPtr1;
//typedef boost::shared_array<unsigned char> RawBufferPtr;
typedef boost::shared_ptr<unsigned char> RawBufferPtr;
typedef boost::shared_ptr< std::vector<TSPacketStructPtr> > TSPacketStructsPtr;
typedef boost::shared_ptr<TSPacketHeadStruct> TSPacketHeadStructPtr;

enum TSPacketAdaptationFieldControlTypes
{
	TSPAF_ReservedByISO=0,
	TSPAF_None=1,
	TSPAF_OnlyAdaptationField=2,
	TSPAF_PayloadAfterAdaptationField=3
};

struct TSPacketStruct
{
	public:
		union
		{
			struct
			{
				union
				{
					TSPacketHeadStruct Header;
					unsigned char HeadData[4];
				};
				unsigned char Data[184];
			};
			unsigned char TSData[188];
		};

		TSPacketStruct();
		const TSPacketStruct & operator=(const TSPacketStruct &aTSPSrc);

		static TSPacketStructPtr NewNullTSPacket();


		static TSPacketStructPtr NewTSPacket(unsigned short aPID);

		static void FastCopyToBuffer(TSPacketStructPtr aTmpTP, unsigned char * aBuffer);

		static TSPacketStructPtr NewTSPacket(unsigned short aPID, bool aIsStartPacket,
		        TSPacketAdaptationFieldControlTypes aAdaptField);

		static TSPacketStructPtr NewTSPacket(unsigned short aPID, bool aIsStartPacket);

		inline bool IsCanFixCount()
		{
			if (GetPID()!=0x1FFF)
				return true;
			else
				return false;
		}

		inline void FixCount(unsigned char aCount)
		{
			Header.continuity_counter=aCount;
		}
		inline void SetPID(unsigned short NewPID)
		{
			Header.PID_Hi=NewPID>>8;
			Header.PID_Lo=NewPID&0x00ff;
		}

		inline unsigned short GetPID()
		{
			unsigned short Tmp=Header.PID_Hi<<8;
			Tmp+=Header.PID_Lo;
			return Tmp;
		}
};

#endif /*TSPACKETSTRUCT_H_*/
