#include <iostream>

using namespace std;

class Solution {
public:
    int addDigits(int num)
    {
        return 1 + (num - 1) % 9;
    }
};

int main()
{
    cout << "Hello World!" << endl;

    Solution s;
    int a = s.addDigits(388);
    cout << a << endl;
    return 0;
}

