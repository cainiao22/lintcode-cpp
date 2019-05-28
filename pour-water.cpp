/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-28
* @brief         倒水
*
* @description   给定一个评估图， heights[i] 表示该地的高度。所有下标对应的地面宽度均为 1。请问V个单位的水落在下标为 K 的地面之后，每个下标对应的地面水量是多少？

                 水首先从下标K降落，接着它依据下述规则流动：

                 首先，液滴不能流向更高的地方；
                 如果液滴能向左最终能下降，那么向左移动；
                 否则，如果能向右最终能下降，则向右移动；
                 否则，留当前位置。
                 其中，“最终能下降”意味着如果液滴像那个方向移动，最终能够处于更低高度。

                 假设整个区域左右两侧有无限高的地形。此外，一单位水不能拆分，即每个单位必须恰好落在一个区块内。


* @example       样例 1:

输入: heights = [2,1,1,2,1,2,2], V = 4, K = 3
输出: [2,2,2,3,2,2,2]
解释:
  #       #
  #       #
  ##  # ###
  #########
   0123456    <- index
   2112122    <- level(height)

  第一滴水落在K = 3:

  #       #
  #   w   #
  ##  # ###
  #########
   0123456

  无论向左还是向右，水只能向更低高度移动。所以这里，它向左移动。

  #       #
  #       #
  ## w# ###
  #########
   0123456
   2122122

  而后，继续向左移动不会最终下降了，它停在原地。下一单位水下落：

  #       #
  #   w   #
  ## w# ###
  #########
   0123456

  它向左移动（即使也可以向右移动，但依据规则必须向左移动）。

  #       #
  #  w    #
  ## w# ###
  #########
   0123456

  #       #
  #       #
  ##ww# ###
  #########
   0123456
   2222122

  经过上述过程后，第三滴水下落。它向右移动。

  #       #
  #   w   #
  ##ww# ###
  #########
   0123456

  #       #
  #       #
  ##ww#w###
  #########
   0123456
   2222222

  最后，第四滴水下落。无论向左向右，它都最终不会变低，所以它呆在原地。

  #       #
  #   w   #
  ##ww#w###
  #########
   0123456
   2223222

  结果为 [2,2,2,3,2,2,2]:

      #
  #######
  #######
  0123456
样例 2:

输入: heights = [1,2,3,4], V = 2, K = 2
输出: [2,3,3,4]
解释: 最后一滴水落到位置1，因为继续往左走不会下降。
样例 3:

输入: heights = [3,1,3], V = 5, K = 1
输出: [4,4,4]
* @solution
*/


#include "commonutils.h"


class PourWater : public CommonUtils
{
public:
    vector<int> pourWater(vector<int> &heights, int V, int K)
    {
        for(int i=0; i<V; i++)
        {
            int cur = K - 1;
            int target = K;
            while(cur >= 0 && heights[cur] <= heights[cur + 1])
            {
                if(heights[cur] < heights[cur + 1])
                {
                    target = cur;
                }

                cur --;
            }

            if(target != K)
            {
                heights[target] ++;
                continue;
            }

            cur = K + 1;
            target = K;
            while(cur <heights.size() && heights[cur] <= heights[cur - 1])
            {
                if(heights[cur] < heights[cur - 1])
                {
                    target = cur;
                }

                cur ++;
            }

            if(target != K)
            {
                heights[target] ++;
                continue;
            }

            heights[K] ++;
        }

        return heights;
    }

    void run()
    {
        vector<int> heights({13,7,9,6,4,4,4,10,15,9});
        int v = 7, k = 1;
        this->pourWater(heights, v, k);

        printVector(heights);
    }
};

int main()
{
    PourWater a;
    a.run();
    return 0;
}













