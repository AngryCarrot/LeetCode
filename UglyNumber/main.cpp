#include <iostream>

using namespace std;

class Solution {
public:
    // 263. Ugly Number
    // the number whose prime factors are only 2, 3, 5
    // 1 is treated as ugly number
    bool isUgly(int num) {
        if (0 == num)
            return false;
        while (num % 2 == 0)
        {
            num /= 2;
        }
        while (num % 3 == 0)
        {
            num /= 3;
        }
        while (num % 5 == 0)
        {
            num /= 5;
        }
        return 1 == num;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

