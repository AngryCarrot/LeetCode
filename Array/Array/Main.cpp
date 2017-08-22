#include "Solution.h"

int main()
{
	vector<vector<int>> matrix = { 
		{1, 4, 7, 11, 15},
		{2, 5, 8, 12, 19},
		{3, 6, 9, 16, 22},
		{10, 13, 14, 17, 24}, 
		{18, 21, 23, 26, 30} };
	int target = 44;

	Solution sln;
	sln.searchMatrix2(matrix, target);

	vector<int> nums = { 2,6,4,8,10,9,15 };
	sln.findUnsortedSubarray(nums);
	nums = { 1,6,3,9,2,7,8,10 };
	sln.findUnsortedSubarray(nums);
	nums = { 1,2,3,4 };
	sln.findUnsortedSubarray(nums);
	nums = { 2,3,1,2,4,3 };
	int sum = 7;
	sln.minSubArrayLen(sum, nums);
	vector<char> tasks = { 'A','A','A','A','A','A','B','C','D','E','F','G' };
	int n = 2;
	sln.leastInterval(tasks, n);
	int i = 1;
	sizeof(i++);
	cout << i << endl;
	return 0;
}