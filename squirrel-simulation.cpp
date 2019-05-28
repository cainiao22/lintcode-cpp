/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-12
* @brief         模拟松鼠
* @description   给定一个二维网格, 其中有一棵树, 一个松鼠和几枚坚果. 松鼠同一时间内最多只能携带一枚坚果. 松鼠可以向上, 下, 左, 右的相邻的方格移动.

                 请问, 松鼠要把所有的坚果送到树下, 最少需要移动多少格距离.
                 所有给定的位置都不会重叠.
                 松鼠一次最多只能携带一枚坚果.
                 给定的坚果位置没有顺序.
                 高度和宽度是正整数。3 <= 高度 * 宽度 <= 10,000.
                 给定的网格中至少包含一个坚果, 同时只有一棵树和一只松鼠.


* @example       输入: height = 5, width = 7,
                 treePosition = [2, 2],
                 squirrelPosition = [4, 4],
                 nuts = [[3, 0], [2, 5]]
                 输出: 12
* @solution      计算出所有坚果到树的距离(即曼哈顿距离)的距离之和, 该和乘以二就是松鼠从树来回取所有坚果的路程之和.

                 但是其中有一枚坚果不需要从树的位置往返去取, 而是从松鼠的初始位置去取, 然后送到树下. 枚举这枚坚果是哪颗, 然后取总距离最小的情况即可.
                 最小的那个应该是松鼠到坚果的距离 + 坚果到树的距离

                 保证sum - dist(坚果i-树) + dist(松鼠 + 坚果i) 最小
                 也就是保证 dist(坚果i-树) - dist(松鼠 + 坚果i)最大
*/


#include<iostream>
#include<vector>
#include<algorithm>


using namespace std;


class SquirrelSimulation
{
public:
    int minDistance(int height, int width, vector<int> &tree, vector<int> &squirrel, vector<vector<int>> &nuts) {

       int sum = 0;
       int index = 0;
       //dist(坚果i-树) - dist(松鼠 + 坚果i)
       int maxDist = -1e9;
       for(int i=0; i<nuts.size(); i++)
       {
           int cost = (abs(tree[0] - nuts[i][0]) + abs(tree[1] - nuts[i][1]));
           sum += cost * 2;
           int dist = abs(squirrel[0] - nuts[i][0]) + abs(squirrel[1] - nuts[i][1]);
           maxDist = max(maxDist, cost - dist);
       }

       sum -= maxDist;

       return sum;
    }
};
