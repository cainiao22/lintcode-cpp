/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-19
* @brief         最优除法
* @description   给定一个正整数列表，相邻的整数会执行浮点数除法，例如[2, 3, 4]->2 / 3 /4。

                 请在任意位置加入任意数量的括号，以此改变运算优先级。找出如何加括号能使结果最大，
                 以字符串的形式返回表达式。注意：表达式不要包括多余的括号。
* @example
*                例1:

                 输入: [1000,100,10,2]
                 输出: "1000/(100/10/2)"
                 解释:
                 1000/(100/10/2) = 1000/((100/10)/2) = 200
                 然而, 多重括号"1000/((100/10)/2)"是多余的, 因为它没有改变运算优先级. 所以应该返回 "1000/(100/10/2)".

                 其他的结果:
                 1000/(100/10)/2 = 50
                 1000/(100/(10/2)) = 50
                 1000/100/10/2 = 0.5
                 1000/100/(10/2) = 2
                 例2:

                 输入: [1000,100]
                 输出: "1000/100"


* @solution      有点像矩阵连成问题
*/


#include<iostream>
#include<string>
#include<vector>

using namespace std;



class OptimalDivision
{
public:
    double INF = -10e9;
    double MINF = 10e9;
    string optimalDivision(vector<int> &nums)
    {
        //dp[i][j][0] 最大数 dp[i][j][1]最小数
       double dp[nums.size()][nums.size()][2];
       string map[nums.size()][nums.size()][2];
       for(int i=0; i<nums.size(); i++)
       {
           dp[i][i][0] = dp[i][i][1] = nums[i];
           map[i][i][0] = map[i][i][1] = to_string(nums[i]);
           if(i < nums.size() -1)
           {
               dp[i][i+1][0] = dp[i][i+1][1] = nums[i] * 1.0 / nums[i+1];
               string s = to_string(nums[i]) + "/" + to_string(nums[i+1]);
               map[i][i+1][0] = map[i][i+1][1] = s;
           }
       }

       for(int len = 2; len < nums.size(); len ++)
       {
           for(int i=0; i + len < nums.size(); i++)
           {
               int j = i + len;
               dp[i][j][0] = INF;
               dp[i][j][1] = MINF;
               for(int k=i; k<j; k++)
               {
                   if(dp[i][j][0] < dp[i][k][0] * 1.0 / dp[k+1][j][1])
                   {
                       dp[i][j][0] = dp[i][k][0] * 1.0 / dp[k+1][j][1];
                       if(k+1 == j)
                       {
                           map[i][j][0] = map[i][k][0] + "/" + map[k+1][j][1];
                       }
                       else
                       {
                           map[i][j][0] = map[i][k][0] + "/" + "(" + map[k+1][j][1] + ")";
                       }
                   }

                   if(dp[i][j][1] > dp[i][k][1] * 1.0 / dp[k+1][j][0])
                   {
                       dp[i][j][1] = dp[i][k][1] * 1.0 / dp[k+1][j][0];
                       if(k+1 == j)
                       {
                           map[i][j][1] = map[i][k][1] + "/" + map[k+1][j][0];
                       }
                       else
                       {
                           map[i][j][1] = map[i][k][1] + "/" + "(" + map[k+1][j][0] + ")";
                       }
                   }

               }
           }
       }

       return map[0][nums.size()-1][0];

    }

    //将第二个数直至最后一个数优先进行除法运算，在与第一个数相除可得到最大值
    string optimalDivision2(vector<int> &nums)
    {
        if(nums.size() == 0) {
                    return "";
                }
                if (nums.size() == 1) {
                    return nums[0] + "";
                }
                if (nums.size() == 2) {
                    return nums[0] + "/" + nums[1];
                }
                string s;
                s = to_string(nums[0]) + "/(" + to_string(nums[1]);
                for (int i = 2; i < nums.size(); i++) {
                    s = s + "/" + to_string(nums[i]);
                }
                s = s + ")";
                return s;
    }

    void run()
    {
        vector<int> nums({6,2,3,4,5});
        string s = this->optimalDivision(nums);
        cout<<s<<endl;
    }
};

/*
int main()
{
    OptimalDivision a;
    a.run();
    return 0;
}
*/
