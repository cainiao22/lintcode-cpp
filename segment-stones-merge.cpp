/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-08
* @brief         段式石子归并
* @description
*               有一个石子归并的游戏。最开始的时候，有n堆石子排成一列，目标是要将所有的石子合并成一堆。合并规则如下：

                每一次可以合并连续x堆石子，left <= x <= right
                每次合并的代价为所合并的x堆石子的重量之和
                求出最小的合并代价，如果无法完成合并返回0
                1 <= n <= 100，2 <= left <= right <= n
                1 <= weight[i] <= 1000
* @example
*               给出 n = 4, left = 3, right = 3, weight = [1,2,3,4] ,返回 0。

                解释：
                无法完成合并
                给出 n = 3, left = 2, right = 3 , weight = [1,2,3], 返回 6。

                解释：
                将1,2,3合并即可，合并代价为1+2+3=6。


* @solution  又像dp问题 类似于矩阵计算,比它复杂
*            dp[i][j][k] 表示将i~j区间的数据合并为k堆所需要的代价
*            dp[i][j][k] = min(dp[i][t][k-1] + dp[t+1][j][1]){i<=t<=j}
*            最终i~j都要合并为1堆
*            dp[i][j][1] = min(dp[i][j][k] + weight[i~j]){left<=k<=right}
*            最终结果
*            dp[1][n][1]
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

//TODO 段式石子归并
class SegmentStonesMerge
{
public:
    int INF = 100000;
    int getMinimumCost(int n, int left, int right, vector<int> &weight) {
        int dp[n+1][n+1][n+1];
        int sum[n+1] = {0};
        for(int i=1; i<=n; i++)
        {
            sum[i] = sum[i-1] + weight[i-1];
        }

        for(int i=0; i<=n; i++)
        {
            for(int j=0; j<=n; j++)
            {
                for(int k=0; k<=n; k++)
                {
                    dp[i][j][k] = INF;
                    if(k == j - i + 1)
                    {
                        dp[i][j][k] = 0;
                    }
                }
            }
        }

        for(int len = left + 1; len <=n; len++)
        {
            for(int i=1; i+len - 1<=n; i++)
            {
                int j = i + len - 1;
                for(int k=1; k<=len; k++)
                {
                    for(int x=1; x <k; x ++)
                    {
                        for(int t=i; t<=j; t++)
                        {
                            dp[i][j][k] = min(dp[i][j][k], dp[i][t][x] + dp[t+1][j][k-x]);
                        }
                    }
                }

                for(int k=left; k<=right; k++)
                {
                    dp[i][j][1] = min(dp[i][j][1], dp[i][j][k] + (sum[j] - sum[i-1]));
                }
            }

        }

        return dp[1][n][1] >= INF ? -1 : dp[1][n][1];
    }


    void run()
    {
        vector<int> weight({1,2,3, 4});
        int n = 4, left = 3, right = 3;
        int result = this->getMinimumCost(n, left, right, weight);
        cout<<result<<endl;
    }
};

int main1()
{
    SegmentStonesMerge a;
    a.run();
    return 0;
}
