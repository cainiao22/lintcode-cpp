/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-26
* @brief         强密码检验器
*
*
* @description   当以下条件都满足时，一个密码被视为是强密码：

                 至少包含6个字符，但不超过20个字符。
                 至少包含一个小写字母，一个大写字母，和一个数字。
                 不能包含三个连续的重复字符（"...aaa..."是弱密码，但"...aa...a..."是强密码，假设它们的其他条件都满足了）。
                 写一个函数strongPasswordChecker(s)，它将一个字符串s作为输入，并且返回将其转换成强密码需要的最少改变次数。如果s已经是一个强密码了，返回0。

                 插入、删除或者替换任意一个字符都视为一次改变。


* @example       输入: s = "aaa123"
                 输出: 1


* @solution
*/


#include "commonutils.h"

//TODO 强密码检验器 太难了
class StrongPasswordsChecker : public CommonUtils
{
public:
    int strongPasswordChecker(string &s)
    {
        int dp[s.size()][3];

    }

    void run()
    {

    }
};

/*
int main()
{
    StrongPasswordsChecker a;
    a.run();
    return 0;
}
*/
