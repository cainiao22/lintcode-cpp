/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-27
* @brief         循环数组中的环
*
*
* @description   给你一个包含正整数和负整数的数组。如果在某个位置包含正整数 n ，那么你将从这个位置出发正向（向右）移动 n 步；
*                相反的，如果在某个位置包含负整数 -n ，那么你将从这个位置出发反向（向左）移动 n 步。数组被视为首尾相连的，
*                即第一个元素视为在最后一个元素的右边，最后一个元素视为在第一个元素的左边。你的任务是判断其中是否包含环：
*                一个环从某一个确定的位置出发，在经过若干次移动后仍能回到这个位置。环中必须包含一个以上的元素，
*                且环必须是单向（不是正向就是反向）移动的
* @example
*                样例1：

*                输入：[2, -1, 1, 2, 2]
*                输出：true
*                解释：存在一个环，其下标可以表示为0 -> 2 -> 3 -> 0。
*                样例2：

*                输入：[-1, 2]
*                输出：false
* @solution
*/


#include "commonutils.h"


class CircularArrayLoop : public CommonUtils
{
public:
    bool circularArrayLoop(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> visited(nums.size());
        for(int i=0; i<n; i++)
        {
            if(visited[i]) continue;
            map<int, int> path;
            int cur = i;
            while(true)
            {
                int next = ((cur + nums[cur]) % n + n) % n;
                if(next == cur || nums[cur] * nums[next] < 0)
                {
                    break;
                }
                if(path.count(next))
                {
                    return true;
                }

                path[cur] = next;
                cur = next;
                visited[cur] = true;
            }
        }
        
        return false;
    }

    //TODO bug{1, 1, 2} 基于第一个思路的优化，去除visit和path数组
    bool circularArrayLoop2(vector<int> &nums)
    {
        int n = nums.size();
        for(int i=0; i<n; i++)
        {
            if(nums[i] == 0) continue;
            int cur = nums[i];
            nums[i] = 0;
            int next = ((i + cur + n) % n + n) % n;
            if(cur == next) continue;

            while(cur * nums[next] > 0)
            {
                nums[next] = 0;
                cur = nums[next];
                next = ((cur + next + n) % n + n) % n;
            }
            //BUG 这里的循环不一定是从i这里开始的
            if(i == next) return true;
        }

        return false;
    }


    int getNext(vector<int> &nums, int i)
    {
        int n = nums.size();
        return ((i + nums[i]) % n + n) % n;
    }

    //基于快慢指针的方式
    bool circularArrayLoop3(vector<int> &nums)
    {
        int n = nums.size();
        for(int i=0; i<nums.size(); i++)
        {
            if(nums[i] == 0) continue;
            int slow = i, fast = getNext(nums, i);

            int val = nums[i];
            while(val * nums[fast] > 0 && val * nums[getNext(nums, fast)] > 0)
            {
                if(slow == fast)
                {
                    if(slow == getNext(nums, slow)) break;
                    return true;
                }

                slow = getNext(nums, slow);
                fast = getNext(nums, getNext(nums, fast));
            }

            slow = i;
            while(val * nums[slow] > 0)
            {
                nums[slow] = 0;
                slow  = getNext(nums, slow);
            }
        }

        return false;
    }



    void run()
    {
        vector<int> nums({1, 1, 2});
        bool result = this->circularArrayLoop3(nums);
        cout<<result<<endl;
    }
};


