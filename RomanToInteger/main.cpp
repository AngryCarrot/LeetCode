#include <iostream>
#include <map>
using namespace std;

class Solution {
public:
    Solution()
    {
        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;
    }

    int romanToInt(string s) {
        int l = s.length() - 1;
        int result = this->m[s[l]];
        for (int i = l - 1; i != -1; --i)
        {
            if (this->m[s[i]] < this->m[s[i + 1]])
            {
                result -= this->m[s[i]];
            }
            else
            {
                result += this->m[s[i]];
            }
        }
        return result;
    }
private:
//    map<char, int> m;
    int m[256];
};

int main()
{
    cout << "Hello World!" << endl;
    Solution s;
    int r = s.romanToInt("MCMXCVI");
    cout << r << endl;
    return 0;
}

