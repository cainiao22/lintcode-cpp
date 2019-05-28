/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-23
* @brief         and和or
* @description
*                给 n 个非负整数，请你求出最大或和，最小或和，最大与和，最小与和这四个数之和。

*                最大或和为在 n 个数中，任取若干个数（不能不取），进行或运算后最大的数。
*                最小或和为在 n 个数中，任取若干个数（不能不取），进行或运算后最小的数。
*                最大与和为在 n 个数中，任取若干个数（不能不取），进行与运算后最大的数。
*                最小与和为在 n 个数中，任取若干个数（不能不取），进行与运算后最小的数。
*                1 <= n <= 1000000，0 <= nums[i] <= 2^32 - 1。
*
*
* @example
*                Example 1:

*                Input:
*                n = 3
*                nums = [1, 2, 3]
*                Output:
*                7
*                Explanation:
*                maximum OR sum: 3, minimum OR sum: 1, maximum AND sum: 3, minimum AND sum: 0.
*                result: 3 + 1 + 3 + 0 = 7.
*                Example 2:

*                Input:
*                n = 3
*                nums = [0, 0, 1]
*                Output:
*                2
*                Explanation:
*                maximum OR sum: 1, minimum OR sum: 0, maximum AND sum: 1, minimum AND sum: 0.
*                result: 1 + 0 + 1 + 0 = 2.
*                Example 3:

*                Input:
*                n = 5
*                nums = [12313, 156, 4564, 212, 12]
*                Output:
*                25090
*                Explanation:
*                maximum OR sum: 12765, minimum OR sum: 12, maximum AND sum: 12313, minimum AND sum: 0.
*                result: 12765 + 12 + 12313 = 25090
*                Example 4:

*                Input:
*                n = 3
*                nums = [111111, 333333, 555555]
*                Output:
*                1588322
*                Explanation:
*                maximum OR sum: 917047, minimum OR sum: 111111, maximum AND sum: 555555, minimum AND sum: 4609.
*                result: 917047+ 111111+ 555555+ 4609 = 1588322.
* @solution
*/


#include "commonutils.h"


class AndAndOr : public CommonUtils
{
public:
    long long getSum(int n, vector<int> &nums)
    {
        // a & b <= min(a,b)    a|b >= max(a,b)
        int maxOr = nums[0], minOr = nums[0], maxAnd = nums[0], minAnd = nums[0];
        for(int i=1; i<nums.size(); i++)
        {
            maxOr |= nums[i];
            minOr = min(minOr, nums[i]);
            maxAnd = max(maxAnd, nums[i]);
            minAnd &= nums[i];
        }
        //一个转了，其他的自动扩
        return (long long)maxOr + minOr + maxAnd + minAnd;
    }
};
