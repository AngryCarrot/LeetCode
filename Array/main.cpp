#include <iostream>
#include <vector>
#include <set>

#include <algorithm>

#include <cstdlib>
#include <cstring>

using namespace std;

void printElement(const set<int> &v);
void printElement(const vector<int> &v);

class Solution {
public:
    // 283. Move Zeroes
    /* Given an array nums, write a function to move all 0's to the end of it
     * while maintaining the relative order of the non-zero elements.
     * 1. You must do this in-place without making a copy of the array.
     * 2. Minimize the total number of operations.
     * */
    void moveZeroes(vector<int>& nums)
    {
        int length = nums.size();
    }
    // 414. Third Maximum Number
    /*
     * non-empty
     * third distinct
     * better solution is below
     * */
    int thirdMax(vector<int>& nums)
    {
        if (nums.empty())
        {
            return 0;
        }
        if (1 == nums.size())
        {
            return nums[0];
        }
        if (2 == nums.size())
        {
            return nums[0] < nums[1] ? nums[1] : nums[0];
        }
        int result = 0;

        set<int> s(nums.cbegin(), nums.cend());
        printElement(s);
        vector<int> v(s.cbegin(), s.cend());
        if (v.empty())
        {
            return 0;
        }
        if (1 == v.size())
        {
            return v[0];
        }
        if (2 == v.size())
        {
            return v[0] < v[1] ? v[1] : v[0];
        }
        make_heap(v.begin(), v.end());
        pop_heap(v.begin(), v.end());
        pop_heap(v.begin(), v.end()-1);
        result = v[0];

        return result;
    }
    int thirdMaxBetter(vector<int>& nums)
    {
        set<int> top3;
        for (int item : nums)
        {
            top3.insert(item);
            if (3 < top3.size())
            {
                top3.erase(top3.begin());
            }
        }
        return top3.size() == 3 ? *top3.begin() : *top3.rbegin();
    }

    // 448. Find All Numbers Disappeared in an Array
    vector<int> findDisappearedNumbers(vector<int>& nums)
    {
        u_int32_t length = nums.size() + 1;
        int *bulk = new int[length];
        memset(bulk, 0, sizeof(int) * length); // If no initialize, the code would get wrong.
        for (int item : nums)
        {
            ++bulk[item];
        }
        vector<int> result;
        for (u_int32_t i = 1; i != length; ++i)
        {
            if (!bulk[i])
            {
                result.push_back(i);
            }
        }
        delete []bulk;
        return result;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    Solution s;
    vector<int> a = {4,3,2,7,8,2,3,1};
    vector<int> b = {2, 2, 3, 1};
//    vector<int> r = s.findDisappearedNumbers(a);
//    printElement(r);
    cout << s.thirdMax(a) << endl;
    return 0;
}



void printElement(const vector<int> &v)
{
    for (const int item: v)
    {
        cout << item << " ";
    }
    cout << endl;
}

void printElement(const set<int> &v)
{
    for (const int item: v)
    {
        cout << item << " ";
    }
    cout << endl;
}
