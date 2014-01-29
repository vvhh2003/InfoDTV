/*
 * ClobalConfig.hpp
 *
 *  Created on: 2009-3-10
 *      Author: victor
 */

#ifndef CLOBALCONFIG_HPP_
#define CLOBALCONFIG_HPP_

#include "../eternity4/eternity/eternity.hpp"
#include <string>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace eternity;
struct GlobalConfigObject
{
	string TargetIP;
	int TargetIPPort;
	string HostIP;
	int HostIPPort;
	string DBPath;
	bool IsDebugMode;
	string DebugTSFile;
	string DynamicFileTmpPath;
	string LogPath;
	string DefaultDBName;
	int DefaultBitRate;
	string SPTSFilePath;
	bool IsDVBMode;
	bool IsQAMMode;
	long QAMFreqHz;
	int DeviceType;


	void xml_serialize(xml_archive &xml)
	{
		if (xml.is_loading())
		{
			xml.read("TargetIP", TargetIP, 0);
			xml.read("TargetIPPort", TargetIPPort, 0);
			xml.read("HostIP", HostIP, 0);
			xml.read("HostIPPort", HostIPPort, 0);
			xml.read("DBPath", DBPath, 0);
			xml.read("IsDebugMode", IsDebugMode, 0);
			xml.read("DebugTSFile", DebugTSFile, 0);
			xml.read("DynamicFileTmpPath", DynamicFileTmpPath, 0);
			xml.read("LogPath", LogPath, 0);
			xml.read("DefaultDBName", DefaultDBName, 0);
			xml.read("DefaultBitRate", DefaultBitRate, 0);
			xml.read("SPTSFilePath", SPTSFilePath, 0);
			xml.read("IsDVBMode", IsDVBMode, 0);
			xml.read("IsQAMMode", IsQAMMode, 0);
			xml.read("DeviceType", DeviceType, 0);
			xml.read("QAMFreqHz", QAMFreqHz, 0);
		}
		else
		{
			xml.write("TargetIP", TargetIP);
			xml.write("TargetIPPort", TargetIPPort);
			xml.write("HostIP", HostIP);
			xml.write("HostIPPort", HostIPPort);
			xml.write("DBPath", DBPath);
			xml.write("IsDebugMode", IsDebugMode);
			xml.write("DebugTSFile", DebugTSFile);
			xml.write("DynamicFileTmpPath", DynamicFileTmpPath);
			xml.write("LogPath", LogPath);
			xml.write("DefaultDBName", DefaultDBName);
			xml.write("DefaultBitRate", DefaultBitRate);
			xml.write("SPTSFilePath", SPTSFilePath);
			xml.write("IsDVBMode", IsDVBMode);
			xml.write("IsQAMMode", IsQAMMode);
			xml.write("DeviceType", DeviceType);
			xml.write("QAMFreqHz", QAMFreqHz);

		}
	}
	void xml_serialize(xmlstring_archive &xml)
	{
		if (xml.is_loading())
		{
			xml.read("TargetIP", TargetIP, 0);
			xml.read("TargetIPPort", TargetIPPort, 0);
			xml.read("HostIP", HostIP, 0);
			xml.read("HostIPPort", HostIPPort, 0);
			xml.read("DBPath", DBPath, 0);
			xml.read("IsDebugMode", IsDebugMode, 0);
			xml.read("DebugTSFile", DebugTSFile, 0);
			xml.read("DynamicFileTmpPath", DynamicFileTmpPath, 0);
			xml.read("LogPath", LogPath, 0);
			xml.read("DefaultDBName", DefaultDBName, 0);
			xml.read("DefaultBitRate", DefaultBitRate, 0);
			xml.read("SPTSFilePath", SPTSFilePath, 0);
			xml.read("IsDVBMode", IsDVBMode, 0);
			xml.read("IsQAMMode", IsQAMMode, 0);
			xml.read("DeviceType", DeviceType, 0);
			xml.read("QAMFreqHz", QAMFreqHz, 0);
		}
		else
		{
			xml.write("TargetIP", TargetIP);
			xml.write("TargetIPPort", TargetIPPort);
			xml.write("HostIP", HostIP);
			xml.write("HostIPPort", HostIPPort);
			xml.write("DBPath", DBPath);
			xml.write("IsDebugMode", IsDebugMode);
			xml.write("DebugTSFile", DebugTSFile);
			xml.write("DynamicFileTmpPath", DynamicFileTmpPath);
			xml.write("LogPath", LogPath);
			xml.write("DefaultDBName", DefaultDBName);
			xml.write("DefaultBitRate", DefaultBitRate);
			xml.write("SPTSFilePath", SPTSFilePath);
			xml.write("IsDVBMode", IsDVBMode);
			xml.write("IsQAMMode", IsQAMMode);
			xml.write("DeviceType", DeviceType);
			xml.write("QAMFreqHz", QAMFreqHz);
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
typedef boost::shared_ptr<GlobalConfigObject> GlobalConfigObjectPtr;

#endif /* CLOBALCONFIG_HPP_ */
