/*
 * InfoDTVTSBuilderManager.h
 *
 *  Created on: 2008-12-26
 *      Author: victor
 */

#ifndef INFODTVTSBUILDERMANAGER_H_
#define INFODTVTSBUILDERMANAGER_H_
#include "Interface.h"
using namespace std;


namespace InfoDTV
{
	namespace DynamicBuilder
	{
		namespace FileBuilder
		{

			class InfoDTVTSBuilderManager:public ITSBuilderManager
			{
				private:
					map<string,ITSBuilder*> FBuilderMap;
					map<string,string> FBuilderParamsMap;
				public:
					InfoDTVTSBuilderManager();

					void RegisterBuilder(string aUUID,ITSBuilder *aBuilder,string ParamsMap);

					void UnRegisterBuilder(string aUUID);

					string GetParamsFromBuilder(string aUUID);
					string GetTargetIDFromBuilder(string aUUID,string aFileName);
			};

			static InfoDTVTSBuilderManager GlobalBuilderManager;
		}
	}
}
#endif /* INFODTVTSBUILDERMANAGER_H_ */
