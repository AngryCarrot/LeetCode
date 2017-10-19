#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

const string INPUT = "D:\\Workspace\\VSProject\\LeetCode\\input.txt";
#define FREOPEN freopen(INPUT.c_str(), "r", stdin)


/** Definition for a binary tree node.*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*bool isSame(TreeNode* t1, TreeNode* t2)
{
	if (t1 == nullptr && t2 == nullptr)
	{
		return true;
	}
	if (((t1 == nullptr) && (t2 != nullptr))
		|| ((t1 != nullptr) && (t2 == nullptr)))
	{
		return false;
	}
	if (t1->val == t2->val)
	{
		return isSame(t1->left, t2->left) && isSame(t1->right, t2->right);
	}
	else
	{
		return false;
	}
}*/

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
				if (word1[i - 1] == word2[j - 1])
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
	string reverseWords3(string& s)
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
	Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2.
	(each operation is counted as 1 step.)
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

	/*93. Restore IP Addresses
	Given a string containing only digits, restore it by returning all possible valid IP address combinations.
	For example:
	Given "25525511135",
	return ["255.255.11.135", "255.255.111.35"]. (Order does not matter) */
	vector<string> restoreIpAddresses(string& s)
	{
		vector<string> results;
		int length = s.length();
		if (length < 4 || length > 12)
		{
			return results;
		}
		//25525511135;
		//255.255.11.135;
		string ip;
		for (int i = 1; i <= min(3, length - 3); ++i)
		{
			int one = atoi(s.substr(0, i).c_str());
			if (one > 255)
			{
				continue;
			}
			for (int j = 1; j <= min(3, length - i - 2); ++j)
			{
				int two = atoi(s.substr(i, j).c_str());
				if (two > 255)
				{
					continue;
				}
				for (int k = 1; k <= min(3, length - i - j - 1); ++k)
				{
					int three = atoi(s.substr(i + j, k).c_str());
					if (three > 255)
					{
						continue;
					}
					int four = atoi(s.substr(i + j + k).c_str());
					{
						if (four > 255)
						{
							continue;
						}
					}
					ip = to_string(one) + "." + to_string(two) + "." + to_string(three) + "." + to_string(four);
					if (ip.length() - 3 == length)
					{
						results.emplace_back(ip);
					}
				}
			}
		}
		return results;
	}

	/*434. Number of Segments in a String */
	int countSegments(string& s)
	{
		int results = 0;
		s.append(" ");
		int length = s.length();
		for (int i = 1; i < length; ++i)
		{
			if (s[i] == ' ' && s[i - 1] != ' ')
			{
				++results;
			}
		}
		return results;
	}
	int countSegmentsNB(string& s)
	{
		stringstream ss(s);
		int results = 0;
		while (ss >> s)
		{
			++results;
		}
		return results;
	}
	/*657. Judge Route Circle */
	bool judgeCircle(string moves)
	{
		pair<int, int> position(0, 0);
		for (char c : moves)
		{
			switch (c)
			{
			case 'U':
				++position.second;
				break;
			case 'D':
				--position.second;
				break;
			case 'L':
				--position.first;
				break;
			case 'R':
				++position.first;
				break;
			default:
				break;
			}
		}
		return position.first == 0 && position.second == 0;
	}

	/*547. Friend Circles
	Input:
	[[1,1,0],
	 [1,1,0],
	 [0,0,1]]
	Output: 2
	*/
	int findCircleNum(vector<vector<int>>& M)
	{
		int results = 0;
		int rows = M.size();
		if (0 == rows)
		{
			return results;
		}
		int cols = M[0].size();
		if (0 == cols)
		{
			return results;
		}
		vector<vector<bool>> used(rows, vector<bool>(cols, false));
		queue<int> rsq;
		queue<int> csq;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = i; j < cols; ++j)
			{
				if (!used[i][j] && M[i][j] == 1)
				{
					used[i][j] = true;
					++results;
					rsq.push(i);
					csq.push(j);
					while (!rsq.empty())
					{
						int k = rsq.size();
						for (int l = 0; l < k; ++l)
						{
							int ii = rsq.front();
							int jj = csq.front();
							rsq.pop();
							csq.pop();
							if (ii - 1 >= 0 && M[ii - 1][jj] == 1 && !used[ii - 1][jj])
							{
								used[ii - 1][jj] = true;
								rsq.push(ii - 1);
								csq.push(jj);
							}
							if (ii + 1 < rows && M[ii + 1][jj] == 1 && !used[ii + 1][jj])
							{
								used[ii + 1][jj] = true;
								rsq.push(ii + 1);
								csq.push(jj);
							}
							if (jj - 1 >= i && M[ii][jj - 1] == 1 && !used[ii][jj - 1])
							{
								used[ii][jj - 1] = true;
								rsq.push(ii);
								csq.push(jj - 1);
							}
							if (jj + 1 < cols && M[ii][jj + 1] == 1 && !used[ii][jj + 1])
							{
								used[ii][jj + 1] = true;
								rsq.push(ii);
								csq.push(jj + 1);
							}
						}
					}
				}
			}
		}
		return results;
	}

	/*680. Valid Palindrome II
	Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome*/
	bool validPalindrome(string& s)
	{
		int left = 0;
		int right = s.length() - 1;
		while (left < right)
		{
			if (s[left] == s[right])
			{
				++left;
				--right;
			}
			else
			{
				return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
			}
		}
		return true;
	}
	bool isPalindrome(string& s, int left, int right)
	{
		while (left <= right)
		{
			if (s[left] != s[right])
			{
				return false;
			}
			else
			{
				++left;
				--right;
			}
		}
		return true;
	}
	/*520. Detect Capital
	Given a word, you need to judge whether the usage of capitals in it is right or not.
	We define the usage of capitals in a word to be right when one of the following cases holds:
		All letters in this word are capitals, like "USA".
		All letters in this word are not capitals, like "leetcode".
		Only the first letter in this word is capital if it has more than one letter, like "Google".
	Otherwise, we define that this word doesn't use capitals in a right way. */
	bool detectCapitalUse(string& word)
	{
		int upperCase = count_if(begin(word), end(word), [](char c) {return c >= 'A' && c <= 'Z'; });
		int length = word.length();
		// rule 1
		if (upperCase == length)
		{
			return true;
		}
		// rule 2
		if (upperCase == 0)
		{
			return true;
		}
		// rule 3
		if (upperCase == 1 && (word[0] >= 'A' && word[0] <= 'Z'))
		{
			return true;
		}
		return false;
	}

	/*606. Construct String from Binary Tree
		Input: Binary tree: [1,2,3,4]
			   1
			 /   \
			2     3
		   /
		  4
		Output: "1(2(4))(3)"
		Explanation: Originallay it needs to be "1(2(4)())(3()())",
		but you need to omit all the unnecessary empty parenthesis pairs.
		And it will be "1(2(4))(3)".

		Input: Binary tree: [1,2,3,null,4]
			   1
			 /   \
			2     3
			 \
			  4
		Output: "1(2()(4))(3)"
		Explanation: Almost the same as the first example,
		except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.*/
	string tree2str(TreeNode* t)
	{
		string results;
		tree2strHelper(t, results);
		results.pop_back();
		results.erase(0, 1);
		return results;
	}
	void tree2strHelper(TreeNode* t, string& results)
	{
		if (t == nullptr)
		{
			return;
		}
		results.append(to_string(t->val));
		if (t->left != nullptr)
		{
			results.append("(");
			tree2strHelper(t->left, results);
			results.append(")");
			if (t->right != nullptr)
			{
				results.append("(");
				tree2strHelper(t->right, results);
				results.append(")");
			}
		}
		else
		{
			if (t->right != nullptr)
			{
				results.append("()(");
				tree2strHelper(t->right, results);
				results.append(")");
			}
		}
	}
	string tree2strNB(TreeNode* t)
	{
		if (t == nullptr)
			return "";
		if (t->left == nullptr && t->right == nullptr)
			return t->val + "";
		if (t->right == nullptr)
			return t->val + "(" + tree2strNB(t->left) + ")";
		return t->val + "(" + tree2strNB(t->left) + ")(" + tree2strNB(t->right) + ")";
	}

	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
	{
		vector<TreeNode*> results;
		map<string, int> memo;
		findDuplicateSubtrees(root, memo, results);
		return results;
	}
	void findDuplicateSubtrees(TreeNode* root, map<string, int>& memo, vector<TreeNode*>& results)
	{
		if (root == nullptr)
		{
			return;
		}
		string t2s = serialize(root);
		if (memo[t2s] == 1)
		{
			results.emplace_back(root);
		}
		memo[t2s]++;
		findDuplicateSubtrees(root->left, memo, results);
		findDuplicateSubtrees(root->right, memo, results);
	}
	string serialize(TreeNode* root)
	{
		if (root == nullptr)
		{
			return "#";
		}
		return to_string(root->val) + "(" + serialize(root->left) + ")(" + serialize(root->right) + ")";
	}

	/*551. Student Attendance Record I
	You are given a string representing an attendance record for a student. The record only contains the following three characters:

		'A' : Absent.
		'L' : Late.
		'P' : Present.

	A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).
	You need to return whether the student could be rewarded according to his attendance record.*/
	bool checkRecord(string s)
	{
		int length = s.length();
		int count = 0;
		for (int i = 0; i < length; ++i)
		{
			if (i >= 2 && s[i] == 'L' && s[i - 1] == 'L' && s[i - 2] == 'L')
			{
				return false;
			}
			if (s[i] == 'A')
			{
				++count;
				if (count > 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	/*459. Repeated Substring Pattern
	Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
	*/
	bool repeatedSubstringPattern(string& s)
	{
		int length = s.length();
		for (int i = 0; i < length / 2; ++i)
		{
			if (isCopied(s, s.substr(0, i + 1)))
			{
				return true;
			}
		}
		return false;
	}
	bool isCopied(const string& s1, const string& s2)
	{
		int length1 = s1.length();
		int length2 = s2.length();
		if (length1 % length2 != 0)
		{
			return false;
		}
		int k = length1 / length2;
		for (int i = 0; i < k; ++i)
		{
			string sss = s1.substr(i * length2, length2);
			if (s1.substr(i * length2, length2) != s2)
			{
				return false;
			}
		}
		return true;
	}
	/*真他妈的牛逼
	str + str means doubling, (str + str).substr(1, str.size() * 2 - 2) means removing the first char of the first half and the last char of the second half.
			If there is no pattern, both of the first copy and the second copy will be changed,
		so str will not be found in (str + str).substr(1, str.size() * 2 - 2).
			If there is a pattern, the first char of str can still be found in the first half,
		and the last char of str can also be found in the second half.
	Here is an example: abcabc is the original string, and (bcabc abcab) includes abcabc.*/
	bool repeatedSubstringPatternNB(string& s)
	{
		return (s + s).substr(1, s.length() * 2 - 2).find(s) != -1;
	}

	/*58. Length of Last Word
	Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
	return the length of last word in the string.
	If the last word does not exist, return 0.*/
	int lengthOfLastWord(string s)
	{
		int tail = s.length() - 1;
		while (tail >= 0 && s[tail] == ' ')
		{
			--tail;
		}
		int count = 0;
		while (tail >= 0 && s[tail] != ' ')
		{
			++count;
			--tail;
		}
		return count;
	}

	/*38. Count and Say
	1.     1----------->1 is read off as "one 1" or 11.
	2.     11----------->11 is read off as "two 1s" or 21.
	3.     21----------->21 is read off as "one 2, then one 1" or 1211.
	4.     1211----------->
	5.     111221----------->
	*/
	string countAndSay(int n)
	{
		if (n == 0)
		{
			return "";
		}
		if (n == 1)
		{
			return "1";
		}
		n -= 2;
		string result = "11";
		while (n--)
		{
			string tmp = "";
			char ch = result[0];
			int count = 1;
			for (int i = 1; i < result.length(); ++i)
			{
				if (ch == result[i])
				{
					++count;
				}
				else
				{
					tmp.append(to_string(count) + ch);
					ch = result[i];
					count = 1;
				}
			}
			tmp.append(to_string(count) + ch);
			result = tmp;
		}
		return result;
	}
	/*151. Reverse Words in a String
	Given an input string, reverse the string word by word.
		For example,
		Given s = "the sky is blue",
		return "blue is sky the".
	What constitutes a word?
		A sequence of non-space characters constitutes a word.
	Could the input string contain leading or trailing spaces?
		Yes. However, your reversed string should not contain leading or trailing spaces.
	How about multiple spaces between two words?
		Reduce them to a single space in the reversed string.*/
	void reverseWords(string &s)
	{
		//s.append(" ");
		int length = s.length();
		int startIdx = 0;
		for (int i = 0; i < length; ++i)
		{
			if (s[i] != ' ')
			{
				startIdx = i;
				break;
			}
			startIdx++;
		}
		if (startIdx == length)
		{
			s = "";
			return;
		}
		int endIdx = length - 1;
		while (s[endIdx] == ' ')
		{
			--endIdx;
		}
		string results = "";
		for (int i = endIdx; i >= startIdx; --i)
		{
			if (s[i] != ' ')
			{
				results.push_back(s[i]);
			}
			else
			{
				if (s[i - 1] != ' ')
				{
					results.push_back(s[i]);
				}
			}
		}
		int left = 0;
		int right = 0;
		while ((right = results.find_first_of(' ', left)) != -1)
		{
			int i = left;
			int j = right - 1;
			while (i < j)
			{
				swap(results[i++], results[j--]);
			}
			left = right + 1;
		}
		int i = left;
		int j = results.length() - 1;
		while (i < j)
		{
			swap(results[i++], results[j--]);
		}
		s = results;
		cout << s << endl;
	}

	/*383. Ransom Note
	Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.
	Each letter in the magazine string can only be used once in your ransom note.*/
	bool canConstruct(string ransomNote, string magazine)
	{
		map<char, int> ransoms;
		map<char, int> dict;
		for (char c : ransomNote)
		{
			++ransoms[c];
		}
		for (char c : magazine)
		{
			++dict[c];
		}
		for (auto item : ransoms)
		{
			if (dict[item.first] < ransoms[item.first])
			{
				return false;
			}
		}
		return true;
	}

	/*5. Longest Palindromic Substring
	Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.*/
	string longestPalindrome(string s)
	{
		int length = s.length();
		if (length == 0)
		{
			return "";
		}
		if (length == 1)
		{
			return s;
		}
		string longest = "";
		for (int i = 0; i < length - 1; ++i)
		{
			string p1 = expandSubString(s, i, i);
			if (longest.length() < p1.length())
			{
				longest = p1;
			}
			string p2 = expandSubString(s, i, i + 1);
			if (longest.length() < p2.length())
			{
				longest = p2;
			}
		}
		return longest;
	}
	string expandSubString(string& s, int left, int right)
	{
		int i = left;
		int j = right;
		int length = s.length() - 1;
		while (i >= 0 && j <= length && s[i] == s[j])
		{
			--i;
			++j;
		}
		return s.substr(i + 1, j - i - 1);
	}

	/*556. Next Greater Element III
	Given a positive 32-bit integer n, you need to find the smallest 32-bit integer
	which has exactly the same digits existing in the integer n and is greater in value than n.
	If no such positive 32-bit integer exists, you need to return -1.*/
	int nextGreaterElement(int n) {
		string s = to_string(n);
		next_permutation(begin(s), end(s));
		auto res = stoll(s);
		return (res > INT_MAX || res <= n) ? -1 : res;
	}
	/*如果从数字的第k位开始到数字尾部都是递减的并且第k位数字比第k-1位数字大，
	表明从第k位开始到尾部的这段数字是他们能组合出的最大数字，
	在下一个数字中他们要整体倒序变为能组合出的最小数字，
	倒序后从这段数字序列中找出第一个大于第k-1位数字的位置和第k-1位交换即可。
	举个栗子，如果n=13452，其中52是递减的，而且5>4，
	这样我们先把52倒序，n就变为13425，然后从25中找出第一个大于4的数字和4交换，就得到了最终结果13524。
	需要注意的是下一个数字可能会超出INT_MAX范围。具体代码：*/
	int nextGreaterElementNB(int n) {
		string num = to_string(n);
		int i = num.size() - 1;

		while (i && num[i] <= num[i - 1])
		{
			--i;
		}
		if (i == 0)
		{
			return -1;
		}
		reverse(begin(num), end(num));
		for (int j = i; j < num.size(); ++j)
		{
			if (num[j] > num[i - 1])
			{
				swap(num[j], num[i - 1]);
				break;
			}
		}

		if (num.size() == 10 && num > to_string(INT_MAX))
		{
			return -1;
		}
		return stoi(num);
	}

	/*539. Minimum Time Difference
	Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum minutes difference between any two time points in the list.
	Example 1:
	Input: ["23:59","00:00"]
	Output: 1*/
	int findMinDifference(vector<string>& timePoints)
	{
		vector<int> timestamp;
		int result = INT_MAX;

		for (string timePoint : timePoints)
		{
			int hour = atoi(timePoint.substr(0, timePoint.find(':')).c_str());
			int minite = atoi(timePoint.substr(timePoint.find(':') + 1).c_str());
			int minutes = hour * 60 + minite;
			timestamp.emplace_back(minutes);
		}

		/*for (int i = 0; i < timePoints.size(); ++i)
		{
			timestamp.emplace_back(timestamp[i] + 24 * 60);
		}*/
		sort(begin(timestamp), end(timestamp));
		timestamp.emplace_back(timestamp.front());

		for (int i = 1; i < timestamp.size(); ++i)
		{
			int diff = timestamp[i] - timestamp[i - 1];
			result = min(result, diff < 0 ? diff + 1440 : diff);
		}
		return result;
	}

	/*71. Simplify Path
	Given an absolute path for a file (Unix-style), simplify it.
	path = "/home/", => "/home"
	path = "/a/./b/../../c/", => "/c"
	"/home/foo/.ssh/authorized_keys/"
	"/home/foo/.ssh/../.ssh2/authorized_keys/"
	"/a/./b///../c/../././../d/..//../e/./f/./g/././//.//h///././/..///"	*/
	string simplifyPath(string path)
	{
		string last = "";
		stack<string> stk;
		stk.push("/");
		path.push_back('/');
		int length = path.length();
		for (int i = 1; i < length; ++i)
		{
			if (path[i] == '/' && path[i - 1] != '/')
			{
				if (last == "..")
				{
					if (stk.top() != "/")
					{
						stk.pop();
					}
				}
				else
				{
					if (last != ".")
					{
						stk.push(last);
					}
				}
				last = "";
			}
			else
			{
				if (path[i] == '.' || isalnum(path[i]) || path[i] == '_')
				{
					last.push_back(path[i]);
				}
			}
		}
		if (stk.size() == 1)
		{
			return "/";
		}
		string result = "";
		while (stk.top() != "/")
		{
			result = "/" + stk.top() + result;
			stk.pop();
		}
		return result;
	}

	/* 678. Valid Parenthesis String 
	Any left parenthesis '(' must have a corresponding right parenthesis ')'.
	Any right parenthesis ')' must have a corresponding left parenthesis '('.
	Left parenthesis '(' must go before the corresponding right parenthesis ')'.
	'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
	An empty string is also valid.
	*/
	bool checkValidString(string& s) {
		if (s == "" || s == "*")
		{
			return true;
		}
		int count = 0;
		return checkValidString(s, count);
	}
	bool checkValidString(const string& s, int count)
	{
		if (s == "")
		{
			return count == 0;
		}
		if (s == ")") return count = 1;
		if (s == "(") return false;
		if (s == "*") return count == 0 || count == 1;
		if (s[0] == '*')
		{
			bool r1 = checkValidString(s.substr(1), count + 1);
			bool r2 = checkValidString(s.substr(1), count);
			bool r3 = checkValidString(s.substr(1), count - 1);
			return r1 || r2 || r3;
		}
		if (s[0] == '(')
		{
			++count;
		}
		if (s[0] == ')')
		{
			if (count <= 0)
			{
				return false;
			}
			--count;
		}
		return checkValidString(s.substr(1), count);
	}

	bool checkValidStringNB(string& s) 
	{
		int lower = 0;
		int upper = 0;
		for (char c : s)
		{
			if (c == '(')
			{
				++lower;
				++upper;
			}
			else
			{
				if (c == ')')
				{
					--lower;
					--upper;
				}
				else
				{
					--lower;
					++upper;
				}
			}
			lower = max(lower, 0);
			if (upper < 0)
			{
				return false;
			}
		}
		return lower == 0;
	}

	/* 241. Different Ways to Add Parentheses
	Input: "2*3-4*5"
			(2*(3-(4*5))) = -34
			((2*3)-(4*5)) = -14
			((2*(3-4))*5) = -10
			(2*((3-4)*5)) = -10
			(((2*3)-4)*5) = 10
	这题与95：Unique Binary Search Trees 2一样的解法
	*/
	vector<int> diffWaysToCompute(string& input) 
	{
		vector<int> result;
		for (int i = 0; i < input.length(); ++i)
		{
			if (isOperator(input[i]))
			{
				vector<int> left = diffWaysToCompute(input.substr(0, i));
				vector<int> right = diffWaysToCompute(input.substr(i + 1));
				for (int itemLeft : left)
				{
					for (int itemRight : right)
					{
						result.emplace_back(calc(itemLeft, itemRight, input[i]));
					}
				}
			}
		}
		if (result.size() == 0)
		{
			result.emplace_back(stoi(input));
		}
		return result;
	}
	bool isOperator(const char& c)
	{
		bool result = false;
		switch (c)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			result = true;
			break;
		default:
			result = false;
			break;
		}
		return result;
	}
	int calc(int op1, int op2, int op)
	{
		int result = false;
		switch (op)
		{
		case '+':
			result = op1 + op2;
			break;
		case '-':
			result = op1 - op2;
			break;
		case '*':
			result = op1 * op2;
			break;
		case '/':
			result = op1 / op2;
			break;
		default:
			result = 0;
			break;
		}
		return result;
	}
};

