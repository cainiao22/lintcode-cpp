/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-28
* @brief         最长无重复字符的子串

* @description   给定一个字符串，请找出其中无重复字符的最长子字符串
*
* @example
*                样例 1:
*
*                输入: "abcabcbb"
*                输出: 3
*                解释: 最长子串是 "abc".
*                样例 2:
*
*                输入: "bbbbb"
*                输出: 1
*                解释: 最长子串是 "b".
*
* @solution
*/

#include "commonutils.h"

class LongestSubstringWithoutRepeatingCharacters : public CommonUtils
{
public:
    int lengthOfLongestSubstring(string &s)
    {
        if(s.size() == 0)
        {
            return 0;
        }
        int start = -1;
        map<char, int> m;
        int result = 0;
        for(int i=0; i<s.size(); i++)
        {
            if(m.count(s.at(i)))
            {
                //假如当前字符串在start的前面，那么忽略
                start = max(start, m[s.at(i)]);

            }
            result = max(result, i - start);
            m[s.at(i)] = i;
        }

        return result;
    }

    void run()
    {
        string s = "an++--viaj";
        cout<<this->lengthOfLongestSubstring(s)<<endl;
    }
};


