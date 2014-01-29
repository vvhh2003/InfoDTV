#ifndef ISOFTMULTIPLEXER_H_
#define ISOFTMULTIPLEXER_H_
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "IMultiplexer.h"
#include "../Common/TSPacketStruct.h"

namespace MultiplexerCore
{

	class ISoftMultiplexer : public IMultiplexer
	{
		public:
			virtual ~ISoftMultiplexer(){}
			/**
			 * @param  aBufferLength
			 * @param  aBuffer
			 */
			virtual void FillBuffer(int aBufferLength, RawBufferPtr aBuffer) =0;

			/**
			 * @param  aBufferLength
			 * @param  aBuffer
			 */
			virtual void FillPreSecBuffer(int aBufferLength, RawBufferPtr aBuffer) =0;

	};

	typedef boost::shared_ptr<ISoftMultiplexer> ISoftMultiplexerPtr;
}
#endif /*ISOFTMULTIPLEXER_H_*/
