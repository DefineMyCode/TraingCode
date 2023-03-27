//规定1->A 2->B 3->C ......26->Z
//那么一个数字字符串比如"111"就可以转换为：
//"AAA"、"KA"、"AK"
//给定一个只有数字的字符串str，返回有多少种转换结果
//https://leetcode.cn/problems/decode-ways/
//leetcode 91
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int GetAns1(string s, int index)
{
	//当前方法正确
	if (index == s.size())
		return 1;
	//当前为0往后没有能解码的方法
	if (s[index] == '0')
		return 0;
	//当前数值单独解码
	int ans = GetAns1(s, index + 1);
	//当前数值与下一个组合解码
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