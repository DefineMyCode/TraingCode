//https://leetcode.cn/problems/stickers-to-spell-word/
//我们有 n 种不同的贴纸。每个贴纸上都有一个小写的英文单词。
//您想要拼写出给定的字符串 target ，方法是从收集的贴纸中切
//割单个字母并重新排列它们。如果你愿意，你可以多次使用每个
//贴纸，每个贴纸的数量是无限的。
//返回你需要拼出 target 的最小贴纸数量。如果任务不可能，则返回 - 1 。
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

string cut(string becut, string str)
{
	int counts[26] = { 0 };
	//统计becut中各个字母出现的次数
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
	//遍历卡片
	for (int i = 0;i < stickers.size();i++)
	{
		string newtarget = cut(target, stickers[i]);
		//当前卡片有用
		if (newtarget.size() != target.size()) {
			minans = min(minans, _minSticks1(stickers, newtarget));
		}
	}
	//min还是系统最大值所有卡片都没用最小方法
	//不存在只有min不为系统最大值则应将min+1
	//表示加上第一次使用的卡片
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
		
	//统计target的词频
	vector<int> count_target(26, 0);
	for (int i = 0;i < target.size();i++){
		count_target[target[i] - 'a']++;
	}

	//遍历卡片
	for (int i = 0;i < count_sticks.size();i++)
	{
		//当前贴纸中有target的首字母
		if (count_sticks[i][target[0] - 'a'] > 0) {
			string newtarget = cut2(count_target, count_sticks[i]);
			minans = min(minans, _minSticks2(count_sticks, newtarget,dp));

		}
	}
	//min还是系统最大值所有卡片都没用最小方法
	//不存在只有min不为系统最大值则应将min+1
	//表示加上第一次使用的卡片
	minans += minans == INT_MAX ? 0 : 1;
	dp.insert({ target,minans });
	return minans;
}


int minStickers(vector<string>& stickers, string target)
{
	//int ret = _minSticks1(stickers, target);

	//求贴纸的词频
	vector<vector<int>> count_sticks(stickers.size(), vector<int>(26, 0));
	//遍历贴纸
	for (int i=0;i<stickers.size();i++)
	{
		//统计当前贴纸的词频
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