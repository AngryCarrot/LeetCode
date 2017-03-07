#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

#include <cstdio>

using namespace std;

void printVector(vector<int> v);

class Solution {
public:
    /** 349. Intersection of Two Arrays
     * @brief intersection Given two arrays, write a function to compute their intersection.
     * @param nums1 = [1, 2, 2, 1]
     * @param nums2 = [2, 2]
     * @return [2]
     * STL set implemetation: 19ms
     */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        set<int> result;
        if (!nums1.size() || !nums2.size())
        {
            vector<int> r;
            return r;
        }
        set<int> s1(nums1.begin(), nums1.end());
        for (int i : nums2)
        {
            if (s1.count(i))
            {
                result.insert(i);
            }
        }
        vector<int> r(result.begin(), result.end());
        return r;
    }
    /**
     * @brief intersection2
     * @param nums1
     * @param nums2
     * @return
     * 排序方法实现:9ms
     */
    vector<int> intersection2(vector<int>& nums1, vector<int>& nums2)
    {
        vector<int> result;
        if (!nums1.size() || !nums2.size())
        {
            return result;
        }

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int len1 = nums1.size();
        int len2 = nums2.size();
        for (unsigned int idx1 = 0, idx2 = 0; idx1 != len1 && idx2 != len2;)
        {
            if (nums1[idx1] < nums2[idx2])
            {
                ++idx1;
            }
            else
            {
                if (nums1[idx1] > nums2[idx2])
                {
                    ++idx2;
                }
                else
                {
                    result.push_back(nums1[idx1]);
                    ++idx1;
                    ++idx2;
                }
            }
        }

        set<int> s(result.begin(), result.end());

        return vector<int>(s.begin(), s.end());
    }

    /** 350. Intersection of Two Arrays II
     * @brief intersect
     * @param nums1 = [1, 2, 2, 1]
     * @param nums2 = [2, 2]
     * @return [2, 2]
     */
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
    {
        vector<int> result;
        if (!nums1.size() || !nums2.size())
        {
            return result;
        }

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int len1 = nums1.size();
        int len2 = nums2.size();
        for (unsigned int idx1 = 0, idx2 = 0; idx1 != len1 && idx2 != len2;)
        {
            if (nums1[idx1] < nums2[idx2])
            {
                ++idx1;
            }
            else
            {
                if (nums1[idx1] > nums2[idx2])
                {
                    ++idx2;
                }
                else
                {
                    result.push_back(nums1[idx1]);
                    ++idx1;
                    ++idx2;
                }
            }
        }
        return result;
    }
};

vector<int> getInput(string line);

int main(int argc, char *argv[])
{
    Solution s;
    cout << "Hello World!" << endl;
    string line;
    freopen("../input.txt", "r", stdin);
    while (getline(cin, line))
    {
//        cout << line << endl;
        vector<int> nums1 = getInput(line);
//        printVector(nums1);
        getline(cin, line);
        vector<int> nums2 = getInput(line);
//        printVector(nums2);
        printVector(s.intersection2(nums1, nums2));
    }
    return 0;
}

void printVector(vector<int> v)
{
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

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
