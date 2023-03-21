//��һ�������� ��һ������ΪN��·�� 
//�󵱻������ƶ�K����պ���aimλ�õķ�����
//���������м�ʱ���������ƶ�
//����������1��λ��ʱ��һ��ֻ���ƶ���2
//����������Nʱ��һ��ֻ���ƶ���N-1
#include <iostream>
#include <vector>
using namespace std;

//���ƶ�����    ��ǰλ��    ·������   Ŀ��λ��
int GetAns1(int k, int cur,int n, int aim)
{
	//û�п��ƶ��Ĵ����� ��Ŀ��λ������һ��
	if (k == 0)
		return cur == aim ? 1 : 0;
	//��1λ�ô�
	if (cur == 1) {
		return GetAns1(k - 1, 2, n, aim);
	}
	//��nλ��
	if (cur == n) {
		return GetAns1(k - 1, n - 1, n, aim);
	}
	//���м� ��������ҷ����ĺ�
	return GetAns1(k - 1, cur - 1, n, aim) + GetAns1(k - 1, cur + 1, n, aim);
}

//�ݹ�
int passway1(int k, int cur, int n,int aim,vector<vector<int>>& dp)
{
	//����������ֱ�ӷ��ش�
	if (dp[cur][k] != -1)
		return dp[cur][k];
	//��ǰ��δ��������
	int ans=0;
	if (k == 0) {
		ans= cur == aim ? 1 : 0;
	}
	else if (cur == 1) {
		ans = passway1(k - 1, 2, n, aim, dp);
	}
	else if (cur == n) {
		ans = passway1(k - 1, n - 1, n, aim, dp);
	}
	else {
		ans = passway1(k - 1, cur - 1, n, aim, dp) + passway1(k - 1, cur + 1, n, aim, dp);
	}
	dp[cur][k] = ans;
	return ans;
}

int GetAns2(int k, int start, int n, int aim)
{
	//����Ϊ�� ·���ĳ���Ϊ��
	vector<vector<int>> dp(n + 1, vector<int>(k + 1,-1));	
	return passway1(k,start,n,aim,dp);
}

//ѭ������
int GetAns3(int k, int start, int n, int aim)
{
	//��ǰλ��Ϊi�ƶ�����Ϊjʱ�Ĵ�
	//dp[i][j]
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
	//��һ��->����Ϊ0 ֻ��aimλ����1
	dp[aim][0] = 1;
	//�������ƶ��Ĳ���
	for (int i = 1;i <= k;i++)
	{	
		dp[1][i] = dp[2][i - 1];
		//����λ��
		for (int j = 2;j < n;j++)
		{
			dp[j][i] = dp[j - 1][i - 1] + dp[j + 1][i - 1];
		}
		dp[n][i] = dp[n - 1][i - 1];
	}
	//for (int i = 0;i <= n;i++)
	//{
	//	for (int j = 0;j <= k;j++)
	//		cout << dp[i][j] << ' ';
	//	cout << endl;
	//}
	return dp[start][k];
}

int main()
{
	//K��   Ŀ��λ�� ��ʼλ��
	int N, K, aim, start;
	cin >> N >> K >> start >> aim;

	cout << "ans:" << GetAns1(K, start, N, aim) << endl;
	cout << "ans:" << GetAns2(K, start, N, aim) << endl;
	cout <<"ans:" << GetAns3(K, start, N, aim) << endl;
	return 0;
}