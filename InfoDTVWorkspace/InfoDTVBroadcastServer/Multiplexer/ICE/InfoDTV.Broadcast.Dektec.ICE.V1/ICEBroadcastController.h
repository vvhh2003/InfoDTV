#ifndef ICEBROADCASTCONTROLLER_H_
#define ICEBROADCASTCONTROLLER_H_
#include <IceUtil/IceUtil.h>
#include "BroadcastController.h"
#include "../../../Interface/BroadcastInterface.h"

namespace InfoDTV
{

	namespace Broadcast
	{
		class BroadcastControllerI:virtual public BroadcastController
		{
			//BroadcastCore::ITSBroadcastControlPtr FBroadcastControl;
			BroadcastCore::ITSBroadcastControl* FBroadcastControl;
			public:
		//	BroadcastControllerI(BroadcastCore::ITSBroadcastControlPtr aBroadcastControl):
				BroadcastControllerI(BroadcastCore::ITSBroadcastControl* aBroadcastControl);
				virtual ~BroadcastControllerI();
				virtual bool StartBroadcast(const ::std::string& aConfigDBName,::Ice::Int aOutputBitRate,const ::Ice::Current& _Current);
				virtual bool StopBroadcast(const ::Ice::Current& _Current);
				virtual bool RestartBroadcast(const ::Ice::Current& _Current);

				virtual bool IsInBroadcasting(const ::Ice::Current& _Current);

				virtual ::Ice::Int GetBroadcastBitRate(const ::Ice::Current& _Current);
				virtual ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList(const ::Ice::Current& _Current);

				virtual ::std::string GetBroadcastConfigDBName(const ::Ice::Current& _Current);
				virtual int DeleteRuntimeConfigDB(const ::std::string& aRuntimeConfigDB,const ::Ice::Current& _Current);
		};
	}
}
#endif /*ICEBROADCASTCONTROLLER_H_*/
