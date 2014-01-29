/*
 * Interface.h
 *
 *  Created on: 2008-12-28
 *      Author: victor
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <map>
#include <string>
using namespace std;
namespace InfoDTV
{

	namespace DynamicBuilder
	{
		namespace FileBuilder
		{
			class ITSBuilder
			{
				public:
					map<string,unsigned short> FileIDIndexer;
			};


			class ITSBuilderManager
			{
				public:
					virtual void RegisterBuilder(string aUUID,ITSBuilder *aBuilder,string ParamsMap)=0;
					virtual void UnRegisterBuilder(string aUUID)=0;
					virtual string GetTargetIDFromBuilder(string aUUID,string aFileName)=0;
			};
		}
	}
}

#endif /* INTERFACE_H_ */
