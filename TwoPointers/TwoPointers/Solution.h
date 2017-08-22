#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;


class Solution
{
public:
	/*532. K-diff Pairs in an Array
	Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.
	*/
	int findPairs(vector<int>& nums, int k)
	{
		int result = 0;
		int length = nums.size();
		if (length < 1)
		{
			return result;
		}

		sort(begin(nums), end(nums));

		int left = 0;
		int right = left + 1;
		while (right < length)
		{
			int i = nums[left];
			int j = nums[right];

			if (i + k < j)
			{
				++left;
			}
			else
			{
				if (i + k > j)
				{
					++right;
				}
				else
				{
					++result;
					while (left < length && i == nums[left])
					{
						++left;
					}
					while (right < length && j == nums[right])
					{
						++right;
					}
				}
			}
			if (left == right)
			{
				right++;
			}
		}
		return result;
	}
	/*28. Implement strStr()
	Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
	*/
	int strStr(string& haystack, string& needle)
	{
		int hayLength = haystack.length();
		int needleLength = needle.length();
		if (hayLength < needleLength)
		{
			return -1;
		}
		if (needleLength == 0)
		{
			return 0;
		}

		int idx = -1;
		int j = 0;
		int i = 0;
		while (i < hayLength)
		{
			if (haystack[i] == needle[j])
			{
				++i;
				++j;
				if (j == needleLength)
				{
					return i - j;
				}
			}
			else
			{
				if (j == 0)
				{
					++i;
				}
				else
				{
					i = i - j + 1;
					j = 0;
				}
			}
		}
		return -1;
	}

	/*524. Longest Word in Dictionary through Deleting
	*/
	string findLongestWord(string s, vector<string>& d) 
	{
		int result = -1;
		for (int i = 0; i < d.size(); ++i)
		{
			string item = d[i];
			if (isSubSequence(s, item))
			{
				if (result != -1)
				{
					result = cmp(item, d[result]) ? i : result;
				}
				else
				{
					result = i;
				}
			}
		}
		return result == -1 ? "" : d[result];
	}
	bool cmp(string& a, string& b)
	{
		int la = a.length();
		int lb = b.length();
		if (la > lb)
		{
			return true;
		}
		else
		{
			if (la < lb)
			{
				return false;
			}
		}
		int i = 0;
		int j = 0;
		while (i < la && j < lb)
		{
			if (a[i] == b[j])
			{
				++i;
				++j;
			}
			else
			{
				return a[i] < b[j];
			}
		}
		return true;
	}
	bool isSubSequence(string& src, string& dest)
	{
		int lengthSrc = src.length();
		int lengthDest = dest.length();

		if (lengthSrc < lengthDest)
		{
			return false;
		}
		if (lengthDest == 0)
		{
			return true;
		}

		int i = 0; 
		int j = 0;
		while (i + lengthDest - j <= lengthSrc)
		{
			if (src[i] == dest[j])
			{
				++i;
				++j;
				if (j == lengthDest)
				{
					return true;
				}
			}
			else
			{
				++i;
			}
		}
		return false;
	}
	/*80. Remove Duplicates from Sorted Array II
	Follow up for "Remove Duplicates": What if duplicates are allowed at most twice?*/
	int removeDuplicates(vector<int>& nums) 
	{
		int length = nums.size();
		if (length <= 2)
		{
			return length;
		}
		int i = 0;
		for (int n : nums)
		{
			if (i < 2 || n > nums[i - 2])
			{
				nums[i++] = n;
			}
		}
		return i;
	}

	/*16. 3Sum Closest
	Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
	*/
	int threeSumClosest(vector<int>& nums, int target) 
	{
		sort(begin(nums), end(nums));
		int length = nums.size();
		int result = nums[0] + nums[1] + nums[length - 1];
		for (int i = 0; i < length - 2; i++)
		{
			int left = i + 1;
			int right = length - 1;
			while (left < right)
			{
				int sum = nums[i] + nums[left] + nums[right];
				if (sum < target)
				{
					++left;
				}
				else
				{
					--right;
				}
				if (abs(result - target) > abs(sum - target))
				{
					result = sum;
				}
			}
		}
		return result;
	}

	/*567. Permutation in String
	Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.
	*/
	bool checkInclusion(string& s1, string& s2) 
	{
		int l1 = s1.size();
		int l2 = s2.size();
		if (l1 > l2)
		{
			return false;
		}
		
		vector<int> m1(26, 0);
		vector<int> m2(26, 0);
		for (int j = 0; j < l1; ++j)
		{
			m1[s1[j] - 'a']++;
			m2[s2[j] - 'a']++;
		}
		if (m1 == m2)
		{
			return true;
		}
		for (int i = 1; i < l2 - l1 + 1; ++i)
		{
			char c = s2[i + l1 - 1];
			m2[c - 'a']++;
			m2[s2[i - 1] - 'a']--;
			if (m1 == m2)
			{
				return true;
			}
		}
		return false;
	}	
};

