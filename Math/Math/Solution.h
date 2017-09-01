#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;


class Solution
{
public:
	/*326. Power of Three
	Given an integer, write a function to determine if it is a power of three.
	Could you do it without using any loop / recursion?*/
	bool isPowerOfThree(int n) 
	{
		return n > 0 && (n == 1 || (n % 3 == 0 && isPowerOfThree(n / 3)));
	}
	bool isPowerOfThreeNB(int n)
	{
		// 1162261467 is 3^19,  3^20 is bigger than int  
		return (n>0 && 1162261467 % n == 0);
	}
	/*231. Power of Two
	Given an integer, write a function to determine if it is a power of two.*/
	bool isPowerOfTwo(int n) 
	{
		return (n > 0) && 0 == (n & (n - 1));
	}
	/*342. Power of Four
	Given an integer (signed 32 bits), write a function to check whether it is a power of 4.*/
	bool isPowerOfFour(int num) 
	{
		return num > 0 && (num & (num - 1)) == 0 && (num - 1) % 3 == 0;
	}
	bool isPowerOfFourNB(int num)
	{
		bool result = false;
		switch (num)
		{
		case 1:
		case 1 << 2:
		case 1 << 4:
		case 1 << 6:
		case 1 << 8:
		case 1 << 10:
		case 1 << 12:
		case 1 << 14:
		case 1 << 16:
		case 1 << 18:
		case 1 << 20:
		case 1 << 22:
		case 1 << 24:
		case 1 << 26:
		case 1 << 28:
		case 1 << 30:
			result = true;
			break;
		default:
			result = false;
			break;
		}
		return result;
	}
	/*645. Set Mismatch
	Given an array nums representing the data status of this set after the error. Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.*/
	vector<int> findErrorNums(vector<int>& nums) 
	{
		int n = nums.size();
		int sum = 0;
		for (int num : nums)
		{
			sum += num;
		}
		for (int i = 1; i < n + 1; ++i)
		{
			sum -= i;
		}
		int d = 0;
		for (int num : nums)
		{
			int idx = abs(num) - 1;
			if (nums[idx] < 0)
			{
				d = idx + 1;
				break;
			}
			else
			{
				nums[idx] = -nums[idx];
			}
		}
		vector<int> result;
		result.emplace_back(d);
		result.emplace_back(d - sum);
		return result;
	}
	/*633. Sum of Square Numbers
	*/
	bool judgeSquareSum(int c) 
	{
		int left = 0;
		int right = (int)sqrt(c);
		while (left <= right)
		{
			int sum = left * left + right * right - c;
			if (sum < 0)
			{
				++left;
			}
			else
			{
				if (sum > 0)
				{
					--right;
				}
				else
				{
					return true;
				}
			}
		}
		return false;
	}
	// TLE
	bool judgeSquareSumHashMap(int c)
	{
		map<int, int> m;
		for (int n = 0; n * n <= c; ++n)
		{
			int a = n * n;
			m[a]++;
			if (m.find(c - a) != end(m))
			{
				return true;
			}
		}
		return false;
	}

	/*400. Nth Digit
	一列按顺序排列的数，找出这个数中出现在第n个位置的数字
	这个狗日的题目base和num如果不用long居然会溢出
	*/
	int findNthDigit(int n) 
	{
		long base = 9;
		int pow = 1;

		// Step 1: find the interval the digit lay in
		while (n > base * pow)
		{
			n -= base * pow;
			base *= 10;
			pow++;
		}

		// Step 2: find the number the digit in
		int idx = n % pow;
		if (idx == 0)
		{
			idx = pow;
		}
		//int num = base / 9 + n / pow;
		long num = 1;
		for (int i = 1; i < pow; i++)
			num *= 10;
		num += (idx == pow) ? n / pow - 1 : n / pow;
		
		// Step 3: find out which digit is what we want
		for (int i = idx; i < pow; ++i)
		{
			num /= 10;
		}
		return num % 10;
	}

	/*279. Perfect Squares
	Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n
	n = 12 = 4 + 4 + 4, return 3; n = 13 = 4 + 9, return 2;
	109 ms*/
	int numSquares(int n) 
	{
		int result = 0;

		vector<int> dp;
		dp.emplace_back(0);
		dp.emplace_back(1);

		for (int i = 2; i < n + 1; ++i)
		{
			dp.emplace_back(i);
			for (int j = 1; j * j <= i; ++j)
			{
				if (j * j == i)
				{
					dp[i] = 1;
					continue;
				}
				dp[i] = min(dp[j * j] + dp[i - j * j], dp[i]);
			}
		}
		result = dp[n];
		return result;
	}
	// 实现有问题
	int numSquaresNB(int n)
	{
		static vector<int> dp({ 0, 1 });
		
		while (dp.size() <= n)
		{
			int m = dp.size();
			int c = m;
			for (int j = 1; j * j <= m; ++j)
			{
				c = min(dp[j * j] + dp[m - j * j], c);
			}
			dp.emplace_back(c);
		}
		return dp[n];
	}

	/*9. Palindrome Number
	Determine whether an integer is a palindrome. Do this without extra space.*/
	bool isPalindrome(int x) 
	{
		if (x < 0 || (x != 0 && x % 10 == 0))
		{
			return false;
		}
		int rev = 0;
		while (x > rev)
		{
			rev = rev * 10 + x % 10;
			x /= 10;
		}
		return x == rev || x == rev / 10;
	}
};

