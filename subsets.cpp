/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-05
* @brief         子集
*
* @description   给定一个含不同整数的集合，返回其所有的子集。
*
* @example
*                样例 1：

*                输入：[0]
*                输出：
*                [
*                  [],
*                  [0]
*                ]
*                样例 2：

*                输入：[1,2,3]
*                输出：
*                [
*                  [3],
*                  [1],
*                  [2],
*                  [1,2,3],
*                  [1,3],
*                 [2,3],
*                  [1,2],
*                  []
*                ]
* @solution
*/




#include "commonutils.h"



class SubSet : protected CommonUtils
{
public:

    vector<vector<int>> total;

    //dfs递归解决
    void helper(vector<int> nums, int index, vector<int> item)
    {
        if(index == nums.size())
        {
            vector<int> temp(item);
            total.push_back(temp);
            return;
        }
        item.push_back(nums[index]);
        helper(nums, index+1, item);
        item.pop_back();
        helper(nums, index+1, item);

    }

    //bfs解决
    vector<vector<int>> bfs(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        queue<vector<int>> q;
        vector<int> empty;
        q.push(empty);

        while(!q.empty())
        {
            vector<int> top = q.front();
            q.pop();
            vector<int> a(top);
            total.push_back(a);
            for(int i=0; i<nums.size(); i++)
            {
                if(top.size() == 0 || top.at(top.size() - 1) < nums[i])
                {
                    vector<int> copy(top);
                    copy.push_back(nums[i]);

                    q.push(copy);
                }
            }
        }

        return total;
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<int> item;
        this->helper(nums, 0, item);
        return total;
    }
};











