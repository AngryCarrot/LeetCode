#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


class Solution
{
public:
	/*14. Longest Common Prefix
	求最长公共前缀
	*/
	string longestCommonPrefix(vector<string>& strs) 
	{
		string prefix = "";
		int length = strs.size();
		if (length == 0)
		{
			return prefix;
		}

		for (int i = 0; i < strs[0].size(); i++)
		{
			for (int j = 1; j < length; j++)
			{
				if (strs[0][i] != strs[j][i])
				{
					return prefix;
				}
			}
			prefix += strs[0][i];
		}

		return prefix;
	}
	/*125. Valid Palindrome
	判断是否回文
	*/
	bool isPalindrome(string s) 
	{
		int left = 0;
		int right = s.length() - 1;
		while (left < right)
		{
			if (!isalnum(s[left]))
			{
				++left;
			}
			else
			{
				if (!isalnum(s[right]))
				{
					--right;
				}
				else
				{
					if (tolower(s[left++]) != tolower(s[right--]))
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	/*583. Delete Operation for Two Strings
	Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.
	*/
	int minDistance(string& word1, string& word2) 
	{
		int result = 0;
		int length1 = word1.length();
		int length2 = word2.length();
		if (length1 == 0)
		{
			return length2;
		}
		if (length2 == 0)
		{
			return length1;
		}

		vector<vector<int>> dp(length1 + 1, vector<int>(length2 + 1, 0));
		for (int i = 1; i <= length1; ++i)
		{
			for (int j = 1; j <= length2; ++j)
			{
				if (word1[i-1] == word2[j-1])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else
				{
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		result = length1 + length2 - (dp[length1][length2] << 1);
		return result;
	}
	/*553. Optimal Division
	Given a list of positive integers, the adjacent integers will perform the float division. For example, [2,3,4] -> 2 / 3 / 4.
	求结果最大的加括号方式
	*/
	string optimalDivision(vector<int>& nums) 
	{
		int length = nums.size();
		if (length == 1)
		{
			return to_string(nums[0]);
		}
		if (length == 2)
		{
			return to_string(nums[0]) + "/" + to_string(nums[1]);
		}
		string result;
		result = to_string(nums[0]) + "/(" + to_string(nums[1]);
		for (int i = 2; i < nums.size(); ++i)
		{
			result += "/" + to_string(nums[i]);
		}
		result += ")";
		return result;
	}
	/*541. Reverse String II
	字符串s的[0,k)个元素翻转，第[k, 2k)保持不变，[2k, 3k-1)翻转......即每隔k个翻转一次
	*/
	string reverseStr(string& s, int k) 
	{
		int length = s.length();
		if (length <= k)
		{
			reverse(begin(s), end(s));
			return s;
		}
		
		int nums = length % (2 * k) == 0 ? length / (2 * k) : length / (2 * k) + 1;
		for (int i = 0; i < nums; ++i)
		{
			int left = i * k * 2;
			int right = min(length - 1, left + k - 1);
			while (left < right)
			{
				swap(s[left], s[right]);
				++left;
				--right;
			}
		}
		return s;
	}
	/*557. Reverse Words in a String III
	Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
	*/
	string reverseWords(string& s) 
	{
		int idx = s.find(' ');
		if (idx == -1)
		{
			reverse(begin(s), end(s));
			return s;
		}
		idx = 0;
		int left_prev = 0;		
		int left = 0;
		int right = 0;
		while ((idx = s.find(' ', left_prev)) != -1)
		{
			left = left_prev;
			right = idx - 1;
			left_prev = idx + 1;
			while (left < right)
			{
				swap(s[left], s[right]);
				++left;
				--right;
			}
		}
		reverse(begin(s) + s.find_last_of(' ') + 1, end(s));
		return s;
	}

	/*521. Longest Uncommon Subsequence I
	Given a group of two strings, you need to find the longest uncommon subsequence of this group of two strings. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.
	A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.
	The input will be two strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.
	最长非公共子序列，注意子序列与子串的区别
	最长非公共子序列：这些字符串之一的最长子序列，且该子序列不应该是其他字符串的任一子序列
	*/
	int findLUSlength(string a, string b) 
	{
		int al = a.length();
		int bl = b.length();
		if (al != bl)
		{
			return max(al, bl);
		}
		else
		{
			return a == b ? -1 : al;
		}
	} 
	/* 522. Longest Uncommon Subsequence II
	Given a list of strings, you need to find the longest uncommon subsequence among them. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.
	A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.
	The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.
	*/
	int findLUSlength2(vector<string>& strs) 
	{
		int result = -1;
		int length = strs.size();
		for (int i = 0; i < length; i++)
		{
			int j = 0;
			for (j = 0; j < length; j++)
			{
				if (i == j)
				{
					continue;
				}
				if (checkSubSeq(strs[i], strs[j]))
				{
					break;
				}
			}
			if (j == length)
			{
				result = max(result, (int)strs[i].length());
			}
		}
		return result;
	}
	bool checkSubSeq(string& a, string& b)
	{
		int i = 0;
		for (char& c : b)
		{
			if (c == a[i])
			{
				++i;
			}
			if (i == a.size())
			{
				break;
			}
		}
		return i == a.size();
	}
	/*72. Edit Distance
	Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
	a) Insert a character
	b) Delete a character
	c) Replace a character
	*/
	int editDistance(string word1, string word2)
	{
		int m = word1.length(), n = word2.length();
		vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
		for (int i = 1; i <= m; i++)
		{
			dp[i][0] = i;
		}
		for (int j = 1; j <= n; j++)
		{
			dp[0][j] = j;
		}
		for (int i = 1; i <= m; i++) 
		{
			for (int j = 1; j <= n; j++) 
			{
				if (word1[i - 1] == word2[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1];
				}
				else
				{
					dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
				}
			}
		}
		return dp[m][n];
	}
	/*468. Validate IP Address
	Write a function to check whether an input string is a valid IPv4 address or IPv6 address or neither.
	*/
	string validIPAddress(string IP) 
	{

	}
};

