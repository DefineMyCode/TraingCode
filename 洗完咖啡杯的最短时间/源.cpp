//��n�������ȿ���������k��ѡ��
//�ֱ���m0 m1 m2 ... mk-1 ��ʾ����ô��̨���Ȼ�
//m0 ����һ�����ȵ�ʱ��Ϊ w0 m1-w1 ...
//ÿ̨���Ȼ�����һ�����Ⱥ���ܼ�������
//k̨���Ȼ�����ͬʱ������
//����һ̨ϴ���ȱ��Ļ�������Ҫ wash ��ʱ������ϴ
//���ȱ�����ͬʱϴ ���ǿ��ȱ�Ҳ����
//�� air ��ʱ���ӷ��ɾ� ������Ҫ����ϴ�� �ӷ�����ͬʱ����
//�����ܼ�ϴ�ֻӷ�
//����ÿ�����ȿ��ȵ����õ����Ⱦͺ���
//�ʴ�ÿ���˶����꿧�ȵ� ÿ�����ȱ�����ɾ�������Ҫ����ʱ��

#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//���Ȼ�
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

	//����ʱ��
	int usabletime;
	//�ݿ���ʱ��
	int worktime;
};

bool MachineCompare(const Machine& a, const Machine& b) {
	return a.usabletime + a.worktime > b.usabletime + b.worktime;
}

void PrintMachine(const Machine& a) {
	cout << "usabletime: " << a.usabletime << ' ' << "worktime:" << a.worktime << endl;
}

//���ÿ�����Ⱥ����ʱ��ڵ�
vector<int> GetDrinks(vector<Machine> ms, int n)
{
	////����
	//cout << "after make_heap:" << endl;
	//make_heap(ms.begin(), ms.end(), MachineCompare);

	//for (int i = 0;i < ms.size();i++)
	//	PrintMachine(ms[i]);

	//ÿ�����Ⱥ����ʱ��ڵ�
	vector<int> drinks;

	//�����Ŷӵ����Ž� ��ÿ���˺��꿧�ȵĶ�ʱ��
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

//��ǰ���ȱ� ϴ�Ļ���ɶʱ�����
int _EndTime(int curcap,int free,const vector<int>& drinks,int n,int wash,int air)
{
	//û�б�����
	if (curcap == drinks.size())
		return 0;
	//ѡ���û�����ϴ��ǰ����
	int curend_wash = max(free, drinks[curcap]) + wash;
	//ʣ�µı�����Ҫ�����ʱ��
	int curend1 = _EndTime(curcap + 1, curend_wash, drinks, n, wash, air);
	//��ǰѡ�������ʱ���������һ�����ӱ�ɾ������ ���ȡmax
	int p1 = max(curend_wash, curend1);

	//ѡ���õ�ǰ���ӻӷ���ɾ�
	int curend_air = max(free, drinks[curcap]) + air;
	//ʣ�µı�����Ҫ�����ʱ��
	int curend2 = _EndTime(curcap + 1, free, drinks, n, wash, air);
	//��ǰѡ�������ʱ���������һ�����ӱ�ɾ������ ���ȡmax
	int p2 = max(curend_air, curend2);

	return min(p1, p2);
}

//                        ���Ȼ� n���� ϴһ�����ӵ�ʱ�� �ӷ��ɾ���Ҫ��ʱ��        
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
	//free������ȷ�� ֱ����Ϊ������
	int maxfree = 0;
	for (int curcap = 0;curcap < n;curcap++) {
		maxfree = max(maxfree, drinks[curcap]) + wash;
	}

	vector<vector<int>> dp(n + 1, vector<int>(maxfree + 1, 0));

	for (int curcap = n - 1;curcap >= 0;curcap--) {
		for (int free = 0;free <= maxfree;free++) {
			//ѡ���û�����ϴ��ǰ����
			int curend_wash = max(free, drinks[curcap]) + wash;
			//�������б�maxfree��������
			if (curend_wash > maxfree)
				continue;
			//ʣ�µı�����Ҫ�����ʱ��
			int curend1 = dp[curcap + 1][curend_wash];
			//��ǰѡ�������ʱ���������һ�����ӱ�ɾ������ ���ȡmax
			int p1 = max(curend_wash, curend1);

			//ѡ���õ�ǰ���ӻӷ���ɾ�
			int curend_air = max(free, drinks[curcap]) + air;
			//�������б�maxfree��������
			if (curend_air > maxfree)
				continue;
			//ʣ�µı�����Ҫ�����ʱ��
			int curend2 = dp[curcap + 1][free];
			//��ǰѡ�������ʱ���������һ�����ӱ�ɾ������ ���ȡmax
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