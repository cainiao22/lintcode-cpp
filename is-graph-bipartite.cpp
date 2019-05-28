/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-22
* @brief         图可以被二分么
*
* @description   给定一个无向图 graph, 输出 true 当且仅当这个图是可以被二分的（也叫二部图）。

                 如果一个图是二部图，则意味着我们可以将图里的点集分为两个独立的子集A和B，并且图中所有的边都是一个端点属于A，另一个端点属于B。

                 关于图的表示：graph[i] 为一个列表，表示与节点i有边相连的节点。这个图中一共有 graph.length 个节点，为0到graph.length-1。

                 图中没有自边或者重复的边存在，即: graph[i] 中不包含 i, 也不会包含某个点两次


                 graph 中包含的总节点数的范围为 [1, 100]。
                 graph[i] 只包含范围为 [0, graph.length - 1].中的一些整数。
                 graph[i] 不会包含 i 自己或是某个值两次。
                 图是无向的：如果点 j 存在于 graph[i]这个列表里，则 i 也会存在于 graph[j]这个列表里


* @example
*               样例 1:

*               输入: [[1,3], [0,2], [1,3], [0,2]]
*               输出: true
*               解释:
*                 图看上去长这样：
*                 0----1
*                 |    |
*                 |    |
*                 3----2
*                 所以我们可以把图分成以下两部分，并且各自内部没有连线: {0, 2} and {1, 3}.
*               样例 2:
*
*               输入: [[1,2,3], [0,2], [0,1,3], [0,2]]
*               输出: false
*               解释:
*                 图看上去长这样：
*                 0----1
*                 | \  |
*                 |  \ |
*                 3----2
*                 我们没有办法将这个点集分为两个独立的子集。（即各自内部没有连线）
*
*
*
* @solution 又像并查集
*/



#include<iostream>
#include<vector>
#include<queue>

using namespace std;


class BipartiteGraph{
public:

    /**
     * @brief 用染色法，把图中的点染成黑色和白色。
              首先取一个点染成白色，然后将其相邻的点染成黑色，如果发现有相邻且同色的点，那么就退出，可知这个图并非二分图
     * @param graph
     * @return
     */
    //TODO bug 图可以被二分么,对于{{}, {2}, {0}}这种类型的数据没办法做出判断
    bool isBipartite(vector<vector<int>> &graph)
    {
        //未染色为0， 白色为1，黑色为2
        int colors[graph.size()] = {0};
        queue<int> q;
        for(int i=0; i<graph.size(); i++)
        {
            if(colors[i] == 0)
            {
                q.push(i);
                colors[i] = 1;
                while(!q.empty())
                {
                    int j = q.front();
                    q.pop();
                    for(int k=0; k<graph[j].size(); k++)
                    {
                        if(colors[graph[j][k]] == colors[j])
                        {
                            return false;
                        }
                        else if(colors[graph[j][k]] == 0)
                        {
                            colors[graph[i][j]] = -colors[j];
                            q.push(graph[j][k]);
                        }

                    }
                }
            }

        }

        return true;
    }

    bool isBipartite2(vector<vector<int>> &graph)
    {
        int colors[graph.size()] = {0};
        for(int i=0; i<graph.size(); i++)
        {
            if(colors[i] == 0)
            {
                colors[i] = 1;
                for(int j=0; j<graph[i].size(); j++)
                {
                    bool result = helper(graph, graph[i][j], -1, colors);
                    if(!result)
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool helper(vector<vector<int>> &graph, int node, int color, int* colors)
    {
        if(colors[node] == -color)
        {
            return false;
        }
        if(colors[node] == 0)
        {
            colors[node] = color;
            for(int i=0; i<graph[node].size(); i++)
            {
                bool result = helper(graph, graph[node][i], -color, colors);
                if(!result)
                {
                    return false;
                }
            }
        }

        return true;

    }


    void run()
    {
        vector<vector<int>> graph;
        //[1,3], [0,2], [1,3], [0,2]
        vector<int> v1({1,3}), v2({0, 2}), v3({1, 3}), v4({0, 2});
        graph.push_back(v1);
        graph.push_back(v2);
        graph.push_back(v3);
        graph.push_back(v4);
        bool result = this->isBipartite(graph);
        cout<<result<<endl;
    }
};








