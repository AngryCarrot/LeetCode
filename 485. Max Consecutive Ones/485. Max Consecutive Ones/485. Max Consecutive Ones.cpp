// 485. Max Consecutive Ones.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution 
{
public:
	int findMaxConsecutiveOnes(vector<int>& nums) 
	{
		if (nums.empty())
		{
			return 0;
		}
		int maxNo = 0;
		int count = 0;
		for (int item : nums)
		{
			if (1 == item)
			{
				++count;
			}
			else
			{
				count = 0;
			}
			maxNo = maxNo > count ? maxNo : count;			
		}
		return maxNo;
	}
};

int main()
{
	vector<int> v = { 1, 1, 0, 1, 1, 1 };
	Solution s;
	int result = s.findMaxConsecutiveOnes(v);
	cout << result << endl;
    return 0;
}

