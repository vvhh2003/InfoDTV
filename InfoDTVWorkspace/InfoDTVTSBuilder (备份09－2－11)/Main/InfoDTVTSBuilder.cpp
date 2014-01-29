//============================================================================
// Name        : InfoDTVTSBuilder.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

#include <boost/lexical_cast.hpp>
#include "../InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.h"
using namespace std;

void println(string aMsg)
{
    cout << aMsg << endl;
}

void print(string aMsg)
{
    cout << aMsg ;
}

int main() {
	cout << "!!!InfoDTV TS Builder @Copyright Victor 2009!!!" << endl;

	println("Input Save TS File Name:");
	print(">");
	string aTSSaveFileName;
	cin>>aTSSaveFileName;

	println("Input UUID:");
	print(">");
	string aUUID;
	cin>>aUUID;

	println("Input TS Params:");
	print(">");
	string aTSParams;
	cin>>aTSParams;

	println("Input PID:");
	print(">");
	string aPIDStr;
	cin>>aPIDStr;
	int aPID=boost::lexical_cast<int>(aPIDStr);

	cout<<aPID<<endl;


	println("Input IBL Path:");
	print(">");
	string aPath;
	cin>>aPath;

	println("OK All Done!");
	println("Your Input:");
	println("UUID:"+aUUID+"\t TS Params:"+aTSParams+"\t PID:"+aPIDStr+"\t Path:"+aPath);
	println("All Save To TS File:"+aTSSaveFileName);
	println("Continue?");
	print(">(Y/N):");
	string aY;
	cin>>aY;
	if(aY!="y"&&aY!="Y")
	    {
		println("Exist!");
		return 0;
	    }
	println("Start Run..");

	InfoDTV::DynamicBuilder::FileBuilder::InfoDTVTSBuilder Builder(aUUID,aTSParams,aPID,aPath);
	Builder.Init();

	string aCMD;
	std::ofstream OutFileStream;
	std::ofstream OutLogFileStream;
	bool IsFrist=true;
	int i=0;
	while (aCMD!="QUIT"&&aCMD!="quit")
	    {

		if(aCMD=="r"||aCMD!="R"||IsFrist)
		    {
			Builder.Process();
			string SaveFileName=aTSSaveFileName+boost::lexical_cast<string>(i)+".TS";
			string SaveLogFileName=aTSSaveFileName+boost::lexical_cast<string>(i)+".Log";
			OutFileStream.open(SaveFileName.c_str(),std::ios::binary);
			OutLogFileStream.open(SaveLogFileName.c_str(),std::ios::binary);
			RawBufferPtr TmpBuffer=Builder.BufferManager.BeginRead();
			int size=Builder.BufferManager.GetBufferLength();
			OutFileStream.write((char *)(TmpBuffer.get()), size);
			OutFileStream.close();
			Builder.PrintAllToStream(OutLogFileStream);
			OutLogFileStream.close();
		    }
		i++;
		println("you can use 'R' to build TS for version changed..");
		println("Please Input CMD:");
		print(">");
		cin>>aCMD;
	    }
	println("Exist!");
	return 0;
}
