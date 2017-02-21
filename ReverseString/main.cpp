#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    string reverseString(string s) {
/*
        int length = s.length();
        string t = "";
        for (int i = length - 1; i >= 0; --i)
        {
            t += s[i];
        }
        return t;
*/
        const char *ss = s.c_str();
        int length = s.length();
        char *st = new char[length];
        strcpy(st, ss);
        char *temp = nullptr;
        char t = '1';
        char *start = st;
        char *end = st + length - 1;
        while(start < end)
        {
            t = *start;
            *start = *end;
            *end = t;
            ++start;
            --end;
        }
        //cout << string(st) << endl;
        return string(st);
    }
};

int main()
{
    cout << "Hello World!" << endl;
    Solution s;

    string str = "";
    while (cin >> str)
    {
        cout << s.reverseString(str) << endl;
    }

    return 0;
}

