#include "Solution.h"

int main()
{
	Solution sln;
	string haystack = "1234567235";
	string needle = "235";
	sln.strStr(haystack, needle);
	
	string s = "abpcplea";
	vector<string> d = { "ale", "apple", "monkey", "plea" };
	sln.findLongestWord(s, d);

	string s1 = "ab";
	string s2 = "eidbaooo";
	sln.checkInclusion(s1, s2);

	return 0;
}