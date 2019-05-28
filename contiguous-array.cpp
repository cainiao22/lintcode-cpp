/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-26
* @brief         连续数组
*
*
* @description   给一个二进制数组，找到 0 和 1 数量相等的子数组的最大长度
*
* @example       输入: [0,1]
                 输出: 2
                 解释: [0, 1] 是具有相等数量的 0 和 1 的最长子数组。

                 输入: [0,1,0]
                 输出: 2
                 解释: [0, 1] (或者 [1, 0]) 是具有相等数量 0 和 1 的最长子数组。
* @solution
*/


#include "commonutils.h"

class ContiguousArray : protected CommonUtils
{
public:
    int findMaxLength(vector<int> &nums)
    {
        int sum[nums.size() + 1] = {0};
        for(int i=0; i<nums.size(); i++)
        {
            sum[i + 1] = sum[i] + (nums[i] ? 1 : -1);
        }

        int result = 0;
        for(int i=1; i<=nums.size() - 1; i++)
        {
            //优化
            int min = 1;
            if(result > 0)
            {
                min = result;
            }
            for(int j=i+min; j<=nums.size(); j++)
            {
                if(sum[j] - sum[i-1] == 0)
                {
                    result = max(j-i+1, result);
                }
            }
        }
        return result;
    }

    //进一步优化将时间复杂度降为O(N)
    int findMaxLength2(vector<int> &nums)
    {
        //存放以前的map,
        map<int, int> m;
        int result = 0;
        int sum = 0;
        m[0] = -1;
        for(int i=0; i<nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : nums[i];
            if(m.count(sum))
            {
                result = max(result, i - m[sum]);
            }
            else
            {
                m.insert(pair<int, int>(sum, i));
            }
        }
        
        return result;
    }

    void run()
    {
        vector<int> nums({0,1});
        cout<<this->findMaxLength2(nums)<<endl;
    }
};



