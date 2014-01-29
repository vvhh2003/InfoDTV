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
using namespace std;
using namespace eternity;
struct PSIDynamicGlobalConfigObject
{
	string HostIP;
	int HostIPPort;
	string ChannelName;
	string DefineXMLFile;
	string ValueXMLFile;
	int TimerInterval;
	int RunMode;
	void xml_serialize(xml_archive &xml)
	{
		if (xml.is_loading())
		{

			xml.read("HostIP", HostIP, 0);
			xml.read("HostIPPort", HostIPPort, 0);
			xml.read("ChannelName", ChannelName, 0);
			xml.read("DefineXMLFile", DefineXMLFile, 0);
			xml.read("ValueXMLFile", ValueXMLFile, 0);
			xml.read("TimerInterval", TimerInterval, 0);
			xml.read("RunMode", RunMode, 0);
		}
		else
		{
			xml.write("HostIP", HostIP);
			xml.write("HostIPPort", HostIPPort);
			xml.write("ChannelName", ChannelName);
			xml.write("DefineXMLFile", DefineXMLFile);
			xml.write("ValueXMLFile", ValueXMLFile);
			xml.write("TimerInterval", TimerInterval);
			xml.write("RunMode", RunMode);
		}
	}
	void xml_serialize(xmlstring_archive &xml)
	{
		if (xml.is_loading())
		{
			xml.read("HostIP", HostIP, 0);
			xml.read("HostIPPort", HostIPPort, 0);
			xml.read("ChannelName", ChannelName, 0);
			xml.read("DefineXMLFile", DefineXMLFile, 0);
			xml.read("ValueXMLFile", ValueXMLFile, 0);
			xml.read("TimerInterval", TimerInterval, 0);
			xml.read("RunMode", RunMode, 0);
		}
		else
		{
			xml.write("HostIP", HostIP);
			xml.write("HostIPPort", HostIPPort);
			xml.write("ChannelName", ChannelName);
			xml.write("DefineXMLFile", DefineXMLFile);
			xml.write("ValueXMLFile", ValueXMLFile);
			xml.write("TimerInterval", TimerInterval);
			xml.write("RunMode", RunMode);
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
typedef boost::shared_ptr<PSIDynamicGlobalConfigObject> PSIDynamicGlobalConfigObjectPtr;

#endif /* GLOBALCONFIG_HPP_ */
