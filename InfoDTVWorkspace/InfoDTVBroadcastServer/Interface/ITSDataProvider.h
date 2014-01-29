#ifndef ITSDATAPROVIDER_H_INCLUDED
#define ITSDATAPROVIDER_H_INCLUDED


#include "InterfaceCommon.h"
#include "../Common/Log/Log.h"
#include "../Common/TSPacketStruct.h"
#include <iostream>
/**
  * class ITSDataProvider
  */
using namespace std;
namespace MultiplexerCore
{

	class ITSDataProvider
	{
		public:

			virtual ~ITSDataProvider(){};
			ITSDataProvider(){};
			/**
			 */
			virtual void Active ( )=0;


			/**
			 * @param  aNewConfig
			 */
			virtual void ConfigChanged (string aNewConfig )  =0;


			/**
			 */
			virtual void DeActive ( )  =0;


			/**
			 * @return string
			 */
			virtual string GetProviderInfo ( )  =0;


			/**
			 * @return string
			 */
			virtual string GetProviderStateInfo ( )  =0;


			/**
			 * @return TSPacketStruct
			 */
			virtual TSPacketStructPtr GetTSPacket ( )  =0;


			//  /**
			//   * @param  aCount
			//   */
			//  virtual RawBufferPtr GetTSPackets (long aCount )  =0;


			/**
			 */
			virtual void Reset ( )  =0;


			/**
			 * @return bool
			 */
			virtual bool getIsActived ( )  =0;


			/**
			 * @return long
			 */
			virtual string getTypeID ( )  =0;


			/**
			 * @return string
			 */
			virtual string GetCurrentConfig ( )  =0;

	};
	typedef  boost::shared_ptr< ITSDataProvider > ITSDataProviderPtr;
};

#endif // ITSDATAPROVIDER_H_INCLUDED
