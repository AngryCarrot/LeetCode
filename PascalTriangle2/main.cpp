#include <iostream>
#include <vector>

using namespace std;

void printAll(vector<int> nums)
{
    for (int i = 0; i != nums.size(); ++i)
    {
        cout << nums.at(i) << " ";
    }
    cout << endl;
}

class Solution {
public:
    /**
     * @brief getRow
     * 119. Pascal's Triangle II
     * @param rowIndex
     * @return
     */
    vector<int> getRow(int rowIndex)
    {
        vector<int> result;
        if (!rowIndex)
        {
            return {1};
        }
        for (int i = 0; i != rowIndex + 1; ++i)
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
                    v.push_back(result[j - 1] + result[j]);
                }
            }
            result = v;
            v.clear();
        }
        return result;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    Solution s ;
    vector<int> r = s.getRow(3);
    printAll(r);
    return 0;
}

