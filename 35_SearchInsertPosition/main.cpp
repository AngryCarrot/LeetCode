#include <iostream>
#include <sstream>
#include <vector>

#include <cstdio>

using namespace std;


class Solution {
public:
    /** 35. Search Insert Position
     * @brief searchInsert: Assume no duplicates in the array.
     * @param nums = [1,3,5,6]
     * @param target = 5
     * @return 2 (from 0 index)
     * 坑：[1] 0, [1] 2
     */
    int searchInsert(vector<int>& nums, int target)
    {
        if (!nums.size())
        {
            return 0;
        }
        return binarySearch(nums, 0, nums.size() - 1, target);
    }
    int binarySearch(vector<int> &nums, int left, int right, const int target)
    {
        if (left > right)
        {
            return -1;
        }
        int mid = (left + right) >> 1;

        if (target > nums[mid])
        {
            if (nums.size() == mid+1)
            {
                return mid+1;
            }
            if (target <= nums[mid + 1])
            {
                return mid+1;
            }
            return binarySearch(nums, mid+1, right, target);
        }
        else
        {
            if (target < nums[mid])
            {
                if (0 == mid)
                {
                    return mid;
                }
                if (target > nums[mid - 1])
                {
                    return mid;
                }
                return binarySearch(nums, left, mid-1, target);
            }
            else
            {
                return mid;
            }
        }
    }
    int searchInsertNB(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right)
        {
            int mid = (left + right) >> 1;

            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return left;
    }
};

vector<int> getInput(string line)
{
    string buf;
    stringstream ss;
    ss << line;
    vector<int> nums1;
    while (ss >> buf)
    {
        nums1.push_back(atoi(buf.c_str()));
    }
    return nums1;
}

int main(int argc, char *argv[])
{
    Solution s;
    string line;
    int target = 0;
    freopen("../input.txt", "r", stdin);
    while (getline(cin, line))
    {
        vector<int> nums1 = getInput(line);
        getline(cin, line);
        target = atoi(line.c_str());
        cout << s.searchInsertNB(nums1, target) << endl;
    }
    return 0;
}
