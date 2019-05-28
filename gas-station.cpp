/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-28
* @brief         摘要
* @description
*
*                在一条环路上有 N 个加油站，其中第 i 个加油站有汽油gas[i]，并且从第_i_个加油站前往第_i_+1个加油站需要消耗汽油cost[i]。
*
*                你有一辆油箱容量无限大的汽车，现在要从某一个加油站出发绕环路一周，一开始油箱为空。

*                求可环绕环路一周时出发的加油站的编号，若不存在环绕一周的方案，则返回-1
*
* @example       样例 1:

                 输入:gas[i]=[1,1,3,1],cost[i]=[2,2,1,1]
                 输出:2
                 样例 2:

                 输入:gas[i]=[1,1,3,1],cost[i]=[2,2,10,1]
                 输出:-1

* @solution      O(n)时间和O(1)额外空间
*/

#include "commonutils.h"


class GasStation : public CommonUtils
{
public:
    //暴力解法
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {

        int i=0;
outter:
        for(; i<gas.size(); i++)
        {
            int sum = 0;
            for(int j=i; j<i+gas.size(); j++)
            {
                int index = j % gas.size();
                sum += gas[index] - cost[index];
                if(sum < 0)
                {
                    i++;
                    goto outter;
                }
            }

            return i;
        }

        return -1;
    }

    //优化解法 dubbo array解法
    int canCompleteCircuit2(vector<int> &gas, vector<int> &cost)
    {
        int sum = 0, start = 0;
        for(int i=0; i<gas.size()* 2; i++)
        {
            int index = i % gas.size();
            sum += gas[index] - cost[index];
            if(sum < 0)
            {
                sum = 0;
                start = i + 1;
            }
            else if(i - start + 1 == gas.size())
            {
                return start;
            }
        }

        return -1;
    }

    //另一个类似double array的解法
    int canCompleteCircuit3(vector<int> &gas, vector<int> &cost)
    {
        int start = gas.size() - 1;
        int end = 0;
        int sum = gas[start] - cost[start];
        while(start > end)
        {
            if(sum < 0)
            {
                start --;
                sum += gas[start] - cost[start];
            }
            else
            {
                sum += gas[end] - cost[end];
                end ++;
            }
        }

        return sum >= 0 ? start : -1;
    }

    void run()
    {
        vector<int> gas({1,2,3,3}), cost({2,1,5,1});
        int result = this->canCompleteCircuit2(gas, cost);
        cout<<result<<endl;
    }
};

