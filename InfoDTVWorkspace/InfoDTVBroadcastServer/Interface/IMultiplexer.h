#ifndef IMULTIPLEXER_H_INCLUDED
#define IMULTIPLEXER_H_INCLUDED
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "InterfaceCommon.h"
#include "ITSMuxChannelStreams.h"

/**
 * class IMultiplexer
 */
using namespace std;
namespace MultiplexerCore
{
	
	class IMultiplexer:public boost::enable_shared_from_this<IMultiplexer>
	{
		public:
			
			virtual ~IMultiplexer(){};
			/**
			 * @return long
			 * @param  aStreamName
			 */
			virtual long GetOutputBitRateByName(string aStreamName)  =0;

			/**
			 * @return ITSMuxChannelStreams *
			 */
			virtual ITSMuxChannelStreamsPtr getMuxChannelStreams()  = 0;

			/**
			 * @return long
			 */
			virtual long GetCurrentTotalTSChannelBitRate()  = 0;

			/**
			 * @return long
			 */
			virtual long getOutputBufferLengthPreSec()  = 0;

			/**
			 * @return long
			 */
			virtual long getOutputBitRate() = 0;

			/**
			 */
			virtual StringListPtr GetOutputStreamNames()  = 0;

			/**
			 * @return list <int>
			 */
			virtual IntListPtr GetOutputPIDs()  = 0;

			/**
			 */
			virtual void Reset()  = 0;

			/**
			 */
			virtual void Clear()  = 0;

	};
	
	typedef boost::shared_ptr<IMultiplexer> IMultiplexerPtr;
}

#endif // IMULTIPLEXER_H_INCLUDED
