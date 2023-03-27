//�涨1->A 2->B 3->C ......26->Z
//��ôһ�������ַ�������"111"�Ϳ���ת��Ϊ��
//"AAA"��"KA"��"AK"
//����һ��ֻ�����ֵ��ַ���str�������ж�����ת�����
//https://leetcode.cn/problems/decode-ways/
//leetcode 91
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int GetAns1(string s, int index)
{
	//��ǰ������ȷ
	if (index == s.size())
		return 1;
	//��ǰΪ0����û���ܽ���ķ���
	if (s[index] == '0')
		return 0;
	//��ǰ��ֵ��������
	int ans = GetAns1(s, index + 1);
	//��ǰ��ֵ����һ����Ͻ���
	if (index + 1 < s.size() && (s[index] - '0') * 10 + (s[index + 1] - '0') <= 26)
		//ans += index + 2 < s.size() ? GetAns(s, index + 2) : 1;
		ans += GetAns1(s, index + 2);
	return ans;

}

int GetAns2(string s)
{
	vector<int> ans(s.size()+1, 0);
	ans[s.size()] = 1;
	for (int i = s.size() - 1;i >= 0;i--)
	{
		if (s[i] != '0')
		{
			int curans = ans[i+1];
			if (i + 1 < s.size() && (s[i] - '0') * 10 + (s[i + 1] - '0') <= 26)
				curans +=ans[i+2];
			ans[i] = curans;
		}
	}
	return ans[0];
}

int numDecodings(string s)
{
	//return GetAns1(s, 0);
	return GetAns2(s);
}


int main()
{
	string s = "1111";
	cout << numDecodings(s);
	return 0;
}