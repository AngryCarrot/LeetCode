#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack()
    {
    }

    void push(int x)
    {
        container.push(x);
        if (minStack.empty())
        {
            minStack.push(x);
        }
        else
        {
            int min = minStack.top();
            if (min <= x)
            {
                minStack.push(min);
            }
            else
            {
                minStack.push(x);
            }
        }
    }

    void pop()
    {
        container.pop();
        minStack.pop();
    }

    int top()
    {
        return container.top();
    }

    int getMin()
    {
        return minStack.top();
    }
private:
    stack<int> container;
    stack<int> minStack;
};

class Solution {
public:
    /** 239. Sliding Window Maximum
     * @brief maxSlidingWindow
     *  Window position                Max
        ---------------               -----
        [1  3  -1] -3  5  3  6  7       3
         1 [3  -1  -3] 5  3  6  7       3
         1  3 [-1  -3  5] 3  6  7       5
         1  3  -1 [-3  5  3] 6  7       5
         1  3  -1  -3 [5  3  6] 7       6
         1  3  -1  -3  5 [3  6  7]      7
     * @param nums = [1 3 -1 -3 5 6 7]
     * @param k = 3
     * @return [3,3,5,5,6,7]
     */
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> result;
        const int length = nums.size();
        if (0 == length)
        {
            return result;
        }
        const int end = length - k + 1;
        int maxIdx = 0;
        int maxVal = this->findMax(nums, 0, k, maxIdx);
        result.push_back(maxVal);
        for (int i = 1; i < end; ++i)
        {
            if (maxVal <= nums[i + k - 1])
            {
                maxVal = nums[i + k - 1];
                maxIdx = i + k - 1;
                result.push_back(maxVal);
            }
            else
            {
                if (maxIdx >= i)
                {
                    result.push_back(maxVal);
                }
                else
                {
                    maxVal = this->findMax(nums, i, i + k, maxIdx);
                    result.push_back(maxVal);
                }
            }
        }
        return result;
    }
    int findMax(vector<int> nums, int begin, int end, int &maxIdx)
    {
        int maxVal = nums[begin];
        maxIdx = begin;
        for (int i = begin + 1; i < end; ++i)
        {
            if (maxVal <= nums[i])
            {
                maxVal = nums[i];
                maxIdx = i;
            }
        }
        return maxVal;
    }
    /** 20. Valid Parentheses
     * @brief isValid
     * @details Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
     * @param s
     * @return
     * @note "){"
     */
    bool isValid(string s)
    {
        const int length = s.length();
        if (0 == length)
        {
            return true;
        }
        if (1 == length)
        {
            return false;
        }
        stack<char> stk;
        for (char c : s)
        {
            if ('(' == c || '[' == c || '{' == c)
            {
                stk.push(c);
            }
            else
            {
                switch (c)
                {
                case ')':
                    // !stk.empty() is pit I
                    if (!stk.empty() && '(' == stk.top())
                    {
                        stk.pop();
                    }
                    else
                    {
                        return false;
                    }
                    break;
                case ']':
                    if (!stk.empty() && '[' == stk.top())
                    {
                        stk.pop();
                    }
                    else
                    {
                        return false;
                    }
                    break;
                case '}':
                    if (!stk.empty() && '{' == stk.top())
                    {
                        stk.pop();
                    }
                    else
                    {
                        return false;
                    }
                    break;
                }
            }
        }
        // pit 2
        if (stk.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    /**
     * @brief nextGreaterElement
     * @param findNums
     * @param nums
     * @return
     */
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {

    }
};

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    vector<string> v = {"1234", "2345", "+"};
    string s = "1234";
    for (string item : v)
    {
        int i = atoi(item.c_str());
        cout << i << endl;
    }

    int j = stoi(s);
    cout << j << endl;

    return 0;
}
