#include <iostream>
#include <bitset>
#include <vector>

using namespace std;


class Solution {
public:
    // 401. Binary Watch
    vector<string> readBinaryWatch(int num)
    {
    }
    // 191. Number of 1 Bits
    int hammingWeight(uint32_t n)
    {
        /*
         * while (n)
         * {
         *     n &= n - 1;
         *     ++count;
         * }
        */
        bitset<32> b(n);
        return b.count();
    }
    // 461. Hamming Distance
    /*
     * 1   (0 0 0 1)
     * 4   (0 1 0 0)
     *        ↑   ↑
    */
    int hammingDistance(int x, int y)
    {
        if (x == y)
        {
            return 0;
        }
        // Ensure that x is bigger than y
        if (x < y)
        {
            x = x + y;
            y = x - y;
            x = x - y;
        }
        int count = 0;
        int xa = 0, ya = 0;
        while (x)
        {
            xa = x & 1;

            ya = y ? y & 1 : 0;

            if (xa != ya)
            {
                ++count;
            }
            x >>= 1;
            y >>= 1;
        }
        return count;
    }
};
int main()
{
    cout << "Hello World!" << endl;
    Solution s;
    int a = s.hammingWeight(10);
    cout << a << endl;
    return 0;
}

