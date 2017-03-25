#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <map>
#include <unordered_map>

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

void printElement(const set<int> &v);
void printElement(const vector<int> &v);

/** 380. Insert Delete GetRandom O(1)
 * @brief The RandomizedSet class
 * @details
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
class RandomizedSet
{
public:
    /** Initialize your data structure here. */
    RandomizedSet()
    {
        srand((unsigned int)time(0));
        container.clear();
        keys.clear();
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        if (container.cend() != container.find(val))
        {
            return false;
        }
        else
        {
            container[val] = val;
            keys.push_back(val);
            return true;
        }
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        map<int, int>::iterator iter = container.find(val);
        if (container.cend() == iter)
        {
            return false;
        }
        else
        {
            container.erase(iter);
            for (vector<int>::iterator iter = keys.begin(); iter != keys.end(); ++iter)
            {
                if (val == *iter)
                {
                    keys.erase(iter);
                    break;
                }
            }
            return true;
        }
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        int length = keys.size();
        if (1 == length)
        {
            return keys[0];
        }

        return keys[rand() % length];
    }
private:
    map<int, int> container;
    vector<int> keys;
};
class RandomizedSetNB {
public:
    unordered_map<int, int >mp;
    vector<int>vc;
    int n;
    /** Initialize your data structure here. */
    RandomizedSetNB() {
        srand(time(NULL));
        n = 0;
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
       if (mp.find(val) == mp.end()) {
            if (n < vc.size()) {
                vc[n] = val;
            } else {
                vc.push_back(val);
            }
            mp[val] = n;
            n++;
            return true;
        }
        return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {

        if (mp.find(val) != mp.end()) {
            vc[mp[val]] = vc[n-1];
            mp[vc[n-1]] = mp[val];
            n--;
            mp.erase(val);
            return true;
        }
        return false;
    }

    /** Get a random element from the set. */
    int getRandom() {
        if (n < 1)
            return 0;
        return vc[rand()%n];
    }
};


class Solution {
public:
    /** 62. Unique Paths
     * @brief uniquePaths
     * @details A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
     * The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below). How many possible unique paths are there?
     * @expire m and n will be at most 100.
     * @param m 3
     * @param n 7
     * @return 28
     */
    int uniquePaths(int m, int n)
    {
        map<pair<int, int>, int> paths;
        int answer = uniquePaths(m, n, paths);
        return answer;
    }
    int uniquePaths(int m, int n, map<pair<int, int>, int>& paths)
    {
        if (1 == m || 1 == n)
        {
            return 1;
        }
        auto iter = paths.find(std::make_pair(m, n));
        if (paths.end() != iter)
        {
            return iter->second;
        }
        else
        {
            int down = this->uniquePaths(m-1, n, paths);
            int right = this->uniquePaths(m, n-1, paths);
            int result = down + right;
            paths[std::make_pair(m, n)] = result;
            return result;
        }
    }
    /** 63. Unique Paths II
     * @brief uniquePathsWithObstacles An obstacle and empty space is marked as 1 and 0 respectively in the grid.
     * @param obstacleGrid
     * @return
     * @pit: [[0,1]]+[[0,0],[1,1],[0,0]]
     */
    // Time Limited Error
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        const int rows = obstacleGrid.size();
        const int cols = obstacleGrid[0].size();
        if (1 == obstacleGrid[rows-1][cols-1])
        {
            return 0;
        }
        int answer = this->uniquePathsWithObstacles(obstacleGrid, 0, rows-1, 0, cols-1);
        return answer;
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid, int top, int bottom, int left, int right)
    {
        if (1 == obstacleGrid[top][left])
        {
            return 0;
        }
        if (top == bottom)
        {
            for (int i = left; i <= right; ++i)
            {
                if (1 == obstacleGrid[top][i])
                {
                    return 0;
                }
            }
            return 1;
        }
        if (left == right)
        {
            for (int i = top; i <= bottom; ++i)
            {
                if (1 == obstacleGrid[i][left])
                {
                    return 0;
                }
            }
            return 1;
        }
        return this->uniquePathsWithObstacles(obstacleGrid, top, bottom, left+1, right)
                + this->uniquePathsWithObstacles(obstacleGrid, top+1, bottom, left, right);
    }
    int uniquePathsWithObstaclesMy(vector<vector<int> > &obstacleGrid)
    {
        const int rows = obstacleGrid.size();
        const int cols = obstacleGrid[0].size();
        if (1 == obstacleGrid[rows-1][cols-1] || 1 == obstacleGrid[0][0])
        {
            return 0;
        }
        vector<int> result(cols, 0);
        result[0] = 1;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (1 == obstacleGrid[i][j])
                {
                    result[j] = 0;
                }
                else
                {
                    if (0 < j)
                    {
                        result[j] = result[j] + result[j-1];
                    }
                }
            }
        }
        return result[cols-1];
    }
    int uniquePathsWithObstaclesNB(vector<vector<int>>& obstacleGrid)
    {
        const int rows = obstacleGrid.size();
        const int cols = obstacleGrid[0].size();
        vector<vector<int> > dp(rows + 1, vector<int> (cols + 1, 0));
        dp[0][1] = 1;
        for (int i = 1; i <= rows; ++i)
        {
            for (int j = 1; j <= cols; ++j)
            {
                if (0 == obstacleGrid[i-1][j-1])
                {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }
        return dp[rows][cols];
    }

    /** 64. Minimum Path Sum
     * @brief minPathSum Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
     * @expire You can only move either down or right at any point in time.
     * @param grid
     * @return
     */
    int minPathSum(vector<vector<int>>& grid)
    {
        const int M = grid.size();
        const int N = grid[0].size();
        vector<int> row(N, 0);
        row[N-1] = grid[M-1][N-1];
        for (int i = N-2; i >= 0; --i)
        {
            row[i] += row[i+1] + grid[M-1][i];
        }
        for (int i = M - 2; i >= 0; --i)
        {
            cout << "I: " << i << " " << endl;
            for (int j = N - 1; j >= 0; --j)
            {
                if (N-1 == j)
                {
                    row[j] = row[j] + grid[i][j];
                }
                else
                {
                    row[j] = min(row[j+1], row[j]) + grid[i][j];
                }
            }
        }
        return row[0];
    }
    int minPathSumNB(vector<vector<int> > &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<int> curV(m+1, INTMAX_MAX);
        curV[0] = 0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                curV[j+1] = grid[j][i]+min(curV[j+1], curV[j]);
                curV[0] = curV[1];
            }
        }
        return curV[m];
    }

    /** 120. Triangle
     * @brief minimumTotal Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
     * @param triangle
     * @example [
                     [2],
                    [3,4],
                   [6,5,7],
                  [4,1,8,3]
                ]
     * @return 11 (2 + 3 + 5 + 1 = 11)
     * Time Limited Error
     */
    int minimumTotal(vector<vector<int>>& triangle)
    {
        const int LEVELS = triangle.size();
        if (1 == LEVELS)
        {
            return triangle[0][0];
        }
        int *p = new int[LEVELS];
        int d = 0;
        int level = 0;
        p[d] = triangle[level][d];

        map<string, int> m;

        int answer = minimumTotalHelper(triangle, level, d, p, LEVELS, m);

        delete []p;
        return answer;
    }
    int minimumTotalHelper(vector<vector<int>>& triangle, int level, int d, int* p, const int LEVELS, map<string, int> m)
    {
        p[level] = triangle[level][d];
        if (LEVELS == level+1)
        {
            return triangle[level][d];
        }
        int left = 0;
        string lkey = to_string(level+1).append(to_string(d));
        auto t = m.find(lkey);
        if (m.end() != t)
        {
            left = t->second;
        }
        else
        {
            left = minimumTotalHelper(triangle, level+1, d, p, LEVELS, m);
            m[lkey] = left;
        }
        int right = 0;
        string rkey = to_string(level+1).append(to_string(d+1));
        t = m.find(rkey);
        if (m.end() != t)
        {
            right = t->second;
        }
        else
        {
            right = minimumTotalHelper(triangle, level+1, d+1, p, LEVELS, m);
            m[rkey] = right;
        }

        if (left < right)
        {
            p[level] += left;
        }
        else
        {
            p[level] += right;
        }
        return p[level];
    }
    int minimumTotalNB(vector<vector<int>>& triangle)
    {
        const int LEVELS = triangle.size();
        if(1 == LEVELS)
        {
            return triangle[0][0];
        }
        int* dp = new int[LEVELS];
        //initial by last row
        for (int i = 0; i < triangle[LEVELS - 1].size(); i++)
        {
            dp[i] = triangle[LEVELS - 1][i];
        }
        // iterate from last second row
        for (int i = LEVELS - 2; i >= 0; i--)
        {
            for (int j = 0; j < triangle[i].size(); j++)
            {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }
        int answer = dp[0];
        delete []dp;
        return answer;
    }

    /** 153. Find Minimum in Rotated Sorted Array
     * @brief findMin
     * @param nums [4 5 6 7 0 1 2]
     * @return 0
     */
    int findMin(vector<int>& nums)
    {
        const int length = nums.size();
        if (nums[0] < nums[length - 1])
        {
            return nums[0];
        }
        int pre = 0;
        int post = length - 1;
        int mid = (pre + post) >> 1;
        while (nums[pre] > nums[post])
        {
            if (pre + 1 == post)
            {
                return nums[post];
            }
            mid = (pre + post) >> 1;
            if (nums[pre] <= nums[mid])
            {
                pre = mid;
            }
            else
            {
                post = mid - 1;
            }
        }
    }
private:
    map<char, vector<string>> keys;
public:
    Solution()
    {
        keys[0] = {};
        keys[1] = {};
        keys[2] = {"a", "b", "c"};
        keys[3] = {"d", "e", "f"};
        keys[4] = {"g", "h", "i"};
        keys[5] = {"j", "k", "l"};
        keys[6] = {"m", "n", "o"};
        keys[7] = {"p", "q", "r", "s"};
        keys[8] = {"u", "v", "w"};
        keys[9] = {"x", "y", "z"};
    }

    /** 17. Letter Combinations of a Phone Number
     * @brief letterCombinations Given a digit string, return all possible letter combinations that the number could represent.
     * @param digits Digit string "23"
     * @return ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
     */
    vector<string> letterCombinations(string digits)
    {
        vector<string> result;
        const int length = digits.size();
        if (0 == length)
        {
            return result;
        }
        if (1 == length)
        {
            result = this->keys[digits[0] - '0'];
            return result;
        }
        string current;
        letterCombinationsHelper(digits, current, result);
        return result;
    }
    void letterCombinationsHelper(string digits, string current, vector<string> &result)
    {
        if (1 == digits.length())
        {
            vector<string> a = this->keys[digits[0] - '0'];
            if (0 == a.size())
            {
                result.push_back(current);
            }
            else
            {
                for (string str : a)
                {
                    string ss = current;
                    ss.append(str);
                    result.push_back(ss);
                }
            }
            return;
        }
        for (string s : this->keys[digits[0] - '0'])
        {
            current.append(s);
            letterCombinationsHelper(digits.substr(1, digits.length()), current, result);
            current.pop_back();
        }
    }

    /** 39. Combination Sum
     * @brief combinationSum
     * @details  Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
     * The same repeated number may be chosen from C unlimited number of times.
     * @param candidates [2, 3, 6, 7]
     * @param target 7
     * @return [  [7],  [2, 2, 3]  ]
     */
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> current;
        this->helper(candidates, target, 0, current, result);
        return result;
    }
    void helper(vector<int> & candidates, int target, int start, vector<int> current, vector<vector<int>> &result)
    {
        if (0 == target)
        {
            result.push_back(current);
            return;
        }
        for (int i = start; i < candidates.size(); ++i)
        {
            if (candidates[i] > target)
            {
                return;
            }
            current.push_back(candidates[i]);
            helper(candidates, target - candidates[i], i, current, result);
            current.pop_back();
        }
    }

    /** 40. Combination Sum II
     * @brief combinationSum2
     * @expire Each number in C may only be used once in the combination.
     * @param candidates
     * @param target
     * @return
     */
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        vector<vector<int>> results;
        vector<int> current;
        sort(candidates.begin(), candidates.end());
        for (int i : candidates)
        {
            cout << i << " ";
        }
        cout << endl;

        helper2(candidates, target, 0, current, results);
        return results;
    }
    void helper2(vector<int> &candidates, int target, int start, vector<int> current, vector<vector<int>> &result)
    {
        if (0 == target)
        {
            result.push_back(current);
            return;
        }
        int cur = 0;
        for (int i = start; i < candidates.size(); ++i)
        {
            cur = candidates[i];
            if (cur > target)
            {
                return;
            }
            current.push_back(cur);
            helper2(candidates, target - cur, i+1, current, result);
            current.pop_back();
            // 避免重复组合
            while (i < candidates.size() && candidates[i+1] == candidates[i])
            {
                ++i;
            }
        }
    }

    /** 216. Combination Sum III +++++++++++++++++++++++++++++++++++++++++++++++++
     * @brief combinationSum3
     * @details Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
     * @param k
     * @param n
     * @return
     */
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<vector<int>> result;
        vector<int> current;
        combinationSum3Helper(k, n, 1, 0, current, result);
        return result;
    }
    void combinationSum3Helper(int k, int n, int level, int sum, vector<int> &current, vector<vector<int>> &result)
    {
        if (sum == n && 0 == k)
        {
            result.push_back(current);
            return;
        }
        else
        {
            if (sum > n || k <= 0)
            {
                return;
            }
        }
        for (int i = level; i < 10; ++i)
        {
            if (sum + i > n)
            {
                return;
            }
            sum += i;
            current.push_back(i);
            combinationSum3Helper(k-1, n, i+1, sum, current, result);
            current.pop_back();
            sum -= i;
        }
    }

    /** 377. Combination Sum IV
     * @brief Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.
     * @param nums = [1, 2, 3]
     * @param target = 4
     * @return 7 = [(1, 1, 1, 1), (1, 1, 2), (1, 2, 1), (1, 3), (2, 1, 1), (2, 2), (3, 1)]
     * @warning TLE
     */
    int combinationSum4(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());
        int count = 0;
        int idx = 0;
        this->combinationSum4Helper(nums, target, count);
        return count;
    }
    void combinationSum4Helper(vector<int> &nums, int target, int &count)
    {
        if (0 == target)
        {
            ++count;
            return;
        }
        for (int i = 0; i < nums.size(); ++i)
        {
            if (target < nums[i])
            {
                return;
            }
            this->combinationSum4Helper(nums, target-nums[i], count);
        }
    }
    int combinationSum4NB(vector<int>& nums, int target)
    {
        vector<int> dp(target + 1);
        dp[0] = 1;
        sort (nums.begin(), nums.end());
        for (int i = 1; i <= target; i++)
        {
            for (auto num : nums)
            {
                if (i < num)
                {
                    break;
                }
                dp[i] += dp[i - num];
            }
        }
        return dp.back();
    }

    /** 77. Combinations
     * @brief Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
     * @details 从1到n的k种组合方式
     * @param n
     * @param k
     * @return
     */
    vector<vector<int>> combine(int n, int k)
    {
            vector<vector<int>> results;
            vector<int> current;
            this->combineHelper(n, k, 1, current, results);
            return results;
    }
    void combineHelper(int n, int k, int start, vector<int> current, vector<vector<int>> &results)
    {
        if (0 == k)
        {
            results.push_back(current);
        }
        for (int i = start; i < n+1; ++i)
        {
            current.push_back(i);
            this->combineHelper(n, k-1, i+1, current, results);
            current.pop_back();
        }
    }

    /** 46. Permutations
     * @brief permute: 求数组的全排列
     * @details  Given a collection of distinct numbers, return all possible permutations.
     * @bold distinct
     * @param nums
     * @return 23ms     NB: 16ms
     */
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> results;
        this->permuteHelper(nums, 0, results);
        return results;
    }
    void permuteHelper(vector<int>& nums, int start, vector<vector<int>>& results)
    {
        if (1 == nums.size() - start)
        {
            vector<int> i;
            i.push_back(nums[start]);
            results.push_back(i);
            return;
        }
        this->permuteHelper(nums, start+1, results);
        for (int i = results.size() - 1; i >= 0; --i)
        {
            vector<int> temp = results.back();
            results.pop_back();
            for (int j = 0; j <= temp.size(); ++j)
            {
                temp.insert(temp.begin() + j, nums[start]);
                results.insert(results.begin(), temp);
                temp.erase(temp.begin() + j);
            }
        }
    }
    vector<vector<int>> permuteNB(vector<int>& nums)
    {
        vector<vector<int>> results;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        this->permuteNBHelper(nums, used, current, results);
        return results;
    }
    void permuteNBHelper(vector<int>& nums, vector<bool> used, vector<int> current, vector<vector<int>>& results)
    {
        if (nums.size() == current.size())
        {
            results.push_back(current);
        }
        for (int i = 0; i < nums.size(); ++i)
        {
            if (!used[i])
            {
                used[i] = true;
                current.push_back(nums[i]);
                this->permuteNBHelper(nums, used, current, results);
                current.pop_back();
                used[i] = false;
            }
        }
    }
    /**
     * @brief permuteNBNB ????????????????????????????
     * @param nums
     * @return
     */
    vector<vector<int>> permuteNBNB(vector<int>& nums)
    {
        vector<vector<int> > ret;
        Helper(ret, num, 0);
        return ret;
    }
    void permuteNBNBHelper(vector<int>& nums, int current, vector<vector<int>>& results)
    {
        if(pos == num.size()-1)
        {
            ret.push_back(num);
        }
        else
        {
            for(int i = pos; i < num.size(); i ++)
            {
                //swap all the ints to the current position
                swap(num[pos], num[i]);
                Helper(ret, num, pos+1);
                swap(num[pos], num[i]);
            }
        }
    }
    /** 47. Permutations II
     * @brief Given a collection of numbers that might contain duplicates, return all possible unique permutations.
     * @param nums
     * @return
     */
    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        vector<vector<int>> results;
        vector<bool> used(nums.size(), false);
        vector<int> current;
        this->permuteUniqueHelper(nums, 0, results, used, current);
        return results;
    }
    void permuteUniqueHelper(vector<int>& nums, int start, vector<vector<int>>& results, vector<bool> &used, vector<int> &current)
    {
        if (current.size() == nums.size())
        {
            results.push_back(current);
            return;
        }
        for (int i = 0; i < nums.size(); ++i)
        {
            if (0 != i && nums[i] == nums[i - 1] && used[i - 1])
            {
                continue;
            }
            if (!used[i])
            {
                current.push_back(nums[i]);
                used[i] = true;
                this->permuteUniqueHelper(nums, i, results, used, current);
                used[i] = false;
                current.pop_back();
            }
        }
    }

    /** 228. Summary Ranges
     * @brief summaryRanges  Given a sorted integer array without duplicates, return the summary of its ranges.
     * @param nums [0,1,2,4,5,7]
     * @return ["0->2","4->5","7"]
     */
    vector<string> summaryRanges(vector<int>& nums)
    {
        const int length = nums.size();
        vector<string> result;
        if (0 == length)
        {
            return result;
        }
        if (1 == length)
        {
            result.push_back(to_string(nums[0]));
            return result;
        }
        int left = 0;
        int i = 1;
        for (; i < length; ++i)
        {
            if (nums[i] != nums[i - 1] + 1)
            {
                string s = "";
                s += to_string(nums[left]);
                if (nums[left] != nums[i - 1])
                {
                    s += "->";
                    s += to_string(nums[i - 1]);
                }
                result.push_back(s);
                left = i;
            }
        }
        if (length == i)
        {
            string s = "";
            s += to_string(nums[left]);
            if (nums[left] != nums[i - 1])
            {
                s += "->";
                s += to_string(nums[i - 1]);
            }
            result.push_back(s);
        }
        return result;
    }
    /** 169. Majority Element
     * @brief majorityElement
     * @param num
     * @return
     */
    int majorityElement(vector<int> &num)
    {
        int curIdx = 0, count = 1;
        for (int i = 1; i < num.size(); ++i)
        {
            num[i] == num[curIdx] ? ++count : --count;
            if (!count)
            {
                curIdx = i;
                count = 1;
            }
        }

        return num[curIdx];
    }
    /** 229. Majority Element II
     * @brief majorityElement Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
     * @expire Time: O(n), Space: O(1)
     * @param nums
     * @return
     * @warning 要找出的是出现次数大于⌊ n/3 ⌋的元素，因此最多只可能存在两个这样的元素，而且要求O(1)的空间复杂度，因此只能使用摩尔投票法。首先我们遍历一遍数组找出两个候选元素，接着再遍历一遍数组，判断候选元素的出现次数是否超过三分之一即可。我们如何确定两个候选元素呢？当有候选元素未设置时，先将当前遍历到的元素设置为候选元素。若遍历到的元素和其中一个候选元素相等时，候选元素的计数器加一，若和两个候选元素都不相等，则两个候选元素的计数器都减一。
其实摩尔投票法的本质就是将元素进行分组，每组中都是不同的元素，最后剩下的那些元素就可能是出现次数最多的元素。例如上文中的解法就是将所有元素分成若干个三元组，每组中的数字都是各不相同的。如果一个元素出现的次数超过了三分之一，那么它必然在剩下的元组中存在，因此它能成为候选元素。
     */
    vector<int> majorityElement2(vector<int>& nums)
    {
        const int length = nums.size();
        vector<int> result;
        if (0 == length)
        {
            return result;
        }
        if (0 == length)
        {
            result.push_back(nums[0]);
            return result;
        }
        if (2 == length)
        {
            if (nums[0] == nums[1])
            {
                result.push_back(nums[0]);
                return result;
            }
            return nums;
        }
        int n1 = nums[0];
        int c1 = 0;
        int n2 = nums[1];
        int c2 = 0;
        for (int num : nums)
        {
            if (num == n1)
            {
                ++c1;
                continue;
            }
            if (num == n2)
            {
                ++c2;
                continue;
            }
            if (c1 == 0)
            {
                n1 = num;
                ++c1;
            }
            else
            {
                if (c2 == 0)
                {
                    n2 = num;
                    ++c2;
                }
                else
                {
                    --c1;
                    --c2;
                }
            }
        }
        c1 = c2 = 0;
        for (int item : nums)
        {
            if (n1 == item)
            {
                ++c1;
            }
            else
            {
                if (n2 == item)
                {
                    ++c2;
                }
            }
        }
        if (c1 > length / 3)
        {
            result.push_back(n1);
        }
        if (c2 > length / 3)
        {
            result.push_back(n2);
        }
        return result;
    }
    /** 287. Find the Duplicate Number
     * @brief findDuplicate
     * @details Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.
     * @expire  You must not modify the array (assume the array is read only).===>No sort
     *          You must use only constant, O(1) extra space.===>No hash
     *          Your runtime complexity should be less than O(n2).===>No brute force
     *          There is only one duplicate number in the array, but it could be repeated more than once.
     * @param nums
     * @return
     */
    int findDuplicate(vector<int>& nums)
    {
        const int length = nums.size();
        int count = 0;
        int n = length - 1;
        int mid = 0;
        int left = 1;
        int right = n;
        while (left < right)
        {
            count = 0;
            mid = (left + right) >> 1;
            for (int i = 0; i < length; ++i)
            {
                if (left <= nums[i] && nums[i] <= mid)
                {
                    ++count;
                }
            }
            if (count + left <= mid + 1)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return left;
    }
    /** 15. 3Sum
     * @brief threeSum
     * @details Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
     * @param nums
     * @return
     */
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        const int length = nums.size();
        sort(nums.begin(), nums.end());
        int i = 0;
        int last = length - 1;
        vector<vector<int>> result;
        while (i < last)
        {
            int a = nums[i];
            int j = i + 1;
            int k = last;
            while (j < last)
            {
                int b = nums[j];
                int c = nums[k];
                int sum = a + b + c;
                if (0 == sum)
                {
                    result.push_back({a, b, c});
                }
                if (0 >= sum)
                {
                    while (nums[j] == b && j < k)
                    {
                        ++j;
                    }
                }
                if (0 <= sum)
                {
                    while (nums[k] == c && j < k)
                    {
                        --k;
                    }
                }
            }
            while (nums[i] == 1 && i < last)
            {
                ++i;
            }
        }
        return result;
    }
    vector<vector<int>> threeSumNB(vector<int>& nums)
    {
        vector<vector<int>> triples;
        sort(nums.begin(), nums.end());
        int i = 0, last = nums.size() - 1;
        while (i < last)
        {
            int a = nums[i], j = i+1, k = last;
            while (j < k)
            {
                int b = nums[j], c = nums[k], sum = a + b + c;
                if (sum == 0)
                {
                    triples.push_back({a, b, c});
                }
                if (sum <= 0)
                {
                    while (nums[j] == b && j < k)
                    {
                        j++;
                    }
                }
                if (sum >= 0)
                {
                    while (nums[k] == c && j < k)
                    {
                        k--;
                    }
                }
            }
            while (nums[i] == a && i < last)
            {
                i++;
            }
        }
        return triples;
    }
    /** 81. Search in Rotated Sorted Array II
     * @brief search2 What if duplicates are allowed?
     * @param nums
     * @param target
     * @return
     */
    bool search2(vector<int>& nums, int target)
    {
    }
    /** 33. Search in Rotated Sorted Array
     * @brief search
     * @param nums
     * @param target
     * @return
     */
    int search(vector<int>& nums, int target)
    {
        const int length = nums.size();
        if (!length)
        {
            return -1;
        }
        if (nums[0] < nums[length - 1])
        {
            return this->biSearch(nums, 0, length - 1, target);
        }
        int midIndex = this->sf(nums);
        if (nums[midIndex] >= target)
        {
            if (nums[0] < target)
            {
                return this->biSearch(nums, 0, midIndex, target);
            }
            else
            {
                return this->biSearch(nums, midIndex + 1, length - 1, target);
            }
        }
        else
        {
            return -1;
        }
    }
    int sf(vector<int> nums)
    {
        const int length = nums.size();
        int pre = 0;
        int post = length - 1;
        int mid = 0;
        while (nums[pre] > nums[post])
        {
            if (pre + 1 == post)
            {
                return pre;
            }
            mid = (pre + post) / 2;
            if (nums[mid] >= nums[pre])
            {
                pre = mid;
            }
            else
            {
                if (nums[mid] <= nums[post])
                {
                    post = mid;
                }
            }
        }
    }

    int biSearch(vector<int> nums, int left, int right, int target)
    {
        int pre = left;
        int mid = (left + right) / 2;
        int post = right;
        while (pre <= post)
        {
            mid = (pre + post) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            if (nums[mid] < target)
            {
                pre = mid + 1;
            }
            else
            {
                post = mid - 1;
            }
        }
        return -1;
    }

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
    vector<int> c = {1, 2, 3};
    int aa = 0;
    string line;
    freopen("../input.txt", "r", stdin);
    while (getline(cin, line))
    {
        a = getInput(line);
        cin >> aa;
        s.permute(c);
//        cout << s.combinationSum2(a, aa) << endl;
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
