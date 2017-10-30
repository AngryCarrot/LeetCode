#include "Solution.h"


#include <ctime>

#include <random>
random_device rd;   // non-deterministic generator
mt19937 gen(rd());  // to seed mersenne twister.
uniform_int_distribution<> dist(0, 100); // distribute results between 1 and 6 inclusive.
uniform_real_distribution<> distF(0, 100);



int main()
{
	FREOPEN;
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
	sln.reverseWords3(s);

	vector<string> strs = { "aaa", "acb" };
	sln.findLUSlength2(strs);

	s = "25525511135";
	sln.restoreIpAddresses(s);

	s = "Hello, he is SB!";
	sln.countSegmentsNB(s);

	s = "abca";
	sln.validPalindrome(s);

	s = "abab";
	sln.repeatedSubstringPattern(s);

	s = "";
	sln.lengthOfLastWord(s);
	s = "abab";
	sln.lengthOfLastWord(s);
	s = "hello world";
	sln.lengthOfLastWord(s);
	s = "world  ";
	sln.lengthOfLastWord(s);

	int n = 5;
	sln.countAndSay(n);

	s = "the sky is blue";
	sln.reverseWords(s);
	s = "  the sky is blue";
	sln.reverseWords(s);
	s = "the  sky is  blue";
	sln.reverseWords(s);
	s = "1 ";
	sln.reverseWords(s);

	strs = { "3:59","10:00", "14:09", "19:08" };
	sln.findMinDifference(strs);
	strs = { "05:31", "22:08", "00:35" };
	sln.findMinDifference(strs);

	s = "(*))";
	// sln.checkValidString(s);
	//s = "(())((())()()(*)(*()(())())())()()((()())((()))(*";
	s = ")()()((()())((()))(*"; 
	sln.checkValidString(s);
	s = "(*)";
	sln.checkValidString(s);

	s = "2*3-4*5";
	sln.diffWaysToCompute(s);
	/*
	vector<int> Nns = { 5000, 50000, 500000, 3000000, 5000000 };
	double result = 0.0f;
	srand(time(0));
	for (int Nn : Nns)
	{
		int m = 0;
		int mm = 0;
		for (int i = 0; i < Nn; ++i)
		{
			double x = rand() % 1001 * 1.0 / 1000;
			double y = rand() % 1001 * 1.0 / 1000;
			if (x * x + y * y <= 1.0f)
			{
				++m;
			}
			double xx = distF(gen) / 100;
			double yy = distF(gen) / 100;
			if (xx * xx + yy * yy <= 1.0f)
			{
				++mm;
			}
		}
		result += m * 4.0 / Nn;
		cout << mm << " " << Nn << " " << (4.0f * mm / Nn) << endl;
	}
	cout << (result / Nns.size()) << endl;
	*/
	s = "42";
	sln.calculate(s);
	s = "3+2*2";
	sln.calculate(s);
	s = "3+4*2/4";
	sln.calculate(s);
	s = " 3/2";
	sln.calculate(s); 
	s = " 3+5 /  2";
	sln.calculate(s);
	s = "3+4*2/2-3*4*54/4";
	sln.calculate(s);
	s = "1*2-3/4+5*6-7*8+9/10";
	sln.calculate(s);

	n = 3;
	sln.generateParenthesis(n);
	
	s = "";
	sln.countBinarySubstrings(s);
	s = "00110011";
	sln.countBinarySubstrings(s);

	string A = "abcd";
	string B = "cdabcdab";
	sln.repeatedStringMatch(A, B);
	A = "bb";
	B = "bbbbbbb";
	sln.repeatedStringMatch(A, B);

	return 0;
}