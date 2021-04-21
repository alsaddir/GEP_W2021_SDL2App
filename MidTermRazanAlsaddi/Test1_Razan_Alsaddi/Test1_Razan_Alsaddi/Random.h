#pragma once
#include <cstdlib>
#include <ctime>
namespace GEP
{
	static bool isFirstTimeSeed = false;
	int RandomRange(int minRange, int maxRange)
	{
		if (!isFirstTimeSeed)
		{
			srand(time(0));
			isFirstTimeSeed = true;
		}
		//returns a random number between minRange and maxRange
		//inclusive.. 
		return (rand() % (maxRange - minRange + 1)) + minRange;
	}
}
