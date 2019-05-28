/**
* @projectName   lintcode-cpp

* @author        yanpf
* @date          2019-05-13
* @brief         最长回文子串
* @description   给出一个字符串（假设长度最长为1000），求出它的最长回文子串，你可以假定只有一个满足条件的最长回文串
* @example
*                样例 1:
*
*                输入:"abcdzdcab"
*                输出:"cdzdc"
*                样例 2:
*
*                输入:"aba"
*                输出:"aba"
*
* @solution
*/

#include "commonutils.h"


class LongestPalindromicSubstring : public CommonUtils
{
public:
    //从中心点向外扩散
    string longestPalindrome(string &s)
    {
        int max = 0;
        string result = "";
        for(int i=0; i<s.length(); i++)
        {
            int j=0;
            //奇数
            while(i + j < s.length() && i-j >= 0)
            {
                if(s[i-j] == s[i+j])
                {
                    j ++;
                }
                else
                {
                    break;
                }
            }

            if(max < j * 2 - 1)
            {
                max = j * 2 - 1;
                result = s.substr(i-j + 1, j*2 - 1);
            }

            //偶数
            j = 0;
            if(s[i] == s[i+1])
            {
                while(i - j >= 0 && i+j + 1 < s.length())
                {
                    if(s[i-j] == s[i+j + 1])
                    {
                        j ++;
                    }
                    else
                    {
                        break;
                    }
                }

                if(max < j* 2)
                {
                    max = j * 2;
                    result = s.substr(i-j + 1, j* 2);
                }
            }
        }

        return result;
    }

    int findLongestPalindromeFrom(string &s, int left, int right)
    {
        while(left >= 0 && right < s.length())
        {
            if(s[left] != s[right])
            {
                break;
            }

            left --;
            right ++;
        }

        return right - left - 1;
    }

    //思路和第一个一样只是把获取长度那个方法抽取出来了
    string longestPalindrome2(string &s)
    {
        int longest = 0;
        int start = -1;
        for(int i=0; i<s.length(); i++)
        {
            int len = this->findLongestPalindromeFrom(s, i, i);
            if(longest < len)
            {
                longest = len;
                start = i - len / 2;
            }

            len = this->findLongestPalindromeFrom(s, i, i+1);
            if(longest < len)
            {
                longest = len;
                start = i - len / 2 + 1;
            }
        }

        return s.substr(start, longest);
    }

    //dp解法 dp[i][j] 表示i-j是否是回文串
    string longestPalindromeDp(string &s)
    {
        int longest = 1;
        int start = 0;
        int dp[s.length()][s.length()] = {0};
        for(int i=s.length() - 2; i>=0; i--)
        {
            dp[i][i] = 1;
            if(s[i] == s[i+1])
            {
                longest = 2;
                start = i;
                dp[i][i+1] = 1;
            }
        }
        dp[s.length() - 1][s.length() - 1] = 1;

        for(int i=s.length() - 1; i>=0; i--)
        {
            for(int j=i+2; j<s.length(); j++)
            {
                dp[i][j] = dp[i+1][j-1] && s[i] == s[j];
                if(dp[i][j] && (j-i+1) > longest)
                {
                    start = i;
                    longest = j - i + 1;
                }
            }
        }

        return s.substr(start, longest);
    }

    int start = 0;
    int length = 0;
    void manacher(string &s)
    {
        int len[s.length()];
        int p0 = -1;
        int far = -1;
        for(int i=0; i<s.length(); i++)
        {
            if(i >= far)
            {
                while(far + 1 < s.length() && i * 2 - far - 1 >= 0)
                {
                    if(s[far + 1] == s[i * 2 - far - 1])
                    {
                        far ++;
                    }
                    else
                    {
                        break;
                    }
                }
                len[i] = far - i + 1;
                p0 = i;
            }
            else
            {
                len[i] = min(len[p0 * 2 - i], far - i + 1);
            }

            if(len[i] > length)
            {
                length = len[i];
                start = i;
            }
        }

        cout<<s<<endl;
        for(int i=0; i<s.length(); i++)
        {
            cout<<len[i]<<'\t';
        }
        cout<<endl;
    }


    string longestPalindromeManacher(string &s)
    {
        string s2 = "";
        for(int i=0; i<s.length() * 2 + 1; i++)
        {
            if(i % 2 == 0)
            {
                s2 = s2 + "#";
            }
            else
            {
                s2 = s2 + s[i/2];
            }
        }
        this->manacher(s2);
        return s.substr((start - length) / 2 + 1, length - 1);
    }




    void run()
    {
        string s = "abcdzzdcab";
        cout<<this->longestPalindromeManacher(s)<<endl;
    }
};

