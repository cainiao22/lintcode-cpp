/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-26
* @brief         格雷编码
*
* @description   格雷编码是一个二进制数字系统，在该系统中，两个连续的数值仅有一个二进制的差异。
                 给定一个非负整数 n ，表示该代码中所有二进制的总数，请找出其格雷编码顺序。
                 一个格雷编码顺序必须以 0 开始，并覆盖所有的 2^n 个整数


* @example      样例 1:

                输入: 1
                输出: [0, 1]
                样例 2:

                输入: 2
                输出: [0, 1, 3, 2]
                解释:
                  0 - 00
                  1 - 01
                  3 - 11
                  2 - 10

* @solution 这个有规律，G[n]=G[n-1]倒着来，例如{0,1}，它的下一位就是{11,10},刚好倒过来了。在下一位就是{110,111,101,100}
*/

#include "commonutils.h"


class GrayCode : protected CommonUtils
{
public:
    vector<int> grayCode(int n)
    {
        // write your code here
        vector<int> result({0});
        for(int i=1; i<=n; i++)
        {
            int index = result.size() - 1;
            int pre = 1 << (i - 1);
            for(int i=index; i>=0; i--)
            {
                result.push_back(pre + result[i]);
            }

        }

        return result;
    }

    /**
     * @brief 递归解法
     * @param n
     * @return
     */
    vector<int> grayCodeDFS(int n)
    {
        if(n == 0)
        {
            return vector<int>({0});
        }
        vector<int> item = grayCodeDFS(n-1);
        int size = item.size();
        for(int i=size - 1; i>=0; i--)
        {
            item.push_back((1 << (n-1)) + item[i]);
        }

        return item;
    }

    //TODO 格雷编码 最直接的方式从当前位置直接获取
    vector<int> grayCode3(int n)
    {
        vector<int> result(1 << n);
        for (size_t i = 0; i < (1 << n); i++)
            result[i] = i ^ (i >> 1);
        return result;
    }

    void run()
    {
        vector<int> result = this->grayCodeDFS(3);
        this->printVector(result);
    }
};





