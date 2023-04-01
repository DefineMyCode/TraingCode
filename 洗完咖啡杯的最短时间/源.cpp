//有n个人来喝咖啡他们有k个选择
//分别是m0 m1 m2 ... mk-1 表示有这么多台咖啡机
//m0 做好一杯咖啡的时间为 w0 m1-w1 ...
//每台咖啡机做好一杯咖啡后才能继续做但
//k台咖啡机可以同时做咖啡
//现有一台洗咖啡杯的机器它需要 t1 的时间来清洗
//咖啡杯不能同时洗 但是咖啡杯也可以
//在t2 的时间后挥发干净 即不需要再清洗了 挥发可以同时进行
//但不能即洗又挥发
//假设每个来喝咖啡的人拿到咖啡就喝完
//问从每个人都喝完咖啡到 每个咖啡杯都变干净最少需要多少时间

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

int main()
{
	Machine m0(0, 1), m1(0, 3), m2(0, 4), m3(0, 4), m4(0, 5);
	vector<Machine> ms{ m0,m1,m2 };
	int n = 10;

	for (int i = 0;i < ms.size();i++)
		PrintMachine(ms[i]);

	//建堆
	cout << "after make_heap:" << endl;
	make_heap(ms.begin(), ms.end(), MachineCompare);

	for (int i = 0;i < ms.size();i++)
		PrintMachine(ms[i]);

	vector<int> drinks;
	
	//做出排队的最优解 即每个人喝完咖啡的短时间
	for (int i = 0;i < n;i++) {
		Machine curM = ms[0];
		cout << "curM:";
		PrintMachine(curM);

		curM.usabletime += curM.worktime;
		drinks.push_back(curM.usabletime);

		pop_heap(ms.begin(), ms.end(), MachineCompare);

		ms.pop_back();
		ms.push_back(curM);
		push_heap(ms.begin(), ms.end(), MachineCompare);
	}

	cout << "drinks:" << endl;
	for (int i = 0;i < drinks.size();i++)
		cout << drinks[i] << ' ';


	return 0;
}