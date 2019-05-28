/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-12
* @brief         大楼轮廓
*
* @description   水平面上有 N 座大楼，每座大楼都是矩阵的形状，可以用一个三元组表示 (start, end, height)，分别代表其在x轴上的起点，终点和高度。
*                大楼之间从远处看可能会重叠，求出 N 座大楼的外轮廓线。
                 外轮廓线的表示方法为若干三元组，每个三元组包含三个数字 (start, end, height)，代表这段轮廓的起始位置，终止位置和高度。
                 请注意合并同样高度的相邻轮廓，不同的轮廓线在x轴上不能有重叠。
* @example       样例
                 给出三座大楼：

                 [
                   [1, 3, 3],
                   [2, 4, 4],
                   [5, 6, 1]
                 ]
                 外轮廓线为：

                 [
                   [1, 2, 3],
                   [2, 4, 4],
                   [5, 6, 1]
                 ]
* @solution
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;


//TODO 大楼轮廓
class TheSkyline
{
public:
    static int compare(vector<int> &v1, vector<int> &v2)
    {
        if(v1[0] != v2[0])
        {
            return v2[0] - v1[0];
        }
        if(v1[1] != v2[1])
        {
            return v2[1] - v1[1];
        }

        return v2[2] - v1[2];
    }

    vector<vector<int>> buildingOutline(vector<vector<int>> &buildings)
    {
        //sort(buildings.begin(), buildings.end(), TheSkyline::compare);
        vector<int> window;
        map<int, pair<int, int>> f;
        vector<vector<int>> result;
        for(int i=0; i<buildings.size(); i++)
        {
            if(!f.count(buildings[i][0]))
            {
                f.insert(pair<int, pair<int, int>>(buildings[i][0], pair<int, int>(0, buildings[i][2])));
            }
            else if(f[buildings[i][0]].second < buildings[i][2])
            {
                int temp = f[buildings[i][0]].first;
                f.insert(pair<int, pair<int, int>>(buildings[i][0], pair<int, int>(temp, buildings[i][2])));
            }

            if(!f.count(buildings[i][1]))
            {
                f.insert(pair<int, pair<int, int>>(buildings[i][1], pair<int, int>(buildings[i][2], 0)));
            }
            else if(f[buildings[i][1]].first < buildings[i][2])
            {
                int temp = f[buildings[i][1]].second;
                f.insert(pair<int, pair<int, int>>(buildings[i][1], pair<int, int>(buildings[i][2], temp)));
            }

            window.push_back(buildings[i][0]);
            window.push_back(buildings[i][1]);
        }

        sort(window.begin(), window.end());

        int pre = 0;
        for(int i=1; i<window.size(); i++)
        {
            if(f[window[pre]].second <= f[window[i]].first && f[window[pre]].second != f[window[i]].second)
            {
                result.push_back(vector<int>({window[pre], window[i], f[pre].first}));
                pre = i;
            }
        }

        return result;
    }

    void run()
    {
        vector<int> v1({1, 3, 3}), v3({5, 6, 1}), v2({2, 4, 4});
        vector<vector<int>> buildings({v1, v2, v3});
        vector<vector<int>> result = this->buildingOutline(buildings);
        cout<<result[0][0]<<endl;
    }
};

/*
int main()
{
    TheSkyline a;
    a.run();
    return 0;
}
*/
