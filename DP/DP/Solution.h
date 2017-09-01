#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


// Definition for a binary tree node.
struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution
{
public:
	/*70. Climbing Stairs
	You are climbing a stair case. It takes n steps to reach to the top.
	Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?*/
	int climbStairs(int n)
	{
	}

	/*413. Arithmetic Slices
	A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
	*/
	int numberOfArithmeticSlices(vector<int>& A) 
	{
	}

	/*343. Integer Break
	Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.
	*/
	int integerBreak(int n) 
	{
		if (n == 2)
		{
			return 1;
		}
		if (n == 3)
		{
			return 2;
		}
		int product = 1;
		while (n > 4)
		{
			n -= 3;
			product *= 3;
		}
		product *= n;
		return product;
	}

	/*647. Palindromic Substrings 回文子串
	Given a string, your task is to count how many palindromic substrings in this string.
	The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.*/
	int countSubstrings(string s) 
	{
		int length = s.length();
		if (length == 0)
		{
			return 0;
		}
		int count = 0;
		for (int i = 0; i < length; ++i)
		{
			countSubstringsHelper(s, i, i, count);
			countSubstringsHelper(s, i, i + 1, count);
		}
		return count;
	}
	int countSubstringsHelper(string& s, int i, int j, int& count)
	{
		while (i >= 0 && j < s.length() && s[i] == s[j])
		{
			++count;
			--i;
			++j;
		}
		return 0;
	}

	/*646. Maximum Length of Pair Chain
	You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.
	Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.
	Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given pairs. You can select pairs in any order.*/
	int findLongestChain(vector<vector<int>>& pairs) 
	{
		int length = pairs.size();
		if (length <= 1)
		{
			return length;
		}
		sort(begin(pairs), end(pairs), 
			[](vector<int>& a, vector<int>& b) 
			{
				return a[1] < b[1] || a[1] == b[1] && a[0] < b[0]; 
			});
		vector<int> dp(length, 1);
		for (int i = 1; i < length; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				dp[i] = max(dp[i], pairs[j][1] < pairs[i][0] ? dp[j] + 1 : dp[j]);
			}
		}
		return dp[length - 1];
	}

	/*91. Decode Ways
	A message containing letters from A-Z is being encoded to numbers using the following mapping:
	'A' -> 1
	'B' -> 2
	...
	'Z' -> 26
	Given an encoded message containing digits, determine the total number of ways to decode it.*/
	int numDecodings(string s) 
	{
		int length = s.length();
		if (length < 1) // 这里如果是<=，则“0”用例错误
		{
			return length;
		}
		vector<int> dp(length + 1, 0);
		dp[0] = 1;
		dp[1] = s[0] != '0' ? 1 : 0;

		for (int i = 2; i <= length; ++i)
		{
			int a = atoi(s.substr(i - 1, 1).c_str());
			int b = atoi(s.substr(i - 2, 2).c_str());
			if (1 <= a && a <= 9)
			{
				dp[i] += dp[i - 1];
			}
			if (10 <= b && b <= 26)
			{
				dp[i] += dp[i - 2];
			}
		}
		return dp[length];
	}

	/*96. Unique Binary Search Trees
	Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
	*/
	int numTrees(int n) 
	{
		vector<int> dp(n + 1, 0);
		dp[0] = 1;
		dp[1] = 1;
		for (int i = 2; i <= n; ++i)
		{
			for (int j = 1; j <= i; ++j)
			{
				dp[i] += dp[j - 1] * dp[i - j];
			}
		}
		return dp[n];
	}

	/*95. Unique Binary Search Trees II
	Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.
	*/
	vector<TreeNode*> generateTrees(int n) 
	{
	}

	/*516. Longest Palindromic Subsequence
	*/
	int longestPalindromeSubseq(string s) 
	{
	}

	/*494. Target Sum
	You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol
	Find out how many ways to assign symbols to make sum of integers equal to target S.
	*/
	int findTargetSumWays(vector<int>& nums, int S)
	{
		int length = nums.size();
		int result = 0;
		int current = 0;
		findTargetSumWaysHelper(nums, S, 0, current, result);
		return result;
	}
	int findTargetSumWaysHelper(vector<int>& nums, int S, int left, int current, int& result)
	{
		if (left + 1 == nums.size())
		{
			result += S == 0;
			return 0;
		}
		findTargetSumWaysHelper(nums, S - nums[left], left + 1, current, result);
		findTargetSumWaysHelper(nums, S + nums[left], left + 1, current, result);
		return 0;
	}
	int findTargetSumWaysNB(vector<int>& nums, int S)
	{
	}

	/* 	322	Coin Change
	You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.*/
	int coinChange(vector<int>& coins, int amount)
	{
	}

	/*357. Count Numbers with Unique Digits
	Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n.
	最后有个+1是因为dp[0] = 10而不是9，写9是为了方便计算*/
	int countNumbersWithUniqueDigits(int n)
	{
		if (n == 0)
		{
			return 1;
		}
		int length = min(10, n);
		vector<int> dp(length + 1, 0);
		dp[1] = 9;
		int result = 9;
		int base = 9;
		for (int i = 2; i <= length; ++i)
		{
			dp[i] = dp[i - 1] * base--;
		}
		result = accumulate(begin(dp), end(dp), 0);
		return result + 1;
	}

	/*338. Counting Bits
	Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.
	踏马的位运算不加括号居然还报错*/
	vector<int> countBits(int num)
	{
		vector<int> dp(num + 1, 0);
		for (int i = 1; i <= num; ++i)
		{
			dp[i] = dp[i >> 1] + (i & 1);
		}
		return dp;
	}
};


/** 303. Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
* Your NumArray object will be instantiated and called as such:
* NumArray obj = new NumArray(nums);
* int param_1 = obj.sumRange(i,j);
*/
class NumArray {
public:
	NumArray(vector<int> nums) {
		int length = nums.size();
		int sum = 0;
		for (int num : nums)
		{
			sum += num;
			sums.emplace_back(sum);
		}
	}

	int sumRange(int i, int j) {
		if (i == 0)
		{
			return sums[j];
		}
		return sums[j] - sums[i - 1];
	}
private:
	vector<int> sums;
};

