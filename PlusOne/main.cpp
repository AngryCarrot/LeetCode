#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result;
        int flag = 1;
        int r = 0;
        int length = digits.size();
        for (int i = length - 1; i >= 0; --i)
        {
            r = (digits[i] + flag) % 10;
            result.insert(result.begin(), r);
            flag = r == 0;
        }
        /*for (vector<int>::reverse_iterator iter = digits.rbegin(); iter != digits.rend(); ++iter)
        {
            r = *iter + flag;
            result.insert(result.begin(), r % 10);
            flag = r / 10;
        }*/
        if (flag)
        {
            result.insert(result.begin(), flag);
        }
        return result;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    vector<int> digits = {9};
    Solution s;
    vector<int> r = s.plusOne(digits);
    for(int item : r)
    {
        cout << item << endl;
    }

    return 0;
}

