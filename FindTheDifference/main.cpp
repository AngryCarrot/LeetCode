#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class Solution {
public:
    char findTheDifferenceXOR(string s, string t)
    {
        char r=0;
        for(char c:s) r ^=c;
        for(char c:t) r ^=c;
        return r;
    }

    char findTheDifference(string s, string t) {
        int a[26];
        memset(a, 0, sizeof(a));
        for (char c : t)
        {
            cout << c << " ";
            ++a[c - 'a'];
        }
        cout << endl;
        for(char c : s)
        {
            cout << c << " ";
            --a[c - 'a'];
        }
        cout << endl;
        for (int i = 0; i != 26; ++i)
        {
            cout << a[i] << " ";
            if (0 != a[i])
            {
                return i + 'a';
            }
        }
        cout << endl;
        return '\0';
    }
};

int main()
{
    string s = "bcde";
    string t = "abcde";
    Solution ss;
    char c = ss.findTheDifference(s, t);

    cout << c << endl;

    return 0;
}

