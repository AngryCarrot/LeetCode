#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 217. Contains Duplicate
    bool containsDuplicate(vector<int>& nums)
    {
        if (nums.empty())
        {
            return false;
        }
        set<int> s;
        set<int>::iterator iter;
        for (int item : nums)
        {
            iter = s.find(item);
            if (iter != s.end())
            {
                return true;
            }
            else
            {
                s.insert(item);
            }
        }
        return false;
    }
    // NB NB的解决方案：直接判断set和vector的长度大小
    bool containsDuplicate_NB(vector<int> &nums)
    {
        if (nums.empty())
        {
            return false;
        }
        return nums.size() > set<int>(nums.begin(), nums.end()).size();
    }
    bool containsDuplicate1(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i=0; i<int(nums.size())-1; i++) {
            if (nums[i]==nums[i+1])
                return true;
        }
        return false;
    }

    bool containsDuplicate2(vector<int>& nums) {
        map<int, bool> myMap;
        // unordered_map<int, bool> myMap;
        for (auto& num: nums) {
            if (myMap.find(num) != myMap.end())
                return true;
            else
                myMap[num] = true;
        }
        return false;
    }

    bool containsDuplicate3(vector<int>& nums) {
        multimap<int, bool> myMap;
        // unordered_multimap<int, bool> myMap;
        for (auto& num: nums) {
            if (myMap.find(num) != myMap.end())
                return true;
            myMap.insert(make_pair(num, true));
        }
        return false;
    }

    bool containsDuplicate4(vector<int>& nums) {
        set<int> mySet;
        // unordered_set<int> mySet;
        // multiset<int> mySet;
        // unordered_multiset<int> mySet;
        for (auto& num: nums) {
            if (mySet.find(num) != mySet.end())
                return true;
            mySet.insert(num);
        }
        return false;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    cout << sizeof(u_int64_t) << endl;

    vector<int> v = {};

    Solution s;
    cout << s.containsDuplicate(v) << endl;

    return 0;
}

