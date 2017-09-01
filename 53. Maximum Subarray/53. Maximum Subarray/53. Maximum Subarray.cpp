// 53. Maximum Subarray.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
public:
	int maxSubArray(vector<int>& nums) 
	{
		int result = nums[0];
		int localMax = nums[0];
		
		for (int i = 1; i != nums.size(); ++i)
		{
			if (nums[i] + localMax > nums[i])
			{
				localMax = nums[i] + localMax;
			}
			else
			{
				localMax = nums[i];
			}
			if (localMax > result)
			{
				result = localMax;
			}
		}
		return result;
	}
};

int main()
{
    return 0;
}

