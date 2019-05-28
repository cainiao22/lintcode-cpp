/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-23
* @brief         巴士路线
* @description
*                给定一个巴士路线列表 routes. routes[i] 是第 i 辆巴士的循环路线. 例如, 如果 routes[0] = [1, 5, 7], 那么第一辆巴士按照 1 -> 5 -> 7 -> 1 -> 5 -> 7 ... 的路径不停歇地行进.

                 给定 S 和 T, 问在仅仅乘巴士的情况下, 从 S 赶到 T 最少乘多少辆不同的巴士? 如果无法赶到, 返回 -1.

                 1 <= routes.length <= 500
                 1 <= routes[i].length <= 500
                 0 <= routes[i][j] < 10 ^ 6

* @example
*                样例 1:

*                输入: routes = [[1, 2, 7], [3, 6, 7]], S = 1, T = 6
*                输出: 2
*                解释: 坐第一辆车到 7, 然后坐第二辆车到 6.
*                样例 2:

*                输入: routes = [[1], [15, 16, 18], [3, 4,12,14]], S = 3, T = 15
*                输出: -1
*                解释: 没有从 3 到 15 的路线.
*
* @solution
*/


#include "commonutils.h"


class BusRoutes : public CommonUtils
{
public:

    int dfs(GraphNode* node, int preColor, int target)
    {
        if(target == node->val)
        {
            return 0;
        }
        node->visited = true;
        int res = 1e9;
        for(int i=0; i<node->edgeList.size(); i++)
        {
            GraphEdge* edge = node->edgeList[i];
            if(edge->visited) continue;
            edge->visited = true;
            for(int j=0; j<edge->nodeList.size(); j++)
            {
                if(edge->nodeList[j]->visited) continue;
                int item = dfs(edge->nodeList[j], edge->color, target);
                if(preColor != edge->color)
                {
                    item += 1;
                }
                res = min(res, item);
            }
        }

        node->visited = false;
        return res;
    }

    int numBusesToDestination(vector<vector<int>> &routes, int S, int T)
    {
        map<int, GraphNode*> map;
        for(int i=0; i<routes.size(); i++)
        {
            for(int j=0; j<routes[i].size(); j++)
            {
                int nodeVal = routes[i][j];
                GraphNode* node = NULL;
                if(map.count(nodeVal))
                {
                    node = map[nodeVal];
                }
                else
                {
                    node = new GraphNode(nodeVal);
                    map[nodeVal] = node;
                }
                if(j > 0)
                {
                    GraphEdge *edge = new GraphEdge(i);
                    edge->addNode(node);
                    node->addEdge(edge);
                    GraphNode* pre = map[routes[i][j-1]];
                    edge->addNode(pre);
                    pre->addEdge(edge);
                }

            }
        }

        return dfs(map[S], -1, T);
    }

    //比较巧妙的方式
    int numBusesToDestination2(vector<vector<int>> &routes, int S, int T)
    {
        if(S == T)
        {
            return 0;
        }
        map<int, vector<int>> station2bus;
        for(int i=0; i<routes.size(); i++)
        {
            for(int station : routes[i])
            {
                if(!station2bus.count(station))
                {
                    vector<int> item;
                    station2bus[station] = item;
                }
                station2bus[station].push_back(i);
            }
        }

        set<int> visited;
        queue<int> q({S});
        int res = 0;
        while(!q.empty())
        {
            res ++;
            int len = q.size();
            for(int i=0; i<len; i++)
            {
                int top = q.front();
                q.pop();
                for(int bus : station2bus[top])
                {
                    if(visited.count(bus)) continue;
                    visited.insert(bus);
                    for(int j : routes[bus])
                    {
                        if(j == T) return res;
                        q.push(j);
                    }
                }
            }

        }

        return -1;
    }

    //比较巧妙的方式
    int numBusesToDestination3(vector<vector<int>> &routes, int S, int T)
    {
        if(S == T)
        {
            return 0;
        }
        map<int, vector<int>> station2bus;
        int len = routes.size();
        for(int i=0; i<len; i++)
        {
            for(int station : routes[i])
            {
                if(!station2bus.count(station))
                {
                    vector<int> item;
                    station2bus[station] = item;
                }
                station2bus[station].push_back(i);
            }
        }

        set<int> visited;
        queue<pair<int, int>> q({{S, 0}});

        while(!q.empty())
        {
            int stop = q.front().first;
            int cnt = q.front().second;
            q.pop();
            if(stop == T)
            {
                return cnt;
            }

            for(int bus : station2bus[stop])
            {
                for(int station : routes[bus])
                {
                    if(visited.count(station))
                    {
                        continue;
                    }
                    visited.insert(station);
                    q.push(pair<int, int>(station, cnt + 1));
                }

            }

        }

        return -1;
    }

    void run()
    {
        vector<vector<int>> routes({{1, 2, 7}, {3, 6, 7}});
        int S = 1, T = 6;
        int res = this->numBusesToDestination2(routes, S, T);
        cout<<res<<endl;
    }
};



