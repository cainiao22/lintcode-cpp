/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-08
* @brief         图是否是树

* @description   给出 n 个节点，标号分别从 0 到 n - 1 并且给出一个 无向 边的列表 (给出每条边的两个顶点), 写一个函数去判断这张｀无向｀图是否是一棵树
* @example       样例 1:

                 输入: n = 5 edges = [[0, 1], [0, 2], [0, 3], [1, 4]]
                 输出: true.
                 样例 2:

                 输入: n = 5 edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]]
                 输出: false.
* @solution
*/


#include "commonutils.h"


class GraphVaildTree : public CommonUtils
{
public:
    //BFS解法
    bool validTree(int n, vector<vector<int>> &edges)
    {
        //树的特点是一个孩子只能有一个父节点
        map<int, set<int>> graph;
        for(vector<int> edge : edges)
        {
            if(graph.count(edge[0]) == 0)
            {
                set<int> s;
                graph[edge[0]] = s;
            }

            graph[edge[0]].insert(edge[1]);

            if(graph.count(edge[1]) == 0)
            {
                set<int> s;
                graph[edge[1]] = s;
            }

            graph[edge[1]].insert(edge[0]);
        }

        queue<int> q;
        q.push(0);
        set<int> visited;
        visited.insert(0);

        while(!q.empty())
        {
            int top = q.front();
            q.pop();
            set<int> neighbours = graph[top];
            for(int neighbour : neighbours)
            {
                if(visited.count(neighbour) > 0)
                {
                    return false;
                }
                //a-b这条边已经访问过了，就把b-a去掉
                graph[neighbour].erase(top);
                q.push(neighbour);
                visited.insert(neighbour);
            }
        }

        return visited.size() == n;

    }


    int num = 0;
    bool dfs(int pre, int cur, bool* visited, map<int, set<int>> graph)
    {
        if(visited[cur])
        {
            return false;
        }

        visited[cur] = true;
        num ++;
        for(int next : graph[cur])
        {
            //这个和上面解法的remove[cur]是一样的，即如果当前节点的下一个节点刚好是pre,也就是又指回去了，那就忽略
            if(next == pre)
            {
                continue;
            }

            if(!dfs(cur, next, visited, graph))
            {
                return false;
            }
        }

        return true;

    }

    //DFS解法
    bool validTree2(int n, vector<vector<int>> &edges)
    {
        bool visited[n];
        map<int, set<int>> graph;
        for(int i=0; i<n; i++)
        {
            visited[i] = false;
            graph[i] = set<int>();
        }
        for(vector<int> edge : edges)
        {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }

        bool result = dfs(-1, 0, visited, graph);
        if(!result)
        {
            return false;
        }

        return num == n;
    }


    int getRoot(int node, int* root)
    {
        if(root[node] == node)
        {
            return node;
        }
        return root[node] = getRoot(root[node], root);
    }

    //并查集 判断图中是否有环
    bool validTree3(int n, vector<vector<int>> &edges)
    {
        if(edges.size() != n-1)
        {
            return false;
        }
        int root[n];
        for(int i=0; i<n; i++)
        {
            root[i] = i;
        }

        for(int i=0; i<edges.size(); i++)
        {
            //如果两个节点在一个集合里面，然而他俩之间也有边相连，那么整个这个集合就是一个回路
            int root1 = getRoot(edges[i][0], root);
            int root2 = getRoot(edges[i][1], root);
            if(root1 == root2)
            {
                return false;
            }
            root[root2] = root1;
        }

        return true;

    }

    void run()
    {
        vector<vector<int>> edges({{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}});
        bool result = this->validTree(5, edges);
        cout<<result<<endl;
    }
};


