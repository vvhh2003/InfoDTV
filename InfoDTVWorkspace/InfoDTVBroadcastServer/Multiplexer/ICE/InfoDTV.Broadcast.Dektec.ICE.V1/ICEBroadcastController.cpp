/*
 * ICEBroadcastController.cpp
 *
 *  Created on: 2009-1-12
 *      Author: victor
 */

#include "ICEBroadcastController.h"

using namespace InfoDTV::Broadcast;
BroadcastControllerI::~BroadcastControllerI()
{

}
BroadcastControllerI::BroadcastControllerI(BroadcastCore::ITSBroadcastControl* aBroadcastControl):
	FBroadcastControl(aBroadcastControl)
	{

	}
bool BroadcastControllerI::StartBroadcast(const ::std::string& aConfigDBName,::Ice::Int aOutputBitRate,const ::Ice::Current& _Current)
{
	return FBroadcastControl->StartBroadcast(aConfigDBName,(long)aOutputBitRate);
}

bool BroadcastControllerI::StopBroadcast(const ::Ice::Current& _Current)
{
	return FBroadcastControl->StopBroadcast();
}

bool BroadcastControllerI::RestartBroadcast(const ::Ice::Current& _Current)
{
	return FBroadcastControl->RestartBroadcast();
}

bool BroadcastControllerI::IsInBroadcasting(const ::Ice::Current& _Current)
{
	return FBroadcastControl->IsInBroadcasting();
}

::Ice::Int BroadcastControllerI::GetBroadcastBitRate(const ::Ice::Current& _Current)
{
	return FBroadcastControl->GetBroadcastBitRate();
}

::InfoDTV::Broadcast::StringSeq BroadcastControllerI::GetRuntimeConfigDatabaseNameList(const ::Ice::Current& _Current)
{
	return FBroadcastControl->GetRuntimeConfigDatabaseNameList();
}

::std::string BroadcastControllerI::GetBroadcastConfigDBName(const ::Ice::Current& _Current)
{
	return FBroadcastControl->GetBroadcastConfigDBName();
}

int BroadcastControllerI::DeleteRuntimeConfigDB(const ::std::string& aRuntimeConfigDB,const ::Ice::Current& _Current)
{
	return FBroadcastControl->DeleteRuntimeConfigDB(aRuntimeConfigDB);
}
