/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-05
* @brief         摘要
* @description   给出一个有n个整数的数组S，在S中找到三个整数a, b, c，找到所有使得a + b + c = 0的三元组
*
*
* @example
*
*                例1:
*
*                输入:[2,7,11,15]
*                输出:[]
*                例2:

*                输入:[-1,0,1,2,-1,-4]
*                输出:[[-1, 0, 1],[-1, -1, 2]]
*
* @solution
*/


#include "commonutils.h"

class ThreeSum : private CommonUtils
{
public:
    vector<vector<int>> threeSum(vector<int> &numbers)
    {
        vector<vector<int>> result;
        sort(numbers.begin(), numbers.end());
        for(int i=0; i<numbers.size();)
        {
            int start = i + 1, end = numbers.size() - 1;
            int sum = - numbers[i];
            while(start < end)
            {
                int temp = numbers[start] + numbers[end];
                if(temp < sum)
                {
                    start ++;
                }
                else if (temp > sum)
                {
                    end --;
                }
                else
                {
                    vector<int> item({numbers[i], numbers[start], numbers[end]});
                    result.push_back(item);
                    int t = numbers[start];
                    while(start < end && numbers[start] == t)
                    {
                        start ++;
                    }
                    t = numbers[end];
                    while(start < end && numbers[end] == t)
                    {
                        end --;
                    }
                }
            }

            int j = i;
            while(i < numbers.size() && numbers[i] == numbers[j])
            {
                i++;
            }
        }

        return result;
    }

    void run()
    {
        vector<int> numbers({1,0,-1,-1,-1,-1,0,1,1,1});
        this->threeSum(numbers);
    }
};


