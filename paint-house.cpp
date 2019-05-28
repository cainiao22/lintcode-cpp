/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-15
* @brief         房屋染色
* @description
*                这里有n个房子在一列直线上，现在我们需要给房屋染色，分别有红色蓝色和绿色。每个房屋染不同的颜色费用也不同，
*                你需要设计一种染色方案使得相邻的房屋颜色不同，并且费用最小，返回最小的费用。
                 费用通过一个nx3 的矩阵给出，比如cost[0][0]表示房屋0染红色的费用，cost[1][2]表示房屋1染绿色的费用
*
* @example       样例 1:
                 输入: [[14,2,11],[11,14,5],[14,3,10]]
                 输出: 10
                 解释: 蓝 绿 蓝, 2 + 5 + 3 = 10

                 样例 2:
                 输入: [[1,2,3],[1,4,6]]
                 输出: 3

* @solution
*/

#include "commonutils.h"

class PaintHouse : public CommonUtils
{
public:
    int minCost(vector<vector<int>> &costs)
    {
        if(costs.size() == 0)
        {
            return 0;
        }
        int numColors = costs[0].size();
        int dp[costs.size() + 1][numColors];
        for(int i=0; i<numColors; i++)
        {
            dp[0][i] = 0;
        }

        for(int i=1; i<costs.size() + 1; i++)
        {
            for(int j=0; j < numColors; j++)
            {
                int MIN = 1e9;
                for(int k=0; k<numColors; k++)
                {
                    if(k != j)
                    {
                        MIN = min(MIN, dp[i-1][k] + costs[i-1][j]);
                    }
                }
                dp[i][j] = MIN;
            }
        }

        int result = 1e9;
        for(int i=0; i<numColors; i++)
        {
            result = min(result, dp[costs.size()][i]);
        }

        return result;
    }


    int minCost2(vector<vector<int>> &costs)
    {
        if(costs.size() == 0)
        {
            return 0;
        }
        int numColors = costs[0].size();
        int dp[2][numColors];
        for(int i=0; i<numColors; i++)
        {
            dp[0][i] = 0;
        }
        int cur = 1;
        for(int i=1; i<costs.size() + 1; i++)
        {
            for(int j=0; j < numColors; j++)
            {
                int MIN = 1e9;
                for(int k=0; k<numColors; k++)
                {
                    if(k != j)
                    {
                        MIN = min(MIN, dp[1-cur][k] + costs[i-1][j]);
                    }
                }
                dp[cur][j] = MIN;
            }
            cur = 1 - cur;
        }

        int result = 1e9;
        for(int i=0; i<numColors; i++)
        {
            result = min(result, dp[1 - cur][i]);
        }

        return result;
    }

    void run()
    {
        //{14,2,11},{11,14,5},{14,3,10}
        vector<vector<int>> costs({{14,2,11},{11,14,5},{14,3,10}});
        int result = this->minCost2(costs);
        cout<<result<<endl;
    }
};


