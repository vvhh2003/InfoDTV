#ifndef DYNAMICBUFFERREVICER_H_
#define DYNAMICBUFFERREVICER_H_
#include <IceUtil/IceUtil.h>
#include "DynICEBufferSender.h"
#include "../../Common/TSPacketStruct.h"
#include "../../Common/Log/Log.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Poco/Mutex.h"
using namespace std;
namespace Multiplexer_DataProvider_V1
{

	/*文件管理需要一下几个功能
	 * 1 在播出完成时 若具有新的文件需要提供新的文件名
	 * 2 在开始播出新文件时删除上一个文件
	 * 3 文件命名以GUID为准
	 * 4 启动时删除该目录下的全部文件
	 */


	class FileManager
	{
		private:
			InfoDTV_Common_Log::InfoDTVLogger FLogger;
			bool FHasNewFile;
			bool FIsInRead;
			string FCurrentFileName;
			string FNewFileName;
			bool FIsLogInfo;
			Poco::FastMutex  FMutex;
			void Log(string aMsg)
			{
				if(FIsLogInfo)
				 FLogger.information(aMsg);
			}
			void LogError(string ALogStr)
			{
			    FLogger.error(ALogStr);
			}
		public:
			FileManager(bool aIsLogInfo);
			~FileManager();
			void SetLoggerName(string aName);
			//返回一个新的文件名
			string BeginRead();

			void EndRead();

			void SetNewFile(const string aNewFileName);

	};
	typedef boost::shared_ptr<FileManager> FileManagerPtr;
}

namespace InfoDTV
{

	namespace Multiplexer
	{

		namespace Dynamic
		{

			namespace Provider
			{
				class DynamicBufferTransferI : virtual public InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer
				{
				    private:
				    	Multiplexer_DataProvider_V1::FileManagerPtr FFileManager;
						string FServiceName;
						string FSessionID;
						bool FIsLogInfo;
						long FTotalRecvLength;
						long  FTotalToBeRecvedLength;
						RawBufferPtr FBuffer;
						InfoDTV_Common_Log::InfoDTVLogger FLogger;
						string FDynamicFileDataProvider_GlobalDBPath;
						std::ofstream FFileStream;

						void Log(string ALogStr)
						{
							if(FIsLogInfo)
						    FLogger.information(ALogStr);
						}
						void LogError(string ALogStr)
						{
						    FLogger.error(ALogStr);
						}
					public:
						DynamicBufferTransferI(Multiplexer_DataProvider_V1::FileManagerPtr aFileManager,
						        string aServiceName,bool aIsLogInfo,string aDynamicFileDataProvider_GlobalDBPath) ;

						virtual ~DynamicBufferTransferI();

						virtual void SendBuffer(const string& aServiceName, const string& aBufferGuid,
						        ::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength,
						        const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&aSeq,
						        const ::Ice::Current& _Current);
				};
			}
		}
	}
}
#endif /*DYNAMICBUFFERREVICER_H_*/
