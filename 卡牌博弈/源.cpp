//给定一个整型数组arr,代表数值不同的纸牌排成一条线
//玩家A和玩家B依次拿走每张纸牌
//规定玩家A先拿，玩家B后拿
//但是每个玩家每次只能拿走最右或最左的纸牌
//玩家A和玩家B都绝顶聪明
//请返回最后获胜者的分数

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//当前是我拿牌
int f(vector<int>& arr, int L, int R);

//对手拿牌
int g(vector<int>& arr, int L, int R);

void PrintAns(vector<int>& arr)
{
	if (arr.size() == 0)
	{
		cout << "A B得分都为0" << endl;
		return;
	}
		
	int L = 0, R = arr.size() - 1;
	int first = f(arr, L, R);
	int seconed = g(arr, L, R);
	if (first > seconed)
		cout << "获胜者为A:" << first << endl;
	else
		cout<< "获胜者为B:" << seconed << endl;
}

//对手拿牌
int g1(vector<int>& arr, int L, int R,vector<vector<int>>& fmap, vector<vector<int>>& gmap)
{
	if (gmap[L][R] != -1)
		return gmap[L][R];
	//只剩一张牌了 我是后手所以没牌拿了
	int ans = 0;
	if (L == R)
		ans = 0;

	//对手拿了左边的牌
	int p1 = f(arr, L + 1, R);
	//对手拿了右边的牌
	int p2 = f(arr, L, R - 1);
	ans = min(p1, p2);
	//由于我是后手 那对手一定会让我拿最差情况
	gmap[L][R] = ans;
	return ans;
}

//先手获得的最好分数返回
int f1(vector<int>& arr, int L, int R, vector<vector<int>>& fmap, vector<vector<int>>& gmap)
{
	if (fmap[L][R] != -1)
		return fmap[L][R];
	int ans = 0;
	//只剩一张牌了
	if (L == R)
		ans = arr[L];
	//其他情况就拿左然后后手或右然后后手的最大值
	int p1 = arr[L] + g1(arr, L + 1, R,fmap,gmap);
	int p2 = arr[R] + g1(arr, L, R - 1,fmap,gmap);
	ans = max(p1, p2);
	fmap[L][R] = ans;
	return ans;
}

//加缓存
void PrintAns2(vector<int>& arr)
{
	if (arr.size() == 0)
	{
		cout << "A B得分都为0" << endl;
		return;
	}
	vector<vector<int>> fmap(arr.size(), vector<int>(arr.size(),-1));
	vector<vector<int>> gmap(arr.size(), vector<int>(arr.size(),-1));
	int L = 0, R = arr.size() - 1;
	int first = f1(arr, L, R,fmap,gmap);
	int seconed = g1(arr, L, R,fmap,gmap);
	if (first > seconed)
		cout << "获胜者为A:" << first << endl;
	else
		cout << "获胜者为B:" << seconed << endl;
}

//dp
void PrintAns3(vector<int>& arr)
{
	if (arr.size() == 0)
	{
		cout << "A B得分都为0" << endl;
		return;
	}
	vector<vector<int>> fmap(arr.size(), vector<int>(arr.size(), 0));
	vector<vector<int>> gmap(arr.size(), vector<int>(arr.size(), 0));
	int L = 0, R = arr.size() - 1;
	//设置对角为卡牌的面额
	for (int i = L;i <= R;i++){
		fmap[i][i] = arr[i];
	}

	//填fmap 与gmap
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
		cout << "获胜者为A:" << first << endl;
	else
		cout << "获胜者为B:" << seconed << endl;
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

//对手拿牌
int g(vector<int>& arr, int L, int R)
{
	//只剩一张牌了 我是后手所以没牌拿了
	if (L == R)
		return 0;
	
	//对手拿了左边的牌
	int p1 = f(arr, L + 1, R);
	//对手拿了右边的牌
	int p2 = f(arr, L, R - 1);

	//由于我是后手 那对手一定会让我拿最差情况
	return min(p1,p2);
}

//先手获得的最好分数返回
int f(vector<int>& arr, int L, int R)
{
	//只剩一张牌了
	if (L == R)
		return arr[L];
	//其他情况就拿左然后后手或右然后后手的最大值
	int p1 = arr[L] + g(arr, L + 1, R);
	int p2 = arr[R] + g(arr, L, R - 1);
	return max(p1,p2);
}