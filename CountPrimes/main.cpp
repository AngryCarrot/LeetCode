#include <iostream>
#include <cmath>
//#include <cstdlib>

using namespace std;

class Solution {
public:
    // 204. Count Primes
    int countPrimes(int n)
    {
        if (n <= 2)
        {
            return 0;
        }
        u_int64_t count = 0;
        u_int64_t length = n / 2 + 1;
        bool *result = new bool[length];
        if (!result)
        {
            cout << "Allocate failed!" << endl;
            return -1;
        }
        for (u_int64_t i = 0; i != length; ++i)
        {
            result[i] = true;
        }
        for (u_int64_t i = 0; i != length; ++i)
        {
            if (result[i])
            {
                u_int64_t j = i * (2 * i + 6) + 3;
                for (; j < length; j += 2 * i + 3)
                {
                    result[j] = false;
                }
            }
        }
        for (u_int64_t i = 0; 2 * i + 3 < n; ++i)
        {
            if (result[i])
            {
                count++;
                if (i < 100)
                {
                    cout << 2 * i + 3 << endl;
                }
            }
        }
        delete []result;
        return count+1;
    }
    int countPrimes2(int n)
    {
        if (n <= 2)
            return 0;
        int res=n>>1, m=sqrt(n-1); // intilize res to n/2, removes all even number(not 2) and 1
        bool *table=new bool[n];
        for(int i=3,j,step;i<=m;i+=2)
        {
            if(!table[i])
            { // i is an odd prime
                for(step=i<<1, j=i*i; j<n; j+=step) // step=i*2, ignore even numbers
                {
                    if(!table[j])
                    {
                        table[j]=1;
                        --res;
                    }
                }
            }
        }
        delete []table;
        return res;
    }
};
int main()
{
    cout << "Hello World!" << endl;
    Solution s;
    cout << s.countPrimes(4) << endl;
    return 0;
}

