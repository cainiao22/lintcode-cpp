/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-15
* @brief         计算不同数字整数的个数
* @description   给定非负整数n，计算具有不同数字字符的所有整数，其中0 \leq x \lt 10^n0≤x<10
​
* @example       样例1

                 输入： 2
                 输出： 91
                 解释：
                 答案应该是0≤x<100范围内的总数，除去[11,22,33,44,55,66,77,88,99]
                 样例2

                 输入： 3
                 输出： 739
* @solution
*/



#include<iostream>

using namespace std;


class CountNumbersWithUniqueDigits
{
public:
    int countNumbersWithUniqueDigits(int n)
    {
        if (n == 0) {
            return 1;
        }
        //dp[i]代表 以第i位开始的对于单个数字，它可以组成的数字个数
         int dp[10];
         dp[0] = 1;
         if(n > 10)
         {
             n = 10;
         }
         //这个可以使用滚动数组做优化，因为dp[i]只和dp[i-1]相关联
         for(int i=1; i<n; i++)
         {
             dp[i] = (10 - i) * dp[i-1];
         }

         int sum = 10;
         for(int i=1; i<n; i++)
         {
             sum += dp[i] * 9;
         }

         return sum;
    }

    int countNumbersWithUniqueDigits2(int n)
    {
        if (n == 0) {
            return 1;
        }
        //dp[i]代表 以第i位开始的对于单个数字，它可以组成的数字个数
         int dp;
         dp = 1;
         if(n > 10)
         {
             n = 10;
         }

         int sum = 10;
         //这个可以使用滚动数组做优化，因为dp[i]只和dp[i-1]相关联
         for(int i=1; i<n; i++)
         {
             dp = (10 - i) * dp;
             sum += dp * 9;
         }
         return sum;
    }

    int countNumbersWithUniqueDigits3(int n)
    {
        if (n == 0) {
            return 1;
        }
        //dp[i]代表 以第i位开始的可以组成的数字个数
         int dp;
         //i从一位开始
         dp = 9;
         if(n > 10)
         {
             n = 10;
         }

         int sum = 10;
         //这个可以使用滚动数组做优化，因为dp[i]只和dp[i-1]相关联
         for(int i=2; i<=n; i++)
         {
             dp = (11 - i) * dp;
             sum += dp;
         }
         return sum;
    }

    /**
     * @brief n = 0, 0; 因为没有一个数字是由0个不同的数字组成的
              n = 1, 10; 0,1,2,3,4,5,6,7,8,9. 这些数字在0到9的范围内是由1个不同的数字组成的
              n = 2, 91(81 + 10); 对于两位数来说, 由两个不同数字组成的组合个数一共有9 * 9种, 然后再加上一位数的10种, 一共是91种
              以此类推, 那么n位数的公式就是9 * 9 * 8 * 7 * ... + f(n - 1), f代表的是求n位数由n个不同数字组成的解法个数
     * @param n
     * @return
     */
    int countNumbersWithUniqueDigits4(int n)
    {
        if (n == 0) {
            return 1;
        }
        if (n > 10) {
            n = 10;
        }
        int ans = 1;
        int multiple = 9;
        for (int i = n - 1; i >= 0; i--) {
            if (i == 0) {
                ans += multiple;
            } else { //最高位开始的时候有9个可能的数，
                ans += (n - i + 1) * multiple;
            }
            multiple = multiple * (10 - n + i - 1);
        }
        return ans;
    }


    void run()
    {
        for(int i=0; i<10; i++)
        {
            int result = this->countNumbersWithUniqueDigits(i);
            int result2 = this->countNumbersWithUniqueDigits4(i);
            cout<<result<<endl;
            cout<<result2<<endl;
        }

    }
};


//int main()
//{
//    CountNumbersWithUniqueDigits a;
//    a.run();
//    return 0;
//}
