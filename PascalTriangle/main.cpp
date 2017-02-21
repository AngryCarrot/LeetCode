#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief generate
     * 118. Pascal's Triangle
     * @param numRows 5
     * @return
     * [
         [1],
        [1,1],
       [1,2,1],
      [1,3,3,1],
     [1,4,6,4,1] ]
     */
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> result;
        if (!numRows)
        {
            return result;
        }

        for (int i = 0; i != numRows; ++i)
        {
            vector<int> v;
            for (int j = 0; j != i + 1; ++j)
            {
                if (0 == j || i == j)
                {
                    v.push_back(1);
                }
                else
                {
                    v.push_back(result[i-1][j - 1] + result[i-1][j]);
                }
            }
            result.push_back(v);
        }

        return result;
    }
};

void printAll(vector<int> nums)
{
    for (int i = 0; i != nums.size(); ++i)
    {
        cout << nums.at(i) << " ";
    }
    cout << endl;
}

int main()
{
    cout << "Hello World!" << endl;
    vector<int> vv = {1, 2, 3, 4, 5};
    printAll(vv);
    Solution s;
    vector<vector<int>> v = s.generate(5);
    for (int i = 0; i != v.size(); ++i)
    {
        printAll(v[i]);
    }
    return 0;
}

