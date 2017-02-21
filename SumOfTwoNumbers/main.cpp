#include <iostream>

using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
        int result = 0;
        while (b)
        {
            result = a ^ b;
            b = (a & b) << 1;
            a = result;
        }
        return a;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    Solution s;
    cout << s.getSum(5, 7) << endl;
    return 0;
}

