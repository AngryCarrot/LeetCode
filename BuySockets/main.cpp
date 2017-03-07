#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief maxProfit
     * 121. Best Time to Buy and Sell Stock
     * max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
     * In this case, no transaction is done, i.e. max profit = 0.
     * @param prices [7, 1, 5, 3, 6, 4] [7, 6, 4, 3, 1]
     * @return 5 0
     */
    int maxProfit(vector<int>& prices)
    {
        const int length = prices.size();
        if (1 >= length)
        {
            return 0;
        }
        int minPrice = prices[0];
        int maxProf = 0;
        for (int i = 1; i != length; ++i)
        {
            minPrice = min(prices[i], minPrice);
            maxProf = max(prices[i] - minPrice, maxProf);
        }
        return maxProf;
    }
    /** 122. Best Time to Buy and Sell Stock II
     * @brief maxProfit: You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times)
     * However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
     * 不限制交易次数, 只要可以赚就做交易
     * 若同一天可以进行卖出和买入、则用该方法
     * 若同一天只能进行买入或卖出这两者之一的操作，则下面的解答是错的
     * @param prices
     * @return
     */
    int maxProfit_2(vector<int>& prices)
    {
        const int length = prices.size();
        if (1 >= length)
        {
            return 0;
        }
        int maxProf = 0;
        int diff = 0;
        for (int i = 1; i != length; ++i)
        {
            diff = prices[i] - prices[i-1];
            if (0 < diff)
            {
                maxProf += diff;
            }
        }
        return maxProf;
    }

    /** 309. Best Time to Buy and Sell Stock with Cooldown
     * @brief maxProfitCoolDown
     * @param prices [1, 2, 3, 0, 2]
     * @return 3
     * @details [buy, sell, cooldown, buy, sell]
     */
    int maxProfitCoolDown(vector<int>& prices)
    {
        const int length = prices.size();
        if (1 >= length)
        {
            return 0;
        }
        int *buys = new int[length];
        int *sells = new int[length];

        buys[0] = -prices[0];
        buys[1] = max(buys[0], -prices[1]);
        sells[0] = 0;
        sells[1] = max(sells[0], buys[0] + prices[1]);

        for (int i = 2; i < length; ++i)
        {
            sells[i] = max(sells[i-1], buys[i-1] + prices[i]);
            buys[i] = max(sells[i-2] - prices[i], buys[i-1]);
        }

        int maxProf = sells[length - 1];
        delete buys;
        delete sells;
        return maxProf;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

