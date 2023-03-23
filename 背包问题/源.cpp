#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//暴力递归
//    背包剩余容量 当前物品     物品价值        物品体积       
int maxval(int capty, int cur, vector<int>& v, vector<int>& w)
{
	//容量为负数 或 物品不存在 当前策略不合理
	if (capty < 0)
		return -1;
	//已经没有可以拿的物品了
	if (cur == v.size())
		return 0;
	//不拿当前物品 下一个物品时背包内的价值
	int p1 = maxval(capty, cur + 1, v, w);
	//拿当前物品 消耗对应容量 下一个物品时背包内的价值
	int p2 = maxval(capty - w[cur], cur + 1, v, w);
	if (p2 != -1) {//拿当前物品可能是不合理的
		return max(p1, p2+v[cur]);
	}
	else return p1;
}

//缓存
int dp1(int capty, int cur, vector<int>& v, vector<int>& w,vector<vector<int>>& dp)
{
	if (dp[capty][cur] != -1)
		return dp[capty][cur];
	int maxval = 0;
	//已经没有可以拿的物品了
	if (cur == v.size())
		maxval = 0;
	else
	{
		//不拿当前物品 下一个物品时背包内的价值
		int p1 = dp1(capty, cur + 1, v, w, dp);
		//拿当前物品 消耗对应容量 下一个物品时背包内的价值
		if (capty - w[cur] >= 0) {
			int p2 = dp1(capty - w[cur], cur + 1, v, w, dp)+v[cur];
			maxval = max(p1, p2);
		}
		else maxval = p1;
	}
	dp[capty][cur] = maxval;
	return maxval;
}

//dp
int dp2(int n, int k,vector<int>& v, vector<int>& w)
{
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
	//遍历物品
	for (int cur = k - 1;cur > 0;cur--)
	{
		//遍历容量
		for (int capty = 1;capty <= n;capty++)
		{
			int p1 = dp[capty][cur + 1];
			if (capty - w[cur] >= 0) {
				int p2 = dp[capty - w[cur]][cur + 1] + v[cur];
				dp[capty][cur] = max(p1, p2);
			}
			else dp[capty][cur] = p1;
		}

	}
	return dp[n][1];
}


void PrintAns(int n, vector<int>& v, vector<int>& w)
{
	cout << "最大价值为：" << maxval(n, 1, v, w) << endl;;
	vector<vector<int>> dp(n + 1, vector<int>(v.size() + 1, -1));
	cout << "最大价值为：" << dp1(n, 1, v, w, dp) << endl;
	cout << "最大价值为：" << dp2(n, v.size(), v, w) << endl;

}
int main()
{
	//给你一个容量为n的背包以及k个物品
	//每个物品有对应的价值以及体积
	//问背包能装的物品最大价值数是多少
	int n, k;
	//cin >> n >> k;
	n = 11;
	//每件物品的价值 第一个为预留位
	vector<int> v{0,2,3,1,1,5,1};
	//每件物品的体积
	vector<int> w{0,3,2,3,4,5,1};
	PrintAns(n, v, w);


	return 0;
}