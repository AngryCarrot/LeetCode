#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

void printElement(const set<int> &v);
void printElement(const vector<int> &v);

class Solution {
public:
    /** 238. Product of Array Except Self
     * @brief productExceptSelf:  Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
     * @expire Solve it without division and in O(n).
     * @param nums = [1,2,3,4]
     * @return [24, 12, 8, 6]
     */
    vector<int> productExceptSelf(vector<int>& nums)
    {
        const int length = nums.size();
        vector<int> result;
        result.push_back(1);
        for (int i = 1; i != length; ++i)
        {
            result.push_back(nums[i - 1]);
        }
        int last = 1;
        for (int i = length - 1; i >= 0; --i)
        {
            result[i] *= last;
            last *= nums[i];
        }
        return result;
    }
    /** 53. Maximum Subarray
     * @brief maxSubArray: 最长子序列和
     * @param nums = [-2,1,-3,4,-1,2,1,-5,4]
     * @return sum([4,-1,2,1]) = 5
     * @details 用动态规划的方法，就是要找到其转移方程式，也叫动态规划的递推式，动态规划的解法无非是维护两个变量，局部最优和全局最优，我们先来看Maximum SubArray的情况，如果遇到负数，相加之后的值肯定比原值小，但可能比当前值大，也可能小，所以，对于相加的情况，只要能够处理局部最大和全局最大之间的关系即可，对此，写出转移方程式如下：
     * local[i + 1] = Max(local[i] + A[i], A[i]);
     * global[i + 1] = Max(local[i + 1], global[i]);
     */
    int maxSubArray(vector<int>& nums)
    {
        if (!nums.size())
        {
            return 0;
        }
        const int length = nums.size();
        int maxSum = nums[0];
        int curSum = nums[0];
        for (int i = 1; i != length; ++i)
        {
            curSum = max(curSum + nums[i], nums[i]);
            maxSum = max(curSum, maxSum);
        }
        return maxSum;
    }
    /**  152. Maximum Product Subarray
     * @brief maxProduct
     * @param nums [2,3,-2,4]
     * @return 6
     * @details: 这道题跟 Maximum Subarray 模型上和思路上都比较类似，还是用一维动态规划中的“局部最优和全局最优法”。这里的区别是维护一个局部最优不足以求得后面的全局最优，这是由于乘法的性质不像加法那样，累加结果只要是正的一定是递增，乘法中有可能现在看起来小的一个负数，后面跟另一个负数相乘就会得到最大的乘积。不过事实上也没有麻烦很多，我们只需要在维护一个局部最大的同时，在维护一个局部最小，这样如果下一个元素遇到负数时，就有可能与这个最小相乘得到当前最大的乘积和，这也是利用乘法的性质得到的。
     * 而对于Product Subarray，要考虑到一种特殊情况，即负数和负数相乘：如果前面得到一个较小的负数，和后面一个较大的负数相乘，得到的反而是一个较大的数，如{2，-3，-7}，所以，我们在处理乘法的时候，除了需要维护一个局部最大值，同时还要维护一个局部最小值
     */
    int maxProduct(vector<int>& nums)
    {
        const int length = nums.size();
        int globalMax = nums[0];
        int maxP = nums[0];
        int minP = nums[0];
        int lastMax = maxP;
        for (int i = 1; i != length; ++i)
        {
            lastMax = maxP;
            maxP = max(max(lastMax * nums[i], nums[i]), minP * nums[i]);
            minP = min(min(lastMax * nums[i], nums[i]), minP * nums[i]);
            globalMax = max(maxP, globalMax);
        }
        return globalMax;
    }
    /** 198. House Robber
     * @details
     * @brief rob
     * @param nums
     * @return
     * @expire 可改成O(1)空间复杂度
     */
    int rob(vector<int>& nums)
    {
        const int length = nums.size();
        if (0 == length)
        {
            return 0;
        }
        if (1 == length)
        {
            return nums[0];
        }
        int *result = new int[length];
        result[0] = nums[0];
        result[1] = max(result[0], nums[1]);
        for (int i = 2; i < length; ++i)
        {
            result[i] = max(result[i - 2] + nums[i], result[i - 1]);
        }
        int answer = result[length - 1];
        delete []result;
        return answer;
    }
    /** 213. House Robber II
     * @brief rob2
     * @details arranged in a circle
     * @param nums
     * @return
     * @attention House Robber I的升级版. 因为第一个element 和最后一个element不能同时出现. 则分两次call House Robber
     * I. case 1: 不包括最后一个element.
     *    case 2: 不包括第一个element.
     * II.两者的最大值即为全局最大值
     * @nextpage 337. House Robber III----->在树那里
     */    
    int rob2(vector<int>& nums)
    {
        const int length = nums.size();
        if (0 == length)
        {
            return 0;
        }
        if (1 == length)
        {
            return nums[0];
        }
        int *p = new int[length];
        int *d= new int[length];
        p[0] = nums[0];
        d[0] = 0;
        p[1] = max(p[0], nums[1]);
        d[1] = nums[1];
        for (int i = 2; i < length - 1; ++i)
        {
            p[i] = max(p[i - 2] + nums[i], p[i - 1]);
            d[i] = max(d[i - 2] + nums[i], d[i - 1]);
        }
        p[length - 1] = p[length - 2];
        d[length - 1] = max(d[length - 3] + nums[length - 1], d[length - 2]);
        int answer = max(p[length - 1], d[length - 1]);
        delete []p;
        delete []d;
        return answer;
    }
    /** 27. Remove Element
     * @brief removeElement: Given an array and a value, remove all instances of that value in place and return the new length. Do not allocate extra space for another array, you must do this in place with constant memory. The order of elements can be changed. It doesn't matter what you leave beyond the new length.
     * @param nums
     * @param val
     * @return
     */
    int removeElement(vector<int>& nums, int val)
    {
        if (!nums.size())
        {
            return 0;
        }
        const int length = nums.size();
        int idx = 0;
        for (; idx != length; ++idx)
        {
            if (nums[idx] != val)
            {
                continue;
            }
            else
            {
                for (int post = idx+1; post != length; ++post)
                {
                    if (nums[post] != val)
                    {
                        nums[post] = nums[post] + nums[idx];
                        nums[idx] = nums[post] - nums[idx];
                        nums[post] = nums[post] - nums[idx];
                    }
                }
            }
        }
        for (idx = 0; idx != length; ++idx)
        {
            if (nums[idx] == val)
            {
                break;
            }
        }

        return idx;
    }
    // 283. Move Zeroes
    /* Given an array nums, write a function to move all 0's to the end of it
     * while maintaining the relative order of the non-zero elements.
     * 1. You must do this in-place without making a copy of the array.
     * 2. Minimize the total number of operations.
     * */
    void moveZeroes(vector<int>& nums)
    {
        int64_t length = nums.size();
        if (0 == length || 1 == length)
        {
            return;
        }
        for (int64_t pre = 0; pre < length; ++pre)
        {
            if (nums[pre])
            {
                continue;
            }
            int64_t post = pre + 1;
            for (; post < length; ++post)
            {
                if (nums[post])
                {
                    break;
                }
            }
            if (post < length)
            {
                nums[pre] = nums[post];
                nums[post] = 0;
            }
        }
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

    /** 448. Find All Numbers Disappeared in an Array
     * @expire Time: O(n)
     * @expire Space: O(1)
     * @brief findDisappearedNumbers Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once. Find all the elements of [1, n] inclusive that do not appear in this array.
     * @param nums
     * @return
     * 答案在下面
     */
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
    vector<int> findDisappearedNumbersNB(vector<int> &nums)
    {
        const int length = nums.size();
        int index = 0;
        for (int i = 0; i != length; ++i)
        {
            index = abs(nums[i]) - 1;
            nums[index] = nums[index] > 0 ? -nums[index] : nums[index];
        }
        vector<int> result;
        for (int i = 0; i != length; ++i)
        {
            if (nums[i] > 0)
            {
                result.push_back(i + 1);
            }
        }
        return result;
    }

    /** 442. Find All Duplicates in an Array
     * @brief findDuplicates: Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once. Find all the elements that appear twice in this array.
     * @expire Time: O(n)
     * @expire Space: O(1)
     * @param nums
     * @return
     */
    vector<int> findDuplicates(vector<int>& nums)
    {
        vector<int> result;
        const int length = nums.size();
        int index = 0;
        for (int i = 0; i != length; ++i)
        {
            index = abs(nums[i]) - 1;
            if (nums[index] < 0)
            {
                result.push_back(index + 1);
                continue;
            }
            else
            {
                nums[index] = -nums[index];
            }
        }

        return result;
    }
};

vector<int> getInput(string line);

int main()
{
    cout << "Hello World!" << endl;
    Solution s;
    vector<int> a = {4,3,2,7,8,2,0,3,0,1};
    vector<int> b = {2, 2, 3, 1};
    string line;
    freopen("../input.txt", "r", stdin);
    while (getline(cin, line))
    {
        a = getInput(line);
        cout << s.rob2(a) << endl;
//        printElement(a);
    }

    return 0;
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
