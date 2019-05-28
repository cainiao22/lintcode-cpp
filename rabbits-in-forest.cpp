/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-28
* @brief         森林中的兔子
*
*
* @description   在一个森林中，每个兔子都有一种颜色。兔子中的一部分（也可能是全部）会告诉你有多少兔子和它们有同样的颜色。
*                这些答案被放在了一个数组中。
                 返回森林中兔子可能的最少的数量

* @example       样例 1:

                 输入: [1, 1, 2]
                 输出: 5
                 解释:
                   两个回答 "1" 的兔子可能是相同的颜色，姑且说它们为红色.
                   回答 "2" 的兔子一定不会是红色，不然与前面的答案冲突.
                   姑且认为回答 "2" 的兔子是蓝色.
                   那么一定还有 2 只蓝色的兔子在森林里不过没有回答问题.
                   所以森林里兔子的最少总数是 5, 3只回答问题的加上 2 只没回答的.
                                  样例 2:

                 输入: [10, 10, 10]
                 输出: 11
* @solution
*/

#include "commonutils.h"

class RabbitsInForest : public CommonUtils
{
public:
    int numRabbits(vector<int> &answers)
    {
        int sum = 0;
        map<int, int> s;
        for(int i=0; i<answers.size(); i++)
        {
            if(!s.count(answers[i]))
            {
                s[answers[i]] = 1;
            }
            else
            {
                s[answers[i]] = s[answers[i]] + 1;
                if(s[answers[i]] == answers[i] + 1)
                {
                    sum += answers[i] + 1;
                    s.erase(answers[i]);
                }
            }
        }
        for(map<int, int>::iterator it=s.begin() ;it!=s.end();it++)
        {
            sum += it->first;
        }

        sum += s.size();

        return sum;
    }

    int numRabbits2(vector<int> &answers)
    {
        map<int, int> s;
        for(int item : answers)
        {
            s[item + 1] = s[item + 1] + 1;
        }
        int sum = 0;
        for(auto &i : s)
        {
            sum += ceil(i.second * 1.0 / i.first)*i.first;
        }

        return sum;
    }

    void run()
    {
        vector<int> ans({1, 1, 1});
        cout<<this->numRabbits2(ans)<<endl;
        int a = 316018;
        cout<<a<<endl;
    }
};
