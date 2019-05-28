/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-25
* @brief         创建最大数
*
* @description   给出两个长度分别是m和n的数组来表示两个大整数，数组的每个元素都是数字0-9。
*                从这两个数组当中选出k个数字来创建一个最大数，其中k满足k <= m + n。
*                选出来的数字在创建的最大数里面的位置必须和在原数组内的相对位置一致。返回k个数的数组。
*                你应该尽可能的去优化算法的时间复杂度和空间复杂度。
* @example       样例 1:

                 输入：nums1 = [3, 4, 6, 5]， nums2 = [9, 1, 2, 5, 8, 3]，k = 5
                输出：[9, 8, 6, 5, 3]
                解释：
                从第一个数组选择[6, 5]，从第二个数组选择[9, 8, 3]
                样例 2:

                输入：nums1 = [6, 7]， nums2 = [6, 0, 4]，k = 5
                输出：[6, 7, 6, 0, 4]
                解释：
                从第一个数组选择[6, 7]，从第二个数组选择[6, 0, 4]
                样例 3:

                输入：nums1 = [3, 9]， nums2 = [8, 9]，k = 3
                输出：[9, 8, 9]
                解释：
                从第一个数组选择[9]，从第二个数组选择[8, 9]


* @solution     使用枚举+贪心 首先遍历k,从nums1中拿取i个最大数组成数组，然后从nums2中拿取k-i个数组成数组，
*               然后对于这两个数组做merge，拿取局部最大的数组，最后和全局做比较得出全局最大的
*/

#include<iostream>
#include<vector>

using namespace std;

//TODO  free(): corrupted unsorted chunks
class CreateMaximumNumber
{
public:
    vector<int> maxNumber(vector<int> &nums1, vector<int> &nums2, int k)
    {
        //从nums1里面最多可以拿多少个元素。如果nums1元素个数大于k，最多可以拿k个，如果num1元素个数小于k，最多就nums1.size()个
        int max = nums1.size() > k ? k : nums1.size();
        //从nums1里面最少取多少个元素。如果nums2元素个数小于k个，即便全部从nums2里面取也不可能够，所以最少要从nums1里面取k - nums2.size()个，
        //如果nums2元素个数大于等于k个，那么可以全部从nums2里面取，不从nums1里面取
        int min = nums2.size() < k ? (k - nums2.size()) : 0;
        vector<int> result(k, 0);
        for(int i=min; i<=max; i++)
        {
            vector<int> v1 = getMax(nums1, i);
            vector<int> v2 = getMax(nums2, k - i);
            vector<int> item = merge(v1, v2);
            if(greater(item, result))
            {
                item.swap(result);
                result = item;
            }
            else
            {
                result.swap(item);
            }
        }

        return result;
    }


    bool greater(vector<int> &nums1, vector<int> &nums2)
    {
        for(int i=0; i<nums1.size(); i++)
        {
            if(nums1[i] != nums2[i])
            {
                return nums1[i] > nums2[i];
            }
        }

        return false;
    }


    vector<int> merge(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> result(nums1.size() + nums2.size(), 0);
        int i = 0, j = 0, k = 0;
        while(i < nums1.size() && j < nums2.size())
        {
            //这里不能做简单的比较，因为如果nums1[i] == nums2[j]，其实需要取的是他们下一位大的那个
            //{1,6,5,4,7,3,9,5,3,7,8,4,1,1,4}), nums2({4,3,1,3,5,9}
            if(compare(nums1, i, nums2, j))
            {
                result[k++] = nums1[i ++];
            }
            else
            {
                result[k++] = nums2[j ++];
            }
        }

        while(i < nums1.size())
        {
            result[k++] = nums1[i ++];
        }

        while(j < nums2.size())
        {
            result[k++] = nums2[j ++];
        }

        return result;
    }

    //从nums中选取最大的k个数字 贪心
    vector<int> getMax(vector<int> &nums, int k)
    {
        vector<int> result(k, 0);
        int j = 0;
        for(int i=0; i<nums.size() && k > 0; i++)
        {
            while(j > 0 && nums.size() - i > k - j && result[j-1] < nums[i])
            {
                j --;
            }
            result[j ++] = nums[i];
        }

        return result;
    }

    bool compare(vector<int> &nums1, int pos1, vector<int> &nums2, int pos2)
    {
        for(; pos1 < nums1.size() && pos2 < nums2.size(); pos1 ++, pos2 ++)
        {
            if (nums1[pos1] > nums2[pos2])
                return true;
            if (nums1[pos1] < nums2[pos2])
                return false;
        }

        return pos1 != nums1.size();
    }

    void run()
    {
        vector<int> nums1({5,7,7,0,1,6,7,2,2,4,6,8,9,2,0,9,8,7,6,3,9,4,8,8,4,5,3,3,7,4,3,2,8,9,8,4,0,2,0,2,2,0,4,2,2,8,6,7,1,0,8,7,5,4,6,4,1,7,4,4,3,7,5,8,8,0,3,1,3,4,6,0,6,9,6,6,4,2,1,9,3,7,4,4,4,2,1,9,5,2,1,7,6,0,1,3,5,3,7,7}), nums2({8,3,7,8,6,9,1,5,5,0,5,2,8,7,8,3,3,7,9,2});
        int k = 100;
        vector<int> result = this->maxNumber(nums1, nums2, k);
        for(int i=0; i<result.size(); i++)
        {
            cout<<result[i]<<'\t';
        }
    }
};









