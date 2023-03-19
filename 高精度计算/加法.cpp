#include <iostream>
#include <vector>
using namespace std;

#define BASE 8

void VecReverse(vector<int>& v)
{
	if (v.size() <= 1)
		return;
	int L = 0, R = v.size() - 1;
	while (L < R)
	{
		int tmp = v[L];
		v[L] = v[R];
		v[R] = tmp;
		L++;R--;
	}
}

vector<int> Add(string& a, string& b)
{
	if (a.size() < b.size())
		a.swap(b);
	//将加数逆置
	vector<int> v1, v2;
	for (int i = a.size() - 1;i >= 0;i--) {
		int tmp = a[i] - '0';
		//当前数不为10进制
		if (tmp >= 10) {
			if(tmp>='a'-'0')
				v1.push_back(a[i] - 'a'+10);
			else
				v1.push_back(a[i] - 'A' + 10);
		}
		else
			v1.push_back(tmp);
	}
	for (int i = b.size() - 1;i >= 0;i--) {
		int tmp = b[i] - '0';
		//当前数不为10进制
		if (tmp >= 10) {
			if (tmp >= 'a'-'0')
				v2.push_back(b[i] - 'a' + 10);
			else
				v2.push_back(b[i] - 'A' + 10);
		}
		else
			v2.push_back(tmp);
	}
	vector<int> ans;
	int tmp = 0;
	for (int i = 0;i < a.size();i++)
	{
		tmp += v1[i];
		if (i < v2.size()) {
			tmp += v2[i];
		}
		ans.push_back(tmp % BASE);
		tmp /= BASE;
	}
	if (tmp != 0)
		ans.push_back(tmp);
	VecReverse(ans);
	return ans;
}

void PrintSum(vector<int>& v)
{
	for (vector<int>::iterator it = v.begin();it < v.end();it++)
	{
		if (*it >= 10)
			cout << (char)(*it - 10 + 'A');
		else
			cout << *it;
	}
		
	cout << endl;
}

int main()
{
	//加数1 加数2
	string num1, num2;
	cin >> num1 >> num2;

	vector<int> ans=Add(num1, num2);
	PrintSum(ans);
	return 0;
}
