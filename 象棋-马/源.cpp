//��ĳ�ʼλ�����������̵����½�
//����һ�� x y k ��ʾ������³���
//Ҫ������k����պ��� x y ��
//���ж������߷�
//��������Ϊ(0,0) ����(0,9) ����(8,9)
//������

#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

//����(curx,cury) curk ʱ�ߵ�tx ty�ж����߷�
int _ways(int curx, int cury, int curk, int tx, int ty)
{
	//�Ƿ�ֱֵ�ӷ���0
	if (curx > 8 || curx < 0 || cury > 9 || cury < 0 || curk < 0)
		return 0;

	//����Ϊ0
	if (curk == 0)
		return (curx == tx && cury == ty) ? 1 : 0;

	//�������
	int p1 = _ways(curx + 1, cury + 2, curk - 1, tx, ty);
	p1 += _ways(curx + 2, cury + 1, curk - 1, tx, ty);
	p1 += _ways(curx + 2, cury - 1, curk - 1, tx, ty);
	p1 += _ways(curx + 1, cury - 2, curk - 1, tx, ty);
	p1 += _ways(curx - 1, cury - 2, curk - 1, tx, ty);
	p1 += _ways(curx - 2, cury - 1, curk - 1, tx, ty);
	p1 += _ways(curx - 2, cury + 1, curk - 1, tx, ty);
	p1 += _ways(curx - 1, cury + 2, curk - 1, tx, ty);

	return p1;
}

int ways(int x, int y, int k)
{
	//�Ƿ�ֱֵ�ӷ���0
	if (x > 8 || x < 0 || y>9 || y < 0 || k < 0)
		return 0;
	return _ways(0, 0, k, x, y);
}

//����dp���е�ֵ Խ�緵��0
int tips(int x, int y, int k,const vector<vector<vector<int>>>& dp)
{
	//�Ƿ�ֱֵ�ӷ���0
	if (x > 8 || x < 0 || y > 9 || y < 0 || k < 0)
		return 0;

	return dp[k][x][y];
}

int _ways1(int x, int y, int k)
{
	vector<vector<vector<int>>> dp(k+1, vector<vector<int>>(9, vector<int>(10, 0)));
	
	//����Ϊ0
	dp[0][x][y] = 1;
	
	
	for (int curk = 1;curk <= k;curk++) {
		for (int curx = 0;curx < 9;curx++) {
			for (int cury = 0;cury < 10;cury++) {
				int p = tips(curx + 1, cury + 2, curk - 1, dp);
				p += tips(curx + 2, cury + 1, curk - 1, dp);
				p += tips(curx + 2, cury - 1, curk - 1, dp);
				p += tips(curx + 1, cury - 2, curk - 1, dp);
				p += tips(curx - 1, cury - 2, curk - 1, dp);
				p += tips(curx - 2, cury - 1, curk - 1, dp);
				p += tips(curx - 2, cury + 1, curk - 1, dp);
				p += tips(curx - 1, cury + 2, curk - 1, dp);
				dp[curk][curx][cury] = p;
			}
		}	
	}

	return dp[k][0][0];
}

int ways1(int x, int y, int k)
{
	//�Ƿ�ֱֵ�ӷ���0
	if (x > 8 || x < 0 || y>9 || y < 0 || k < 0)
		return 0;
	return _ways1(x, y, k);
}

int main()
{
	int x, y, k;
	x = 5;
	y = 3;
	k = 10;
	clock_t begin, end;

	begin = clock();
	cout << ways1(x, y, k) << endl;
	end = clock();
	cout << "dp time:" << end - begin << endl;

	begin = clock();
	cout << ways(x, y, k) << endl;
	end = clock();
	cout << "recursion time:" << end - begin << endl;
	return 0;
}