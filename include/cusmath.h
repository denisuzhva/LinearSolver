// Multipurpose power function
template <class T>
T cuspower(T base, int exp)
{
	T result = base;
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
