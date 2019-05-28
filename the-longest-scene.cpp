/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-08
* @brief         摘要
* @description
*               一个字符串，每个字符表示一个场景。两个相同字符之间认为是一个连续的场景。
*               例如: abcda，可以认为这五个字符是同一个场景。或者acafghbeb可以认为又aca和beb两个场景。
*               场景之间有重合那么就把场景合起来，例如abcab，这里abca和bcab是重合的，那么认为这五个字符是同一个场景。
*               给一个字符串，求最长场景
* @example
*               给出 str = "abcda", 返回 5。

                解释：
                最长场景为"abcda"。
                给出 str = "abcab", 返回 5。

                解释：
                最长场景为"abcab"。

* @solution     有点像并查集 线段树
*/

#include<iostream>
#include<string>
#include<algorithm>
#include<map>

using namespace std;


namespace longestscenefromjiuzhang {
class Solution {
public:
    /**
     * @param str: The scene string
     * @return: Return the longest scene
     */
    int getLongestScene(string &str) {
        // Write your code here
        pair<int, int> seg[26];
        for (int i = 0; i < 26; i++) {
            seg[i].first = str.size();
            seg[i].second = -1;
        }
        for (int i = 0; i < str.size(); i++) {
            int idx = str[i] - 'a';
            seg[idx].first = min(seg[idx].first, i);
            seg[idx].second = max(seg[idx].second, i);
        }
        sort(seg, seg + 26);
        int maxLen = seg[0].second - seg[0].first + 1;
        int posL = seg[0].first, posR = seg[0].second;
        int ans = maxLen;
        for (int i = 1; i < 26; i++) {
            if (seg[i].first < str.size() && seg[i].second >= 0) {
                if (seg[i].first <= posR) {
                    posR = max(posR, seg[i].second);
                } else {
                    posL = seg[i].first;
                    posR = seg[i].second;
                }
                ans = max(posR - posL + 1, ans);
            }
        }
        return ans;
    }
};

}



class TheLongestScene
{
public:
    int getLongestScene(string &str) {
        pair<int, int> seg[26];
        for(int i=0; i<26; i++)
        {
            seg[i].first = str.size();
            seg[i].second = -1;
        }
        for(int i=0; i<str.size(); i++)
        {
            int index = str.at(i) - 'a';
            if(seg[index].first == str.size())
            {
                seg[index].first = i;
                seg[index].second = i;
            }
            else
            {
                seg[index].second = i;
            }

        }

        int result = 0;
        for(int i=1; i<str.size(); i++)
        {
            int index = str.at(i) - 'a';
            int pre = str.at(i - 1) - 'a';
            if(seg[index].first <= seg[pre].second)
            {
                seg[pre].second = max(seg[pre].second, seg[index].second);
                seg[index].second = max(seg[pre].second, seg[index].second);
                seg[index].first = seg[pre].first;
            }

            result = max(seg[index].second - seg[index].first + 1, result);
        }

        return result;
    }


    void run()
    {
        string s = "acafghbeb";
        int result = this->getLongestScene(s);
        cout<<result<<endl;
    }
};




