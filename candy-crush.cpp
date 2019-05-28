/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-23
* @brief         摘要
* @description
*                这个问题是要实现糖果粉碎传奇的基本消除算法。

*                给出一个二维的整数数组board，它表示一个糖果棋盘，棋盘中board[i][j]不同的正整数表示不同种类的糖果，
*                board[i][j] = 0表示位置(i, j)是空的。给出的棋盘是玩家执行某一步操作后的状态。
*                现在，你需要根据以下规则消除糖果，并将棋盘恢复到稳定的状态：

*                如果三个或者三个以上相同类型的糖果在横向或者纵向相连，同时消除它们，这些糖果的位置变为空。
*                在同时消除所有糖果后，如果空的位置上方有糖果，这些糖果会掉下来，直到他们碰到下方的糖果或者棋盘底部（不会从棋盘上边界掉下新的糖果）。
*                执行完以上步骤后，可能会有新的可以消除的糖果。如果有新的可以被消除的糖果，则重复以上步骤。
*                如果没有新的可以被消除的糖果（也就是说，棋盘是稳定的状态），返回当前的棋盘。
*                你需要执行以上的规则，直到棋盘稳定，然后返回稳定的棋盘。
* @example
* @solution
*/

#include "commonutils.h"

class CandyCrush : public CommonUtils
{
public:

    //清除横向数字
    int clearBoardX(vector<vector<int>> &board, int i, int j)
    {
        int x1 = j, x2 = j;
        while(x1 >= 0 && board[i][x1] == board[i][j])
        {
            x1 --;
        }
        while(x2 <board[i].size() && board[i][x2] == board[i][j])
        {
            x2 ++;
        }

        for(int m = x1+1; m < x2; m++)
        {
            int n = i;
            while(n > 0 && board[n-1][m] != 0)
            {
                board[n][m] = board[n-1][m];
                n --;
            }
            board[n][m] = 0;
        }

    }

    //清除纵向的数字
    void clearBoardY(vector<vector<int>> &board, int i, int j)
    {
        int y1 = i, y2 = i;
        while(y1 >=0 && board[y1][j] == board[i][j])
        {
            y1 --;
        }
        while(y2 < board.size() && board[y2][j] == board[i][j])
        {
            y2 ++;
        }

        int len = y2 - y1 - 1;
        while(y1 >= 0 && board[y1][j] != 0)
        {
            board[y1+len][j] = board[y1][j];
            y1 --;
        }
        y2 = y1 + len;
        while(y2 > y1)
        {
            board[y2][j] = 0;
            y2 --;
        }
    }
    //想复杂了，不需要横向和纵向和为3
    vector<vector<int>> candyCrushHard(vector<vector<int>> &board)
    {
        for(int i=0; i<board.size(); i++)
        {
            for(int j=0; j<board[i].size(); j++)
            {
                if(board[i][j] == 0)
                {
                    continue;
                }
                int x1 = j, x2 = j;
                int y1 = i, y2 = i;
                while(x1 >= 0 && board[i][x1] == board[i][j])
                {
                    x1 --;
                }
                while(x2 <board[i].size() && board[i][x2] == board[i][j])
                {
                    x2 ++;
                }

                while(y1 >= 0 && board[y1][j] == board[i][j])
                {
                    y1 --;
                }

                while(y2 < board.size() && board[y2][j] == board[i][j])
                {
                    y2 ++;
                }
                //TODO 如果横向和纵向和为3，这个len需要改动，具体操作就是和上面一样x方向调用y,y方向调用x,每个坐标取和它方向垂直的相同的数字最后求和
                int len = y2 - y1 - 1 + x2 - x1 - 1 - 1;
                if(len >= 3)
                {
                    for(int m = x1+1; m < x2; m++)
                    {
                        if(m == j) continue;
                        clearBoardY(board, i, m);
                    }

                    for(int m = y1 + 1; m < y2; m++)
                    {
                        if(m != i)
                        {
                            clearBoardX(board, m, j);
                        }
                        else
                        {
                            int n = m;
                            while(n > 0 && board[n-1][j] != 0)
                            {
                                board[n][j] = board[n-1][j];
                                n --;
                            }
                            board[n][j] = 0;
                        }
                    }

                    cout<<"***************"<<endl;
                    printVector2(board);
                    return candyCrush(board);
                }


            }
        }

        return board;
    }

