/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-09
* @brief         全排列
* @description   给定一个数字列表，返回其所有可能的排列
* @example
* @solution
*/

#include<iostream>
#include<vector>
#include<queue>


using namespace std;

class Permutations
{
public:
    vector<vector<int>> result;
    vector<vector<int>> permute(vector<int> &nums)
    {
        helper(nums, 0);
        return result;
    }

    void helper(vector<int> &nums, int index)
    {
        if(index == nums.size())
        {
            vector<int> a;
            for(int i=0; i<nums.size(); i++)
            {
                a.push_back(nums[i]);
            }
            result.push_back(a);
            return;
        }
        for(int i=index; i<nums.size(); i++)
        {
            int temp = nums[index];
            nums[index] = nums[i];
            nums[i] = temp;
            helper(nums, index + 1);
            temp = nums[index];
            nums[index] = nums[i];
            nums[i] = temp;
        }
    }

    void run()
    {
        vector<int> num;
        num.push_back(1);
        num.push_back(2);
        num.push_back(3);
        permute2(num);
        for(int i=0; i<result.size(); i++)
        {
            for(int j=0; j<result[i].size(); j++)
            {
                cout<<result[i][j]<<'\t';
            }
            cout<<endl;
        }
    }

    vector<vector<int>> permute2(vector<int> &nums)
    {
        queue<vector<int>> q;
        for(int i=0; i<nums.size(); i++)
        {
            vector<int> a;
            a.push_back(nums[i]);
            q.push(a);
        }
        int len = q.size();
        while(len > 0)
        {
            for(int i=0; i<len; i++)
            {
                vector<int> item = q.front();
                q.pop();
                if(item.size() == nums.size())
                {
                    result.push_back(item);
                    continue;
                }
                for(int j=0; j<nums.size(); j++)
                {
                    if(!contains(item, nums[j]))
                    {
                        q.push(addVector(item, nums[j]));
                    }
                }
            }
            len = q.size();
        }

        return result;
    }

    bool contains(vector<int> &c, int num)
    {
        for(int i=0; i<c.size(); i++)
        {
            if(c[i] == num)
            {
                return true;
            }
        }

        return false;
    }

    vector<int> addVector(vector<int> a, int num)
    {
        vector<int> b;
        for(int i=0; i<a.size(); i++)
        {
            b.push_back(a[i]);
        }
        b.push_back(num);
        return b;
    }

};

