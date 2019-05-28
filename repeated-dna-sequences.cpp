/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-04-19
* @brief         重复的DNA序列
*
*
* @description   所有DNA由一系列缩写为A，C，G和T的核苷酸组成，例如：“ACGAATTCCG”。 在研究DNA时，有时识别DNA中的重复序列是非常必要的。

                 编写一个函数来查找DNA分子中，长度为10个字母的，不止一次出现的序列（子串）。



* @example       样例1

                 输入: "A"
                 输出: []
                 样例2

                 输入: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
                 输出: ["AAAAACCCCC", "CCCCCAAAAA"]
* @solution
*/


#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;


class RepeatedDnaSequences
{
public:
    int MAX = pow(4,9);
    int encode(string &s)
    {
        int sum = 0;
        for(int i=0; i<s.size(); i++)
        {
           char a = s.at(i);
           if(a == 'A')
           {
               sum = sum * 4;
           }
           else if(a == 'C')
           {
               sum = sum * 4 + 1;
           }
           else if(a == 'G')
           {
               sum = sum * 4 + 2;
           }
           else
           {
               sum = sum * 4 + 3;
           }
        }

        return sum;
    }


    vector<string> findRepeatedDnaSequences(string &s)
    {
        set<string> hashset;
        set<int> dnas;
        vector<string> v;
        for(int i=0; i+10<=s.size(); i++)
        {
            //这里可以优化,窗口函数
            string item = s.substr(i, 10);
            int dna = this->encode(item);
            if(dnas.count(dna))
            {
                hashset.insert(item);
            }
            else
            {
                dnas.insert(dna);
            }
        }

        set<string>::iterator it = hashset.begin();
        while(it != hashset.end())
        {
            v.push_back(*it);
            it ++;
        }

        return v;
    }

    void run()
    {
        string s = "AAAAAAAAAAA";
        vector<string> v = this->findRepeatedDnaSequences(s);
        for(int i=0; i<v.size(); i++)
        {
            cout<<v[i]<<endl;
        }
    }
};

/*
int main()
{
    RepeatedDnaSequences a;
    a.run();
    return 0;
}
*/
