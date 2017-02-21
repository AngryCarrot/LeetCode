#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        unsigned int bit = 1;
        int count = 0;
        for (int i = 0; i != 32; ++i)
        {
            bit = 1 << i;
            count = 0;
            for (int item : nums)
            {
                if (bit & item)
                {
                    ++count;
                }
            }
            if (count % 3)
            {
                result |= bit;
            }
        }
        return result;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5 ,4, 3, 2, 11, 9, 1};
    Solution s;
    cout << s.singleNumber(nums) << endl;

    return 0;
}

