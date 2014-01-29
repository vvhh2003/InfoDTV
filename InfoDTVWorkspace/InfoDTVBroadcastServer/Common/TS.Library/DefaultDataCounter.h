/*
 * DONE!
 */
#ifndef DEFAULTDATACOUNTER_H_
#define DEFAULTDATACOUNTER_H_
#include "MPEGInterface.h"
#include <map>


namespace TSLibrary
{
	class DefaultDataCounter:public ITSDataCounter
	{

		private:
		int FCounter;

		/// <summary>
		/// 取得计数器当前数值
		/// </summary>
		/// <returns>计数器当前数值</returns>
		public:
		DefaultDataCounter():FCounter(0)
		{

		}
		virtual unsigned char GetNextCounter();
	};

	typedef boost::shared_ptr<DefaultDataCounter> DefaultDataCounterPtr;
	typedef std::map<int,DefaultDataCounterPtr> PIDDataCounterPtrMaps;
}

#endif /*DEFAULTDATACOUNTER_H_*/
