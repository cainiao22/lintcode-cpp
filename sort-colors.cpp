/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-25
* @brief          颜色分类

* @description
*                给定一个包含红，白，蓝且长度为 n 的数组，将数组元素进行分类使相同颜色的元素相邻，
*                并按照红、白、蓝的顺序进行排序。
                 我们可以使用整数 0，1 和 2 分别代表红，白，蓝
* @example
*                给你数组 [1, 0, 1, 2], 需要将该数组原地排序为 [0, 1, 1, 2]
* @solution      一个相当直接的解决方案是使用计数排序扫描2遍的算法。

                 首先，迭代数组计算 0,1,2 出现的次数，然后依次用 0,1,2 出现的次数去覆盖数组。

                 你否能想出一个仅使用常数级额外空间复杂度且只扫描遍历一遍数组的算法？
*/


#include<iostream>
#include<vector>

using namespace std;

class SortColors
{
public:
    void sortColors(vector<int> &nums)
    {
        int colors[3] = {0};
        for(int i=0; i<nums.size(); i++)
        {
            colors[nums[i]] ++;
        }
        int index = 0;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<colors[i]; j++)
            {
                nums[index ++] = i;
            }
        }
    }

    //三根指针依次遍历 pl代表最后一个0的位置+1，pr代表第一个2的位置-1，i去遍历数组
    void sortColors2(vector<int> &nums)
    {

        int pl = 0;
        int pr = nums.size() - 1;
        int i = 0;
        while (i <= pr) {
            if (nums[i] == 0) {
                swap(nums, pl, i);
                pl++;
                i++;
            } else if(nums[i] == 1) {
                i++;
            } else {
                swap(nums, pr, i);
                pr--;
            }
        }
    }

    void swap(vector<int> &a, int i, int j)
    {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    void run()
    {
        vector<int> nums({2,0,0,1,2,0,2});
        this->sortColors2(nums);
    }

};

