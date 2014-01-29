#ifndef OBJECTINFOTABLE_H_
#define OBJECTINFOTABLE_H_
#include <boost/shared_ptr.hpp>

#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"

namespace TSLibrary
{
	namespace InfoDTV
	{
		using namespace TSLibrary::DVB;
		const unsigned char ObjectInfoTableID=0xFD;
		struct ObjectInfoRecord
		{
			public:
				unsigned char Object_type;
				unsigned long Original_size;
				unsigned long Original_Crc32;
				unsigned Compressed_flag :1;
				unsigned long Compressed_size;
				RawBufferPtr ObjectContent;
		};
		class ObjectInfoTable : public IPSIStreamPartWriteAble
		{

			private:
				ObjectInfoRecord FObject;
				IPSICrc32CounterPtr FCrc32Counter;
				unsigned short GetObjectInfoLength();

			public:
				unsigned short PID;
				unsigned short ObjectID;
				ObjectInfoTable(IPSICrc32CounterPtr aCrc32Counter);
				ObjectInfoTable(unsigned short aPID, unsigned short aObjectID, IPSICrc32CounterPtr aCrc32Counter);
				virtual ~ObjectInfoTable();
//				void SetObjectType(unsigned char aObjectType)
//				{
//					 FObject.Object_type=aObjectType;
//				}
				unsigned char GetObjectType();

				void ClearObjectContent();

				RawBufferPtr GetObjectContentPtr();

				unsigned long GetObjectSize();
				void SetObjectContent(unsigned char aObjectType, RawBufferPtr aObjectContent,
				        unsigned long aObjectContentLength);
				virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
							        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);

				virtual void TransferHeadTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);

				virtual void TransferRestPartTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);

		};

		typedef boost::shared_ptr<ObjectInfoTable> ObjectInfoTablePtr;
	}
}

#endif /*OBJECTINFOTABLE_H_*/
