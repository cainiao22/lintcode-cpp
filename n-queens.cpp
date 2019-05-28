/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-07
* @brief         N皇后问题
*
* @description   n皇后问题是将n个皇后放置在n*n的棋盘上，皇后彼此之间不能相互攻击。

                 给定一个整数n，返回所有不同的n皇后问题的解决方案。

                 每个解决方案包含一个明确的n皇后放置布局，其中“Q”和“.”分别表示一个女王和一个空位置


* @example       例1:

                 输入:1
                 输出:
                    [["Q"]]


                 例2:

                 输入:4
                 输出:
                 [
                   // Solution 1
                   [".Q..",
                    "...Q",
                    "Q...",
                    "..Q."
                   ],
                   // Solution 2
                   ["..Q.",
                    "Q...",
                    "...Q",
                    ".Q.."
                   ]
                 ]

* @solution
*/

#include "commonutils.h"


class NQueues : public CommonUtils
{
public:

    vector<vector<int>> result;

    void helper(int n, int k, vector<int> item)
    {
        if(k == n)
        {
            vector<int> copy(item);
            result.push_back(copy);
            return;
        }

        for(int i=0; i<n; i++)
        {
            int length = item.size();
            int j = 0;
            for(j=0; j<length; j++)
            {
                if(item[j] == i || abs(item[j] - i) == k - j)
                {
                    break;
                }
            }

            if(j == length)
            {
                item.push_back(i);
                helper(n, k+1, item);
                item.pop_back();
            }
        }
    }

    /**
     * @brief 递归方式
     * @param n
     * @return
     */
    vector<vector<string>> solveNQueens(int n)
    {
        vector<int> item;
        this->helper(n, 0, item);

        vector<vector<string>> res;
        for(int i=0; i<result.size(); i++)
        {
            vector<string> item;
            for(int j=0; j<result[i].size(); j++)
            {
                string a;
                for(int k=0; k<n; k++)
                {
                    if(result[i][j] == k)
                    {
                        a = a + "Q";
                    }
                    else
                    {
                        a = a + ".";
                    }
                }
                item.push_back(a);
            }

            res.push_back(item);
        }

        return res;
    }


    vector<vector<string>> solveNQueens2(int n)
    {
        vector<int> pos(n, 0);
        int i=0;
        while(i >= 0)
        {
            mid:
            while(pos[i] < n)
            {
                for(int j=0; j<i; j++)
                {
                    if(pos[i] == pos[j] || abs(pos[i] - pos[j]) == i - j)
                    {
                        pos[i] ++;
                        goto mid;
                    }
                }

                if(i == n-1)
                {
                    vector<int> copy(pos);
                    result.push_back(copy);
                    pos[i] ++;
                }
                else
                {
                    i ++;
                }
            }
            pos[i] = 0;
            i --;
            pos[i] ++;
        }


        vector<vector<string>> res;
        for(int i=0; i<result.size(); i++)
        {
            vector<string> item;
            for(int j=0; j<result[i].size(); j++)
            {
                string a;
                for(int k=0; k<n; k++)
                {
                    if(result[i][j] == k)
                    {
                        a = a + "Q";
                    }
                    else
                    {
                        a = a + ".";
                    }
                }
                item.push_back(a);
            }

            res.push_back(item);
        }

        return res;

    }


    void run()
    {
        vector<vector<string>> res = this->solveNQueens2(1);
        cout<<res.size()<<endl;
    }

};


