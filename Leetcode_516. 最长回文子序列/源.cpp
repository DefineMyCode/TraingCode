//leetcode:https://leetcode.cn/problems/longest-palindromic-subsequence/
//����һ���ַ��� s ���ҳ�������Ļ��������У������ظ����еĳ��ȡ�
//�����ж���Ϊ�����ı�ʣ���ַ�˳�������£�
//ɾ��ĳЩ�ַ����߲�ɾ���κ��ַ��γɵ�һ�����С�

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    //���s[L...R]��Χ�ڵ������������
    int _longP(string s, int L, int R)
    {
        //һ���ַ� ����һ����1
        if (L == R)
            return 1;
        //�����ַ� ���Ϊ2����Ϊ1
        if (L == R - 1)
            return s[L] == s[R] ? 2 : 1;
        //���������ַ�
        //������������[L+1...R-1]��Χ��
        int p1 = _longP(s, L + 1, R - 1);
        //������������[L...R-1]��Χ��
        int p2 = _longP(s, L, R - 1);
        //������������[L+1...R]��Χ��
        int p3 = _longP(s, L+1, R);
        //������������[L...R]��Χ�� ���ǵ�s[L]==s[R]
        int p4 = s[L] != s[R] ? 0 : 2 + _longP(s, L + 1, R - 1);
        return max(max(p1, p2), max(p3, p4));
    }

    int _longP2(string s)
    {
        int N = s.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));

        //һ���ַ� ����һ����1
        dp[N - 1][N - 1] = 1;//���⴦��[N-1][N-1]
        
        //�����Խ���ͬʱ��(L==R L==R-1) ��������Ĳ��� ��ǰ����Խ��
        for (int i = 0;i <= N - 2;i++){
            dp[i][i] = 1;
            dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
        }
        
        //���������ַ�
        for (int L = N - 3;L >= 0;L--) {
            for (int R = L + 2;R < N;R++) {
                //p1�����ܱ�p2 p3 p4 �����Կ���ֱ��ȥ��
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