/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-23
* @brief         爆破气球的最小箭头数
* @description
*
*                在二维空间中有许多球形气球。 对于每个气球，提供的输入是水平直径的起点和终点坐标。
*                由于它是水平的，因此y坐标无关紧要，因此直径的起点和终点的x坐标就足够了。
*                起点总是小于终点。 最多将有10^4个气球。
*                可以沿x轴从不同点垂直向上发射箭头。 如果xstart≤x≤xend，则坐标为xstart和xend的气球被在x处发射的箭头戳爆。 可以发射的箭头数量没有限制。
*                一次射击的箭头一直无限地向上移动。 问题是要找到戳破所有气球的最小发射箭头数
*
* @example       样例1

                 输入:
                 [[10,16], [2,8], [1,6], [7,12]]
                 输出:
                 2
                 说明：
                 一种方法是发射一个箭头，例如在x = 6（爆破气球[2,8]和[1,6]），发射另一个箭头在x = 11（爆破其他两个气球）。
                 样例2

                 输入:
                 [[1,2],[3,4],[5,6],[7,8]]
                 输出:
                 4
*
* @solution
*/


#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class MininumNumberOfArrows
{
public:

    static bool compare(vector<int> a, vector<int> b)
    {
        if(a[0]!=b[0])
               return a[0]<b[0];
           else if(a[0]==b[0] && a[1]!=b[1])
               return a[1]<b[1];
           else
               return a[2]>b[2];
    }

    int findMinArrowShots(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), MininumNumberOfArrows::compare);
        int right = 0;
        int result = 0;
        for(int i=0; i<points.size(); i++)
        {
            if(right < points[i][0])
            {
                right = points[i][1];
                result ++;
            }
            if(right > points[i][1])
            {
                right = points[i][1];
            }
        }

        return result;
    }

    int findMinArrowShots(vector<pair<int, int>>& points) {
            if (points.size() == 0) {
                return 0;
            }
            sort(points.begin(), points.end(), cmp);
            int ans = 1;
            int lastEnd = points[0].second;
            for (int i = 1; i < points.size(); i++) {
                if (points[i].first > lastEnd) {
                    ans++;
                    lastEnd = points[i].second;
                }
            }
            return ans;
        }

        static bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
            return a.second < b.second;
        }

    void run()
    {
        vector<vector<int>> points({{10,16}, {2,8}, {1,6}, {7,12}});
        int result = this->findMinArrowShots(points);
        cout<<result<<endl;
    }
};


