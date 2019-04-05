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
*/


#include<iostream>
#include<string>
#include<vector>
using namespace std;

class PaperReview
{
    float getSimilarity(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs)
    {
        // Write your code here
    }
};
