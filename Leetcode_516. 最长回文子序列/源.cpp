//leetcode:https://leetcode.cn/problems/longest-palindromic-subsequence/
//给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
//子序列定义为：不改变剩余字符顺序的情况下，
//删除某些字符或者不删除任何字符形成的一个序列。

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    //求出s[L...R]范围内的最长回文子序列
    int _longP(string s, int L, int R)
    {
        //一个字符 回文一定是1
        if (L == R)
            return 1;
        //两个字符 相等为2不等为1
        if (L == R - 1)
            return s[L] == s[R] ? 2 : 1;
        //大于两个字符
        //回文子序列在[L+1...R-1]范围上
        int p1 = _longP(s, L + 1, R - 1);
        //回文子序列在[L...R-1]范围上
        int p2 = _longP(s, L, R - 1);
        //回文子序列在[L+1...R]范围上
        int p3 = _longP(s, L+1, R);
        //回文子序列在[L...R]范围上 但是得s[L]==s[R]
        int p4 = s[L] != s[R] ? 0 : 2 + _longP(s, L + 1, R - 1);
        return max(max(p1, p2), max(p3, p4));
    }

    int _longP2(string s)
    {
        int N = s.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));

        //一个字符 回文一定是1
        dp[N - 1][N - 1] = 1;//额外处理[N-1][N-1]
        
        //两个对角线同时填(L==R L==R-1) 由于上面的操作 当前不会越界
        for (int i = 0;i <= N - 2;i++){
            dp[i][i] = 1;
            dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
        }
        
        //大于两个字符
        for (int L = N - 3;L >= 0;L--) {
            for (int R = L + 2;R < N;R++) {
                //p1不可能比p2 p3 p4 大所以可以直接去掉
                //int p1 = dp[L + 1][R - 1];
                int p2 = dp[L][ R - 1];
                int p3 = dp[L + 1][R];

                //int p4 = s[L] != s[R] ? 0 : 2 + _longP(s, L + 1, R - 1);
                dp[L][R]= max(p2, p3);
                if (s[L] == s[R]) {
                    dp[L][R] = max(dp[L][R], 2 + dp[L + 1][R - 1]);
                }            
            }
         }
        
        return dp[0][N - 1];
    }

    int longestPalindromeSubseq(string s) {
        if (s.size() == 0)
            return 0;
        //return _longP(s, 0, s.size() - 1);
        return _longP2(s);
    }
};

int main()
{
    Solution ans;
    //string s = { "aa" };
    string s = { "bbbab" };
    cout << ans.longestPalindromeSubseq(s) << endl;
	return 0;
}