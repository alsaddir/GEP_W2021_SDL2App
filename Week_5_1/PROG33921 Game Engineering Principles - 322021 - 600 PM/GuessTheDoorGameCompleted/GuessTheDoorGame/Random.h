#pragma once
#include <cstdlib>
#include <ctime>

namespace GEP
{
	static bool isFirstTimeSeed = false;

 int RandomRange(int minRange, int maxRange)
	{
		//seed only for the first time we call this function
		if (!isFirstTimeSeed)
		{
			srand(time(0));
			isFirstTimeSeed = true;
		}

	return (rand() % (maxRange - minRange + 1)) + minRange;

	}

 //we will come to this later when we explain what static_cast is
 //float RandomRange(float minRange, float maxRange)
 //{
	// if (!isFirstTimeSeed)
	// {
	//	 srand(time(0));
	//	 isFirstTimeSeed = true;
	// }

	//// return ( static_cast<float> (rand())  )

 // }


}


