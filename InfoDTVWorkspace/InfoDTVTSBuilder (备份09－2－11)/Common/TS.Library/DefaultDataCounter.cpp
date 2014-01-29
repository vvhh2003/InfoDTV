/*
 * DefaultDataCounter.cpp
 *
 *  Created on: 2009-1-10
 *      Author: victor
 */

#include "DefaultDataCounter.h"
namespace TSLibrary
{
	unsigned char DefaultDataCounter::GetNextCounter()
	{
		if (FCounter == 16)
		{
			FCounter = 0;
		}
		return (FCounter++);
	}
}
