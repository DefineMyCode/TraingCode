//����һ����������arr,������ֵ��ͬ��ֽ���ų�һ����
//���A�����B��������ÿ��ֽ��
//�涨���A���ã����B����
//����ÿ�����ÿ��ֻ���������һ������ֽ��
//���A�����B����������
//�뷵������ʤ�ߵķ���

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//��ǰ��������
int f(vector<int>& arr, int L, int R);

//��������
int g(vector<int>& arr, int L, int R);

void PrintAns(vector<int>& arr)
{
	if (arr.size() == 0)
	{
		cout << "A B�÷ֶ�Ϊ0" << endl;
		return;
	}
		
	int L = 0, R = arr.size() - 1;
	int first = f(arr, L, R);
	int seconed = g(arr, L, R);
	if (first > seconed)
		cout << "��ʤ��ΪA:" << first << endl;
	else
		cout<< "��ʤ��ΪB:" << seconed << endl;
}

//��������
int g1(vector<int>& arr, int L, int R,vector<vector<int>>& fmap, vector<vector<int>>& gmap)
{
	if (gmap[L][R] != -1)
		return gmap[L][R];
	//ֻʣһ������ ���Ǻ�������û������
	int ans = 0;
	if (L == R)
		ans = 0;

	//����������ߵ���
	int p1 = f(arr, L + 1, R);
	//���������ұߵ���
	int p2 = f(arr, L, R - 1);
	ans = min(p1, p2);
	//�������Ǻ��� �Ƕ���һ����������������
	gmap[L][R] = ans;
	return ans;
}

//���ֻ�õ���÷�������
int f1(vector<int>& arr, int L, int R, vector<vector<int>>& fmap, vector<vector<int>>& gmap)
{
	if (fmap[L][R] != -1)
		return fmap[L][R];
	int ans = 0;
	//ֻʣһ������
	if (L == R)
		ans = arr[L];
	//�������������Ȼ����ֻ���Ȼ����ֵ����ֵ
	int p1 = arr[L] + g1(arr, L + 1, R,fmap,gmap);
	int p2 = arr[R] + g1(arr, L, R - 1,fmap,gmap);
	ans = max(p1, p2);
	fmap[L][R] = ans;
	return ans;
}

//�ӻ���
void PrintAns2(vector<int>& arr)
{
	if (arr.size() == 0)
	{
		cout << "A B�÷ֶ�Ϊ0" << endl;
		return;
	}
	vector<vector<int>> fmap(arr.size(), vector<int>(arr.size(),-1));
	vector<vector<int>> gmap(arr.size(), vector<int>(arr.size(),-1));
	int L = 0, R = arr.size() - 1;
	int first = f1(arr, L, R,fmap,gmap);
	int seconed = g1(arr, L, R,fmap,gmap);
	if (first > seconed)
		cout << "��ʤ��ΪA:" << first << endl;
	else
		cout << "��ʤ��ΪB:" << seconed << endl;
}

//dp
void PrintAns3(vector<int>& arr)
{
	if (arr.size() == 0)
	{
		cout << "A B�÷ֶ�Ϊ0" << endl;
		return;
	}
	vector<vector<int>> fmap(arr.size(), vector<int>(arr.size(), 0));
	vector<vector<int>> gmap(arr.size(), vector<int>(arr.size(), 0));
	int L = 0, R = arr.size() - 1;
	//���öԽ�Ϊ���Ƶ����
	for (int i = L;i <= R;i++){
		fmap[i][i] = arr[i];
	}

	//��fmap ��gmap
	for (int i = 1;i <=R;i++) {
		int row = i, col = 0;
		while (col <= R-i) {
			fmap[row][col] = max(arr[row] + gmap[row - 1][col], arr[col] + gmap[row][col + 1]);
			row++;col++;
		}
		row = i, col = 0;
		while (col <= R - i) {
			gmap[row][col] = min(fmap[row - 1][col],fmap[row][col + 1]);
			row++;col++;
		}
	}
	int first = fmap[R][L];
	int seconed = gmap[R][L];
	if (first > seconed)
		cout << "��ʤ��ΪA:" << first << endl;
	else
		cout << "��ʤ��ΪB:" << seconed << endl;
}
int main()
{
	//vector<int> arr{5,7,4,5,8,1,6,0,3,4,6,1,7};
	//vector<int> arr = { 50,100,20,10 };
	vector<int> arr = { 20,100,10 };
	PrintAns(arr);
	PrintAns2(arr);
	PrintAns3(arr);
	return 0;
}

//��������
int g(vector<int>& arr, int L, int R)
{
	//ֻʣһ������ ���Ǻ�������û������
	if (L == R)
		return 0;
	
	//����������ߵ���
	int p1 = f(arr, L + 1, R);
	//���������ұߵ���
	int p2 = f(arr, L, R - 1);

	//�������Ǻ��� �Ƕ���һ����������������
	return min(p1,p2);
}

//���ֻ�õ���÷�������
int f(vector<int>& arr, int L, int R)
{
	//ֻʣһ������
	if (L == R)
		return arr[L];
	//�������������Ȼ����ֻ���Ȼ����ֵ����ֵ
	int p1 = arr[L] + g(arr, L + 1, R);
	int p2 = arr[R] + g(arr, L, R - 1);
	return max(p1,p2);
}