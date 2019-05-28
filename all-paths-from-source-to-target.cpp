/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-07
* @brief         所有可能的路径
*
* @description   给定N个节点的有向无环图。 查找从节点0到节点N-1的所有可能的路径，你可以以任何顺序返回它们。
                 该图给出方式如下：节点为0, 1，…，graph.length - 1。 graph[i]是一个列表，
                 其中的任一个元素j表示图中含有一条 i->j 的有向边

* @example       样例 1:

                 输入: [[1,2],[3],[3],[]]
                 输出: [[0,1,3],[0,2,3]]
                 解释: 该图如下所示:
                   0--->1
                   |    |
                   v    v
                   2--->3
                   一共有两条路径: 0 -> 1 -> 3 和 0 -> 2 -> 3.
                 样例 2:

                 输入: [[1,3],[2],[3],[]]
                 输出: [[0,1,2,3],[0,3]]
* @solution
*/

#include "commonutils.h"

class AllPathFromSourceToTarget : public CommonUtils
{
public:

    vector<bool> visited;
    vector<vector<int>> result;


    void helper(vector<vector<int>> graph, int index, vector<int> item)
    {
        if(index == graph.size() - 1)
        {
            vector<int> copy(item);
            copy.push_back(index);
            result.push_back(copy);
            return;
        }
        visited[index] = true;
        item.push_back(index);
        for(int i=0; i<graph[index].size(); i++)
        {
            if(visited[graph[index][i]])
            {
                continue;
            }
            helper(graph, graph[index][i], item);
        }

        visited[index] = false;
        item.pop_back();
    }


    vector<vector<int>> helper2(vector<vector<int>> &graph, int index)
    {
        if(index == graph.size() - 1)
        {
            return {{index}};
        }

        vector<vector<int>> result;
        for(int neigh : graph[index])
        {
            for(auto path : helper2(graph, neigh))
            {
                path.insert(path.begin(), index);
                result.push_back(path);
            }
        }

        return result;
    }


    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        return this->helper2(graph, 0);
    }

    void run()
    {
        vector<int> v1({1,2}), v2({3}), v3({3}), v4({});
        vector<vector<int>> graph({v1, v2,v3, v4});
        vector<vector<int>> result = this->allPathsSourceTarget(graph);
        printVector2(result);
    }
};

