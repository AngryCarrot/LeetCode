#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    bool isVowel(const char c)
    {
        switch (c) {
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'i':
        case 'I':
        case 'o':
        case 'O':
        case 'u':
        case 'U':
            return true;

        default:
            return false;
        }
    }

    string reverseString(string s) {
        string st = s;
        int length = s.length();
        char *temp = nullptr;
        char t = '1';
        char *start = &st[0];
        char *end = start + length - 1;
        while(start < end)
        {
            while (!isVowel(*start))
            {
                ++start;
            }
            while (!isVowel(*end))
            {
                --end;
            }
            if (start >= end)
            {
                break;
            }
            t = *start;
            *start = *end;
            *end = t;
            ++start;
            --end;
        }
        //cout << string(st) << endl;
        return st;
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

