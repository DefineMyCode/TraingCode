//leetcode链接：https://leetcode.cn/problems/longest-common-subsequence/?utm_source=LCUS&utm_medium=ip_redirect&utm_campaign=transfer2china
//给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
//一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序
//的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
//例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
//两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:

    //返回str1[0...i]与str2[0...j]范围内的最长公共子序列 
    int longSub(string str1, string str2,int i,int j)
    {
        //都只剩一个字符了
        if (i == 0 && j == 0)
            return str1[i] == str2[j] ? 1 : 0;
        else if (i == 0) {//str1只剩一个字符了
            if (str1[i] == str2[j])
                return 1;
            else
                return longSub(str1, str2, i, j - 1);
        }
        else if (j == 0) {//str2只剩一个字符了
            if (str1[i] == str2[j])
                return 1;
            else
                return longSub(str1, str2, i - 1, j);
        }
        else {//i!=0&&j!=0
            //考虑 str1[0 i] 与 str2[0 j-1]有最长公共子序列 
            int p1 = longSub(str1, str2, i, j - 1);

            //考虑 str1[0 i-1] 与 str2[0 j]有最长公共子序列 
            int p2 = longSub(str1, str2, i - 1, j);

            //考虑 str1[0 i] 与 str2[0 j]有最长公共子序列 但当前i j必须相等
            int p3 = str1[i] == str2[j] ? (1 + longSub(str1, str2, i - 1, j - 1)) : 0;

            return max(p1, max(p2, p3));
        }
    }

    int longSub2(string str1, string str2)
    {
        int M = str1.size();
        int N = str2.size();
        vector<vector<int>> dp(M, vector<int>(N, 0));
        //都只剩一个字符了
        dp[0][0] = str1[0] == str2[0] ? 1 : 0;
        //str1只剩一个字符了
        for (int j = 1;j < N;j++) {
            if (str1[0] == str2[j]) {
                dp[0][j] = 1;
            }
            else {
                dp[0][j] = dp[0][j - 1];
            }
        }
        //str2只剩一个字符了
        for (int i = 1;i < M;i++) {
            if (str2[0] == str1[i]) {
                dp[i][0] = 1;
            }
            else {
                dp[i][0] = dp[i-1][0];
            }
        }
        //i!=0&&j!=0
        for (int i = 1;i < M;i++) {
            for (int j = 1;j < N;j++) {
                int p1 = dp[i][j - 1];
                int p2 = dp[i - 1][j];
                int p3 = str1[i] == str2[j] ? (1 + dp[i - 1][j - 1]) : 0;
                dp[i][j]=max(p1,max(p2,p3));
            }
        }
        return dp[M - 1][N - 1];
    }

    int longestCommonSubsequence(string text1, string text2) {
        if (text1.size() == 0 && text2.size() == 0)
            return 0;

        //return longSub(text1, text2, text1.size() - 1, text2.size() - 1);
        return longSub2(text1, text2);
    }
};

int main()
{
    string str1 = { "1b2b3b4b5b6b7b8b9b0" }, str2 = { "a1a2a3a4a5a6a7a8a9a0a1a2a3aaaaaaa" };
    Solution getans;
    cout << getans.longestCommonSubsequence(str1,str2) << endl;
    return 0;
}
