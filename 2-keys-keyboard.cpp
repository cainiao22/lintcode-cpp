/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-28
* @brief         只有2个按键的键盘
*
* @description   初始时在记事本上只有一个字符 'A'。你可以在此记事本上每一步可以进行两种操作：

                 Copy All: 你可以复制记事本上所有的字符（不允许部分复制）
                 Paste: 你可以粘贴上一次复制的字符。
                 给出一个数字 n。你需要在记事本上得到恰好 n 个 'A'， 请问最少需要几步。

* @example       例1:

                 输入: 3
                 输出: 3
                 解释:
                 Intitally, we have one character 'A'.
                 In step 1, we use Copy All operation.
                 In step 2, we use Paste operation to get 'AA'.
                 In step 3, we use Paste operation to get 'AAA'.
                 例2:

                 输入: 1
                 输出: 0
* @solution
*/



#include "commonutils.h"

class TwoKeysKeyboard : public CommonUtils
{
public:
    int minSteps(int n)
    {
        //dp[i][j]代表到达i个A的并且此时我的手里有j个复制好的A最少需要多少步
        int dp[n+1][n+1];
        for(int i=0; i<n+1; i++)
        {
            for(int j=0; j<n+1; j++)
            {
                dp[i][j] = INF;
            }
        }
        dp[1][0] = 0;
        dp[1][1] = 1;
        for(int i=2; i<=n; i++)
        {
            for(int j=1; j<i; j++)
            {
                //这里是粘贴
                dp[i][i-j] = min(dp[i][i-j], dp[j][i-j] + 1);
                //这里是复制
                dp[i][i] = min(dp[i][i], dp[i][i-j] + 1);
            }
        }

        int result = INF;
        for(int i=0; i<=n; i++)
        {
            result = min(dp[n][i], result);
        }

        return result;
    }

    //好巧妙的方法
    int minSteps2(int n)
    {
        int dp[n+1];
        dp[1] = 0;
        for(int i=2; i<=n; i++)
        {
            dp[i] = i;
            for(int j=i/2; j>1; j--)
            {
                if(i % j == 0)
                {
                    dp[i] = dp[j] + (i / j);
                    break;
                }
            }
        }

        return dp[n];
    }

    //递归解法
    int minSteps3(int n)
    {
        if(n == 1) return 0;
        int result = n;
        for(int j=n/2; j>1; j--)
        {
            if(n % j == 0)
            {
                result = min(result, minSteps3(j) + (n / j));
                break;
            }
        }

        return result;
    }
    //TODO 有点看不懂
    int minSteps4(int n)
    {
        int res = 0;
        for(int i=2; i<=n; i++)
        {
            while(n % i == 0)
            {
                res += i;
                n /= i;
            }
        }

        return res;
    }

    void run()
    {
        vector<int> nums({1, 1, 2});
        int result = this->minSteps4(2);
        cout<<result<<endl;
    }
};