    void markDown(vector<vector<int>> &board)
    {
        for(int j=0; j<board[0].size(); j++)
        {
            int i1 = board.size() - 1, i2 = board.size() - 1;
            while(i1 >= 0)
            {
                if(board[i1][j] > 0)
                {
                    board[i2][j] = board[i1][j];
                    i2 --;
                }
                i1 --;
            }
            while(i2 >= 0)
            {
                board[i2][j] = 0;
                i2 --;
            }
        }
    }

    vector<vector<int>> candyCrush(vector<vector<int>> &board)
    {
        bool flag = true;
        while(flag)
        {
            vector<vector<int>> boardCopy(board.size(), vector<int>(board[0].size(), 0));
            for(int i=0; i<board.size(); i++)
            {
                for(int j=0; j<board[i].size(); j++)
                {
                    boardCopy[i][j] = board[i][j];
                }
            }
            flag = false;
            for(int i=0; i<board.size(); i++)
            {
                for(int j=0; j<board[i].size(); j++)
                {
                    if(board[i][j] == 0)
                    {
                        continue;
                    }
                    int x1 = j, x2 = j;
                    int y1 = i, y2 = i;
                    while(x1 >= 0 && board[i][x1] == board[i][j])
                    {
                        x1 --;
                    }
                    while(x2 <board[i].size() && board[i][x2] == board[i][j])
                    {
                        x2 ++;
                    }

                    while(y1 >= 0 && board[y1][j] == board[i][j])
                    {
                        y1 --;
                    }

                    while(y2 < board.size() && board[y2][j] == board[i][j])
                    {
                        y2 ++;
                    }

                    int lenX = x2 - x1 - 1;
                    int lenY = y2 - y1 - 1;
                    flag = flag || lenX >= 3 || lenY >= 3;
                    if(lenX >= 3)
                    {
                        for(int m = x1 + 1; m < x2; m++)
                        {
                            boardCopy[i][m] = 0;
                        }
                    }

                    if(lenY >= 3)
                    {
                        for(int m=y1 + 1; m<y2; m++)
                        {
                            boardCopy[m][j] = 0;
                        }
                    }
                }
            }

            if(flag)
            {
                markDown(boardCopy);
            }
            board = boardCopy;
        }

        return board;
    }

    //另一个比较巧妙的解法 避免了前面数组的拷贝
    vector<vector<int>> candyCrushV2(vector<vector<int>> &board)
    {
        bool flag = true;
        while(flag)
        {
            flag = false;
            for(int i=0; i<board.size(); i++)
            {
                for(int j=0; j<board[i].size(); j++)
                {
                    if(board[i][j] <= 0)
                    {
                        continue;
                    }
                    int x1 = j, x2 = j;
                    int y1 = i, y2 = i;
                    while(x1 >= 0 && abs(board[i][x1]) == abs(board[i][j]))
                    {
                        x1 --;
                    }
                    while(x2 <board[i].size() && abs(board[i][x2]) == abs(board[i][j]))
                    {
                        x2 ++;
                    }

                    while(y1 >= 0 && abs(board[y1][j]) == abs(board[i][j]))
                    {
                        y1 --;
                    }

                    while(y2 < board.size() && abs(board[y2][j]) == abs(board[i][j]))
                    {
                        y2 ++;
                    }

                    int lenX = x2 - x1 - 1;
                    int lenY = y2 - y1 - 1;
                    flag = flag || lenX >= 3 || lenY >= 3;
                    if(lenX >= 3)
                    {
                        for(int m = x1 + 1; m < x2; m++)
                        {
                            //用负数去避免数组拷贝
                            if(board[i][m] > 0)
                            {
                                board[i][m] = -board[i][m];
                            }
                        }
                    }

                    if(lenY >= 3)
                    {
                        for(int m=y1 + 1; m<y2; m++)
                        {
                            if(board[m][j] > 0)
                            {
                                board[m][j] = -board[m][j];
                            }
                        }
                    }
                }
            }

            if(flag)
            {
                markDown(board);
            }
        }

        return board;
    }

    void run()
    {
        vector<vector<int>> board({
                                      {110,    5,  112,  113,  114},
                                      {210,  211,    5,  213,  214},
                                      {310,  311,    3,  313,  314},
                                      {410,  411,  412,    5,  414},
                                      {  5,    1,  512,    3,    3},
                                      {610,    4,    1,  613,  614},
                                      {710,    1,    2,  713,  714},
                                      {810,    1,    2,    1,    1},
                                      {  1,    1,    2,    2,    2},
                                      {  4,    1,    4,    4,  1014}
                                  }
                                  );
        printVector2(board);
        cout<<"*************"<<endl;
        vector<vector<int>> result = this->candyCrushV2(board);
        printVector2(result);
    }
};



