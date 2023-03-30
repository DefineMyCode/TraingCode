//leetcode���ӣ�https://leetcode.cn/problems/longest-common-subsequence/?utm_source=LCUS&utm_medium=ip_redirect&utm_campaign=transfer2china
//���������ַ��� text1 �� text2�������������ַ������ ���������� �ĳ��ȡ���������� ���������� ������ 0 ��
//һ���ַ����� ������ ��ָ����һ���µ��ַ�����������ԭ�ַ����ڲ��ı��ַ������˳��
//�������ɾ��ĳЩ�ַ���Ҳ���Բ�ɾ���κ��ַ�������ɵ����ַ�����
//���磬"ace" �� "abcde" �������У��� "aec" ���� "abcde" �������С�
//�����ַ����� ���������� ���������ַ�������ͬӵ�е������С�
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:

    //����str1[0...i]��str2[0...j]��Χ�ڵ������������ 
    int longSub(string str1, string str2,int i,int j)
    {
        //��ֻʣһ���ַ���
        if (i == 0 && j == 0)
            return str1[i] == str2[j] ? 1 : 0;
        else if (i == 0) {//str1ֻʣһ���ַ���
            if (str1[i] == str2[j])
                return 1;
            else
                return longSub(str1, str2, i, j - 1);
        }
        else if (j == 0) {//str2ֻʣһ���ַ���
            if (str1[i] == str2[j])
                return 1;
            else
                return longSub(str1, str2, i - 1, j);
        }
        else {//i!=0&&j!=0
            //���� str1[0 i] �� str2[0 j-1]������������� 
            int p1 = longSub(str1, str2, i, j - 1);

            //���� str1[0 i-1] �� str2[0 j]������������� 
            int p2 = longSub(str1, str2, i - 1, j);

            //���� str1[0 i] �� str2[0 j]������������� ����ǰi j�������
            int p3 = str1[i] == str2[j] ? (1 + longSub(str1, str2, i - 1, j - 1)) : 0;

            return max(p1, max(p2, p3));
        }
    }

    int longSub2(string str1, string str2)
    {
        int M = str1.size();
        int N = str2.size();
        vector<vector<int>> dp(M, vector<int>(N, 0));
        //��ֻʣһ���ַ���
        dp[0][0] = str1[0] == str2[0] ? 1 : 0;
        //str1ֻʣһ���ַ���
        for (int j = 1;j < N;j++) {
            if (str1[0] == str2[j]) {
                dp[0][j] = 1;
            }
            else {
                dp[0][j] = dp[0][j - 1];
            }
        }
        //str2ֻʣһ���ַ���
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
