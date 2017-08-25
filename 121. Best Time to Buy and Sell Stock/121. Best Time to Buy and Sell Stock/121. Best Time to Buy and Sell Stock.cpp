// 121. Best Time to Buy and Sell Stock.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution 
{
public:
	int maxProfit(vector<int>& prices);
};

int main()
{
	// vector<int> v = { 7, 1, 5, 3, 6, 4 };
	vector<int> v = { 7, 6, 4, 3, 1};
	Solution s;
	cout << s.maxProfit(v) << endl;
    return 0;
}

inline int Solution::maxProfit(vector<int>& prices)
{
	if (prices.empty())
	{
		return 0;
	}
	int result = 0;
	int minValue = prices[0];
	int length = prices.size();
	for (int i = 1; i != length; ++i)
	{
		minValue = min(minValue, prices[i]);
		result = max(result, prices[i] - minValue);
	}
	return result;
}
