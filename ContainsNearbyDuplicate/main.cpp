#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 219. Contains Duplicate II
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        /*if (nums.empty())
        {
            return false;
        }
        int item = 0;
        map<int, int> m;
        map<int, int>::iterator iter;
        int length = nums.size();
        for (int i = 0; i != length; ++i)
        {
            item = nums[i];
            iter = m.find(item);
            if (iter != m.end() && i - m[i] <= k)
            {
                return true;
            }
//            else
            {
                m[item] = i;
            }
        }
        return false;*/
        map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            if (mp.find(nums[i]) != mp.end() && i - mp[nums[i]] <= k)
                return true;
            mp[nums[i]] = i;
        }
        return false;
    }// Sliding window of size k
};

int main()
{
    cout << "Hello World!" << endl;    
    map<int, int> m;
    m[1] = 2;
    m[2] = 3;
    m[1] = 4;
//    cout << m[1] << endl;
    for (map<int, int>::iterator m1_Iter = m.begin( ); m1_Iter != m.end( ); m1_Iter++ )
    {
        cout << " " << m1_Iter->second;
        cout   << " " << endl;
    }
    vector<int> v  ={1, 2, 1};
    Solution s;
    cout << s.containsNearbyDuplicate(v, 1) << endl;
    return 0;
}

