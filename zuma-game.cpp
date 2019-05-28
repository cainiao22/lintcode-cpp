/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-29
* @brief         祖玛游戏
*
*
* @description
*                这是一个祖玛游戏。
*                一行球放在桌面上，球被涂上了红（R）、黄（Y）、蓝（B）、绿（G）和白（W）这么几种颜色，同时你也拥有几个球。
*                每一次，从你拥有的球当中拿出一个，插入到当前行当中（包括最左边和最右边）。然后，如果有三个或更多的同色球挨在一起，
*                然后就消除这几个球。一直这么做直到没有更多的球可以消除。
*                找到最少的需要插入的球的数量，使得所有的球都可以被删除。如果不能删除所有的球，那么就返回-1
*
*
* @example
*
*
*
*                样例 1:
*
*                输入: "WRRBBW", "RB"
*                输出: -1
*                解释: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW
*                样例 2:
*
*                输入: "WWRRBBWW", "WRBRW"
*                输出: 2
*                解释: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty
*                样例 3:
*
*                输入:"G", "GGGGG"
*                输出: 2
*                解释: G -> G[G] -> GG[G] -> empty
*                样例 4:
*
*                输入: "RBYYBBRRB", "YRBGB"
*                输出: 3
*                解释: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty
* @solution
*/

#include "commonutils.h"

class ZumaGame : public CommonUtils
{
public:

    int INF = 1e9;

    //递归解决
    int helper(string &board, vector<int> &c)
    {
        if(board == "")
        {
            return 0;
        }

        int result = INF;
        for(int i=0; i<board.length(); )
        {
            int j = i;
            while(i < board.length() && board[i] == board[j])
            {
                i ++;
            }

            int res = 3 - i + j;
            if(c[board.at(j)] >= res)
            {
                int used = res > 0 ? res : 0;
                c[board.at(j)] -= used;
                string item = board.substr(0, j) + board.substr(i, board.length());
                int temp = helper(item, c);
                result = min(result, used + temp);
                c[board.at(j)] += used;
            }
        }

        return result;
    }

    int findMinStep(string &board, string &hand)
    {
        vector<int> c(128, 0);
        for(int i=0; i<hand.size(); i++)
        {
            c[hand.at(i)] ++;
        }

        int result =  helper(board, c);

        return result == INF ? -1 : result;
    }

    void run()
    {
        string board = "WWRRBBWW";
        string hand = "WRBRW";
        int result = this->findMinStep(board, hand);
        cout<<result<<endl;
    }
};


