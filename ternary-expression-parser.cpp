/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-24
* @brief         三元式解析器
*
* @description   给定一个表示任意嵌套三元表达式的字符串expressions，计算表达式的结果。
*                你可以假设给定的表达式是有效的，并且只由数字0-9,?，T和F组成 (T和F分别表示True和False)。
*
*                给定字符串的长度是≤10000。
*                每个整数都是个位数。
*                条件表达式组从右到左(跟大多数的语言一样)。
*                条件永远是T或F，条件永远不会是一个数字。
*                表达式的结果总是对一个数字0-9,T或F求值
*
*
* @example       样例 1:
                 输入: "F?1:T?3:1"
                 输出:  3

                 解释:
                 最外层的条件表达式的结果式False，因此结果是冒号后面的项，即: T?3:1.
                 所以结果是3

                 样例 2:
                 输入: "T?2:3"
                 输出:  2

                 样例 3:
                 输入: "T?T?F:5:3"
                 输出:  F

                 解释:
                 可以表示成如下 : T? (T?F:5) : 3
                 所以结果是T?F:5的结果，是F


* @solution      用栈从后往前，遇到数字放进栈里。
                 遇到T就保留栈顶的，删掉第二个。
                 遇到F就删除栈顶的，保留第二个。
*/

#include<iostream>
#include<string>
#include<stack>

using namespace std;


class TernayExpressionParser
{
public:
    string parseTernary(string &expression)
    {
        int length = expression.length();
        stack<char> s;
        for(int i=length - 1; i>=0; i--)
        {
            if(expression[i] == ':')
            {
                continue;
            }
            else if(expression[i] == '?')
            {
                i --;
                char top = s.top();
                s.pop();
                char top2 = s.top();
                s.pop();
                if(expression[i] == 'T')
                {
                    s.push(top);
                }
                else
                {
                    s.push(top2);
                }
            }else {
                s.push(expression[i]);
            }
        }

        string result;
        return result + s.top();
    }

    /**
     * @brief 每次把整个 expression string 看成一个整体 'condition?first_part:second_part', 找到分隔符 ':' 对应的下标，
              然后将整个 expression 分成三部分 condition, first_part, second_part, 直至 expression 的长度为1.
     * @param expression
     * @return
     */
    string parseTernary2(string &expression)
    {
        while(expression.size() > 1)
        {
            char cond = expression.at(0);
            int cnt = 0;
            int index = 0;
            for(int i=2; i<expression.size(); i++)
            {
                if(expression.at(i) == '?')
                {
                    cnt --;
                }
                else if(expression.at(i) == ':')
                {
                    cnt ++;
                }

                if(cnt == 1)
                {
                    index = i;
                    break;
                }
            }

            string left = expression.substr(2, index - 2);
            string right = expression.substr(index+1);
            if(cond == 'T')
            {
                expression = left;
            }
            else
            {
                expression = right;
            }
        }

        return expression;
    }

    void run()
    {
        string expression = "T?T?F:5:3";
        string s = this->parseTernary2(expression);
        cout<<s<<endl;
    }
};

