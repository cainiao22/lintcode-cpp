/**
* @projectName   lintcode-cpp
* @author        yanpf
* @date          2019-04-05 HH:mm:ss
* @brief         论文查重
* @description
*               我们定义，两个论文的相似度为最长的相似单词子序列长度 * 2 除以两篇论文的总长度。
             给定两篇论文words1，words2（每个表示为字符串数组），和相似单词对列表pairs，求两篇论文的相似度。

             注意：相似关系是可传递的。例如，如果“great”和“good”类似，而“find”和“good”类似，那么“geat”和“find”类似。
             相似性也是对称的。 例如，“great”和“good”相似，则“good”和“great”相似。
             另外，一个词总是与其本身相似。
* @example
*           Example 1:

            Input：words1= ["great","acting","skills","life"]，words2= ["fine","drama","talent","health"]，pairs=  [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]]
            Output：0.75
            解释：
            两篇单词相似的子单词序列为
            "great","acting","skills"
            "fine","drama","talent"
            总长度为8
            相似度为6/8=0.75`

            Example 2:

            Input：words1= ["I","love","you"]，words2= ["you","love","me"]，pairs=  [["I", "me"]]
            Output：0.33
            解释：
            两篇单词相似的子单词序列为
            "I"
            "me"
            或
            "love"
            "love"
            或
            "you"
            "you"
            总长度为6
            相似度为2/6=0.33


* @solution 并查集应用 + 最长公共子序列
*/


#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

class PaperReview
{
public:
    map<string, string> map;

    string find(string s)
    {
        if(map[s] == s)
        {
            return s;
        }
        map.insert(pair<string, string>(s, find(map[s])));
        return map[s];
    }

    void union_(string a, string b)
    {
        string pa = find(a);
        string pb = find(b);
        map.insert(pair<string, string>(pa, pb));
    }

    float getSimilarity(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs)
    {
        // Write your code here
        for(int i=0; i<pairs.size(); i++)
        {
            map.insert(pair<string, string>(pairs[i][0], pairs[i][1]));
        }
        for(int i=0; i<words1.size(); i++)
        {
            if(map.count(words1[i]) == 0)
            {
                map.insert(pair<string, string>(words1[i], words1[i]));
            }
        }

        for(int i=0; i<words2.size(); i++)
        {
            if(!map.count(words2[i]))
            {
                map.insert(pair<string, string>(words2[i], words2[i]));
            }
        }

        int dp[words1.size() + 1][words2.size() + 1];
        for(int i=0; i<=words1.size(); i++)
        {
           for(int j=0; j<=words2.size(); j++)
           {
               dp[i][j] = 0;
           }
        }

        for(int i=1; i<=words1.size(); i++)
        {
            string p1 = find(words1[i - 1]);
            for(int j=1; j<=words2.size(); j++)
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                string p2 = find(words2[j - 1]);
                if(p1 == p2)
                {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
                }
            }
        }

        double len = dp[words1.size()][words2.size()];

        return len * 2 / (words1.size() + words2.size());
    }

    void run()
    {
        vector<string> w1({"great","acting","skills","life"});
        vector<string> w2({"fine","drama","talent","health"});
        //["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]
        vector<string> p1({"great", "good"});
        vector<string> p2({"fine", "good"});
        vector<string> p3({"acting","drama"}), p4({"skills","talent"});
        vector<vector<string>> pairs({p1, p2, p3, p4});
        double result = this->getSimilarity(w1, w2, pairs);
        cout<<result<<endl;
    }
};

