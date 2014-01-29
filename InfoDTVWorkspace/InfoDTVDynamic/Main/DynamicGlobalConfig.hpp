/*
 * GlobalConfig.hpp
 *
 *  Created on: 2009-3-17
 *      Author: victor
 */

#ifndef PSIDynamicGLOBALCONFIG_HPP_
#define PSIDynamicGLOBALCONFIG_HPP_


#include "eternity4/eternity/eternity.hpp"
#include <string>
#include <boost/shared_ptr.hpp>
#include <vector>
using namespace std;
using namespace eternity;
struct DynamicGlobalConfigObjectItem
{

	string HostIP;
	int HostIPPort;
	string ChannelName;
	unsigned short PID;
	string TSParams;//频点:符号率:QAMType:TSID:NetworkID:ServiceID:PID:timeout
	string IBLPath;
	string PathGuid;
	int TimerInterval;
	int RunMode; //0 普通模式 1 普通将LOG写入文件 100 调试 将TS写入文件 101 调试 将TS写入文件 将LOG写入文件
	string DebugPath;
	void xml_serialize(xml_archive &xml)
	{
		if (xml.is_loading())
		{

			xml.read("HostIP", HostIP, 0);
			xml.read("HostIPPort", HostIPPort, 0);
			xml.read("ChannelName", ChannelName, 0);
			int Tmp;
			xml.read("PID", Tmp, 0);
			PID=Tmp;
			xml.read("TSParams", TSParams, 0);
			xml.read("IBLPath", IBLPath, 0);
			xml.read("PathGuid", PathGuid, 0);
			xml.read("TimerInterval", TimerInterval, 0);
			xml.read("RunMode", RunMode, 0);
			xml.read("DebugPath", DebugPath, 0);
		}
		else
		{
			xml.write("HostIP", HostIP);
			xml.write("HostIPPort", HostIPPort);
			xml.write("ChannelName", ChannelName);
			xml.write("PID", (int)PID);
			xml.write("TSParams", TSParams);
			xml.write("IBLPath", IBLPath);
			xml.write("PathGuid", PathGuid);
			xml.write("TimerInterval", TimerInterval);
			xml.write("RunMode", RunMode);
			xml.write("DebugPath", DebugPath);
		}
	}
	void xml_serialize(xmlstring_archive &xml)
	{
		if (xml.is_loading())
		{
			xml.read("HostIP", HostIP, 0);
			xml.read("HostIPPort", HostIPPort, 0);
			xml.read("ChannelName", ChannelName, 0);
			int Tmp;
			xml.read("PID", Tmp, 0);
			PID=Tmp;
			xml.read("TSParams", TSParams, 0);
			xml.read("IBLPath", IBLPath, 0);
			xml.read("PathGuid", PathGuid, 0);
			xml.read("TimerInterval", TimerInterval, 0);
			xml.read("RunMode", RunMode, 0);
			xml.read("DebugPath", DebugPath, 0);
		}
		else
		{
			xml.write("HostIP", HostIP);
			xml.write("HostIPPort", HostIPPort);
			xml.write("ChannelName", ChannelName);
			xml.write("PID", (int)PID);
			xml.write("TSParams", TSParams);
			xml.write("IBLPath", IBLPath);
			xml.write("PathGuid", PathGuid);
			xml.write("TimerInterval", TimerInterval);
			xml.write("RunMode", RunMode);
			xml.write("DebugPath", DebugPath);
		}
	}




	string SaveToString()
	{
		eternity::xmlstring_archive aa;
		aa.open("", eternity::archive::store);
		this->xml_serialize(aa);
		aa.close();
		return aa.Result();
	}
};
typedef boost::shared_ptr<DynamicGlobalConfigObjectItem> DynamicGlobalConfigObjectItemPtr;


struct DynamicGlobalConfigObject
{

	vector<DynamicGlobalConfigObjectItem> Items;
//	~DynamicGlobalConfigObject()
//	{
//
//		for(vector<DynamicGlobalConfigObjectItem>::iterator itr=Items.begin();itr!=Items.end();itr++)
//		{
//
//		}
//	}
	void xml_serialize(xml_archive &xml)
	{
		if (xml.is_loading())
		{
			xml_read(sequence<objects>(), Items, Items.begin(),xml, "Items");
		}
		else
		{
			xml_write(sequence<objects>(),Items.begin(),Items.end(),xml,"Items");
		}
	}
	void xml_serialize(xmlstring_archive &xml)
	{
		if (xml.is_loading())
		{
			xml_read(sequence<objects>(), Items, Items.begin(),xml, "Items");
		}
		else
		{
			xml_write(sequence<objects>(),Items.begin(),Items.end(),xml,"Items");
		}
	}

	void LoadConfig(string StringConfig,bool IsFileName=false)
	{
		if(IsFileName)
		{
			try
			{
				eternity::xml_archive aa;
				aa.open(StringConfig, eternity::archive::load);
				this->xml_serialize(aa);
			}
			catch (eternity::exception *e)
			{
				cout << "GlobalConfigObject Load Config Error:" << e->what() << endl;
			}

		}
		else
		{

			try
			{
				eternity::xmlstring_archive aa;
				aa.open(StringConfig, eternity::archive::load);
				this->xml_serialize(aa);
			}
			catch (eternity::exception *e)
			{
				cout << "GlobalConfigObject Load Config Error:" << e->what() << endl;
			}

		}
	}
	void SaveToFile(string aFileName)
	{
		eternity::xml_archive aa;
		aa.open(aFileName, eternity::archive::store);
		this->xml_serialize(aa);
		aa.close();
	}

	string SaveToString()
	{
		eternity::xmlstring_archive aa;
		aa.open("", eternity::archive::store);
		this->xml_serialize(aa);
		aa.close();
		return aa.Result();
	}
};
typedef boost::shared_ptr<DynamicGlobalConfigObject> DynamicGlobalConfigObjectPtr;

#endif /* GLOBALCONFIG_HPP_ */
