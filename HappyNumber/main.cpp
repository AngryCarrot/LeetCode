#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    // 202. Happy Number
    /*
     * 19 is a happy number
     * 1^2 + 9^2 = 82
     * 8^2 + 2^2 = 68
     * 6^2 + 8^2 = 100
     * 1^2 + 0^2 + 0^2 = 1
    */
    bool isHappy(int n) {
        if (20 > n)
        {
            switch (n) {
            case 1:
            case 7:
            case 10:
            case 13:
            case 19:
                return true;
                break;
            default:
                return false;
                break;
            }
        }
        int sum = 0;
        while (n)
        {
            sum += pow(n % 10, 2);
            n /= 10;
        }
        return isHappy(sum);
    }
};

int main()
{
    cout << "Hello World!" << endl;

    Solution s;
    cout << s.isHappy(1) << endl;
    return 0;
}

