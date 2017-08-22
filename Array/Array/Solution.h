#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;


// Definition for an interval.
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};



class Solution
{
public:
	/*650. 2 Keys Keyboard
	1. Copy all: partial copy is not allowed.
	2. Paste: paste which are copied last time
	Given a number n, to get exactly n 'A', Output the minimum number of steps to get n 'A'.
	*/
	int minSteps(int n) 
	{
		int result = 0;
		for (int i = 2; i <= n; ++i)
		{
			while (n % i == 0)
			{
				result += i;
				n /= i;
			}
		}
		return result;
	}
	/*560. Subarray Sum Equals K
	Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.
	*/
	int subarraySum(vector<int>& nums, int k) 
	{
		int result = 0;
		int length = nums.size();
		if (length < 1)
		{
			return result;
		}
		vector<int> sums(length, 0);
		sums[0] = nums[0];
		for (int i = 1; i < length; ++i)
		{
			sums[i] = sums[i - 1] + nums[i];
		}
		int left = 0; 
		int right = 0;
		while (right < length || left < length)
		{
			int s = sums[right == length ? right - 1 : right] - sums[left] + nums[left];
			if (s == k)
			{
				++result;
				++right;
				++left;
			}
			else
			{
				if (s < k)
				{
					++right;
				}
				else
				{
					++left;
				}
			}
		}		
		return result;
	}
	/*621. Task Scheduler
	*/
	int leastInterval(vector<char>& tasks, int n)
	{
		int length = tasks.size();
		if (length <= 1 || n == 0)
		{
			return length;
		}
		vector<int> nums(26, 0);
		for (char c : tasks)
		{
			++nums[c - 'A'];
		}
		sort(begin(nums), end(nums));
		
		int i = 25;
		while (i >= 0 && nums[i] == nums[25])
		{
			--i;
		}
		return max(length, (n + 1) * (nums.back() - 1) + 25 - i);
	}
	/*611. Valid Triangle Number
	Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
	*/
	int triangleNumber(vector<int>& nums)
	{
		int result = 0;
		int length = nums.size();
		if (length < 3)
		{
			return result;
		}
		sort(begin(nums), end(nums));
		for (int i = 0; i < length - 2; ++i)
		{
			if (nums[i] == 0)
			{
				continue;
			}
			for (int j = i + 1; j < length - 1; ++j)
			{
				for (int k = j + 1; k < length; ++k)
				{
					int a = nums[i];
					int b = nums[j];
					int c = nums[k];
					if (a + b > c)
					{
						if (c - a < b)
						{
							++result;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		return result;
	}
	bool isValidTriangle(int a, int b, int c)
	{
		int maxVal = max(a, max(b, c));
		int minVal = min(a, min(b, c));
		int sum = a + b + c;
		return ((sum - maxVal) > maxVal) && ((maxVal - minVal) < sum - maxVal - minVal);
	}
	/*48. Rotate Image
	You are given an n x n 2D matrix representing an image.
	Rotate the image by 90 degrees (clockwise).
	In Place!!!!!!!!!!!!!!!!!!!!
	*/
	void rotate(vector<vector<int>>& matrix)
	{
		int n = matrix.size();
		for (int i = 0; i < n; ++i)
		{
			for (int j = i; j < n; ++j)
			{
				swap(matrix[i][j], matrix[j][i]);
			}
		}
		for (auto& item : matrix)
		{
			reverse(begin(item), end(item));
		}
	}
	/*34. Search for a Range
	Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.
	If the target is not found in the array, return [-1, -1].
	Time : O(log n).*/
	vector<int> searchRange(vector<int>& nums, int target)
	{
		vector<int> result(2, -1);
		int length = nums.size();
		if (0 == length || target < nums[0] || target > nums[length - 1])
		{
			return result;
		}
		int left = 0;
		int right = length - 1;
		// find left
		while (left < right)
		{
			int mid = left + (right - left) / 2;
			if (nums[mid] < target)
			{
				left = mid + 1;
			}
			else
			{
				right = mid;
			}
		}
		if (nums[left] != target)
		{
			return result;
		}
		result[0] = left;
		left = 0;
		right = length - 1;
		while (left < right)
		{
			// find right, in order to avoid stucking
			int mid = (right - left) / 2 + left + 1;
			if (nums[mid] > target)
			{
				right = mid - 1;
			}
			else
			{
				left = mid;
			}
		}
		result[1] = right;
		return result;
	}
	int lower_bound(vector<int>& nums, const int target)
	{
		int left = 0;
		int right = nums.size() - 1;
		while (left < right)
		{
			int mid = (right - left) / 2 + left;
			if (nums[mid] > target)
			{
				right = mid - 1;
			}
			else
			{
				if (nums[mid] < target)
				{
					left = mid + 1;
				}
				else
				{

				}
			}
		}
	}
	/*56. Merge Intervals
	Given a collection of intervals, merge all overlapping intervals.
	*/
	vector<Interval> merge(vector<Interval>& intervals)
	{
		vector<Interval> result;
		int length = intervals.size();
		if (0 == length)
		{
			return result;
		}
		sort(begin(intervals), end(intervals), [&](Interval a, Interval b) {
			return a.start < b.start;
		});
		result.push_back(intervals[0]);
		for (Interval& item : intervals)
		{
			if (result.back().end < item.start)
			{
				result.emplace_back(item);
			}
			else
			{
				result.back().end = max(result.back().end, item.end);
			}
		}
		return result;
	}
	/*74. Search a 2D Matrix
	m行n列的矩阵，每行元素递增排列，每行最后一个元素小于下一行第一个元素
	*/
	bool searchMatrix(vector<vector<int>>& matrix, int target)
	{
		int rows = matrix.size();
		if (rows == 0)
		{
			return false;
		}
		int cols = matrix[0].size();
		if (cols == 0)
		{
			return false;
		}

		// Don't treat it as a 2D matrix, just treat it as a sorted list
		int length = rows * cols;
		int left = 0;
		int right = length - 1;
		int middle = (right - left) / 2 + left;

		while (left <= right)
		{
			middle = (right - left) / 2 + left;
			int row = middle / cols;
			int col = middle % cols;
			if (matrix[row][col] < target)
			{
				left = middle + 1;
			}
			else
			{
				if (matrix[row][col] > target)
				{
					right = middle - 1;
				}
				else
				{
					return true;
				}
			}
		}
		return false;
	}
	/* 240. Search a 2D Matrix II
	m行n列的矩阵，每行元素从左到右递增排列，每列元素从上到下递增排列
	*/
	bool searchMatrix2(vector<vector<int>>& matrix, int target)
	{
		int rows = matrix.size();
		if (rows == 0)
		{
			return false;
		}
		int cols = matrix[0].size();
		if (cols == 0)
		{
			return false;
		}

		int row = 0;
		int col = cols - 1;

		while (row < rows)
		{
			while (col >= 0)
			{
				if (matrix[row][col] > target)
				{
					--col;
					if (col == -1)
					{
						return false;
					}
				}
				else
				{
					if (matrix[row][col] < target)
					{
						++row;
						if (row == rows)
						{
							return false;
						}
					}
					else
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool searchMatrix2NB(vector<vector<int>>& matrix, int target)
	{
		int rows = matrix.size();
		if (rows == 0)
		{
			return false;
		}
		int cols = matrix[0].size();
		if (cols == 0)
		{
			return false;
		}
		int row = 0;
		int col = cols - 1;
		while ((row < rows) && (col >= 0))
		{
			if (matrix[row][col] == target)
			{
				return true;
			}
			else
			{
				if (matrix[row][col] < target)
				{
					++row;
				}
				else
				{
					--col;
				}
			}
		}
		return false;
	}
	/*561. Array Partition I
	Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.
	*/
	int arrayPairSum(vector<int>& nums)
	{
		int result = 0;
		int length = nums.size();
		sort(begin(nums), end(nums));
		for (int i = 0; i < length; i += 2)
		{
			result += nums[i];
		}
		return result;
	}
	/*581. Shortest Unsorted Continuous Subarray
	Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.
	You need to find the shortest such subarray and output its length.
	*/
	int findUnsortedSubarray(vector<int>& nums)
	{
		int length = nums.size();
		if (length < 2)
		{
			return 0;
		}

		int left = 0;
		int right = length - 1;
		vector<int> dp = nums;
		sort(begin(dp), end(dp));
		while (left < length && nums[left] == dp[left])
		{
			++left;
		}
		while (right > left && nums[right] == dp[right])
		{
			--right;
		}
		return right - left + 1;
	}

	/*566. Reshape the Matrix
	You're given a matrix represented by a two-dimensional array, and two positive integers r and c representing the row number and column number of the wanted reshaped matrix, respectively.
	The reshaped matrix need to be filled with all the elements of the original matrix in the same row-traversing order as they were.
	If the 'reshape' operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.
	*/
	vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c)
	{

	}

	/*162. Find Peak Element
	A peak element is an element that is greater than its neighbors.
	Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.
	The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
	You may imagine that num[-1] = num[n] = -∞.
	时间复杂度：O(logn)
	*/
	int findPeakElement(vector<int>& nums)
	{

	}

	/*565. Array Nesting TODO:
	A zero-indexed array A consisting of N different integers is given. The array contains all integers in the range [0, N - 1].
	Sets S[K] for 0 <= K < N are defined as follows:
	S[K] = { A[K], A[A[K]], A[A[A[K]]], ... }.
	Sets S[K] are finite for each K and should NOT contain duplicates.
	Write a function that given an array A consisting of N integers, return the size of the largest set S[K] for this array.
	*/
	int arrayNesting(vector<int>& nums)
	{

	}

	/*78. Subsets
	Given a set of distinct integers, nums, return all possible subsets.
	*/
	vector<vector<int>> subsets(vector<int>& nums)
	{

	}
	/*90. Subsets II
	Given a collection of integers that might contain duplicates, nums, return all possible subsets.
	*/
	vector<vector<int>> subsetsWithDup(vector<int>& nums)
	{

	}

	/*54. Spiral Matrix
	矩阵蛇形输出：Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
	[	[ 1, 2, 3 ],
		[ 4, 5, 6 ],
		[ 7, 8, 9 ]	]
	You should return [1,2,3,6,9,8,7,4,5].
	*/
	vector<int> spiralOrder(vector<vector<int>>& matrix)
	{

	}

	/* 59. Spiral Matrix II
	Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
	For example, Given n = 3,
	You should return the following matrix:
	[	[ 1, 2, 3 ],
		[ 8, 9, 4 ],
		[ 7, 6, 5 ]		]
	*/
	vector<vector<int>> generateMatrix(int n)
	{

	}

	/*73. Set Matrix Zeroes
	Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
	(1). A straight forward solution using O(mn) space is probably a bad idea.
	(2). A simple improvement uses O(m + n) space, but still not the best solution.
	(3). Could you devise a constant space solution?最高要求：空间复杂度为O(1)
	*/
	void setZeroes(vector<vector<int>>& matrix)
	{
		int m = matrix.size();
		if (0 == m)
		{
			return;
		}
		int n = matrix[0].size();
		if (0 == n)
		{
			return;
		}

		vector<pair<int, int>> zeros;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (0 == matrix[i][j])
				{
					zeros.emplace_back(make_pair(i, j));
				}
			}
		}
		for (auto item : zeros)
		{
			int row = item.first;
			int col = item.second;
			for (int i = 0; i < m; ++i)
			{
				matrix[i][col] = 0;
			}
			for (int j = 0; j < n; ++j)
			{
				matrix[row][j] = 0;
			}
		}
	}
	void setZeroesNB(vector<vector<int>>& matrix)
	{
		int m = matrix.size();
		if (0 == m)
		{
			return;
		}
		int n = matrix[0].size();
		if (0 == n)
		{
			return;
		}
		bool firstRowExist0 = false;
		bool firstColExist0 = false;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (0 == matrix[i][j])
				{
					if (0 == i)
					{
						firstRowExist0 = true;
					}
					if (0 == j)
					{
						firstColExist0 = true;
					}
					matrix[0][j] = 0;
					matrix[i][0] = 0;
				}
			}
		}
		for (int i = 1; i < m; ++i)
		{
			for (int j = 1; j < n; ++j)
			{
				if ((0 == matrix[i][0]) || (0 == matrix[0][j]))
				{
					matrix[i][j] = 0;
				}
			}
		}
		if (firstRowExist0)
		{
			for (int j = 0; j < n; ++j)
			{
				matrix[0][j] = 0;
			}
		}
		if (firstColExist0)
		{
			for (int i = 0; i < m; ++i)
			{
				matrix[i][0] = 0;
			}
		}
	}

	/*209. Minimum Size Subarray Sum
	Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.
	最短连续子序列使得其和大于等于s
	If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
	*/
	int minSubArrayLen(int s, vector<int>& nums)
	{
		int length = nums.size();
		vector<int> sums(length + 1, 0);
		for (int i = 1; i <= length; ++i)
		{
			sums[i] = sums[i - 1] + nums[i - 1];
		}
		int result = INT_MAX;
		int i = 0;
		for (i = 0; i < length; ++i)
		{
			int end = binarySearch(i + 1, length, s + sums[i], sums);
			if (end == length + 1)
			{
				break;
			}
			if (end - i < result)
			{
				result = end - i;
			}
		}

		return result == INT_MAX ? 0 : result;
	}
	int binarySearch(int left, int right, int key, vector<int>& sums)
	{
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (sums[mid] >= key)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		return left;
	}
	int minSubArrayLenNB(int s, vector<int>& nums)
	{

	}

	/*55. Jump Game
	Given an array of non-negative integers, you are initially positioned at the first index of the array.
	Each element in the array represents your maximum jump length at that position.
	Determine if you are able to reach the last index.
	For example: A = [2,3,1,1,4], return true.
				 A = [3,2,1,0,4], return false.
	*/
	bool canJump(vector<int>& nums)
	{
		int length = nums.size();
		if (length < 2)
		{
			return true;
		}
		int count = 1;
		bool flag = true;
		int i = length - 2;
		for (; i >= 0; --i)
		{
			if (nums[i] >= count)
			{
				count = 1;
				flag = true;
			}
			else
			{
				flag = false;
				++count;
			}
		}
		return flag;
	}

	/*11. Container With Most Water
	Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
	*/
	int maxArea(vector<int>& height)
	{
		int length = height.size();
		if (length == 2)
		{
			return min(height[0], height[1]);
		}
		int water = 0;
		int left = 0;
		int right = length - 1;
		while (left < right)
		{
			int h = min(height[right], height[left]);
			water = max(h * (right - left), water);
			while ((left < right) && (height[left] <= h))
			{
				++left;
			}
			while ((left < right) && (height[right] <= h))
			{
				--right;
			}
		}
		return water;
	}
};

