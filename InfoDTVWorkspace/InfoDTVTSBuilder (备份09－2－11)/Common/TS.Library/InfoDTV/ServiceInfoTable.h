#ifndef SERVICEINFOTABLE_H_
#define SERVICEINFOTABLE_H_
#include <boost/shared_ptr.hpp>

#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"

namespace TSLibrary
{
	namespace InfoDTV
	{
		struct ServiceInfoTableRecord
		{
			public:
				unsigned Service_Object_ID_Start_Hi :8;
				unsigned Service_Object_ID_Start_Lo :8;
				unsigned Service_Object_ID_End_Hi :8;
				unsigned Service_Object_ID_End_Lo :8;
				unsigned Reserved1 :8;
				unsigned Service_Scenario_ID_Start :8;
				unsigned Reserved2 :8;
				unsigned Service_Scenario_ID_End :8;
				ServiceInfoTableRecord();
				void Init();
				void setServiceObjectID(unsigned short aService_Object_ID_Start, unsigned short aService_Object_ID_End);
		};
		typedef boost::shared_ptr<ServiceInfoTableRecord> ServiceInfoTableRecordPtr;
		using namespace TSLibrary::DVB;
		const unsigned char ServiceInfoTableID=0xFE;
		class ServiceInfoTable : public IPSIStreamWriteAble
		{
			private:
				ITSDataCounterPtr FDataCounter;
				IPSICrc32CounterPtr FCrc32Counter;
			public:

				unsigned short PID;
				unsigned char Version;
				ServiceInfoTableRecord ServiceInfoRec;
				ServiceInfoTable();
				ServiceInfoTable(unsigned short aPID);
				virtual ~ServiceInfoTable();
				ServiceInfoTable(unsigned short aPID, unsigned char aVersion, unsigned char aScenarioStartID,
				        unsigned char aScenarioEndID, unsigned short aObjectStartID, unsigned short aObjectEndID);
				void SetServiceInfo(unsigned char aVersion, unsigned char aScenarioStartID,
				        unsigned char aScenarioEndID, unsigned short aObjectStartID, unsigned short aObjectEndID);

				virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);
		};
	}
}
#endif /*SERVICEINFOTABLE_H_*/
