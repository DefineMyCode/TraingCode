#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//�����ݹ�
//    ����ʣ������ ��ǰ��Ʒ     ��Ʒ��ֵ        ��Ʒ���       
int maxval(int capty, int cur, vector<int>& v, vector<int>& w)
{
	//����Ϊ���� �� ��Ʒ������ ��ǰ���Բ�����
	if (capty < 0)
		return -1;
	//�Ѿ�û�п����õ���Ʒ��
	if (cur == v.size())
		return 0;
	//���õ�ǰ��Ʒ ��һ����Ʒʱ�����ڵļ�ֵ
	int p1 = maxval(capty, cur + 1, v, w);
	//�õ�ǰ��Ʒ ���Ķ�Ӧ���� ��һ����Ʒʱ�����ڵļ�ֵ
	int p2 = maxval(capty - w[cur], cur + 1, v, w);
	if (p2 != -1) {//�õ�ǰ��Ʒ�����ǲ������
		return max(p1, p2+v[cur]);
	}
	else return p1;
}

//����
int dp1(int capty, int cur, vector<int>& v, vector<int>& w,vector<vector<int>>& dp)
{
	if (dp[capty][cur] != -1)
		return dp[capty][cur];
	int maxval = 0;
	//�Ѿ�û�п����õ���Ʒ��
	if (cur == v.size())
		maxval = 0;
	else
	{
		//���õ�ǰ��Ʒ ��һ����Ʒʱ�����ڵļ�ֵ
		int p1 = dp1(capty, cur + 1, v, w, dp);
		//�õ�ǰ��Ʒ ���Ķ�Ӧ���� ��һ����Ʒʱ�����ڵļ�ֵ
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
	//������Ʒ
	for (int cur = k - 1;cur > 0;cur--)
	{
		//��������
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
	cout << "����ֵΪ��" << maxval(n, 1, v, w) << endl;;
	vector<vector<int>> dp(n + 1, vector<int>(v.size() + 1, -1));
	cout << "����ֵΪ��" << dp1(n, 1, v, w, dp) << endl;
	cout << "����ֵΪ��" << dp2(n, v.size(), v, w) << endl;

}
int main()
{
	//����һ������Ϊn�ı����Լ�k����Ʒ
	//ÿ����Ʒ�ж�Ӧ�ļ�ֵ�Լ����
	//�ʱ�����װ����Ʒ����ֵ���Ƕ���
	int n, k;
	//cin >> n >> k;
	n = 11;
	//ÿ����Ʒ�ļ�ֵ ��һ��ΪԤ��λ
	vector<int> v{0,2,3,1,1,5,1};
	//ÿ����Ʒ�����
	vector<int> w{0,3,2,3,4,5,1};
	PrintAns(n, v, w);


	return 0;
}