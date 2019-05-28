/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-15
* @brief         更新二进制位
* @description   给出两个32位的整数N和M，以及两个二进制位的位置i和j。写一个方法来使得N中的第i到j位等于M（M会是N中从第i为开始到第j位的子串）
*                保证从i到j的二进制可以完全覆盖M。例如，如果M=10011,那么可以保证在i和j之间至少有5位。 类似j=3和i=2不会出现因为M无法完全覆盖二进制的第二位和第三位。
* @example
* @solution
*/

#include<iostream>

using namespace std;

class UpdateBits
{
public:
    int updateBits(int n, int m, int i, int j)
    {
        //目的是保障i~j之间的数字全为1
        int a = (1 << (j + 1)) - (1 << i);
        a = ~ a;
        //直接左移32位会全部变为0
        if(j >= 31)
        {
            a = (1 << i) - 1;
        }


        n = n & a;
        n = n | (m << i);
        return n;
    }

    void run()
    {
        cout<<(1 << 31) - 1<<endl;
        int n = -2;
        int m = 10;
        int i = 24, j = 27;
        int c = this->updateBits(n, m, i, j);
        cout<<c<<endl;
    }
};


/**
int main()
{
    UpdateBits a;
    a.run();
    return 0;
}

**/
