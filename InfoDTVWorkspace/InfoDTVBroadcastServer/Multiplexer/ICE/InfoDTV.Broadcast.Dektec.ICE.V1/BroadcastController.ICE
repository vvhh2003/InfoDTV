#ifndef INFODTV_ICE
#define INFODTV_ICE

module InfoDTV
{
	module Broadcast
	{
			sequence<string> StringSeq;
			interface BroadcastController
			{
				bool StartBroadcast(string aConfigDBName,int aOutputBitRate);
  			    bool StopBroadcast();
   			    bool RestartBroadcast();
   			    bool IsInBroadcasting();
   			    int GetBroadcastBitRate();
				StringSeq GetRuntimeConfigDatabaseNameList();
				string GetBroadcastConfigDBName();
		         int DeleteRuntimeConfigDB(string RuntimeConfigDB);
			};
		
	};
};

#endif
