#include "Solution.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

void print(vector<int>& v)
{
	for (int item : v)
	{
		cout << item << " ";
	}
	cout << endl;
}

int main()
{
	Twitter obj;
	obj.postTweet(1, 1);
	obj.getNewsFeed(1);
	obj.follow(2, 1);
	obj.getNewsFeed(2);
	obj.unfollow(2, 1);
	obj.getNewsFeed(2);

	obj.postTweet(1, 5);
	obj.getNewsFeed(1);
	obj.follow(1, 2);
	obj.postTweet(2, 6);
	obj.getNewsFeed(1);
	obj.unfollow(1, 2);
	obj.getNewsFeed(1);

	// 小顶堆
	auto cmp = [](int left, int right) { return left > right; };
	std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);

	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
		q3.push(n);

	while (!q3.empty())
	{
		cout << q3.top() << endl;
		q3.pop();
	}

	Solution sln;
	vector<int> nums = {1, 3, 2, 2, 5, 2, 3, 7};
	cout << sln.findLHS(nums) << endl;
	string s = "egg";
	string t = "add";
	cout << std::boolalpha << sln.isIsomorphic(s, t) << endl;
	s = "foo";
	t = "bar";
	cout << std::boolalpha << sln.isIsomorphic(s, t) << endl;
	s = "paper";
	t = "title";
	cout << std::boolalpha << sln.isIsomorphic(s, t) << endl;
	 s = "ab";
	 t = "aa";
	cout << std::boolalpha << sln.isIsomorphic(s, t) << endl;
	s = "add";
	cout << sln.frequencySort(s) << endl;
	cout << sln.frequencySortNoSort(s) << endl;
	nums = { 1 };
	int k = 1;
	auto v = sln.topKFrequent(nums, k);
	print(v);
	vector<int> A = { 1, 2 };
	vector<int> B = { -2,-1 };
	vector<int> C = { -1, 2 };
	vector<int> D = { 0, 2 };
	int sums_4 = sln.fourSumCount(A, B, C, D);
	cout << sums_4 << endl;
	string secret = "1234";
	string guess = "5678";
	sln.getHint(secret, guess);

	nums = { 1, 5, 1, 1, 6, 4 };
	nums = { 1,1,2,1,2,2,1 };
	nums = { 1 };
	sln.wiggleSort(nums);
	print(nums);
	nums = { 0, 1, 0, 1, 1, 0, 1, 0, 0 };
	nums = { 0,2,1,2,1,0,2,1,2,2,1,1,0,0,0 };
	sln.sortColors(nums);
	print(nums);
	nums = { 0, 3, 5, 4, 2, 1, 7, 9 };
	sln.findMaxLength(nums);

	s = "AAAAACCCCCAAAAACCCCC";
	sln.findRepeatedDnaSequencesNBNB(s);

	nums = { 1,2,3,4,5,6,7,8,9,9 };
	sln.hIndex2(nums);

	vector<string> sssss = { "root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)","root 4.txt(efgh)" };

	sln.findDuplicate(sssss);

	s = "dvdf";
	sln.lengthOfLongestSubstring(s);
	s = "abcabcbb";
	sln.lengthOfLongestSubstring(s);
	s = "bbbbb";
	sln.lengthOfLongestSubstring(s);
	s = "pwwkew";
	sln.lengthOfLongestSubstring(s);

	vector<vector<int>> wall = { 
		{ 1,2,2,1 },
		{ 3,1,2 },
		{1, 3, 2}, 
		{2, 4}, 
		{3, 1, 2}, 
		{1, 3, 1, 1} };
	sln.leastBricksNB(wall);

	system("PAUSE");
	return 0;
}