/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-26
* @brief         小行星的碰撞
* @description   给定一个整数数组，代表一行小行星。对于每个小行星，绝对值表示其大小，符号表示其方向（正意义右，负意义左）。
*                每个小行星以相同的速度移动。

                 返回所有碰撞发生后小行星的状态。 如果两颗小行星相遇，则较小的小行星会爆炸。 如果两者的大小相同，则两者都会爆炸。
                 沿同一方向移动的两颗小行星永远不会相遇


* @example       样例 1:

                 输入: [5, 10, -5]
                 输出: [5, 10]
                 解释: 10 和 -5 碰撞得 10. 而 5 和 10 永远不会碰撞.
                 样例 2:

                 输入: [10, 2, -5]
                 输出: [10]
                 解释: 2 和 -5 碰撞后得到 -5. 然后 10 和 -5 碰撞剩下10.


* @solution      堆栈操作
*/

#include "commonutils.h"


class AsteroidCollision : protected CommonUtils
{
public:
    vector<int> asteroidCollision(vector<int> &asteroids)
    {
        stack<int> s;
        for(int i=0; i<asteroids.size(); i++)
        {
            if(asteroids[i] > 0)
            {
                s.push(asteroids[i]);
            }
            else
            {
                while(!s.empty() && s.top() > 0 && s.top() < -asteroids[i])
                {
                    s.pop();
                }

                if(s.empty() || s.top() < 0)
                {
                    s.push(asteroids[i]);
                }
                else if(s.top() == -asteroids[i])
                {
                    s.pop();
                }
            }
        }

        vector<int> result(s.size());
        int i = s.size() - 1;
        while(!s.empty())
        {
            result[i --] = s.top();
            s.pop();
        }
        return result;
    }

    void run()
    {
        vector<int> asteroids({10, 2, -5, -10});
        vector<int> result  = this->asteroidCollision(asteroids);
        this->printVector(result);
    }
};



