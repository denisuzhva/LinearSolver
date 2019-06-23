#include "../include/cusmath.h"



// Multipurpose power function
float cusPower(const float& base, const int& exp)
{
	float result = base;
	if (exp > 0)
	{
		for (unsigned i = 0; i < exp-1; i++)
        	{
			//std::cout << "Result: " << result << std::endl;
        		result *= base;
        	}
	        return result;
    	}
	else 
	{
		for (unsigned i = 0; i < -exp+1; i++)
		{
			result /= base;
		}
		return result;
	}
}


// Fast inverse square root of a number
float cusInvSqrt(const float& base) 
{
	long i;
	float x2, y;
	const float threehalfs = 1.5f;
	x2 = base * 0.5f;
	y  = base;
	i  = *(long*)&y;
	i  = 0x5f3759df - (i >> 1);
	y  = *(float*)&i;
	y  = y * (threehalfs - (x2 * y * y));
//	y  = y * (threehalfs - (x2 * y * y));
	return y;
}
