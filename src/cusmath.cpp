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
float cusInvSqrt(float x) 
{
	float xhalf = 0.5f * x;
        int i = *(int*)&x;            // store floating-point bits in integer
        i = 0x5f3759df - (i >> 1);    // initial guess for Newton's method
        x = *(float*)&i;              // convert new bits into float
        x = x*(1.5f - xhalf*x*x);     // One round of Newton's method
        return x;
}
