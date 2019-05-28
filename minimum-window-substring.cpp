/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-06
* @brief         摘要
*
* @description   给定一个字符串source和一个目标字符串target，在字符串source中找到包括所有目标字符串字母的最短子串
*
*
* @example       样例
*                例1:

*                输入:
*                ""
*                ""
*                输出:
*                ""
*                例2:
*
*                输入:
*                "ADOBECODEBANC"
*                "ABC"
*                输出:
*                "BANC"
*
* @solution
*/


#include "commonutils.h"


class MinimumWindowSubstr : public CommonUtils
{
public:

    string helper(string &source, int* target, int sum)
    {
        int result = INF;
        string a = "";
        int array[128];
        for(int index=0; index<source.length(); )
        {
            for(int i=0; i<128; i++)
            {
                array[i] = target[i];
            }
            int targetSum = sum;
            while(target[source[index]] == 0)
            {
                index ++;
            }
            int j = index;

            while(j < source.length() && targetSum > 0)
            {
                if(array[source[j]] > 0)
                {
                    array[source[j]] --;
                    targetSum -= source[j];
                }
                if(targetSum == 0)
                {
                    break;
                }
                j ++;
            }
            if(targetSum == 0 &&  j - index < result)
            {
                a = source.substr(index, j - index + 1);
                result = j - index;
            }

             index ++;
        }

        return a;
    }

    string minWindow(string &source , string &target)
    {
        int arr[128] = {0};
        int sum = 0;
        for(int i=0; i<target.length(); i++)
        {
            arr[target[i]] ++;
            sum += target[i];
        }

        return this->helper(source, arr, sum);
    }


    //窗口函数实现
    string minWindow2(string &source, string &target)
    {
        int sourceArr[128] ={0}, targetArr[128] = {0};
        int now = 0, k = 0;
        for(int i=0; i<target.size(); i++)
        {
            targetArr[target[i]] ++;
            if(targetArr[target[i]] == 1)
            {
                k++;
            }
        }

        int ansl = -1, ansr = -1;
        int l = 0, r = 0;
        for(l=0; l<source.length(); l++)
        {
            while(r < source.length() && now < k)
            {
                sourceArr[source[r]] ++;
                if(sourceArr[source[r]] == targetArr[source[r]])
                {
                    now ++;
                }

                r ++;
            }

            if(now == k)
            {
                if(ansl == -1 || r - l < ansr - ansl)
                {
                    ansl = l;
                    ansr = r;
                }
            }

            if(sourceArr[source[l]] == targetArr[source[l]])
            {
                now --;
            }
            sourceArr[source[l]] --;
        }

        if(ansl == -1)
        {
            return "";
        }

        return source.substr(ansl, ansr - ansl);

    }

    string minWindow3(string &source, string &target)
    {
        int ans = INF;
        string minStr = "";
        int targetArr[128] = {0};
        int targetSum = 0;
        int sourceSum = 0;
        for(int i=0; i<target.length(); i++)
        {
            targetArr[target[i]] ++;
            targetSum ++;
        }

        int j = 0;
        for(int i=0; i<source.length(); i++)
        {
            if(targetArr[source[i]] > 0)
            {
                sourceSum ++;
            }

            targetArr[source[i]] --;
            while(sourceSum >= targetSum)
            {
                if(ans > i - j + 1)
                {
                    ans = i - j + 1;
                    minStr = source.substr(j, i-j+1);
                }

                targetArr[source[j]] ++;
                if(targetArr[source[j]] > 0)
                {
                    sourceSum --;
                }

                j++;
            }
        }

        return minStr;
    }


    void run()
    {
        string source = "aaaaab";
        string target = "ab";

        string result = this->minWindow3(source, target);
        cout<<result<<endl;
    }

};
