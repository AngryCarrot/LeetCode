#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    // 283. Move Zeroes
    /*
     * You must do this in-place without making a copy of the array.
     * Minimize the total number of operations.
     * */
    void moveZeroes(vector<int>& nums)
    {
        int length = nums.size();
        int tmp = 0;
        for (int i = 0; i < length; ++i)
        {
            if (nums[i])
            {
                continue;
            }
            else
            {
                int j = i + 1;
                for (; j < length; ++j)
                {
                    if (nums[j])
                    {
                        break;
                    }
                }
                if (j < length)
                {
                    nums[i] = nums[j];
                    nums[j] = 0;
                }
            }
        }
    }
    // Better solution
    void moveZeroes(vector<int>& nums)
    {
        int len = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] != 0)
            {
                if (nums[len] != nums[i])
                {
                    swap(nums[len], nums[i]);
                }
                ++len;
            }
        }
    }
};
void printAll(vector<int> v)
{
    int length = v.size();
    for (int i = 0; i != length; ++i)
    {
        cout << std::setw(3) << i;
    }
    cout << endl;
    for (int i = 0; i != length; ++i)
    {
        cout << std::setw(3) << v[i];
    }
    cout << endl << "---------------------------------" << endl;
}

int main()
{
    cout << "Hello World!" << endl;
    srand(0);
    vector<int> v = {4,2,4,0,0,3,0,5,1,0};
    for (int i = 0; i != 10; ++i)
    {
//        v.push_back(rand() % 5);
    }
    Solution s;
    printAll(v);
    s.moveZeroes(v);
    printAll(v);

    return 0;
}

