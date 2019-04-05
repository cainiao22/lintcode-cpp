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

    }
};

int main()
{
    RepeatedSubstringPattern a;
    string s ="aa";
    int result = a.repeatedSubstringPattern(s);
    cout<<(result != -1);
    return 0;
}





















