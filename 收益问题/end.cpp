#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//�ռ临�Ӷ�O(M*N)
void PrintAns1(int M, int N, vector<int>& a, vector<vector<int>>& v, vector<vector<int>>& w)
{
	//ģʽi����jʱ����Ѳ���
	//dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i-1][k-1]]+v[i-1][k-1])
	//M+1��ģʽN+1������
	vector<vector<int>> dp(M+1,vector<int>(N+1,0));
	//����ģʽ
	for (int i = 1;i <= M;i++)
	{
		//��������
		for (int j = 1;j <= N;j++)
		{
			//Ĭ�ϲ����� ��ǰ���Ž�Ϊ��һ��ģʽ��Ӧ�����µ����Ų���
			dp[i][j] = dp[i - 1][j];
			//����iģʽ�µĲ���
			for (int k = 1;k <= a[i - 1];k++)
			{
				//�����������ڵ�ǰģʽ��k������Ҫ������
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

//�ռ临�Ӷ�O(N)
void PrintAns2(int M, int N, vector<int>& a, vector<vector<int>>& v, vector<vector<int>>& w)
{
	//��ǰģʽi����jʱ����Ѳ���
	//dp[j]=max(dp[j],dp[j-w[i-1][k-1]]+v[i-1][k-1])
	//�ϸ�ģʽN+1�������µ����Ž�
	vector<int> dp(N + 1, 0);
	//����ģʽ
	for (int i = 1;i <= M;i++)
	{
		//��������
		for (int j = N;j >= 0;j--)
		{
			//����iģʽ�µĲ���
			for (int k = 1;k <= a[i - 1];k++)
			{
				//�����������ڵ�ǰģʽ��k������Ҫ������
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
	int t;//������������
	cin >> t;
	while (t--) {
		int M, N;//Mģʽ��Nÿ������
		cin >> M >> N;
		vector<int> a;//ÿ��ģʽ�ж��ٸ�����
		vector<vector<int>> v(M);//��Ӧģʽ�в����ļ�ֵ
		vector<vector<int>> w(M);//��Ӧģʽ�в�������������
		//¼��ģʽ�Ͷ�Ӧ����
		for (int i = 0;i < M;i++)
		{
			//ÿ��ģʽ�¶�Ӧ�����ļ�ֵ
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
		//���
		PrintAns2(M, N, a, v, w);
	}
	return 0;
}