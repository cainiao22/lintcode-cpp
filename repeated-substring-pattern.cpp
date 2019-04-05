/**
* @projectName   lintcode-cpp
* @author        yanpf
* @date          2019-04-05
*
* @brief         重复的子串模式
* @description  给你一个非空字符串，判断它能否通过重复它的某一个子串若干次（两次及以上）得到。字符串由小写字母组成，并且它的长度不会超过10000。
*
* @example
*   样例1：

    输入："abab"

    输出：True

    说明：可以由它的子串"ab"重复两次得到。
    样例2：

    输入："aba"

    输出：False
    样例3：

    输入："abcabcabcabc"

    输出：True

    说明：可以由它的子串"abc"重复四次得到（同时也可以是"abcabc"重复两次）。
*/

#include <iostream>
#include <vector>
using namespace std;

class RepeatedSubstringPattern {
public:
    bool repeatedSubstringPattern(string &s)
    {
        // write your code here
        string s2 = s + s;
        s2.erase(s2.begin());
        s2.erase(s2.end() - 1);
        return (s2.find(s) != -1);
    }

    bool repeatedSubstringPattern2(string &s)
    {
        // write your code here
        int next[s.size()];
        next[0] = -1;
        int i=0, j=-1;
        //这里只能使用未优化的方法，因为要求循环节
        while(i < s.size() - 1)
        {
            if(j == -1 || s.at(i) == s.at(j))
            {
                i ++;
                j ++;
                next[i] = j;
            }
            else
            {
                j = next[j];
            }
        }
        for(i=0; i<s.size(); i++)
        {
            cout<<next[i]<<'\t';
        }
        cout<<endl;
        //这个其实就是循环节
        int lenSub = s.size() - 1 - next[s.size() - 1];
        cout<<"循环长度:"<<lenSub<<endl;
        cout<<"s.size():"<<s.size()<<endl;
        //循环节不能为字符串长度并且字符串的长度刚好可以整除循环节
        if(next[s.size() - 1] != -1 &&  s.at(s.size() - 1) != s.at(next[s.size() - 1]))
        {
            return false;
        }
        return lenSub != s.size() && (s.size() % lenSub == 0);
    }

    /**
     * @brief 循环 需要每一位都相等，而字符串的next求解最后一位一般是不能相等的（优化后）
     * @param s
     * @return
     */
    bool repeatedSubstringPattern3(string &s)
    {
        int l = s.length();
        vector<int> next(l);
        next[0] = -1;
        int i, j = -1;
        for (i = 1; i < l; i++) {
            while (j >= 0 && s[i] != s[j + 1]) {
                j = next[j];
            }
            if (s[i] == s[j + 1]) {
                j++;
            }
            next[i] = j;
        }
        for(i=0; i<l; i++)
        {
            cout<<next[i]<<'\t';
        }
        cout<<endl;
        int lenSub = l - 1 - next[l - 1];
        return lenSub != l && l % lenSub == 0;
    }

    int run()
    {
        RepeatedSubstringPattern a;
        string s ="ababa";
        int result = a.repeatedSubstringPattern2(s);
        a.repeatedSubstringPattern3(s);
        cout<<result<<endl;
        return 0;
    }
};
























