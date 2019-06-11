#include "../include/cusmath.h"



// Multipurpose power function
template <class T1>
T1 power(T1 &base, int exp)
{
    T1 result = base;
    if (exp > 0)
    {
        for (unsigned i = 0; i <= exp; i++)
        {
            result *= result;
        }
        return result;
    }
    else if (exp = 0)
    {
        result /= result;
        return result;
    }
    else 
    {
        for (unsigned i = 0; i >= exp; i--)
        {
            result /= result;
        }
        return result;
    }
}