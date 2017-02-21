#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief majorityElement
     * 169. Majority Element
     * The majority element is the element that appears more than ⌊ n/2 ⌋ times.
     * @param nums
     * @return
     */
    int majorityElement_HashTable(vector<int>& nums)
    {
        int n = nums.size();
        if (1 == n)
        {
            return nums[0];
        }
        map<int, int> m;
        for (vector<int>::const_iterator iter = nums.cbegin(); iter != nums.cend(); ++iter)
        {
            if (m.find(*iter) != m.end())
            {
                ++m[*iter];
                if (m[*iter] >= n / 2)
                {
                    return *iter;
                }
            }
            else
            {
                m[*iter] = 1;
            }
        }
        return 0;
    }
    /**
     * @brief majorityElement_Sorting
     * Since the majority element appears more than n / 2 times,
     * the n / 2-th element in the sorted nums must be the majority element.
     * This can be proved intuitively.
     * Note that the majority element will take more than n / 2 positions in the sorted nums (cover more than half of nums).
     * If the first of it appears in the 0-th position,
     * it will also appear in the n / 2-th position to cover more than half of nums.
     * It is similar if the last of it appears in the n - 1-th position.
     * These two cases are that the contiguous chunk of the majority element is to the leftmost and the rightmost in nums.
     * For other cases (imagine the chunk moves between the left and the right end),
     * it must also appear in the n / 2-th position.
     * @param nums
     * @return
     */
    int majorityElement_Sorting(vector<int>& nums)
    {
        nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
        return nums[nums.size() / 2];
    }
    /**
     * @brief majorityElement_Randomization
     * This is a really nice idea and works pretty well (16ms running time on the OJ,
     * almost fastest among the C++ solutions).
     * The proof is already given in the suggested solutions.
     * @param nums
     * @return
     */
    int majorityElement_Randomization(vector<int>& nums)
    {
        int n = nums.size();
        srand(unsigned(time(NULL)));
        while (true)
        {
            int idx = rand() % n;
            int candidate = nums[idx];
            int counts = 0;
            for (int i = 0; i < n; i++)
                if (nums[i] == candidate)
                    counts++;
            if (counts > n / 2)
                return candidate;
        }
    }
    /**
     * @brief majorityElement
     * A brilliant and easy-to-implement algorithm! It also runs very fast, about 20ms.
     * @param nums
     * @return
     */
    int majorityElement_Moore_Voting_Algorithm(vector<int>& nums)
    {
        int major, counts = 0, n = nums.size();
        for (int i = 0; i < n; i++)
        {
            if (!counts)
            {
                major = nums[i];
                counts = 1;
            }
            else
                counts += (nums[i] == major) ? 1 : -1;
        }
        return major;
    }
    /**
     * @brief majorityElement
     * Another nice idea! The key lies in how to count the number of 1's on a specific bit. Specifically, you need a mask with a 1 on the i-the bit and 0 otherwise to get the i-th bit of each element in nums. The code is as follows.
     * @param nums
     * @return
     */
    int majorityElement(vector<int>& nums)
    {
        int major = 0, n = nums.size();
        for (int i = 0, mask = 1; i < 32; i++, mask <<= 1)
        {
            int bitCounts = 0;
            for (int j = 0; j < n; j++)
            {
                if (nums[j] & mask) bitCounts++;
                if (bitCounts > n / 2)
                {
                    major |= mask;
                    break;
                }
            }
        }
        return major;
    }
    /**
     * @brief majorityElement
     * This idea is very algorithmic.
     * However, the implementation of it requires some careful thought about the base cases of the recursion.
     * The base case is that when the array has only one element, then it is the majority one.
     * This solution takes 24ms.
     * @param nums
     * @return
     */
    int majorityElement_Divide_And_Conquer(vector<int>& nums)
    {
        return majority(nums, 0, nums.size() - 1);
    }
private:
    int majority(vector<int>& nums, int left, int right)
    {
        if (left == right)
            return nums[left];
        int mid = left + ((right - left) >> 1);
        int lm = majority(nums, left, mid);
        int rm = majority(nums, mid + 1, right);
        if (lm == rm)
            return lm;
        return count(nums.begin() + left, nums.begin() + right + 1, lm)
                > count(nums.begin() + left, nums.begin() + right + 1, rm)
                ? lm : rm;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

