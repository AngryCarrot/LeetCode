#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

void printAll(vector<int> &nums)
{
    cout << "---------------------------------------------" << endl;
    for (int i = 0; i != nums.size(); ++i)
    {
        //        cout << setw(3) << i;
    }
    //    cout << endl;
    for (int i = 0; i != nums.size(); ++i)
    {
        cout << setw(3) << nums[i];
    }
    cout << endl;
}

class Solution {
public:
    // 189. Rotate Array
    /* Rotate an array of n elements to the right by k steps.
     * For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
     * ///Try to come up as many solutions as you can, there are at least ***3*** different ways to solve this problem. ///
     * */
    void rotate(vector<int>& nums, int k)
    {
        if (nums.empty() || !k)
        {
            return;
        }
        reverse(nums.begin(), nums.end());
        for (int i = 0; i != k; ++i)
        {
            nums.push_back(nums[0]);
            nums.erase(nums.begin());
        }
        reverse(nums.begin(), nums.end());
    }
    /**
     * @brief rotate2
     * Reverse the first n - k elements, the last k elements, and then all the n elements.
     * Time complexity: O(n). Space complexity: O(1).
     * @param nums
     * @param k
     */
    void rotate2(vector<int>& nums, int k)
    {
        reverse(nums.begin(), nums.end() - k);
        reverse(nums.end() - k, nums.end());
        reverse(nums.begin(), nums.end());
    }
    /**
     * @brief rotate3
     * Reverse the first n - k elements, the last k elements, and then all the n elements.
     * Time complexity: O(n). Space complexity: O(1).
     * @param nums
     * @param k
     */
    void rotate3(vector<int>& nums, int k)
    {
        int n = nums.size();
        if ((n == 0) || (k <= 0))
        {
            return;
        }

        int cntRotated = 0;
        int start = 0;
        int curr = 0;
        int numToBeRotated = nums[0];
        int tmp = 0;
        // Keep rotating the elements until we have rotated n
        // different elements.
        while (cntRotated < n)
        {
            do
            {
                tmp = nums[(curr + k)%n];
                nums[(curr+k)%n] = numToBeRotated;
                numToBeRotated = tmp;
                curr = (curr + k)%n;
                cntRotated++;
                printAll(nums);
            } while (curr != start);
            // Stop rotating the elements when we finish one cycle,
            // i.e., we return to start.

            // Move to next element to start a new cycle.
            start++;
            curr = start;
            numToBeRotated = nums[curr];
        }
    }
    /**
     * @brief rotate4
     * Swap the last k elements with the first k elements.
     * Time complexity: O(n). Space complexity: O(1).
     * @param nums
     */
    void rotate4(vector<int>& nums, int k)
    {
        int n = nums.size();
        //for (; k = k%n; n -= k, n += k)
        {
            // Swap the last k elements with the first k elements.
            // The last k elements will be in the correct positions
            // but we need to rotate the remaining (n - k) elements
            // to the right by k steps.
            for (int i = 0; i < k; i++)
            {
                swap(nums[i], nums[n - k + i]);
            }
        }
    }
};

int main()
{
    cout << "Hello World!" << endl;
    vector<int> s = {1, 2, 3, 4, 5, 6, 7};
    Solution ss;
    ss.rotate3(s, 3);
    for (int i = 0; i != s.size(); ++i)
    {
        cout << s[i] << " " ;
    }
    cout << endl;
    return 0;
}

