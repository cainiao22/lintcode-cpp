/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-26
* @brief         摘要
*
*
* @description   给定一个m×n的非负矩阵代表一个大洲，矩阵的每个单元格的值代表此处的地形高度，矩阵的左边缘和上边缘是“太平洋”，下边缘和右边缘是“大西洋”。
                 水流只能在四个方向（上，下，左或右）从一个单元格流向另一个海拔和自己相等或比自己低的单元格。
                 找到那些从此处出发的水既可以流到“太平洋”，又可以流向“大西洋”的单元格的坐标

* @example       例1:

                 输入:
                 matrix =
                 [[1,2,2,3,5],
                 [3,2,3,4,4],
                 [2,4,5,3,1],
                 [6,7,1,4,5],
                 [5,1,1,2,4]]
                 输出:
                 [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
                 解释:
                 Pacific ~ ~ ~ ~ ~
                       ~ 1 2 2 3 5 *
                       ~ 3 2 3 4 4 *
                       ~ 2 4 5 3 1 *
                       ~ 6 7 1 4 5 *
                       ~ 5 1 1 2 4 *
                         * * * * * Atlantic
                 例2:

                 输入:
                 matrix =
                 [[1,2],
                 [4,3]]
                 输出:
                 [[0,1],[1,0],[1,1]]



* @solution
*/


#include<iostream>
#include<vector>
#include<map>
#include<queue>

using namespace std;



class PacificAtlanticWaterFlow
{
public:

    vector<vector<int>> memory;
    vector<vector<int>> dest;

    int INF = 1e9;



    vector<vector<int>> pacificAtlantic(vector<vector<int>> &matrix)
    {
        vector<vector<int>> result;

        vector<int> dx({-1, 0, 1, 0}), dy({0, 1, 0, -1});

        queue<pair<int, int>> q;
        for(int i=0; i<matrix.size(); i++)
        {
            q.push(pair<int, int>(i, 0));
            vector<int> item(matrix[i].size(), 0);
            memory.push_back(item);
            dest.push_back(vector<int>(matrix[i].size(), 0));
            memory[i][0] = 1;
        }

        for(int i=0; i<matrix[0].size(); i++)
        {
            q.push(pair<int, int>(0, i));
            memory[0][i] = 1;
        }

        while(!q.empty())
        {
            pair<int, int> top = q.front();
            q.pop();
            dest[top.first][top.second] |= 1;
            for(int i=0; i<dx.size(); i++)
            {
                if(top.first + dx[i] >= 0
                        && top.second + dy[i] >= 0
                        && top.first + dx[i] < matrix.size()
                        && top.second + dy[i] < matrix[top.first].size()
                        && !memory[top.first + dx[i]][top.second + dy[i]]
                        && matrix[top.first + dx[i]][top.second + dy[i]] >= matrix[top.first][top.second])
                {
                    q.push(pair<int, int>(top.first + dx[i], top.second + dy[i]));
                    memory[top.first + dx[i]][top.second + dy[i]] = 1;
                }
            }
        }

        for(int i=0; i<memory.size(); i++)
        {
            for(int j=0; j<memory[i].size(); j++)
            {
                memory[i][j] = 0;
            }
        }

        for(int i=0; i<matrix.size(); i++)
        {
            q.push(pair<int, int>(i, matrix[i].size() - 1));
            memory[i][matrix[i].size() - 1] = 1;
        }

        for(int i=0; i<matrix[matrix.size() - 1].size(); i++)
        {
            q.push(pair<int, int>(matrix.size() - 1, i));
            memory[matrix.size() - 1][i] = 1;
        }

        while(!q.empty())
        {
            pair<int, int> top = q.front();
            q.pop();
            dest[top.first][top.second] |= 2;
            for(int i=0; i<dx.size(); i++)
            {
                if(top.first + dx[i] >= 0
                        && top.second + dy[i] >= 0
                        && top.first + dx[i] < matrix.size()
                        && top.second + dy[i] < matrix[top.first].size()
                        && !memory[top.first + dx[i]][top.second + dy[i]]
                        && matrix[top.first + dx[i]][top.second + dy[i]] >= matrix[top.first][top.second])
                {
                    q.push(pair<int, int>(top.first + dx[i], top.second + dy[i]));
                    memory[top.first + dx[i]][top.second + dy[i]] |= 2;
                }
            }
        }

        for(int i=0; i<dest.size(); i++)
        {
            for(int j=0; j<dest[i].size(); j++)
            {
                if(dest[i][j] == 3)
                {
                    result.push_back(vector<int>({i, j}));
                }
            }
        }

        return result;
    }






    void run()
    {
        vector<int> m1({1,2,2,3,5}), m2({3,2,3,4,4}), m3({2,4,5,3,1}), m4({6,7,1,4,5}), m5({5,1,1,2,4});
        vector<vector<int>> matrix({m1, m2, m3, m4, m5});

        vector<vector<int>> result = this->pacificAtlantic(matrix);
        for(int i=0; i<result.size(); i++)
        {
            for(int j=0; j<result[i].size(); j++)
            {
                cout<<result[i][j]<<'\t';
            }
            cout<<endl;
        }
    }

};




