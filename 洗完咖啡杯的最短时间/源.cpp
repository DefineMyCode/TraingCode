//有n个人来喝咖啡他们有k个选择
//分别是m0 m1 m2 ... mk-1 表示有这么多台咖啡机
//m0 做好一杯咖啡的时间为 w0 m1-w1 ...
//每台咖啡机做好一杯咖啡后才能继续做但
//k台咖啡机可以同时做咖啡
//现有一台洗咖啡杯的机器它需要 wash 的时间来清洗
//咖啡杯不能同时洗 但是咖啡杯也可以
//在 air 的时间后挥发干净 即不需要再清洗了 挥发可以同时进行
//但不能即洗又挥发
//假设每个来喝咖啡的人拿到咖啡就喝完
//问从每个人都喝完咖啡到 每个咖啡杯都变干净最少需要多少时间

#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//咖啡机
class Machine {
public:
	Machine() {
		usabletime = 0;
		worktime = 0;
	}
	Machine(int usa, int work) {
		this->usabletime = usa;
		this->worktime = work;
	}

	//可用时间
	int usabletime;
	//泡咖啡时间
	int worktime;
};

bool MachineCompare(const Machine& a, const Machine& b) {
	return a.usabletime + a.worktime > b.usabletime + b.worktime;
}

void PrintMachine(const Machine& a) {
	cout << "usabletime: " << a.usabletime << ' ' << "worktime:" << a.worktime << endl;
}

//求出每杯咖啡喝完的时间节点
vector<int> GetDrinks(vector<Machine> ms, int n)
{
	////建堆
	//cout << "after make_heap:" << endl;
	//make_heap(ms.begin(), ms.end(), MachineCompare);

	//for (int i = 0;i < ms.size();i++)
	//	PrintMachine(ms[i]);

	//每杯咖啡喝完的时间节点
	vector<int> drinks;

	//做出排队的最优解 即每个人喝完咖啡的短时间
	for (int i = 0;i < n;i++) {
		Machine curM = ms[0];

		//cout << "curM:";
		//PrintMachine(curM);

		curM.usabletime += curM.worktime;
		drinks.push_back(curM.usabletime);

		pop_heap(ms.begin(), ms.end(), MachineCompare);

		ms.pop_back();
		ms.push_back(curM);
		push_heap(ms.begin(), ms.end(), MachineCompare);
	}

	//cout << "drinks:" << endl;
	//for (int i = 0;i < drinks.size();i++)
	//	cout << drinks[i] << ' ';
	//cout << endl;

	return drinks;
}

//当前咖啡杯 洗的机器啥时候可用
int _EndTime(int curcap,int free,const vector<int>& drinks,int n,int wash,int air)
{
	//没有杯子了
	if (curcap == drinks.size())
		return 0;
	//选择用机器来洗当前杯子
	int curend_wash = max(free, drinks[curcap]) + wash;
	//剩下的杯子需要的最短时间
	int curend1 = _EndTime(curcap + 1, curend_wash, drinks, n, wash, air);
	//当前选择的最终时间是以最后一个杯子变干净来算的 因此取max
	int p1 = max(curend_wash, curend1);

	//选择让当前杯子挥发变干净
	int curend_air = max(free, drinks[curcap]) + air;
	//剩下的杯子需要的最短时间
	int curend2 = _EndTime(curcap + 1, free, drinks, n, wash, air);
	//当前选择的最终时间是以最后一个杯子变干净来算的 因此取max
	int p2 = max(curend_air, curend2);

	return min(p1, p2);
}

//                        咖啡机 n个人 洗一个杯子的时机 挥发干净需要的时间        
int EndTime(vector<Machine> ms, int n, int wash, int air)
{
	if (n <= 0)
		return 0;
	vector<int> drinks = GetDrinks(ms, n);
	return _EndTime(0, 0, drinks, n, wash, air);
}

int EndTimedp(vector<Machine> ms, int n, int wash, int air)
{
	if (n <= 0)
		return 0;
	vector<int> drinks = GetDrinks(ms, n);

	//int curcap, int free, const vector<int>& drinks, int n, int wash, int air
	//free不容易确定 直接设为最大情况
	int maxfree = 0;
	for (int curcap = 0;curcap < n;curcap++) {
		maxfree = max(maxfree, drinks[curcap]) + wash;
	}

	vector<vector<int>> dp(n + 1, vector<int>(maxfree + 1, 0));

	for (int curcap = n - 1;curcap >= 0;curcap--) {
		for (int free = 0;free <= maxfree;free++) {
			//选择用机器来洗当前杯子
			int curend_wash = max(free, drinks[curcap]) + wash;
			//不可能有比maxfree还大的情况
			if (curend_wash > maxfree)
				continue;
			//剩下的杯子需要的最短时间
			int curend1 = dp[curcap + 1][curend_wash];
			//当前选择的最终时间是以最后一个杯子变干净来算的 因此取max
			int p1 = max(curend_wash, curend1);

			//选择让当前杯子挥发变干净
			int curend_air = max(free, drinks[curcap]) + air;
			//不可能有比maxfree还大的情况
			if (curend_air > maxfree)
				continue;
			//剩下的杯子需要的最短时间
			int curend2 = dp[curcap + 1][free];
			//当前选择的最终时间是以最后一个杯子变干净来算的 因此取max
			int p2 = max(curend_air, curend2);
			dp[curcap][free] = min(p1, p2);
		}
	}
	return dp[0][0];
}


int main()
{
	Machine m0(0, 5), m1(0, 6), m2(0, 8), m3(0, 8), m4(0, 4);
	vector<Machine> ms{ m0,m1,m2,m3,m4 };
	Machine mm0(0, 1), mm1(0, 3), mm2(0, 4);
	vector<Machine> ms1{ mm0,mm1,mm2 };

	//n=4 13
	int n = 30, wash = 5, air = 6;
	
	clock_t begindp = clock();
	int endtime1 = EndTimedp(ms, n, wash, air);
	clock_t enddp = clock();
	cout << endl << "EndTimedp_ms EndTime:" << endl;
	cout << endtime1 << endl<<"run dptime:"<<enddp-begindp;

	clock_t beginRe= clock();
	int endtime = EndTime(ms, n, wash, air);
	clock_t endRe = clock();
	cout << endl << "EndTime_ms EndTime:" << endl;
	cout << endtime << endl << "run Retime:" << endRe - beginRe;
	

//	n = 8;
	n = 30;
	begindp = clock();
	endtime1 = EndTimedp(ms1, n, wash, air);
	enddp = clock();
	cout << endl << "EndTimedp_ms1 EndTime:" << endl;
	cout << endtime1 << endl << "run dptime:" << enddp - begindp;

	beginRe = clock();
	endtime = EndTime(ms1, n, wash, air);
	endRe = clock();
	cout << endl << "EndTime_ms1 EndTime:" << endl;
	cout << endtime << endl << "run Retime:" << endRe - beginRe;

	return 0;
}