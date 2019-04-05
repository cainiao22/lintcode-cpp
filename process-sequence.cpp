/**
* @projectName   lintcode-cpp
* @author        yanpf
* @date          2019-04-05 17:38:ss
* @brief         进程队列
*
* @description  有一个进程序列，包含每一个进程的开始点和结束点。

                有一个询问序列，询问某个时间点有多少个进程在跑。

                请你返回询问序列的查询结果
* @example
*               Example 1:

                Input: logs = [(1, 1234), (2, 1234)], queries = [2]
                Output: [2]
                Example 2:

                Input: logs = [(1, 1234), (1, 1235)], queries = [1234]
                Output: [1]
*/

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;


class Interval {
public:
    int start, end;
    Interval(int start, int end)
    {
        this->start = start;
        this->end = end;
    }
};

class ProcessSequence
{
public:
    vector<int> numberOfProcesses(vector<Interval> &logs, vector<int> &queries)
    {
            // Write your code here、
        vector<int> result;
        int m = queries.size();
        int n = logs.size();
        for(int i=0; i<m; i++)
        {
            int sum = 0;
            for(int j=0; j<n; j++)
            {
                if(queries[i] >= logs[j].start && queries[i] <= logs[j].end)
                {
                    sum ++;
                }
            }
            result.push_back(sum);
        }
        return result;
    }

    /**
     * @brief 线性扫描
     * @param logs
     * @param queries
     * @return
     */
    vector<int> numberOfProcesses2(vector<Interval> &logs, vector<int> &queries)
    {
        vector<int> list;
        map<int, int> map;
        for(int i=0; i < logs.size(); i++)
        {
            list.push_back(logs[i].start);
            list.push_back(logs[i].end + 1);
        }
        for(int i = 0; i<queries.size(); i++)
        {
            list.push_back(queries[i]);
        }
        sort(list.begin(), list.end());
        vector<int> cnt(list.size());
        for(int i=0; i<list.size(); i++)
        {
           map.insert(pair<int, int>(list[i], i));
        }

        for(int i=0; i < logs.size(); i++)
        {
           cnt[map[logs[i].start]] ++;
           cnt[map[logs[i].end+1]] --;
        }

        for(int i=1; i<list.size(); i++)
        {
            cnt[i] += cnt[i-1];
        }

        vector<int> result;
        for(int i = 0; i<queries.size(); i++)
        {
            result.push_back(cnt[map[queries[i]]]);
        }

        return result;
    }

    int run()
    {
        ProcessSequence a;
        vector<Interval> logs;
        vector<int> queries;
        logs.push_back(Interval(1, 1234));
        logs.push_back(Interval(2, 1234));
        queries.push_back(2);
        a.numberOfProcesses2(logs, queries);
    }
};


bool comp(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

class SolutionFromJiuzhang {
public:
    /**
     * @param logs: Sequence of processes
     * @param queries: Sequence of queries
     * @return: Return the number of processes
     */
    vector<int> numberOfProcesses(vector<Interval> &logs, vector<int> &queries) {
        // Write your code here
        //1->start, 0->end
        vector<pair<int, int>> timeline;
        for (int i = 0; i < logs.size(); i++) {
            Interval cur = logs[i];
            timeline.push_back(make_pair(cur.start, 1));
            timeline.push_back(make_pair(cur.end, 0));
        }
        sort(timeline.begin(), timeline.end(), comp);

        int count = 0;
        vector<pair<int, int>> nums;
        nums.push_back(make_pair(0, 0));
        for (int i = 0; i < timeline.size(); i++) {
            int curTime = timeline[i].first;

            if (timeline[i].second == 1) {
                count++;
            } else {
                count--;
            }

            nums.push_back(make_pair(curTime, count));
        }

        vector<int> res;
        for (int i = 0; i < queries.size(); i++) {
            int curTime = queries[i];
            //last pos that less or equal than curTime
            int index = findLessOrEqual(nums, curTime);
            res.push_back(nums[index].second);
        }
        return res;
    }

    int findLessOrEqual(vector<pair<int, int>> &nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (target > nums[mid].first) {
                left = mid;
            } else {
                right = mid;
            }
        }

        if (nums[right].first <= target) {
            return right;
        }
        return left;
    }
};



