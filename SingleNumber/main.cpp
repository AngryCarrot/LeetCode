#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = nums[0];
        for (auto item : nums)
        {
            result ^= item;
        }
        result ^= nums[0];
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

