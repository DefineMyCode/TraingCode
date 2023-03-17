#include <iostream>
#include <vector>
using namespace std;

int max_profit(int N, int M, vector<int>& a, vector<vector<int>>& v, vector<vector<int>>& w) {
    vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            dp[i][j] = dp[i - 1][j];
            for (int k = 1; k <= a[i - 1]; k++) {
				if (j >= w[i - 1][k - 1]) {
					dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i - 1][k - 1]] + v[i - 1][k - 1]);
					//dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i][k]] + v[i][k]);
				}               
            }
        }
    }
    return dp[N][M];
}

int main()
{
	int t;cin >> t;
	while (t--)
	{
		//Nģʽ��Mÿ������
		int N, M;
		cin >> N >> M;
		vector<int> a(N);//ÿ��ģʽ�ж��ٸ�����
		vector<vector<int>> v(N);//����
		vector<vector<int>> w(N);//����
		//N��ģʽ
		for (int i = 0;i < N;i++)
		{
			int ai;
			cin >> ai;//ai������
			a[i] = ai;
			//ai������
			for (int k = 0;k < ai;k++)
			{
				int vj;
				cin >> vj;
				v[i].push_back(vj);
			}
			//ai������ֵ
			for (int k = 0;k < ai;k++)
			{
				int wj;
				cin >> wj;
				w[i].push_back(wj);
			}
		}
		int max_profit_val = max_profit(N, M, a, v, w);
		cout << "The maximum profit is: " << max_profit_val << endl;
	}
	return 0;
}
