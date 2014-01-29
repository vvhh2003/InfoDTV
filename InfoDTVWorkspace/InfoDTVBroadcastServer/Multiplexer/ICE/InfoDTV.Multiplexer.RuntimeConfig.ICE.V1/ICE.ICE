
#ifndef INFODTV_ICE
#define INFODTV_ICE

module InfoDTV
{
	module Multiplexer
	{
			module RuntimeConfig
			{
			
				enum AddChannelResult {ACROK, ACRSameName,ACROBError,ACRNoDP,ACRDPInitError};
				
			    struct DataProviderInfo
				{
					string TypeID;
					string Name;
                    string Info;
				};
			
				struct ChannelInfo
				{
					string ChannelName;
					long OutputBitRate; 
					bool IsFixOutputCounter;
                    string DataProviderTypeID;
                    string DataProviderConfig;
				};
				
				sequence<DataProviderInfo> DataProviderInfoSeq;
				
				sequence<ChannelInfo> ChannelInfoSeq;
				
				interface MuxRuntimeConfig
				{
					idempotent ChannelInfoSeq GetAllChannelInfos();
					idempotent DataProviderInfoSeq GetAllDataProviders();
					AddChannelResult AddChannel(ChannelInfo aChannel);
					bool DelectChannel(string aChannelName);
					string CheckDataProviderConfig(string aProviderTypeID,string aTmpConfig);
					bool ModifyChanneIsFixOutputCounter(string aChannelName,bool aNewIsFixOutputCounter);
					bool ModifyChannelOutputBitRate(string aChannelName,long aNewOutputBitRate);
					bool ModifyChannelName(string aChannelName,string aNewChannelName);
					bool ModifyChannelDataProvider(string aChannelName,string aNewDataProviderTypeID,string aNewDataProviderConfig);
					bool ModifyChannelDataProviderConfig(string aChannelName,string aNewDataProviderConfig);
				};
				
			};
	};

};

#endif