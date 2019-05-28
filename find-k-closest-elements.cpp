/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-25
* @brief         在排序数组中找最接近的K个数
*
*
* @description   给一个目标数 target, 一个非负整数 k, 一个按照升序排列的数组 A。在A中找与target最接近的k个整数。
*                返回这k个数并按照与target的接近程度从小到大排序，如果接近程度相当，那么小的数排在前面。
*
*
* @example      输入: A = [1, 2, 3], target = 2, k = 3
                输出: [2, 1, 3]

                输入: A = [1, 4, 6, 8], target = 3, k = 3
                输出: [4, 1, 6]
* @solution
*/

#include<iostream>
#include<vector>

using namespace std;

class FindKCloseNums
{
public:
    vector<int> kClosestNumbers(vector<int> &A, int target, int k)
    {
        vector<int> result(k);
        int left = 0, right = A.size() - 1;
        while(left <= right)
        {
            int mid = (left + right) / 2;
            if(target == A[mid])
            {
                right = mid;
                left = mid + 1;
                break;
            }

            if(target < A[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        int index = 0;
        while(k > 0 && right >= 0 && left < A.size())
        {
            if(abs(target - A[right]) <= abs(target - A[left]))
            {
                result[index ++] = A[right];
                right --;
            }
            else
            {
                result[index ++] = A[left];
                left ++;
            }
            k --;
        }

        while(k > 0 && right >= 0)
        {
            result[index ++] = A[right --];
            k --;
        }

        while(k > 0 && left < A.size())
        {
            result[index ++] = A[left ++];
            k--;
        }

        return result;
    }


    void run()
    {
        vector<int> nums({1,4,6,10,20});
        int target = 21;
        int k = 4;
        vector<int> result = this->kClosestNumbers(nums, target, k);
        for(int i=0; i<result.size();i++)
        {
            cout<<result[i]<<'\t';
        }

        cout<<endl;
    }
};



