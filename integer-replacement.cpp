/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-16
* @brief         整数替换
* @description   给定一个正整数n，你可以做如下的操作：

                 如果n为偶数，将n替换为n/2。
                 如果n为奇数，你可以将n替换为n + 1或n - 1。
                 将n转换为1的最少的替换次数为多少？


* @example       样例
                 样例1：

                 输入：
                 8

                 输出：
                 3

                 说明：
                 8 -> 4 -> 2 -> 1
                 样例2：

                 输入：
                 7

                 输出：
                 4

                 说明：
                 7 -> 8 -> 4 -> 2 -> 1
                 or
                 7 -> 6 -> 3 -> 2 -> 1
* @solution
*/

#include<iostream>
#include<algorithm>
#include<map>
#include<queue>

using namespace std;

class IntegerReplacement
{
public:
    int integerReplacementDP(int n)
    {
        int dp[n+1];
        dp[1] = 0;
        for(int i=2; i<n+1; i++)
        {
            if(i % 2 == 0)
            {
                dp[i] = 1 + dp[i/2];
            }
            else
            {
                dp[i] = 2 + min(dp[(i+1) / 2], dp[(i-1) / 2]);
            }
        }

        return dp[n];
    }

    //递归
    int integerReplacement(int n)
    {
        if(n == 1)
        {
            return 0;
        }
        if(n % 2 == 0)
        {
            return 1 + integerReplacement(n/2);
        }
        else
        {
            int result = 1 + integerReplacement(n -1);
            result = min(result, 1 + integerReplacement(n+1));
            return result;
        }
    }

    map<int, int> memory;
    //递归优化 记忆化搜索
    int integerReplacementmemory(int n)
    {
        if(n == 1)
        {
            return 0;
        }
        if(memory.count(n) > 0)
        {
            return memory[n];
        }
        if(n % 2 == 0)
        {
            int result = 1 + integerReplacementmemory(n/2);
            memory[n] = result;
            return result;
        }
        else
        {
            int result = 1 + integerReplacementmemory(n -1);
            result = min(result, 1 + integerReplacementmemory(n+1));
            memory.insert(pair<int, int>(n, result));
            return result;
        }
    }

     int integerReplacementmemoryBFS(int n)
     {
         queue<int> q;
         q.push(n);
         int result = 0;
         while(!q.empty())
         {
             int len = q.size();
             for(int i=0; i<len; i++)
             {
                 int top = q.front();
                 q.pop();
                 if(top == 1)
                 {
                     return result;
                 }
                 if(top & 0x1)
                 {
                     q.push(top +1);
                     q.push(top -1);
                 }
                 else
                 {
                     q.push(top / 2);
                 }
             }

             result ++;
         }
     }


    void run()
    {
        for(int i=7; i<8; i++)
        {
            int result = this->integerReplacementmemoryBFS(848605084);
            cout<<result<<endl;
        }
    }
};

/*
int main()
{
    IntegerReplacement a;
    a.run();
    return 0;
}
*/
