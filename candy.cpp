/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-07
* @brief         分糖果

* @description
*
*                有 N 个小孩站成一列。每个小孩有一个评级。给定数组 ratings 代表这些小孩的评级。
                 现在你需要按照以下要求，给小孩们分糖果：
                 每个小孩至少得到一颗糖果。
                 评级越高的小孩可以比他相邻的两个小孩得到更多的糖果。

                 你最少要准备多少糖果？

* @example       Example 1:

                 Input: [1, 2]
                 Output: 3
                 Explanation: Give the first child 1 candy and give the second child 2 candies.
                 Example 2:

                 Input: [1, 1, 1]
                 Output: 3
                 Explanation: Give every child 1 candy.
                 Example 3:

                 Input: [1, 2, 2]
                 Output: 4
                 Explanation:
                     Give the first child 1 candy.
                     Give the second child 2 candies.
                     Give the third child 1 candy.
* @solution
*/

#include "commonutils.h"

class Candy : public CommonUtils
{
public:

    vector<int> dp;

    //dp解法 + memory
    int minCandy(int k, vector<int> &ratings)
    {
        dp[k] = 1;
        if(k > 0 && ratings[k] > ratings[k-1])
        {
            dp[k] = max(dp[k], (dp[k-1] > 0 ? dp[k-1] : minCandy(k-1, ratings)) + 1);
        }

        if(k < ratings.size() - 1 && ratings[k] > ratings[k+1])
        {
            dp[k] = max(dp[k], (dp[k+1] > 0 ? dp[k+1] : minCandy(k+1, ratings)) + 1);
        }

        return dp[k];
    }

    int candy(vector<int> &ratings)
    {
        dp.assign(ratings.size(), 0);
        int sum = 0;
        for(int i=0; i<ratings.size(); i++)
        {
            int item = minCandy(i, ratings);
            sum += item;
        }
        return sum;
    }

    //贪心法 两次扫描
    int candy2(vector<int> &ratings)
    {
        dp.assign(ratings.size(), 1);
        for(int i=1; i<ratings.size(); i++)
        {
            if(ratings[i] > ratings[i-1])
            {
                dp[i] = dp[i-1] + 1;
            }
        }

        int sum = 0;
        sum += dp[ratings.size()-1];
        for(int i=ratings.size()-2; i>=0; i--)
        {
            if(ratings[i] > ratings[i+1])
            {
                dp[i] = max(dp[i], dp[i+1] + 1);
            }

            sum += dp[i];
        }

        return sum;
    }

    void run()
    {
        vector<int> ratings({1,2,2});
        int sum = this->candy2(ratings);
        cout<<sum<<endl;
    }
};

