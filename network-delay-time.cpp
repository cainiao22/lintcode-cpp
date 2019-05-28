/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-16
* @brief         网络延迟时间
* @description
*                有 N个网络节点，从 1 到 N标记.
*                给定 times，一个旅行时间和有向边列表 times[i] = (u, v, w)，其中u 是起始点， v是目标点，
*                w是一个信号从起始到目标点花费的时间。
*                现在，我们从一个特定节点 K发出信号，所有节点收到信号需要花费多长时间? 如果不可能，返回-1。
*
* @example
*                样例 1:
*                    输入:  times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
*                	输出:  2

*                样例 2:
*                	输入: times = [[1,2,1],[1,2,2]], N = 2, K = 1
*                	输出:  1
*
*                	解释:
*                	两条路选择最短的
* @solution         单源最短路径问题
*/


#include "commonutils.h"

class NetWordDelayTime : public CommonUtils
{
public:
    int networkDelayTime(vector<vector<int>> &times, int N, int K)
    {
        if(times.size() < N - 1)
        {
            return -1;
        }

        set<int> cur, remains;
        for(int i=1; i<= N; i++)
        {
            if(i == K)
            {
                cur.insert(i);
            }
            else
            {
                remains.insert(i);
            }
        }

        vector<int> dp(N+1, INF);
        dp[K] = 0;
        int result = INF;
        int MIN = INF;
        int index = -1;
        for(int i=0; i<times.size(); i++)
        {
            if(times[i][0] == K && dp[times[i][1]] > times[i][2])
            {
                dp[times[i][1]] = times[i][2];
            }
        }

        while(!remains.empty())
        {
            MIN = INF;
            index = -1;
            for(int remain : remains)
            {
                if(MIN > dp[remain])
                {
                    MIN = dp[remain];
                    index = remain;
                }
            }
            if(index == -1)
            {
                return -1;
            }
            remains.erase(index);
            cur.insert(index);
            for(int i=1; i<dp.size(); i++)
            {
                for(int j=0; j<times.size(); j++)
                {
                    if(times[j][0] == index)
                    {
                        if(dp[times[j][1]] > dp[index] + times[j][2])
                        {
                            dp[times[j][1]] = dp[index] + times[j][2];
                        }
                    }
                }
            }
        }

        int MAX = -INF;
        for(int i=1; i<dp.size(); i++)
        {
            MAX = max(MAX, dp[i]);
        }

        return MAX;
    }


    //标准Dijkstra解法
    int networkDelayTimeDijkstra(vector<vector<int>> &times, int N, int K)
    {
        int dist[N+1] = {INF};
        for(int i=1; i<N+1; i++)
        {
            dist[i] = INF;
        }
        bool visited[N+1] = {false};
        vector<vector<int>> G(N+1, vector<int>(N+1, INF));
        for(int i=0; i<times.size(); i++)
        {
            if(times[i][2] < G[times[i][0]][times[i][1]])
            {
                G[times[i][0]][times[i][1]] = times[i][2];
            }
            if(times[i][0] == K && times[i][2] < dist[times[i][1]])
            {
                dist[times[i][1]] = times[i][2];
            }
        }
        dist[K] = 0;
        visited[K] = true;
        for(int i=0; i<N-1; i++)
        {
            int MIN = INF;
            int index = K;
            //这里可以使用优先队列做优化，将剩余的节点放入一个优先队列中，每次直接拿取最小的
            for(int j=1; j<=N; j++)
            {
                if(!visited[j] && dist[j] < MIN)
                {
                    MIN = dist[j];
                    index = j;
                }
            }

            visited[index] = true;
            //如果使用优先队列做优化，这里需要做更新
            for(int j=1; j<=N; j++)
            {
                if(!visited[j] && dist[j] > dist[index] + G[index][j])
                {
                    dist[j] = dist[index] + G[index][j];
                }
            }
        }

        int MAX = 0;
        for(int i=1; i<=N; i++)
        {
            if(dist[i] > MAX)
            {
                MAX = dist[i];
            }
        }

        return MAX == INF ? -1 : MAX;

    }


    //标准bellman_ford解法
    int networkDelayTime_bellman_ford(vector<vector<int>> &times, int N, int K)
    {
        vector<vector<int>> graph(N+1, vector<int>(N+1, INF));
        int distance[N+1] = {INF};
        for(int i=1; i<N+1; i++)
        {
            distance[i] = INF;
        }

        for(int i=0; i<times.size(); i++)
        {
            if(graph[times[i][0]][times[i][1]] > times[i][2])
            {
                graph[times[i][0]][times[i][1]] = times[i][2];
            }
        }
        distance[K] = 0;
        for(int i=0; i<N-1; i++)
        {
            int flag = 0;
            for(int j=1; j<=N; j++)
            {
                for(int m=1; m<=N; m++)
                {
                    if(distance[m] > distance[j] + graph[j][m])
                    {
                        distance[m] = distance[j] + graph[j][m];
                        flag = 1;
                    }
                }
            }

            if(!flag)
            {
                break;
            }
        }

        int result = -INF;
        for(int i=1; i<=N; i++)
        {
            result = max(result, distance[i]);
        }

        return result == INF ? -1 : result;

    }


    //SPFA解法
    int networkDelayTime_SPFA(vector<vector<int>> &times, int N, int K)
    {
        vector<vector<int>> graph(N+1, vector<int>(N+1, INF));
        vector<int> dist(N+1, INF);
        vector<int> visitedCount(N+1, 0);
        vector<bool> contains(N+1, false);
        dist[K] = 0;
        for(int i=0; i<times.size(); i++)
        {
            if(graph[times[i][0]][times[i][1]] > times[i][2])
                graph[times[i][0]][times[i][1]] = times[i][2];
        }
        vector<int> que;
        que.push_back(K);
        contains[K] = true;
        while(!que.empty())
        {
            int top = que.at(que.size()-1);
            que.pop_back();
            contains[top] = false;
            for(int i=1; i<=N; i++)
            {
                if(graph[top][i] + dist[top] < dist[i])
                {
                    dist[i] = graph[top][i] + dist[top];
                    if(!contains[i])
                    {
                        //如果存在负环，直接返回
                        if(visitedCount[i] ++ >= N)
                        {
                            return -1;
                        }
                        if(!que.empty() && dist[que.front()] < dist[i])
                        {
                            que.push_back(i);
                        }
                        else
                        {
                            que.insert(que.begin(), i);
                        }

                        contains[i] = true;
                    }
                }
            }
        }

        int result = -INF;
        for(int i=1; i<=N; i++)
        {
            result = max(result, dist[i]);
        }

        return result == INF ? -1 : result;
    }

    void run()
    {
        vector<vector<int>> nums({{2,1,1},{2,3,1},{3,4,1}});
        int N = 4;
        int K = 2;
        int result = this->networkDelayTime_bellman_ford(nums, N, K);
        cout<<result<<endl;
    }
};












