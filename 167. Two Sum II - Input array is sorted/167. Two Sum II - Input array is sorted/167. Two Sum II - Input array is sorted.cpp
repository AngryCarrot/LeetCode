// 167. Two Sum II - Input array is sorted.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) 
	{	
		vector<int> result = { 1, 2 };
		for (int i = 0; i != numbers.size(); ++i)
		{
			result.clear();
			result.push_back(i + 1);
			cout << i << ": " << numbers[i] << endl;
			int index = binarySearch(numbers, i + 1, numbers.size() - 1, target - numbers[i]);
			if (-1 != index)
			{
				cout << "(" << i << ", " << index << ")" << endl;
				cout << "(" << numbers[i] << ", " << numbers[index] << ")" << endl;
				result.push_back(index + 1);
				break;
			}
		}
		return result;
	}
	int binarySearchLoop(vector<int>& numbers, int left, int right, const int target)
	{
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (numbers[mid] == target)
			{
				return mid;
			}
			else
			{
				if (numbers[mid] > target)
				{
					right = mid - 1;
				}
				else
				{
					left = mid + 1;
				}
			}
		}
		return -1;
	}
	/*
	递归版本
	1、容易超时
	2、容易溢出
	*/
	int binarySearch(vector<int>& numbers, int left, int right, const int target)
	{
		if (left > right)
		{
			return -1;
		}
		if (left == right && numbers[left] != target)
		{
			return -1;
		}
		int mid = left + right;
		cout << "mid: " << mid << endl;
		mid >>= 1;
		if (numbers[mid] == target)
		{
			return mid;
		}
		else
		{
			if (numbers[mid] > target)
			{				
				return binarySearch(numbers, left, mid - 1, target);
			}
			else
			{
				return binarySearch(numbers, mid + 1, right, target);
			}
		}
	}
};

int main()
{
	vector<int> v = { 2, 7, 11, 15, 16, 17, 19, 20, 21 };	
	Solution s;
	cout << "v.size(): " << v.size() << endl;
	int result = s.binarySearchLoop(v, 1, v.size() - 1, 1);
	cout << result << endl;
	//vector<int> vv = s.twoSum(v, 6);
	//cout << vv[0] << " " << vv[1] << endl;
    return 0;
}

