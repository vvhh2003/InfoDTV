/*
 * ITSDataProcessor.h
 *
 *  Created on: 2009-3-19
 *      Author: victor
 */

#ifndef ITSDATAPROCESSOR_H_
#define ITSDATAPROCESSOR_H_
#include "InterfaceCommon.h"
#include "../Common/Log/Log.h"
#include "../Common/TSPacketStruct.h"
#include "ITSDataProvider.h"
using namespace std;
namespace MultiplexerCore
{
	class ITSDataProcessor;
	typedef  boost::shared_ptr< ITSDataProcessor > ITSDataProcessorPtr;
	class ITSDataProcessor
	{
		protected:

//			ITSDataProcessorPtr FParentDataProcessorPtr;
		public:

			virtual ~ITSDataProcessor(){};
			ITSDataProcessor(){};

//			void setParentDataProvider(ITSDataProviderPtr aParentDataProviderPtr)
//			{
//				FParentDataProviderPtr=aParentDataProviderPtr;
//			}
//			ITSDataProviderPtr getParentDataProvider()
//			{
//				return FParentDataProviderPtr;
//			}

//			void setParentDataProcessor(ITSDataProcessorPtr aParentDataProcessorPtr)
//			{
//				FParentDataProcessorPtr=aParentDataProcessorPtr;
//			}
//			ITSDataProcessorPtr getParentDataProcessor()
//			{
//				return FParentDataProcessorPtr;
//			}
			/**
			 */
			virtual void Active ( )=0;

			/**
			 */
			virtual void DeActive ( )  =0;


			/**
			 * @return TSPacketStruct
			 */
			virtual TSPacketStructPtr GetTSPacket ( )  =0;

			/**
			 * @return bool
			 */
			virtual bool getIsActived ( )  =0;

	};

}
#endif /* ITSDATAPROCESSOR_H_ */
