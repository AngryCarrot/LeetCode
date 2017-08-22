#include "Solution.h"

int main()
{
	Solution sln;
	string s = "a.";

	sln.isPalindrome(s);

	string word1 = "food";
	string word2 = "money";
	sln.minDistance(word1, word2);

	s = "kjdsahfdosaripeouwyfqs";
	int k = 5;
	sln.reverseStr(s, k);

	s = "Let's take LeetCode contest";
	sln.reverseWords(s);

	vector<string> strs = { "aaa", "acb" };
	sln.findLUSlength2(strs);

	return 0;
}