/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-10
* @brief         最长上升子序列
* @description   给定一个整数序列，找到最长上升子序列（LIS），返回LIS的长度
* @example
*
*                样例 1:
*                  输入:  [5,4,1,2,3]
*                  输出:  3

*                  解释:
*                  LIS 是 [1,2,3]

*
*                样例 2:
*                	输入: [4,2,4,5,3,7]
*                	输出:  4

*                	解释:
*                	LIS 是 [2,4,5,7]
* @solution
*/


#include "commonutils.h"



class LongestIncreasingSubSequence : protected CommonUtils
{
public:
    int longestIncreasingSubsequence1(vector<int> &nums)
    {
       vector<int> dp(nums.size(), 1);
       int result = 0;
       for(int i=1; i<nums.size(); i++)
       {
           for(int j=0; j<i; j++)
           {
               if(nums[i] > nums[j])
               {
                   dp[i] = max(dp[i], dp[j] + 1);
               }
           }

           result = max(result, dp[i]);
       }

       return result;
    }

    int binarySearch(int *dp, int length, int target)
    {
        int left = 0, right = length;
        while(left + 1 < right)
        {
            int mid = (right - left) / 2 + left;
            //如果两个数字相等它，上升这个条件也成立
            if(dp[mid] < target)
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }

        return right;
    }

    //dp[i]存储Dp值为i的最小的数字。（有多个位置，以这些位置为结尾的LIS长度都为i， 则这些数字中最小的一个存在dp[i]中）
    //则dp数组严格递增。且下标表示LIS长度，也是严格递增，可以在B数组中进行二分查找
    int longestIncreasingSubsequence(vector<int> &nums)
    {
        if(nums.size() <= 1)
        {
            return nums.size();
        }
        int dp[nums.size() + 1];
        dp[0] = -1e9;
        for(int i=1; i<nums.size() + 1; i++)
        {
            dp[i] = 1e9;
        }
        for(int i=0; i<nums.size(); i++)
        {
            int index = binarySearch(dp, nums.size(), nums[i]);
            dp[index] = nums[i];
        }

        for(int i=nums.size(); i>=1; i--)
        {
            if(dp[i] != 1e9)
            {
                return i;
            }
        }

        return 0;
    }


    void run()
    {
        vector<int> nums({5,4,1,2,3});
        int result = this->longestIncreasingSubsequence(nums);
        cout<<result<<endl;
    }
};






