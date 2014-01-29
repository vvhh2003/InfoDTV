#ifndef SCENARIOINFOTABLE_H_
#define SCENARIOINFOTABLE_H_
#include <boost/shared_ptr.hpp>

#include "../DVB/PSIInterface.h"
#include "../DVB/CommonPSIInclude.h"
using namespace std;
namespace TSLibrary
{
	namespace InfoDTV
	{

		using namespace TSLibrary::DVB;
		const unsigned char ScenarioInfoTableID=0xFE;
		class ScenarioInfoTable : public IPSIStreamWriteAble
		{
			private:
				ITSDataCounterPtr FDataCounter;
				IPSICrc32CounterPtr FCrc32Counter;

				unsigned int GetScenarioInfoSize();
			public:
				unsigned short PID;
				unsigned  Version:5;
				unsigned char ScenarioID;
				vector<unsigned short> LinkedObjectIDs;
				ScenarioInfoTable();
				ScenarioInfoTable(unsigned short aPID, unsigned char aVersion, unsigned char aScenarioID) ;
				virtual ~ScenarioInfoTable();
				void CleanLinkedObjectIDs();

				virtual void TransferTo(ITSDataStreamPtr aTSStream, IPSIDataStreamPtr aStream,
				        ITSDataCounterPtr aDataCounter, IPSICrc32CounterPtr aCrc32Counter);

		};

		typedef boost::shared_ptr<ScenarioInfoTable> ScenarioInfoTablePtr;
	}
}
#endif /*SCENARIOINFOTABLE_H_*/
