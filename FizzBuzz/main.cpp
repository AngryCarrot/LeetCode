#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ve;

        for (int i = 1; i != n + 1; ++i)
        {
            string s = "";
            s = (i % 3 == 0) ? (i % 5 == 0 ? "FizzBuzz" : "Fizz") : (i % 5 == 0 ? "Buzz" : to_string(i));
            ve.push_back(s);
        }

        return ve;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    vector<string> v;
    Solution s;
    int n = 0;
    while (cin >> n)
    {
        v.clear();
        v = s.fizzBuzz(n);
        for (auto item : v)
        {
            cout << item << endl;
        }
    }

    return 0;
}

