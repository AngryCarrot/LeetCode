#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>

#include <bitset>
#include <sstream>
#include <ctime>

using namespace std;

/* 355. Design Twitter
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:
	postTweet(userId, tweetId): Compose a new tweet.
	getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
	follow(followerId, followeeId): Follower follows a followee.
	unfollow(followerId, followeeId): Follower unfollows a followee.
Example:
Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);
*/
class Twitter;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};


/*int cmp111(const pair<char, int>& a, const pair<char, int>& b)
{
	return a.second - b.second;
}
*/
class Solution {
public:
	/*554. Brick Wall
	There is a brick wall in front of you. The wall is rectangular and has several rows of bricks. The bricks have the same height but different width. You want to draw a vertical line from the top to the bottom and cross the least bricks.
	The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this row from left to right.
	If your line go through the edge of a brick, then the brick is not considered as crossed. You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.
	You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.

	Note:
	The width sum of bricks in different rows are the same and won't exceed INT_MAX.
	The number of bricks in each row is in range [1,10,000]. The height of wall is in range [1,10,000]. Total number of bricks of the wall won't exceed 20,000.
	________________TLE________________
	*/
	int leastBricks(vector<vector<int>>& wall)
	{
		int result = INT_MAX;
		map<int, int> dict;
		for (auto row : wall)
		{
			int width = 0;
			for (int brick : row)
			{
				if (brick > 2)
				{
					for (int i = 1; i < brick; ++i)
					{
						dict[width + i]++;
					}
				}
				else
				{
					if (brick == 2)
					{
						dict[width + 1]++;
					}
				}
				width += brick;
			}
		}
		for (auto item : dict)
		{
			result = min(result, item.second);
		}
		if (result == INT_MAX)
		{
			return wall.size();
		}
		return result;
	}
	int leastBricksNB(vector<vector<int>>& wall)
	{
		int result = 0;
		int seal = 0;
		map<int, int> dict;
		for (auto &row : wall)
		{
			int width = 0;
			for (int brick : row)
			{
				width += brick;
				dict[width]++;
			}
		}
		dict.erase(--end(dict));
		for (auto item : dict)
		{
			seal = max(item.second, seal);
		}
		return wall.size() - seal;
	}
	/*3. Longest Substring Without Repeating Characters
	Given a string, find the length of the longest substring without repeating characters.
	注意是连续的，子串与子序列区别
	*/
	int lengthOfLongestSubstring(string s)
	{
		map<int, int> exist;
		int length = 0;
		int result = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			char c = s[i];
			if (exist.find(c) == end(exist))
			{
				++length;
				exist[c] = i;
				result = max(length, result);
			}
			else
			{
				result = max(length, result);
				length = 0;
				i = exist[c];
				exist.clear();
			}
		}
		return result;
	}
	int lengthOfLongestSubstringNB(string &s)
	{
		vector<int> dict(256, -1);
		int maxLen = 0, start = -1;
		for (int i = 0; i != s.length(); i++)
		{
			if (dict[s[i]] > start)
			{
				start = dict[s[i]];
			}
			dict[s[i]] = i;
			maxLen = max(maxLen, i - start);
		}
		return maxLen;
	}
	/*609. Find Duplicate File in System
	"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"
	It means there are n files (f1.txt, f2.txt ... fn.txt with content f1_content, f2_content ... fn_content, respectively) in directory root/d1/d2/.../dm. Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root directory.
	The output is a list of group of duplicate file paths. For each group, it contains all the file paths of the files that have the same content. A file path is a string that has the following format:
	"directory_path/file_name.txt"
	Input:
	["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
	Output:
	[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]
	*/
	vector<vector<string>> findDuplicate(vector<string>& paths)
	{
		map<string, vector<string>> m;
		int length = paths.size();
		for (int i = 0; i < length; i++)
		{
			getFileNames(paths[i], m);
		}
		vector<vector<string>> result;
		for (auto item : m)
		{
			if (item.second.size() >= 2)
			{
				result.emplace_back(item.second);
			}
		}
		return result;
	}
	vector<string> getFileNames(string path, map<string, vector<string>> &m)
	{
		vector<string> result;
		int idx = path.find_first_of(" ");
		string prefix = path.substr(0, idx);
		string files = path.substr(idx + 1);
		string file;
		stringstream ss;
		ss << files;
		while (ss >> file)
		{
			int start = file.find_first_of("(");
			int stop = file.find_last_not_of(")");
			string content = file.substr(start + 1, stop - start);
			string value = prefix + "/" + file.substr(0, start);
			result.emplace_back(value);
			m[content].emplace_back(value);
		}
		return result;
	}
	/* 392. Is Subsequence
	判断s是否是t的子串，相对位置匹配即可
	*/
	bool isSubsequence(string s, string t)
	{
		auto i = begin(s);
		for (char c : t)
		{
			i += (*i == c);
		}
		return i == end(s);
	}
	/*436. Find Right Interval
	Given a set of intervals, for each of the interval i, check if there exists an interval j whose start point is bigger than or equal to the end point of the interval i, which can be called that j is on the "right" of i.
	For any interval i, you need to store the minimum interval j's index, which means that the interval j has the minimum start point to build the "right" relationship for interval i. If the interval j doesn't exist, store -1 for the interval i. Finally, you need output the stored value of each interval as an array.
	找到与每个区间右端点最接近的左端点大于等于该右端点的区间，
	*/
	vector<int> findRightInterval(vector<Interval>& intervals)
	{
		int length = intervals.size();
		vector<int> result;
		map<int, int> m;
		for (size_t i = 0; i < length; i++)
		{
			m[intervals[i].start] = i;
		}
		for (Interval item : intervals)
		{
			auto idx = m.lower_bound(item.end);
			if (idx == end(m))
			{
				result.emplace_back(-1);
			}
			else
			{
				result.emplace_back(idx->second);
			}
		}
		return result;
	}
	/* 275. H-Index II
	Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm
	26ms
	*/
	int hIndex2(vector<int>& citations)
	{
		int length = citations.size();
		if (length == 0 || citations[length - 1] == 0)
		{
			return 0;
		}

		int h = 1;
		for (int i = length - 2; i >= 0; --i)
		{
			if (citations[i] > h)
			{
				++h;
			}
			else
			{
				break;
			}
		}
		return h;
	}
	// 9ms
	int hIndex2NB(vector<int>& citations)
	{
		int length = citations.size();
		if (length == 0 || citations[length - 1] == 0)
		{
			return 0;
		}

		int h = 0;

		int left = 0;
		int right = length - 1;
		int middle = 0;
		while (left <= right)
		{
			middle = left + (right - left) / 2;
			if (citations[middle] >= (length - middle))
			{
				right = middle - 1;
			}
			else
			{
				left = middle + 1;
			}
		}
		h = length - left;
		return h;
	}
	/* 274. H-Index
	Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.
	一个学者发表的n篇论文中，他有h篇被引用至少h次，而其他的n-h篇被引用次数都不超过h。
	*/
	int hIndex(vector<int>& citations)
	{
		int length = citations.size();
		vector<int> bucket(length + 1, 0);
		for (int citation : citations)
		{
			if (citation >= length)
			{
				bucket[length]++;
			}
			else
			{
				bucket[citation]++;
			}
		}
		int result = 0;
		int count = 0;
		for (int i = length; i >= 0; --i)
		{
			count += bucket[i];
			if (count >= i)
			{
				result = i;
				break;
			}
		}
		return result;
	}
	/*187. Repeated DNA Sequences
	All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
	Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
	*/
	vector<string> findRepeatedDnaSequences(string s)
	{
		vector<string> result;
		if (s.length() < 10)
		{
			return result;
		}

		map<string, int> res;
		for (size_t i = 0; i <= s.length() - 10; i++)
		{
			res[s.substr(i, 10)]++;
		}
		for (auto item : res)
		{
			if (item.second > 1)
			{
				result.emplace_back(item.first);
			}
		}
		return result;
	}
	// 第一种方法可能有MLE存储溢出错误，可用位操作方式将10个字母压缩为一个int
	vector<string> findRepeatedDnaSequencesNB(string s)
	{
		vector<string> result;
		int length = s.length();
		if (length < 10)
		{
			return result;
		}
		map<int, int> res;
		map<int, int> mappings;
		mappings['A'] = 1;
		mappings['T'] = 4;
		mappings['C'] = 3;
		mappings['G'] = 7;
		mappings[1] = 'A';
		mappings[3] = 'C';
		mappings[4] = 'T';
		mappings[7] = 'G';

		int mask = 0x3FFFFFFF;
		for (size_t i = 0; i < length - 9; i++)
		{
			string tmp = s.substr(i, 10);
			int key = 0;
			for (int j = 0; j < 10; ++j)
			{
				char c = tmp[j];
				key |= mappings[c];
				if (j != 9)
				{
					key <<= 3;
				}
				bitset<32> ttt(key);
			}
			key &= mask;
			res[key]++;
		}
		int char_mask = 7;
		for (auto item : res)
		{
			if (item.second > 1)
			{
				string tmp = "";
				int key = item.first;
				for (size_t i = 0; i < 10; i++)
				{
					char c = static_cast<char>(mappings[key & char_mask]);
					tmp.insert(0, 1, c);
					key >>= 3;
				}
				result.emplace_back(tmp);
			}
		}
		return result;
	}
	vector<string> findRepeatedDnaSequencesNBNB(string s)
	{
		vector<string> result;
		int length = s.length();
		if (length < 10)
		{
			return result;
		}
		map<int, int> res;
		map<int, int> mappings;
		mappings['A'] = 1;
		mappings['T'] = 4;
		mappings['C'] = 3;
		mappings['G'] = 7;
		mappings[1] = 'A';
		mappings[3] = 'C';
		mappings[4] = 'T';
		mappings[7] = 'G';

		int mask = 0x3FFFFFFF;
		int key = 0;
		for (size_t i = 0; i < length; i++)
		{
			key <<= 3;
			key |= mappings[s[i]];
			key &= mask;
			bitset<32> ttt(key);
			if (i >= 9)
			{
				res[key]++;
			}
		}
		int char_mask = 7;
		for (auto item : res)
		{
			if (item.second > 1)
			{
				string tmp = "";
				int key = item.first;
				for (size_t i = 0; i < 10; i++)
				{
					char c = static_cast<char>(mappings[key & char_mask]);
					tmp.insert(0, 1, c);
					key >>= 3;
				}
				result.emplace_back(tmp);
			}
		}
		return result;
	}
	/*36. Valid Sudoku
	要验证一个数独是否有效就必须满足三个条件：
	横排所有数字无重复
	竖排所有数字无重复
	九宫格内所有数字无重复
	The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
	Note:
	A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
	[".87654321","2........","3........","4........","5........","6........","7........","8........","9........"] true
	["....5..1.",".4.3.....",".....3..1","8......2.","..2.7....",".15......",".....2...",".2.9.....","..4......"] false
	*/
	bool isValidSudoku(vector<vector<char>>& board)
	{
		auto length = board.size();
		//bool colsMap[9][10] = { false };
		vector<vector<bool>> colsMap(9, vector<bool>(10, false));
		//bool subCellMap[9][9][10] = { false };
		vector<vector<vector<bool>>> subCellMap(3, vector<vector<bool>>(3, vector<bool>(10, false)));

		for (size_t i = 0; i < length; i++)
		{
			vector<bool> rowsMap(10, false);
			for (size_t j = 0; j < length; j++)
			{
				char cur = board[i][j];
				if (cur == '.')
				{
					continue;
				}
				// 行是否合法
				int value = cur - '0';
				if (rowsMap[value])
				{
					return false;
				}
				rowsMap[value] = true;
				// 列是否合法
				if (colsMap[j][value])
				{
					return false;
				}
				colsMap[j][value] = true;
				// 子窗口是否合法
				if (subCellMap[i / 3][j / 3][value])
				{
					return false;
				}
				subCellMap[i / 3][j / 3][value] = true;
			}
		}
		return true;
	}

	/*508. Most Frequent Subtree Sum
	Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.
	*/
	vector<int> findFrequentTreeSum(TreeNode* root)
	{
		vector<int> result;
		map<int, int> m;
		int sum = 0;
		this->findFrequentTreeSumHelper(root, m, sum);
		int max = begin(m)->second;

		for (auto item : m)
		{
			if (item.second > max)
			{
				max = item.second;
				result.clear();
				result.emplace_back(item.first);
			}
			else
			{
				if (item.second == max)
				{
					result.emplace_back(item.first);
				}
			}
		}
		return result;
	}
	int findFrequentTreeSumHelper(TreeNode* root, map<int, int>& m, int& sum)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int left_sum = this->findFrequentTreeSumHelper(root->left, m, sum);
		int right_sum = this->findFrequentTreeSumHelper(root->right, m, sum);
		sum = left_sum + right_sum + root->val;
		m[sum]++;
		return sum;
	}
	/*525. Contiguous Array
	Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.
	一个只有0和1两种值的数组，找到一个最长的连续子序列，使得0/1数量相等。
	*/
	int findMaxLength(vector<int>& nums) {
		int length = nums.size();
		if (length <= 1)
		{
			return 0;
		}
		map<int, int> indices;
		indices[0] = 0;
		int result = 0;
		int count = 0;
		for (int i = 0; i < length; i++)
		{

			{
				if (nums[i] == 0)
				{
					--count;
				}
				else
				{
					{
						++count;
					}
				}
				if (indices.find(count) == end(indices))
				{
					indices[count] = i + 1;
				}
				else
				{
					result = max(i + 1 - indices[count], result);
				}
			}
		}
		return result;
	}
	/* 49. Group Anagrams
	Given an array of strings, group anagrams together.
	For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
	Return:
	[
		["ate", "eat","tea"],
		["nat","tan"],
		["bat"]
	]
	Note: All inputs will be in lower-case.
	*/
	vector<vector<string>> groupAnagrams(vector<string>& strs)
	{
		vector<vector<string>> results;
		map<string, vector<string>> mappings;
		int length = strs.size();
		for (int i = 0; i < length; ++i)
		{
			string s = strs[i];
			//sort(begin(s), end(s));
			s = strSort(s);
			if (mappings.find(s) == end(mappings))
			{
				mappings[s] = vector<string>{ strs[i] };
			}
			else
			{
				mappings[s].emplace_back(strs[i]);
			}
		}
		for (auto item : mappings)
		{
			results.emplace_back(item.second);
		}
		return results;
	}
	string strSort(string &s) {
		int count[26] = { 0 }, n = s.length();
		for (int i = 0; i < n; ++i)
			++count[s[i] - 'a'];
		int p = 0;
		string t(n, 'a');
		for (int j = 0; j < 26; ++j)
			for (int i = 0; i < count[j]; ++i)
				t[p++] += j;
		return t;
	}
	/* 299. Bulls and Cows
	判断两个字符串对应位置是否相等，返回相同的数量和不同的数量1A2B，代表一个相同，两个不同，
	*/
	string getHint(string secret, string guess)
	{
		vector<int> s(10, 0);
		vector<int> g(10, 0);
		int equal = 0;
		int inequal = 0;
		auto length = secret.length();
		for (size_t i = 0; i < length; i++)
		{
			if (secret[i] == guess[i])
			{
				++equal;
			}
			else
			{
				s[secret[i] - '0']++;
				g[guess[i] - '0']++;
			}
		}
		for (int i = 0; i < 10; ++i)
		{
			inequal += min(s[i], g[i]);
		}
		return to_string(equal) + "A" + to_string(inequal) + "B";
	}
	/* 18. 4Sum
	Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
	Note: The solution set must not contain duplicate quadruplets.
	*/
	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>> result;
		auto length = nums.size();
		if (length < 4)
		{
			return result;
		}
		sort(begin(nums), end(nums));
		for (size_t i = 0; i < length - 3; i++)
		{
			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
			{
				break;
			}
			if (nums[i] + nums[length - 1] + nums[length - 2] + nums[length - 3] < target)
			{
				continue;
			}
			for (size_t j = i + 1; j < length - 2; j++)
			{
				if (j > i + 1 && nums[j] == nums[j - 1])
				{
					continue;
				}
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
				{
					break;
				}
				if (nums[i] + nums[j] + nums[length - 1] + nums[length - 2] < target)
				{
					continue;
				}
				auto left = j + 1;
				auto right = length - 1;
				while (left < right)
				{
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum < target)
					{
						++left;
					}
					else
					{
						if (sum > target)
						{
							--right;
						}
						else
						{
							result.emplace_back(vector<int>{ nums[i], nums[j], nums[left], nums[right] });
							do
							{
								++left;
							} while (nums[left] == nums[left - 1] && left < right);
							do
							{
								--right;
							} while (nums[right] == nums[right + 1] && left < right);
						}
					}
				}
			}
		}
		return result;
	}
	/* 454. 4Sum II
	给你4个数组，从里面分别选出来一个数，使得这四个数的和为0，返回组合数量。
	*/
	int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
	{
		map<int, int> a_plus_b;
		auto length = A.size();
		for (size_t i = 0; i < length; i++)
		{
			for (size_t j = 0; j < length; j++)
			{
				++a_plus_b[A[i] + B[j]];
			}
		}
		int result = 0;
		for (int c : C)
		{
			for (int d : D)
			{
				if (a_plus_b.find(-c - d) != end(a_plus_b))
				{
					result += a_plus_b[-c - d];
				}
			}
		}
		return result;
	}
	/* 75. Sort Colors
	Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
	Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
	*/
	void sortColors(vector<int>& nums)
	{
		int length = nums.size();
		if (length <= 1)
		{
			return;
		}
		if (length <= 2)
		{
			if (nums[0] > nums[1])
			{
				swap(nums[0], nums[1]);
				return;
			}
		}
		int red = 0;
		int white = 1;
		int blue = length - 1;
		// 坑：for循环结束条件
		for (int i = 0; i <= blue; i++)
		{
			switch (nums[i])
			{
			case 0:
				// swap(nums[i], nums[red]);
				nums[i] = nums[red];
				nums[red] = 0;
				++red;
				break;
			case 1:
				break;
			case 2:
				// swap(nums[i], nums[blue]);
				nums[i] = nums[blue];
				nums[blue] = 2;
				--blue;
				--i;
				break;
			default:
				break;
			}
		}
	}
	/* 324. Wiggle Sort II
	Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
	*/
	void wiggleSort(vector<int>& nums)
	{
		auto length = nums.size();
		int median = this->findKthLargest(nums, (length + 1) / 2);
		auto odd = 1;
		int even = (length % 2 == 0) ? length - 2 : length - 1;
		vector<int> tmp(length, 0);
		for (size_t i = 0; i < length; i++)
		{
			if (nums[i] > median)
			{
				tmp[odd] = nums[i];
				odd += 2;
			}
			else
			{
				if (nums[i] < median)
				{
					tmp[even] = nums[i];
					even -= 2;
				}
			}
		}
		while (even >= 0)
		{
			tmp[even] = median;
			even -= 2;
		}
		while (odd < length)
		{
			tmp[odd] = median;
			odd += 2;
		}
		for (size_t i = 0; i < length; i++)
		{
			nums[i] = tmp[i];
		}
	}
	/* 215. Kth Largest Element in an Array
	Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
	For example,
	Given [3,2,1,5,6,4] and k = 2, return 5.
	*/
	int findKthLargest(vector<int>& nums, int k)
	{
		multiset<int> k_largest;
		auto length = nums.size();
		for (size_t i = 0; i < length; i++)
		{
			k_largest.insert(nums[i]);
			if (k_largest.size() > k)
			{
				k_largest.erase(begin(k_largest));
			}
		}
		return *begin(k_largest);
	}
	/* 347. Top K Frequent Elements
	Given a non-empty array of integers, return the k most frequent elements.
	*/
	vector<int> topKFrequent(vector<int>& nums, int k)
	{
		map<int, int> frequency;
		size_t length = nums.size();
		for (size_t i = 0; i < length; i++)
		{
			++frequency[nums[i]];
		}
		vector<vector<int>> bucket(length + 1);
		for (auto item : frequency)
		{
			if (bucket[item.second].empty())
			{
				bucket[item.second] = vector<int>({ item.first });
			}
			else
			{
				bucket[item.second].emplace_back(item.first);
			}
		}
		vector<int> result(k);
		for (size_t i = 0; i < length && k > 0; i++)
		{
			int idx = length - i;
			if (!bucket[idx].empty())
			{
				for (int item : bucket[idx])
				{
					if (k == 0)
					{
						break;
					}
					else
					{
						result[--k] = item;
					}
				}
			}
		}
		return result;
	}
	vector<int> topKFrequentHeap(vector<int>& nums, int k) {}
	vector<int> topKFrequentPriorityQueue(vector<int>& nums, int k) {}
	/* 451. Sort Characters By Frequency
	将字符串s中出现的各个字母按频率排序，相同频率的字母顺序无关
	*/
	string frequencySort(string s) {
		map<char, int> frequency;
		for (char c : s)
		{
			frequency[c] = frequency.find(c) == end(frequency) ? 1 : ++frequency[c];
		}
		vector<pair<char, int>> v(begin(frequency), end(frequency));
		size_t length = v.size();

		sort(begin(v), end(v), [=](std::pair<char, int>& a, std::pair<char, int>& b)
		{
			return a.second == b.second ? a.second > b.second : a.first > b.first;
			//return a.second > b.second;
		});
		string result = "";
		for (size_t i = 0; i < length; i++)
		{
			result.append(v[i].second, v[i].first);
			cout << v[i].first << endl;
		}
		return result;
	}
	string frequencySortNoSort(string s)
	{
		string result = "";
		map<char, int> frequency;
		//count frequency of each character
		for (char c : s)
		{
			++frequency[c];
		}
		//put character into frequency bucket
		vector<string> bucket(s.length() + 1, "");
		for (auto item : frequency)
		{
			bucket[item.second].append(item.second, item.first);
		}
		//form descending sorted string
		size_t length = bucket.size();
		for (size_t i = 0; i < length; i++)
		{
			string s = bucket[length - 1 - i];
			if (!s.empty())
			{
				result += s;
			}
		}
		return result;
	}

	/* 205. Isomorphic Strings
	Given two strings s and t, determine if they are isomorphic异构词.
	add<->egg: true
	foo<->bar: false
	paper<->title: true
	ab<->aa: false
	*/
	bool isIsomorphic(string& s, string& t)
	{
		map<char, char> s2t;
		map<char, char> t2s;
		size_t length = s.length();
		for (size_t i = 0; i < length; i++)
		{
			if (s2t.find(s[i]) == end(s2t) && t2s.find(t[i]) == end(t2s))
			{
				s2t[s[i]] = t[i];
				t2s[t[i]] = s[i];
			}
			else
			{
				if (s2t.find(s[i]) != end(s2t))
				{
					if (s2t[s[i]] != t[i])
					{
						return false;
					}
				}
				else
				{
					if (t2s[t[i]] != s[i])
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	/* 624. Maximum Distance in Arrays
	一堆按照升序排列的数组，选择两个数组并从中选择两个数，使得两个数的差最大
	保证数组至少两行，每行至少一个元素
	*/
	int maxDistance(vector<vector<int>>& arrays) {
		int left = arrays[0][0], right = arrays[0].back(), answer = 0;
		for (size_t i = 1; i < arrays.size(); i++)
		{
			answer = max(answer, max(abs(arrays[i][0] - right), abs(arrays[i].back() - left)));
			left = min(left, arrays[i][0]);
			right = max(right, arrays[i].back());
		}
		return answer;
	}

	/* 594. Longest Harmonious Subsequence
	We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.
	Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.
	Input: [1,3,2,2,5,2,3,7]
	Output: 5
	Explanation: The longest harmonious subsequence is [3,2,2,2,3].
	*/
	int findLHS(vector<int>& nums)
	{
		// 坑：输入为空--->nums = {}
		if (0 == nums.size())
		{
			return 0;
		}
		map<int, int> container;
		for (auto item : nums)
		{
			container[item]++;
		}
		int maxL = 0;
		for (auto post = ++begin(container); post != end(container); ++post)
		{
			auto prev = --post;
			++post;
			if (post->first == (prev)->first + 1)
			{
				maxL = max(maxL, post->second + (prev)->second);
			}
		}
		return maxL;
	}
};

/**
* Your Twitter object will be instantiated and called as such:
* Twitter obj = new Twitter();
* obj.postTweet(userId,tweetId);
* vector<int> param_2 = obj.getNewsFeed(userId);
* obj.follow(followerId,followeeId);
* obj.unfollow(followerId,followeeId);
*/
struct Tweet
{
	int userID;
	int tweetID;
	int timestamp;
	Tweet(int uid, int tid, int timestmp)
		: userID(uid), tweetID(tid), timestamp(timestmp)
	{};
};

class Twitter
{
public:
	/** Initialize your data structure here. */
	Twitter()
	{
		newest = 10;
	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId)
	{
		tweets[userId].emplace_back(Tweet(userId, tweetId, time++));
		if (followees[userId].find(userId) == end(followees[userId]))
		{
			//followees[userId].insert(userId);
			this->follow(userId, userId);
		}
		//else
		{
		}
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId)
	{
		// 小顶堆
		auto cmp = [](Tweet& left, Tweet& right) { return left.timestamp > right.timestamp; };
		priority_queue<Tweet, vector<Tweet>, decltype(cmp)> pq(cmp);
		for (int user : followees[userId])
		{
			int size = tweets[user].size();
			int length = min(size, newest);
			for (int i = 0; i < length; i++)
			{
				pq.push(tweets[user][size - 1 - i]);
				if (pq.size() > 10)
				{
					pq.pop();
				}
			}
		}
		vector<int> result;
		while (!pq.empty())
		{
			result.emplace_back(pq.top().tweetID);
			pq.pop();
		}
		reverse(begin(result), end(result));
		return result;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId)
	{
		if (followerId != followeeId)
		{
			if (followees.find(followerId) == end(followees))
			{
				this->follow(followerId, followerId);
			}
			if (followees.find(followeeId) == end(followees))
			{
				this->follow(followeeId, followeeId);
			}
		}
		followees[followerId].insert(followeeId);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId)
	{
		if (followerId != followeeId)
		{
			if (followees.find(followerId) != end(followees))
			{
				followees[followerId].erase(followeeId);
			}
		}
	}
private:
	map<int, vector<Tweet>> tweets; // [u] = 用户 u 发的推贴
	map<int, set<int>> followees; // [u] = 用户 u 关注的人
	int newest;
	static int time;
};