/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-11
* @brief         香槟塔
* @description
*                我们将玻璃杯按照金字塔的方式摆放，其中第一行有1个玻璃杯，第二行有2个玻璃杯，第三行有3个玻璃杯，依此类推直到第100行。
*                每个杯子可以装一杯（250毫升）香槟。

                 然后，从顶部的第一个玻璃杯中开始倒入香槟。 当最顶部的玻璃杯已满时，任何多余的液体将立即等量地流到玻璃杯的左右两侧。
                 当第二行玻璃杯变满时，任何多余的香槟都会同样流到这些玻璃杯的左右两侧，依此类推（最底部的玻璃杯倒满后多余的液体会流到地面上）。

                 例如，在倒入一杯香槟后，最顶部的玻璃杯已满。 倒两杯香槟后，第二排的两个杯子都是半满的。 在倒了三杯香槟之后，
                 这两个杯子变满了 - 现在共有3个全杯。 倒入四杯香槟后，第三排中间的玻璃杯半满，两个外侧的玻璃杯四分之一满，如下图所示：

* @example       样例1:

                 输入: poured = 1, query_glass = 1, query_row = 1
                 输出: 0.0
                 解释: 我们从香槟塔的顶端倒入一杯香槟（顶端坐标为(0, 0)）。并没有多余的液体流出，所以顶端杯子下方的任何杯子都是空的。
                 样例2:

                 输入: poured = 2, query_glass = 1, query_row = 1
                 输出: 0.5
                 解释: 我们从香槟塔的顶端倒入两杯香槟（顶端坐标为(0, 0)）。有一杯多余的液体由位于(1, 0)和(1, 1)的杯子平分，它们各自有半杯香槟。
* @solution
*/

#include<iostream>
#include<algorithm>

using namespace std;

class ChampagneTower
{
public:
    double champagneTower(int poured, int query_row, int query_glass)
    {
        int n = max(query_row, query_glass) + 1;
        double dp[n][n];
        dp[0][0] = poured;
        for(int i=1; i<n; i++)
        {
            for(int j=0; j<=i; j++)
            {
                if(j - 1 > 0 && dp[i-1][j-1] > 1)
                {
                    dp[i][j] += dp[i-1][j] - 1;
                    dp[i-1][j] = 1;
                }
                if(dp[i-1][j] > 1)
                {
                    dp[i][j] += (dp[i-1][j] - 1) / 2;
                    dp[i-1][j] = dp[i-1][j] - (dp[i-1][j] - 1) / 2;
                }
            }
        }

        return dp[query_row][query_glass] > 1 ? 1 : dp[query_row][query_glass];
    }

    /**
     * @brief 始只有向(0, 0)的杯子倒入了poured杯香槟 动态规划的一个优化方式，滚动数组
       然后依次计算之后每一层的杯子流入的香槟总体积: 第i层第j个杯子流入的香槟总体积 = (第i - 1层第j - 1个 + 第i - 1层第j个 - 2.0) / 2.0
       当然, 这个模拟计算的过程也可以看作是动态规划的递推过程, 上式就是状态转移方程. 而状态的定义是一个杯子一共流入了多少香槟.
     * @param poured
     * @param query_row
     * @param query_glass
     * @return
     */
    double champagneTower2(int poured, int query_row, int query_glass)
    {
        vector<double> res(101, 0);
        res[0] = poured;
        for (int row = 1; row <= query_row; row++) {
            for (int i = row; i >= 0; i--) {
                res[i + 1] += res[i] = max(0.0, (res[i] - 1) / 2);
            }
        }
        return min(res[query_glass], 1.0);
    }
};
