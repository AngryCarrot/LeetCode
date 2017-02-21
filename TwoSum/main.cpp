#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int size = nums.size();
        int *num = new int[size];
        for (int i = 0; i != size; i++)
        {
            num[i] = target - nums[i];
        }
        vector<int> v;
//cout << nums.size() << endl;
        for (int i = 0; i != size; i++)
        {
            v.clear();
            v.push_back(i);
            vector<int>::iterator index = find(nums.begin(), nums.end(), num[i]);
            //cout << *index << endl;
            if (nums.end() != index)
            {
                int idx = std::distance(nums.begin(), index);
                if (i != idx)
                {
                    v.push_back(idx);
                    break;
                }
            }
        }
        delete []num;

        return v;
    }
};

int main()
{
    Solution s;
    vector<int> v;// = [2, 7, 11, 15];
    v.push_back(3);
    v.push_back(2);
    v.push_back(4);
    //v.push_back(15);
    s.twoSum(v, 6);
    return 0;
}

