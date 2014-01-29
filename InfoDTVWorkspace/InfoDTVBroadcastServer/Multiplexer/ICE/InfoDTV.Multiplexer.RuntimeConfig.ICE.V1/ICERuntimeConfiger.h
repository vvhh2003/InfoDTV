#ifndef ICERUNTIMECONFIGER_H_
#define ICERUNTIMECONFIGER_H_
#include <IceUtil/IceUtil.h>
#include "MultiplexerRuntimeConfigICE.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <boost/serialization/vector.hpp>
#include "boost/filesystem.hpp"   // includes all needed Boost.Filesystem declarations
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>    // for std::cout
#include "../../../eternity4/eternity/eternity.hpp"
//#include <eternity/xmlstring_archive.hpp>
#include <map>
#include "../../../Interface/IMultiplexer.h"
#include "../../../Interface/ITSDataProviderFactory.h"
#include "../../../Common/Log/Log.h"

#include "../../../Common/GlobalConfig.hpp"

using namespace std;

// for ease of tutorial presentation;
//#include "../../../Interface/IMultiplexerRuntimeConfig.h"
//#include "../../MuxRuntimeConfig.h"
using namespace MultiplexerCore;
//using namespace eternity;
namespace fs = boost::filesystem;
namespace InfoDTV
{
	namespace Multiplexer
	{
		namespace RuntimeConfig
		{

			struct StorageChannelInfo : public ChannelInfo
			{
					void xml_serialize(eternity::xmlstring_archive &xml);
					void xml_serialize(eternity::xml_archive &xml);
			};
			const string MuxRuntimeConfigSaveString="INFODTV_CHANNELS";
			class MuxRuntimeConfigI;
			typedef boost::shared_ptr<InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigI> ICERuntimeConfigerPtr;
			//	typedef	boost::shared_ptr<InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigI> MuxRuntimeConfigIPtr;
			typedef map<string,ITSDataProviderFactoryPtr > TSDataProviderFactoryMap;
			class MuxRuntimeConfigI : virtual public InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig
			{
				private:
				    InfoDTV_Common_Log::InfoDTVLogger FLogger;
					void Log(string ALogStr)
					{
					    FLogger.information(ALogStr);
//						cout<<"运行时配置器："<<FLogCounter++<<"\t"<<ALogStr<<endl;
					}
					const MultiplexerCore::IMultiplexerPtr FTSMultiplexer;
					//					const string FDBPath;
					//					const string FBackupDBPath;
					const string FDBFileName;
					const string FBackupDBFileName;
					GlobalConfigObjectPtr FGCOPtr;
					TSDataProviderFactoryMap FTSDataProviderFactoryTable;
					//	const Ice::CommunicatorPtr FCommunicatorPtr;
					//					const Ice::Identity FICEIdentity,
					//					const Ice::ObjectAdapter FICEObjectAdapter;
					//					const string FServerIP;
					//					const int FIPPort;


					void InitLoadProviderFactorys();

					void SaveChannelConfig();


					//					void DeleteChannelConfig()
					//					{
					//						//将DBPath目录下的全部文件删除
					//					}
					//					void BackupChannelConfig()
					//					{
					//						//将DBPath目录下的全部文件复制到BackupDBPath的DBPathName+日期 目录 中
					//					}

					void LoadChannelConfig();


					/*ITSChannelStreamPtr*/
					void InitAddTSChannelStream(StorageChannelInfo &info, ITSMuxChannelStreamsPtr MuxChannelStreams);
					ITSChannelStreamPtr AddNullProviderTSChannelStream(StorageChannelInfo &info,
					        ITSMuxChannelStreamsPtr MuxChannelStreams);
				public:
					virtual ~MuxRuntimeConfigI();
					MuxRuntimeConfigI(IMultiplexerPtr aIMultiplexer, string aDBFileName, string aBackupDBFileName);
					MuxRuntimeConfigI(IMultiplexerPtr aIMultiplexer, string aDBFileName, string aBackupDBFileName,GlobalConfigObjectPtr aGCOPtr);
					void InitConfig();

					void RegisterProviderFactory(string aProviderTypeID, ITSDataProviderFactoryPtr aProviderFactory);
					virtual ChannelInfoSeq GetAllChannelInfos(const Ice::Current & _Current);

					virtual DataProviderInfoSeq GetAllDataProviders(const Ice::Current & _Current);

					virtual AddChannelResult AddChannel(const ChannelInfo& aChannel, const Ice::Current & _Current);

					virtual bool DelectChannel(const ::std::string& aChannelName, const Ice::Current & _Current);

					virtual string CheckDataProviderConfig(const string& aProviderTypeID, const string& aTmpConfig,
					const Ice::Current& _Current);

					virtual bool ModifyChanneIsFixOutputCounter(const string& aChannelName, bool aNewIsFixOutputCounter,
					const Ice::Current& _Current);
					//					virtual bool ModifyChannelOutputBitRate(const string& aChannelName,
					//					        const ::Ice::Long aNewOutputBitRate, const Ice::Current & _Current)
					//					{
					//						if (aChannelName == NULLSTREAM_NAME)
					//							return false;
					//						ITSMuxChannelStreamsPtr MuxChannelStreams = FTSMultiplexer.get()->getMuxChannelStreams();
					//						ITSChannelStreamPtr TmpStream=MuxChannelStreams.get()->GetTSChannelByName(aChannelName);
					//						if (!TmpStream)
					//						{
					//							cout<<"刷新配置失败:通道"<<aChannelName<<"：输出通道不存在！";
					//							return false;
					//						}
					//						if (TmpStream.get()->getOutputBitRate()!=aNewOutputBitRate)
					//						{
					//							cout<<"刷新配置:通道"<<aChannelName<<"属性OutputBitRate从"<<TmpStream.get()->getOutputBitRate() <<"改变为"<<aNewOutputBitRate;
					//							TmpStream.get()->setOutputBitRate(aNewOutputBitRate);
					//							SaveChannelConfig();
					//							cout<<"刷新配置:通道"<<aChannelName<<" OK!";
					//							return true;
					//						}
					//						return false;
					//					}

					virtual bool ModifyChannelOutputBitRate(const string& aChannelName, Ice::Long aNewOutputBitRate,
					const Ice::Current& _Current);
					virtual bool ModifyChannelName(const string& aChannelName, const string& aNewChannelName,
					const Ice::Current& _Current);
					virtual bool ModifyChannelDataProvider(const string& aChannelName, const string& aNewDataProviderTypeID,
					const string& aNewDataProviderConfig, const Ice::Current& _Current);
					virtual bool ModifyChannelDataProviderConfig(const string& aChannelName,
					const string& aNewDataProviderConfig, const Ice::Current& _Current);
				};

			}

			//		void SaveChannelInfo(const string & aFileName, InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo & CI)
			//		{
			//			ofstream ofs(aFileName.c_str());
			//			boost::archive::text_oarchive oa(ofs);
			//			oa << CI;
			//			ofs.close();
			//		}
			//	}
			//
			//	namespace boost
			//	{
			//		namespace serialization
			//		{
			//
			//			template<class Archive> void serialize(Archive & ar, InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo & CI,
			//			        const unsigned int version)
			//			{
			//				ar & CI.ChannelName;
			//				ar & CI.DataProviderTypeID;
			//				ar & CI.DataProviderConfig;
			//				ar & CI.IsFixOutputCounter;
			//				ar & CI.OutputBitRate;
			//
			//			}
			//
			//		}
			//	}
		}
	}
#endif /*ICERUNTIMECONFIGER_H_*/
