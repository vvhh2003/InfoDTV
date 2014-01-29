/*
 * InfoDTVObjectManager.h
 *
 *  Created on: 2008-12-11
 *      Author: victor
 */

#ifndef INFODTVOBJECTMANAGER_H_
#define INFODTVOBJECTMANAGER_H_
#include <map>
//#include <IceUtil/IceUtil.h>
#include "Poco/Mutex.h"
#include <boost/lexical_cast.hpp>
#include <string>
#include "../../Common/TSPacketStruct.h"
#include <boost/enable_shared_from_this.hpp>
#include "../../Common/TS.Library/TSLibrary.h"
#include "InfoDTVFileProcesser.h"
#include "Interface.h"
#include "InfoDTVTSBuilderManager.h"
#include "../../Common/Log/Log.h"
#include <ostream>
using namespace std;
//using namespace TSLibrary::InfoDTV;
namespace InfoDTV
{

	namespace DynamicBuilder
	{
		namespace FileBuilder
		{

			class InfoDTVTSBufferManager
			{
				private:
					RawBufferPtr FBuffer;
					RawBufferPtr FBackupBuffer;
					bool FHasNewBuffer;
					uint FBackupBufferLength;
					uint FBufferLength;
//					IceUtil::Mutex FMutex;
					Poco::Mutex FMutex;
				public:
					InfoDTVTSBufferManager() ;

					uint GetBackupBufferLength();

					uint GetBufferLength();
					RawBufferPtr BeginRead();
					void EndRead();

					void SetNewBuffer(RawBufferPtr aBuffer, int aBufferLength);

			};

			typedef boost::shared_ptr<InfoDTVTSBufferManager> InfoDTVTSBufferManagerPtr;


			class InfoDTVTSBuilder: public ITSBuilder
			{
				private:
					string FUUID;
					string FTSParams;
					int FGlobalPassCount;
					InfoDTV_Common_Log::InfoDTVLogger FLogger;
					void Log(string ALogStr)
					{
						FLogger.information(ALogStr);
					}
					TSLibrary::ITSDataStreamPtr FTSStreamPtr;
					TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr;
					TSLibrary::ITSDataCounterPtr FDataCounter;
					TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter;
//					vector<string> FFileNameList;
					vector<InfoDTVObjectPtr> FObjectList;
					deque<string> FProcessDeque;
					InfoDTVFileProcesser FPProcesser;
					string FFilePath;
					ServiceInfoTable FServiceInfoTable;


					void BeginProcessPath(string aFilePath);

					void InsertNULLPackets();




					void BuildBuffer1();
					void BuildBuffer2();

					void BuildBuffer3();

					void BuildBuffer4();
					void BuildBuffer5();
					void BuildBuffer();

					void RegisterToManager();
					void UnRegisterToManager();
				public:
					unsigned short PID;

//					map<string, unsigned short> FileIDIndexer; from base now
					InfoDTVTSBufferManager BufferManager; //从这里读取生成的码流
					InfoDTVTSBuilder(string aUUID,string aTSParams,unsigned short aPID,string aFilePath) ;

					InfoDTVTSBuilder(string aUUID,string aTSParams,unsigned short aPID,string aFilePath, TSLibrary::ITSDataCounterPtr aDataCounter) ;
//
//					InfoDTVTSBuilder(unsigned short aPID, string aFilePath,TSLibrary::ITSDataCounterPtr aDataCounter ) :
//						FGlobalPassCount(0), FLogCounter(0), FTSStreamPtr(new TSLibrary::DefaultTSDataStream()),
//						        FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream()), FDataCounter(aDataCounter),
//						        FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter()), FPProcesser(FFileNameList,
//						                FObjectList, FileIDIndexer, FProcessDeque,FCrc32Counter), FFilePath(aFilePath),PID(aPID)
//					{
//
//					}

					virtual ~InfoDTVTSBuilder();



					void Init();



					void PrintAllToStream(std::ostream &aOut);
					void PrintAll();

					void Process();

			};
			/*
						class InfoDTVTSBuilder: public boost::enable_shared_from_this<InfoDTVTSBuilder>
						{
							private:
								int FGlobalPassCount;
								int FLogCounter;//=0
								void Log(string ALogStr);
								TSLibrary::ITSDataStreamPtr FTSStreamPtr;
								TSLibrary::DVB::IPSIDataStreamPtr FPSIStreamPtr;
								TSLibrary::ITSDataCounterPtr FDataCounter;
								TSLibrary::DVB::IPSICrc32CounterPtr FCrc32Counter;
								vector<string> FFileNameList;
								vector<InfoDTVObjectPtr> FObjectList;
								deque<string> FProcessDeque;
								InfoDTVFileProcesser FPProcesser;

								void FInit();

								void BeginProcessPath(string aFilePath);
								string FFilePath;
							public:
								unsigned short PID;

								map<string, unsigned short> FileIDIndexer;
								InfoDTVBufferManager BufferManager; //从这里读取生成的码流
								InfoDTVTSBuilder(unsigned short aPID,string aFilePath) ;

								InfoDTVTSBuilder(unsigned short aPID,string aFilePath, TSLibrary::ITSDataCounterPtr aDataCounter) ;
			//
			//					InfoDTVTSBuilder(unsigned short aPID, string aFilePath,TSLibrary::ITSDataCounterPtr aDataCounter ) :
			//						FGlobalPassCount(0), FLogCounter(0), FTSStreamPtr(new TSLibrary::DefaultTSDataStream()),
			//						        FPSIStreamPtr(new TSLibrary::DVB::DefaultPSIDataStream()), FDataCounter(aDataCounter),
			//						        FCrc32Counter(new TSLibrary::DVB::DefaultPSICrc32Counter()), FPProcesser(FFileNameList,
			//						                FObjectList, FileIDIndexer, FProcessDeque,FCrc32Counter), FFilePath(aFilePath),PID(aPID)
			//					{
			//
			//					}

								~InfoDTVTSBuilder();
								void Init();
								void PrintAllToStream(std::ostream &aOut);
								void PrintAll();
								void Process();

						};

			*/



		}

	}
}
#endif /* INFODTVOBJECTMANAGER_H_ */
