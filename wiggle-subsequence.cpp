/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-16
* @brief         摆动序列
* @description   如果连续数字之间的差严格地在正和负之间交替，则这样的数字序列称为摆动序列。 第一个差值（如果存在）可以是正的也可以是负的。
*                少于两个元素的序列通常是摆动序列。

                 例如，[1,7,4,9,2,5]是一个摆动序列，因为连续数字的差(6,-3,5,-7,3)交替为正和负。 相反，[1,4,7,2,5]和[1,7,4,5,5]不是摆动序列，
                 第一个是因为它的前两个连续数字的差是正的，而第二个是因为它的最后一个连续数字的差零。

                 给定一个整数序列，返回作为摆动序列的最长子序列的长度。 通过从原始序列中删除一些元素（和0）来获得子序列，使剩余元素保持其原始顺序。
*
*
* @example       例1:

                 输入: [1,7,4,9,2,5]
                 输出: 6
                 解释: 整个序列都是一个摆动序列。
                 例2:

                 输入: [1,17,5,10,13,15,10,5,16,8]
                 输出: 7
                 解释: 有若干个摆动子序列都满足这个长度。 其中一个为[1,17,10,13,10,16,8]。
* @solution
*/



#include<iostream>
#include<vector>
#include<algorithm>



using namespace std;


class WiggleSubsequence
{
public:
    int wiggleMaxLength(vector<int> &nums)
    {
       // Write your code here
        int dp[nums.size() + 1];
        int map[nums.size() + 1];
        for(int i=0; i<nums.size()+1; i++)
        {
            dp[i] = 1;
            map[i] = 0;
        }
        dp[2] = 2;
        dp[1] = 1;
        dp[0] = 0;
        //到我这里最大，我所对应的那个数字是正还是负
        map[2] = nums[1] - nums[0];
        int max= 2;
        for(int i=3; i<nums.size()+1; i++)
        {
            for(int j=i-1; j>=1; j--)
            {
                if(map[j] > 0 && nums[i-1] - nums[j-1] < 0 && dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;
                    map[i] = nums[i-1] - nums[j-1];
                }
                else if(map[j] < 0 && nums[i-1] - nums[j-1] > 0 && dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;
                    map[i] = nums[i-1] - nums[j-1];
                //3,3,3,2,5 前几个都不符合，但是到2的时候是可以和前面的3做匹配的
                }
                else if(map[j] == 0 && nums[i-1] - nums[j-1] != 0 && dp[i] < 2)
                {
                    dp[i] = 2;
                    map[i] = nums[i-1] - nums[j-1];
                }

                if(max < dp[i])
                {
                    max = dp[i];
                }
            }
        }

        return max;
    }


    //这个是标准dp
    int wiggleMaxLength2(vector<int>& nums)
    {
            if (nums.empty()) return 0;
            //这个是负 p[i]表示如果到我这里为负的最大长度
            vector<int> p(nums.size(), 1);
            //这个是正 q[i]表示如果到我这里为正的最大长度
            vector<int> q(nums.size(), 1);
            for (int i = 1; i < nums.size(); ++i) {
                for (int j = 0; j < i; ++j) {
                    if (nums[i] > nums[j]) p[i] = max(p[i], q[j] + 1);
                    else if (nums[i] < nums[j]) q[i] = max(q[i], p[j] + 1);
                }
            }
            return max(p.back(), q.back());
    }

    /**
     * @brief 复杂度为O(n)的dp,因为down[i]或者up[i]只和前面一个数有关系，所以这个其实可以做优化滚动数组·
     * @param nums
     * @return
     */
    int wiggleMaxLength3(vector<int> &nums)
    {
        int down[nums.size()];
        int up[nums.size()];
        down[0] = 1;
        up[0] = 1;
        for(int i=1; i<nums.size(); i++)
        {
            if(nums[i] - nums[i-1] > 0)
            {
                up[i] = down[i-1] + 1;
                down[i] = down[i-1];
            }
            else if(nums[i] - nums[i-1] < 0)
            {
                down[i] = up[i-1] + 1;
                up[i] = up[i-1];
            }
            else
            {
                down[i] = down[i-1];
                up[i] = up[i-1];
            }
        }

        return max(up[nums.size()-1], down[nums.size()-1]);
    }

    int wiggleMaxLength4(vector<int> &nums)
    {
        if(nums.size() <= 1)
        {
            return nums.size();
        }
        int down = 1, up = 1;
        for(int i=1; i<nums.size(); i++)
        {
            if(nums[i] - nums[i-1] > 0)
            {
                up = down + 1;
            }
            else if(nums[i] - nums[i-1] < 0)
            {
               down = up + 1;
            }
        }

        return max(up, down);
    }

    void run()
    {
        vector<int> nums({1,7,4,9,2,1});
        int result = this->wiggleMaxLength2(nums);
        cout<<result<<endl;
    }
};

/*
int main()
{
    WiggleSubsequence a;
    a.run();
    return 0;
}
*/












