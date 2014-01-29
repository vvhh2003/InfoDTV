#ifndef IBROADCASTINTERFACE_H_
#define IBROADCASTINTERFACE_H_
#include <boost/enable_shared_from_this.hpp>
using namespace std;
namespace BroadcastCore
{
	typedef ::std::vector< ::std::string> StringSeq;


	//	class ITSBroadcastConfigDBManagement
	//	{
	//		public:
	//			virtual ~ITSBroadcastConfigDBManagement();
	//			virtual StringSeq GetRuntimeConfigDatabaseNameList()=0;
	//			virtual string GetBroadcastConfigDBName()=0;
	//			virtual int DeleteRuntimeConfigDB(string RuntimeConfigDB)=0;
	//	};
	//
	//	class ITSBroadcastControlA : virtual public ITSBroadcastConfigDBManagement
	//	{
	//		public:
	//			virtual ~ITSBroadcastControlA();
	//			virtual bool StartBroadcast(string aConfigDBName, int aOutputBitRate)=0;
	//			virtual bool StopBroadcast()=0;
	//			virtual bool IsInBroadcasting()=0;
	//			virtual int GetBroadcastBitRate()=0;
	//			virtual bool RestartBroadcast()=0;
	//	};
	class ITSBroadcastControl //: public boost::enable_shared_from_this<ITSBroadcastControl>
	{
		public:
			virtual ~ITSBroadcastControl(){};
			virtual bool StartBroadcast(string aConfigDBName, long aOutputBitRate)=0;
			virtual bool StopBroadcast()=0;
			virtual bool IsInBroadcasting()=0;
			virtual long GetBroadcastBitRate()=0;
			virtual bool RestartBroadcast()=0;
			virtual StringSeq GetRuntimeConfigDatabaseNameList()=0;
			virtual string GetBroadcastConfigDBName()=0;
			virtual int DeleteRuntimeConfigDB(string RuntimeConfigDB)=0;
	};

	class ITSBroadcastServer
	{
		public:
			virtual ~ITSBroadcastServer(){};
			virtual void StartServer()=0;
			virtual void StopServer()=0;
	};


	//	typedef boost::shared_ptr<ITSBroadcastConfigDBManagement> ITSBroadcastConfigDBManagementPtr;
	typedef boost::shared_ptr<ITSBroadcastControl> ITSBroadcastControlPtr;
	typedef boost::shared_ptr<ITSBroadcastServer> ITSBroadcastServerPtr;

}
#endif /*IBROADCASTINTERFACE_H_*/
