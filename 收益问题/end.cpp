#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//空间复杂度O(M*N)
void PrintAns1(int M, int N, vector<int>& a, vector<vector<int>>& v, vector<vector<int>>& w)
{
	//模式i体力j时的最佳操作
	//dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i-1][k-1]]+v[i-1][k-1])
	//M+1个模式N+1个体力
	vector<vector<int>> dp(M+1,vector<int>(N+1,0));
	//遍历模式
	for (int i = 1;i <= M;i++)
	{
		//遍历体力
		for (int j = 1;j <= N;j++)
		{
			//默认不操作 当前最优解为上一个模式对应体力下的最优操作
			dp[i][j] = dp[i - 1][j];
			//遍历i模式下的操作
			for (int k = 1;k <= a[i - 1];k++)
			{
				//现有体力大于当前模式下k操作需要的体力
				if (j >= w[i - 1][k - 1]) {
					dp[i][j] = max(dp[i][j], dp[i-1][j - w[i - 1][k - 1]] + v[i - 1][k - 1]);
				}
			}
		}
	}

	//for (int i = 0;i <= M;i++)
	//{
	//	for (int j = 0;j <= N;j++) {
	//		cout << dp[i][j] << ' ';
	//	}
	//	cout << endl;
	//}
	cout << "the ans is:" << dp[M][N];
}

//空间复杂度O(N)
void PrintAns2(int M, int N, vector<int>& a, vector<vector<int>>& v, vector<vector<int>>& w)
{
	//当前模式i体力j时的最佳操作
	//dp[j]=max(dp[j],dp[j-w[i-1][k-1]]+v[i-1][k-1])
	//上个模式N+1个体力下的最优解
	vector<int> dp(N + 1, 0);
	//遍历模式
	for (int i = 1;i <= M;i++)
	{
		//遍历体力
		for (int j = N;j >= 0;j--)
		{
			//遍历i模式下的操作
			for (int k = 1;k <= a[i - 1];k++)
			{
				//现有体力大于当前模式下k操作需要的体力
				if (j >= w[i - 1][k - 1]) {
					dp[j] = max(dp[j], dp[j - w[i - 1][k - 1]] + v[i - 1][k - 1]);
				}
			}
		}
	}
	cout <<"the ans is:" << dp[N];
}

int main()
{
	int t;//测试用例数量
	cin >> t;
	while (t--) {
		int M, N;//M模式，N每日体力
		cin >> M >> N;
		vector<int> a;//每个模式有多少个操作
		vector<vector<int>> v(M);//对应模式中操作的价值
		vector<vector<int>> w(M);//对应模式中操作的体力消耗
		//录入模式和对应操作
		for (int i = 0;i < M;i++)
		{
			//每个模式下对应操作的价值
			int ai;cin >> ai;
			a.push_back(ai);
			for (int vi = 0;vi < ai;vi++) {
				int curv;cin >> curv;
				v[i].push_back(curv);
			}
			for (int wi = 0;wi < ai;wi++) {
				int curw;cin >> curw;
				w[i].push_back(curw);
			}
		}
		//求解
		PrintAns2(M, N, a, v, w);
	}
	return 0;
}