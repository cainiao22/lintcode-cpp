/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-08
* @brief         交叉字符串

* @description   给出三个字符串:s1、s2、s3，判断s3是否由s1和s2交叉构成
* @example
*
*                样例 1：

*                输入:
*                "aabcc"
*                "dbbca"
*                "aadbbcbcac"
*                输出:
*                true
*                样例 2：

*                输入:
*                ""
*                ""
*                "1"
*                输出:
*                false
*                样例 3：

*                输入:
*                "aabcc"
*                "dbbca"
*                "aadbbbaccc"
*                输出:
*                false
* @solution
*/


#include "commonutils.h"


class InterleavigString : public CommonUtils
{
public:
    bool isInterleave(string &s1, string &s2, string &s3)
    {
        if(s1.length() + s2.length() != s3.length())
        {
            return false;
        }

        //s1的前i个字符和s2的前j个字符组成s3的前i+j个字符是否可以
        int dp[s1.length()+1][s2.length()+1] = {0};
        dp[0][0] = 1;
        for(int i=1; i<=s1.length(); i++)
        {
            if(s1[i-1] == s3[i-1] && dp[i-1][0])
            {
                dp[i][0] = 1;
            }
            else
            {
                break;
            }
        }

        for(int j=1; j<=s2.length(); j++)
        {
            if(s2[j-1] == s3[j-1] && dp[0][j-1])
            {
                dp[0][j] = 1;
            }
            else
            {
                break;
            }
        }

        for(int i=1; i<=s1.length(); i++)
        {
            for(int j=1; j<=s2.length(); j++)
            {
                //s1的前i-1个和s2的前j个可以组成s3的前i+j-1个，然后s1[i]=s3[i+j],那么s1的前i个和s2的前j个可以组成s3,
                //s1的前i个和s2的前j-1个可以组成s3的前i+j-1个，然后s2[j]=s3[i+j],那么s1的前i个和s2的前j个也可以组成s3
                if((dp[i-1][j] && s3[i+j-1] == s1[i-1]) || (dp[i][j-1] && s3[i+j-1] == s2[j-1]))
                {
                    dp[i][j] = 1;
                }
            }
        }

        return dp[s1.length()][s2.length()];
    }

    //使用滚动数组优化
    bool isInterleave2(string &s1, string &s2, string &s3)
    {
        if(s1.length() + s2.length() != s3.length())
        {
            return false;
        }

        int dp[s2.length() + 1] = {0};
        dp[0] = 1;
        for(int j=1; j<=s2.length(); j++)
        {
            if(s2[j-1] == s3[j-1])
            {
                dp[j] = dp[j-1];
            }
            //只要有一个不满足它后面的就都不满足了
            else
            {
                break;
            }
        }

        for(int i=1; i<=s1.length(); i++)
        {
            for(int j=0; j<=s2.length(); j++)
            {
                //dp[i-1][j] && s3[i+j-1] == s1[i-1] 如果它俩相等,那么dp[i][j] = dp[i-1][j],但是dp[i-1][j]和dp[i][j]是一个所以会有下面这个情况
                if(s1[i-1] != s3[i+j-1])
                {
                    dp[j] = 0;
                }
                //dp[i][j-1] && s3[i+j-1] == s2[j-1]
                if(s2[j-1] == s3[i+j-1])
                {
                    dp[j] |= dp[j-1];
                }
            }
        }

        return dp[s2.length()];

    }

    //递归方式解决
    bool helper(string &s1, int index1, string &s2, int index2, string &s3)
    {
        if(index1 > s1.length() && index2 > s2.length())
        {
            return true;
        }
        bool result = false;
        if(index1 <= s1.length() && s3[index1 + index2 - 2] == s1[index1 - 1])
        {
            result = helper(s1, index1+1, s2, index2, s3);
        }

        if(!result && index2 <= s2.length() && s3[index1 + index2 - 2] == s2[index2 - 1])
        {
            result = helper(s1, index1, s2, index2 + 1, s3);
        }

        return result;
    }


    void run()
    {
        string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
        bool result = this->helper(s1, 1, s2, 1, s3);
        cout<<result<<endl;
    }
};


