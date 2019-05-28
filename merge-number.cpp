/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-10
* @brief         合并数字
* @description   给出n个数，现在要将这n个数合并成一个数，每次只能选择两个数a,b合并，
*                每次合并需要消耗a+b的能量，输出将这n个数合并成一个数后消耗的最小能量
*
*
* @example       Example 1:
                 Input:  [1,2,3,4]
                 Output:  19

                     Explanation:
                     Merge 1,2, which consumes 3 energy, and the rest is [3,4,3].
                     Then merge 3,3, which consumes 6 energy, and the rest is [6,4].
                     Then merge the last two numbers, which consumes 10 energy, and a total of 19 energy was consumed.

                 Example 2:
                     Input: [2,8,4,1]
                     Output:  25

                     Explanation:
                     Merge 1,2, which consumes 3 energy, and the rest is [8,4,3].
                     Merge 3,4, which consumes 7 energy, and the rest is [7,8].
                     Merge the last two numbers, which consumes 15 energy,
                     and a total of 25 energy was consumed.
* @solution
*/


#include "commonutils.h"


class MergeNumber : public CommonUtils
{
public:
    //使用堆排序，每次拿两个最小的合并，再将他俩的和插回去
    int mergeNumber(vector<int> &numbers)
    {
        for(int i=numbers.size()/2; i>=0; i--)
        {
            int cur = i;
            int max = cur;
            while(max < numbers.size())
            {
                if(cur*2 + 1 < numbers.size() && numbers[cur*2+1] < numbers[max])
                {
                    max = cur * 2 + 1;
                }
                if(cur * 2 + 2 < numbers.size() && numbers[cur*2+2] < numbers[max])
                {
                    max = cur * 2 + 2;
                }

                if(max == cur)
                {
                    break;
                }
                int temp = numbers[max];
                numbers[max] = numbers[cur];
                numbers[cur] = temp;
                cur = max;
            }
        }

        int sum = 0;
        int left = numbers.size();
        while(left > 1)
        {
            int min1 = numbers[0];
            left --;

            numbers[0] = numbers[left];
            int cur = 0;
            int min = cur;
            while(cur < left)
            {
                if(cur * 2 + 1 < left && numbers[cur*2+1] < numbers[min])
                {
                    min = cur * 2 + 1;
                }

                if(cur * 2 + 2 < left && numbers[cur*2+2] < numbers[min])
                {
                    min = cur * 2 + 2;
                }

                if(min == cur)
                {
                    break;
                }
                int temp = numbers[min];
                numbers[min] = numbers[cur];
                numbers[cur] = temp;
                cur = min;
            }

            int min2 = numbers[0];
            sum += min1 + min2;
            numbers[0] = min1 + min2;
            cur = 0;
            min = cur;
            cout<<min1<<"+"<<min2<<"="<<(min1 + min2)<<endl;
            cout<<"sum:"<<sum<<endl;
            while(cur < left)
            {
                if(cur * 2 + 1 < left && numbers[cur*2+1] < numbers[min])
                {
                    min = cur * 2 + 1;
                }

                if(cur * 2 + 2 < left && numbers[cur*2+2] < numbers[min])
                {
                    min = cur * 2 + 2;
                }

                if(min == cur)
                {
                    break;
                }
                int temp = numbers[min];
                numbers[min] = numbers[cur];
                numbers[cur] = temp;
                cur = min;
            }
        }

        return sum;
    }

    void run()
    {
        vector<int> numbers({1,3,5,2,4,7,9,10,8,6});
        int result = this->mergeNumber(numbers);
        cout<<result<<endl;
    }
};




