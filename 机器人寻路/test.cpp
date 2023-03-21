//有一个机器人 和一个长度为N的路径 
//求当机器人移动K步后刚好在aim位置的方法数
//机器人在中间时可以左右移动
//当机器人在1的位置时下一次只能移动到2
//当机器人在N时下一步只能移动到N-1
#include <iostream>
#include <vector>
using namespace std;

//可移动次数    当前位置    路径长度   目标位置
int GetAns1(int k, int cur,int n, int aim)
{
	//没有可移动的次数了 在目标位置则算一次
	if (k == 0)
		return cur == aim ? 1 : 0;
	//在1位置处
	if (cur == 1) {
		return GetAns1(k - 1, 2, n, aim);
	}
	//在n位置
	if (cur == n) {
		return GetAns1(k - 1, n - 1, n, aim);
	}
	//在中间 往左和往右方法的和
	return GetAns1(k - 1, cur - 1, n, aim) + GetAns1(k - 1, cur + 1, n, aim);
}

//递归
int passway1(int k, int cur, int n,int aim,vector<vector<int>>& dp)
{
	//求解过该问题直接返回答案
	if (dp[cur][k] != -1)
		return dp[cur][k];
	//当前还未求解该问题
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
	//步数为行 路径的长度为列
	vector<vector<int>> dp(n + 1, vector<int>(k + 1,-1));	
	return passway1(k,start,n,aim,dp);
}

//循环遍历
int GetAns3(int k, int start, int n, int aim)
{
	//当前位置为i移动步数为j时的答案
	//dp[i][j]
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
	//第一列->步数为0 只有aim位置是1
	dp[aim][0] = 1;
	//遍历可移动的步数
	for (int i = 1;i <= k;i++)
	{	
		dp[1][i] = dp[2][i - 1];
		//遍历位置
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
	//K步   目标位置 初始位置
	int N, K, aim, start;
	cin >> N >> K >> start >> aim;

	cout << "ans:" << GetAns1(K, start, N, aim) << endl;
	cout << "ans:" << GetAns2(K, start, N, aim) << endl;
	cout <<"ans:" << GetAns3(K, start, N, aim) << endl;
	return 0;
}