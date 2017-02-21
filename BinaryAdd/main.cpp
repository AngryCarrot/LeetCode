#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b)
    {
        int length = a.length() > b.length() ? a.length() : b.length();
        int la = a.length() - 1;
        int lb = b.length() - 1;
        string result = "";

        int i = 0;
        int flag = 0;
        while (la >= 0 || lb >= 0 || flag)
        {
            int ai = la >= 0 ? a[la--] - 48 : 0;
            int bi = lb >= 0 ? b[lb--] - 48 : 0;
            int r = ai + bi + flag;
            result = char(r % 2 + 48) + result;
            flag = r / 2;
        }

        return result;
    }
};

int main()
{    
    Solution s;
    string result = s.addBinary("10101", "1011");
    cout << result << endl;
    return 0;
}


