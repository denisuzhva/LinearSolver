template <class T1>
T1 cuspower(T1 base, int exp);

// Multipurpose power function
template <class T1>
T1 cuspower(T1 base, int exp)
{
    if (exp > 0)
    {
        for (unsigned i = 0; i <= exp; i++)
        {
            base *= base;
        }
        return base;
    }
    else if (exp = 0)
    {
        base /= base;
        return base;
    }
    else 
    {
        for (unsigned i = 0; i >= exp; i--)
        {
            base /= base;
        }
        return base;
    }
}
