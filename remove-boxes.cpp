/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-17
* @brief         移除箱子
* @description
*                给出几个不同颜色的箱子，用不同的正数表示。
                 你可能会经历几轮拆除箱子，直到没有箱子为止。 每次你可以选择一些具有相同颜色的连续箱子（由k个箱子组成，k >= 1），
                 删除它们并得到k * k分。
                 找到您可以获得的最高分
* @example       样例 1:

*                输入：[1, 3, 2, 2, 2, 3, 4, 3, 1]
*                输出：23
*                解释：
*                [1, 3, 2, 2, 2, 3, 4, 3, 1]
*                ----> [1, 3, 3, 4, 3, 1] (3*3=9分)
*                ----> [1, 3, 3, 3, 1] (1*1=1分)
*                ----> [1, 1] (3*3=9分)
*                ----> [] (2*2=4分)
*                样例 2:
*
*                输入：[1,2,3,4,5,6,7,8,9,10]
*                输出：10
*                解释：
*                每轮得到1*1分，一共10轮。
* @solution
*/


#include "commonutils.h"

class RemoveBoxes : public CommonUtils
{
public:
    //BUG
    int removeBoxesBug(vector<int> &boxes)
    {
        vector<int> equalPre(boxes.size(), 0);
        for(int i=0; i<boxes.size(); i++)
        {
            if(i-1 >= 0 && boxes[i] == boxes[i-1])
            {
                equalPre[i] = boxes[i-1];
            }
            else
            {
                equalPre[i] = i;
            }
        }
        vector<vector<int>> dp(boxes.size(), vector<int>(boxes.size(), 1));
        for(int len=1; len<boxes.size(); len++)
        {
            for(int i=0; i+len < boxes.size(); i++)
            {
                //i,j确定范围
                int j = i + len;
                //下面这段循环是拿走k~l-1对于剩下的怎么处理
                int MAX = 0;
                if(equalPre[j] <= i)
                {
                    dp[i][j] = (j - i + 1) * (j-i+1);
                }
                for(int k=i; k<=j; k++)
                {
                    for(int l=k; l<j; l++)
                    {
                        int sum = dp[k][l];
                        if(k-1 >= i && l + 1 <= j)
                        {
                            int s = 0;
                            int tmp1 = k-1;
                            int tmp2 = l + 1;
                            while(tmp1 >= i && boxes[tmp1] == boxes[l + 1])
                            {
                                s ++;
                                tmp1 --;
                            }
                            while(tmp2 < j && boxes[tmp2] == boxes[k-1])
                            {
                                s ++;
                                tmp2 ++;
                            }

                            sum += s * s;
                            if(tmp1 >= i)
                            {
                                sum += dp[i][tmp1];
                            }
                            if(tmp2 <= j)
                            {
                                sum += dp[tmp2][j];
                            }
                        }
                        else if(k - 1 >= i)
                        {
                            sum += dp[i][k-1];
                        }
                        else if(l+1 <= j)
                        {
                            sum += dp[l+1][j];
                        }

                        MAX = max(MAX, sum);
                    }
                }

                dp[i][j] = MAX;
            }

            return dp[0][boxes.size()-1];
        }
    }

    //这个思想碉堡了
    int helper(vector<int> &boxes, int i, int j, int k, int dp[100][100][100])
    {
        if(i > j) return 0;
        if(dp[i][j][k] > 0) return dp[i][j][k];
        int res = (1+k) * (1+k) + helper(boxes, i+1, j, 0, dp);
        for(int m=i+1; m<=j; m++)
        {
            if(boxes[i] == boxes[m])
            {
                //i+1 ~ m-1单独算      m~j 每次递增 这个是思想核心
                res = max(res, helper(boxes, i+1, m - 1, 0, dp) + helper(boxes, m, j, k+1, dp));
            }
        }

        return dp[i][j][k] = res;
    }

    int removeBoxes(vector<int> &boxes)
    {
        //dp[i][j][k]表示i~j这段序列在i前面有k个和i相同的元素
        int dp[100][100][100] = {0};
        int result = helper(boxes, 0, boxes.size() - 1, 0, dp);
    }


    int removeBoxesIterator(vector<int> &boxes)
    {
        int n = boxes.size();
        if(n == 0)
        {
            return 0;
        }
        int dp[n][n][n] = {0};
        for(int i=0; i<n; i++)
        {
            for(int k=0; k<n; k++)
            {
                dp[i][i][k] = (k+1)*(k+1);
            }
        }

        for(int t=1; t<n; t++)
        {
            for(int i=0; i+t<n; i++)
            {
                int j=i+t;
                //因为i从0开始的，i的前面有i个数字，所以k最大也会到i
                for(int k=0; k<=i; k++)
                {
                    int res = (1+k) * (1+k) + dp[i+1][j][0];
                    for(int m=i+1; m<=j; m++)
                    {
                        if(boxes[i] == boxes[m])
                            res = max(res, dp[i+1][m-1][0] + dp[m][j][k+1]);
                    }

                    dp[i][j][k] = res;
                }
            }
        }

        return dp[0][n-1][0];
    }

    void run()
    {
        vector<int> boxes({1, 3, 2, 2, 2, 3, 4, 3, 1});
        int result = this->removeBoxes(boxes);

        cout<<result<<endl;
    }
};


