#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        int length = nums.size();
        if (0 == length)
        {
            return 0;
        }
        int i = 1;
        int n = 0;
        for (; i != length; ++i)
        {
            if (nums[n] != nums[i])
            {
                nums[++n] = nums[i];
            }
        }
        return n + 1;
    }
    int removeElement(vector<int>& nums, int val)
    {
        for (vector<int>::iterator iter = nums.begin(); iter != nums.end(); ++iter)
        {
            if (val == *iter)
            {
                nums.erase(iter);
                --iter;
            }
        }
        return nums.size();
    }
};

int main()
{
    vector<int> nums = {2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9};
    int val = 3;
    Solution s;
    int l = s.removeDuplicates(nums);
    cout << l << endl;
    return 0;
}

