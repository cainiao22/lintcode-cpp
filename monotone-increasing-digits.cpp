/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-10
* @brief         单调递增数
* @description   给一非负整数 N, 找到小于等于 N 的最大的 单调递增数.
*                (回想一下, 当且仅当每对相邻的数字 x 和 y 满足 x <= y 时, 这个整数才是单调递增数)
* @example       给出 N = 10, 返回 9
                 给出 N = 12345, 返回 12345
                 给出 N = 10000, 返回 9999
* @solution      1.贪心的从高到低位取数，让每一位数尽量大，如果当前数只能选择比原数位小时，后几位全都取9
*                2.找到第一个(不递增或相等)的数，把后面每一位变为0, 然后整体减去1
*/

#include<iostream>

using namespace std;

class MonotoneIncreasingDigits
{
public:
    int monotoneDigits(int num)
    {
         for(int x = num; x >=0; x --)
         {
             int c = x % 10;
             int n = x / 10;
             while(n > 0)
             {
                 if(c >= n % 10)
                 {
                     c = n % 10;
                     n = n / 10;
                 }
                 else
                 {
                     break;
                 }
             }
             if(n == 0)
             {
                 return x;
             }
         }
    }

    int monotoneDigits2(int num)
    {
        int digit[10] = {0};
        int cnt = 0;
        int pos = 0;
        while(num > 0)
        {
            digit[cnt ++] = num % 10;
            num = num / 10;
        }

        for(int i=1; i<cnt; i++)
        {
            if(digit[i] > digit[i-1])
            {
                digit[i] --;
                pos = i;
            }
        }

        for(int i=0; i<pos; i++)
        {
            digit[i] = 9;
        }
        int ans = 0;
        for(int i=cnt-1; i>=0; i--)
        {
            ans = ans * 10 + digit[i];
        }

        return ans;
    }

    int monotoneDigits3(int num)
    {
        long long dig = 10000000000;
        while(dig > 1 && num / dig % 10 <= num / (dig/10) % 10)
        {
            dig /= 10;
        }

        if(dig == 1)
        {
            return num;
        }

        while(dig < num && num / dig % 10 == num / 10 / dig % 10)
        {
            dig *= 10;
        }
        return num / dig * dig - 1;
    }

    void run()
    {
        int result = this->monotoneDigits3(1);
        cout<<result<<endl;
    }
};

