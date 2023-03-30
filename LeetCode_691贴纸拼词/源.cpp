//https://leetcode.cn/problems/stickers-to-spell-word/
//������ n �ֲ�ͬ����ֽ��ÿ����ֽ�϶���һ��Сд��Ӣ�ĵ��ʡ�
//����Ҫƴд���������ַ��� target �������Ǵ��ռ�����ֽ����
//�����ĸ�������������ǡ������Ը�⣬����Զ��ʹ��ÿ��
//��ֽ��ÿ����ֽ�����������޵ġ�
//��������Ҫƴ�� target ����С��ֽ������������񲻿��ܣ��򷵻� - 1 ��
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

string cut(string becut, string str)
{
	int counts[26] = { 0 };
	//ͳ��becut�и�����ĸ���ֵĴ���
	for (int i = 0;i < becut.size();i++){
		counts[becut[i] - 'a']++;
	}
	//becut - str
	for (int i = 0;i < str.size();i++){
		counts[str[i] - 'a']--;
	}
	string newtarget;
	for (int i = 0;i < 26;i++){
		if (counts[i] > 0)
			newtarget.append(counts[i], (char)(i + 'a'));
	}
	return newtarget;
}
int _minSticks1(vector<string>& stickers, string target)
{
	if (target.size() == 0)
		return 0;
	int minans = INT_MAX;
	//������Ƭ
	for (int i = 0;i < stickers.size();i++)
	{
		string newtarget = cut(target, stickers[i]);
		//��ǰ��Ƭ����
		if (newtarget.size() != target.size()) {
			minans = min(minans, _minSticks1(stickers, newtarget));
		}
	}
	//min����ϵͳ���ֵ���п�Ƭ��û����С����
	//������ֻ��min��Ϊϵͳ���ֵ��Ӧ��min+1
	//��ʾ���ϵ�һ��ʹ�õĿ�Ƭ
	return minans + (minans == INT_MAX ? 0 : 1);
}

string cut2(vector<int> becut,const vector<int>& str)
{
	for (int i = 0;i < becut.size();i++){
		becut[i] -= str[i];
	}
	string newtarget;
	for (int i = 0;i < becut.size();i++) {
		if (becut[i] > 0)
			newtarget.append(becut[i], (char)(i + 'a'));
	}
	return newtarget;

}

int _minSticks2(const vector<vector<int>>& count_sticks, string target, unordered_map<string, int>& dp)
{
	if (dp.find(target) != dp.end()) {
		return dp[target];
	}

	int minans = INT_MAX;
	if (target.size() == 0) {
		minans = 0;
		return minans;
	}
		
	//ͳ��target�Ĵ�Ƶ
	vector<int> count_target(26, 0);
	for (int i = 0;i < target.size();i++){
		count_target[target[i] - 'a']++;
	}

	//������Ƭ
	for (int i = 0;i < count_sticks.size();i++)
	{
		//��ǰ��ֽ����target������ĸ
		if (count_sticks[i][target[0] - 'a'] > 0) {
			string newtarget = cut2(count_target, count_sticks[i]);
			minans = min(minans, _minSticks2(count_sticks, newtarget,dp));

		}
	}
	//min����ϵͳ���ֵ���п�Ƭ��û����С����
	//������ֻ��min��Ϊϵͳ���ֵ��Ӧ��min+1
	//��ʾ���ϵ�һ��ʹ�õĿ�Ƭ
	minans += minans == INT_MAX ? 0 : 1;
	dp.insert({ target,minans });
	return minans;
}


int minStickers(vector<string>& stickers, string target)
{
	//int ret = _minSticks1(stickers, target);

	//����ֽ�Ĵ�Ƶ
	vector<vector<int>> count_sticks(stickers.size(), vector<int>(26, 0));
	//������ֽ
	for (int i=0;i<stickers.size();i++)
	{
		//ͳ�Ƶ�ǰ��ֽ�Ĵ�Ƶ
		for (int j = 0;j < stickers[i].size();j++)
			count_sticks[i][stickers[i][j] - 'a']++;
	}

	unordered_map<string, int> dp;

	int ret = _minSticks2(count_sticks, target,dp);
	return ret == INT_MAX ? -1 : ret;
}


int main()
{
	vector<string> stickers{ "control","heart","interest","stream","sentence","soil","wonder","them","month","slip","table","miss","boat","speak","figure","no","perhaps","twenty","throw","rich","capital","save","method","store","meant","life","oil","string","song","food","am","who","fat","if","put","path","come","grow","box","great","word","object","stead","common","fresh","the","operate","where","road","mean" };
	string target = "stoodcrease";
	cout << minStickers(stickers, target) << endl;

	//stickers = ["notice","possible"], target = "basicbasic"
	// 
	// 
	//string newstr = cut(target, stickers[0]);
	//cout << newstr << endl;
	//newstr = cut(newstr, stickers[0]);
	//cout << newstr << endl;
	//newstr = cut(newstr, stickers[1]);
	//cout << newstr << endl;
	//return 0;

}