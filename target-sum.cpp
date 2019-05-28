/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-24
* @brief         目标和
* @description   给定一个非负整数的列表a1,a2,...an，再给定一个目标S。现在用+和-两种运算，对于每一个整数，
*                选择一个作为它前面的符号。

                 找出有多少种方法，使得这些整数的和正好等于S。
* @example
*                例1:

*                输入: nums为 [1, 1, 1, 1, 1], S 为 3.
*                输出: 5
*                解释:

*                -1+1+1+1+1 = 3
*                +1-1+1+1+1 = 3
*                +1+1-1+1+1 = 3
*                +1+1+1-1+1 = 3
*                +1+1+1+1-1 = 3
*
*                有5种方法让和为3.
*                例2:
*
*                输入: nums 为 [], S 为 3.
*                输出: 0
*                解释:
*                没有方法能让和为3
*
*
*
*
* @solution
*/

#include<iostream>
#include<vector>

using namespace std;


class TargetSum
{
public:

    int findTargetSumWays(vector<int> &nums, int s)
    {
        return helper(nums, s, 0);
    }

    //最简单的递归
    int helper(vector<int> &nums, int s, int index)
    {

        if(index == nums.size())
        {
            if(s == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        return helper(nums, s - nums[index], index + 1)
                + helper(nums, s + nums[index], index + 1);
    }


    //思路清奇   先求所有数的和，相当于都是用的“+”。然后类似subset问题的深度优先搜选出不同组合的数字来减掉，
    //相当于用的是“-”。这里注意减的时候减去两倍，因为之前求和的时候加上了。

    int count = 0;
    int findTargetSumWays2(vector<int> &nums, int s)
    {
        int sum = 0;
        for(int i=0; i<nums.size(); i++)
        {
            sum += nums[i];
        }

        this->findSubtracted(nums, sum, 0, s);
        return count;
    }

    void findSubtracted(vector<int> &nums, int sum, int startIndex, int s)
    {
        if(sum == s)
        {
            count ++;
        }
        for(int i=startIndex; i<nums.size(); i++)
        {
            sum -= nums[i] * 2;
            findSubtracted(nums, sum, startIndex + 1, s);
            sum += nums[i] * 2;
        }
    }


    //dp解法 dp[i][j] 表示前i个数字组成和为j的种数。因为j有可能为负数(-sum ~ sum)，所以将j整体做了平移,平移了sum
    int findTargetSumWaysDp(vector<int> &nums, int s)
    {
        int sum = 0;
        for(int i=0; i<nums.size(); i++)
        {
            sum += nums[i];
        }

        if(sum < s)
        {
            return 0;
        }

        //因为多了一个0所以需要加1，这个其实也可以用滚动数组做
        int dp[2][sum * 2 + 1];

        for(int i=0; i<2; i++)
        {
            for(int j=0; j<sum*2 +1; j++)
            {
                dp[i][j] = 0;
            }
        }

        dp[0][sum + nums[0]] += 1;
        dp[0][sum - nums[0]] += 1;
        int cur = 1;
        for(int i=1; i<nums.size(); i++)
        {
            for(int j=0; j<sum*2 +1; j++)
            {
                if(dp[i-1][j] != 0)
                {
                    dp[cur][j+nums[i]] += dp[1 - cur][j];
                    dp[cur][j-nums[i]] += dp[1 - cur][j];
                    //用完记得还原为0
                    dp[1 - cur][j] = 0;
                }
            }
            cur = 1 - cur;
        }

        //这里要注意，前sum个代表负数
        return dp[1-cur][sum + s];
    }


    void run()
    {
        vector<int> nums({1, 1, 1, 1, 1});
        int result = this->findTargetSumWaysDp(nums, 3);
        cout<<result<<endl;
    }
};



















