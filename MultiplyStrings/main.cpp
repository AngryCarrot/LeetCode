#include <iostream>

using namespace std;

class Solution {
public:
    string multiplySingle(string num1, int n)
    {
        if (1 == n)
        {
            return num1;
        }
        int l1 = num1.length() - 1;
        int flag = 0;
        int t = 0;
        string result = "";
        while (l1 >= 0 || flag)
        {
            t = n * (l1 >= 0 ? num1[l1--] - 48 : 0) + flag;
            result.insert(result.begin(), t % 10 + 48);
            flag = t / 10;
        }
        return result;
    }

    string StringAdd(string num1, string num2)
    {
        int l1 = num1.length() - 1;
        int l2 = num2.length() - 1;
        int flag = 0;
        string result = "";
        int t = 0;
        int tl1 = 0, tl2 = 0;
        while (l1 >= 0 || l2 >= 0 || flag)
        {
            tl1 = l1 >= 0 ? num1[l1--] - 48 : 0;
            tl2 = l2 >= 0 ? num2[l2--] - 48 : 0;
            t = tl1 + tl2 + flag;
            result.insert(result.begin(), t % 10 + 48);
            flag = t / 10;
        }
        return result;
    }

    string multiply(string num1, string num2) {
        if ("0" == num1 || "0" == num2)
        {
            return "0";
        }
        int l1 = num1.length() - 1;
        int l2 = num2.length() - 1;
        if (l2 > l1)
        {
            swap(num1, num2);
            l1 = l1 + l2;
            l2 = l1 - l2;
            l1 = l1 - l2;
        }
        int l1_l = l1;
        int flag = 0;
        string result = "", r2 = "";
        int t = 0;
        int tl1 = 0;
        int tl2 = 0;
        while (l1 >= 0)
        {
            tl1 = l1 >= 0 ? num1[l1] - 48 : 1;
            r2 = this->multiplySingle(num2, tl1);
            string s(l1_l - l1, '0');
            r2 += s;
            result = this->StringAdd(result, r2);
            --l1;
        }

        return result;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    Solution s;
    string n1 = "125";
    string n2 = "0";
    string result = s.multiply(n1, n2);
    cout << result << endl;
    return 0;
}

