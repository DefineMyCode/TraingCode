//��n�������ȿ���������k��ѡ��
//�ֱ���m0 m1 m2 ... mk-1 ��ʾ����ô��̨���Ȼ�
//m0 ����һ�����ȵ�ʱ��Ϊ w0 m1-w1 ...
//ÿ̨���Ȼ�����һ�����Ⱥ���ܼ�������
//k̨���Ȼ�����ͬʱ������
//����һ̨ϴ���ȱ��Ļ�������Ҫ t1 ��ʱ������ϴ
//���ȱ�����ͬʱϴ ���ǿ��ȱ�Ҳ����
//��t2 ��ʱ���ӷ��ɾ� ������Ҫ����ϴ�� �ӷ�����ͬʱ����
//�����ܼ�ϴ�ֻӷ�
//����ÿ�����ȿ��ȵ����õ����Ⱦͺ���
//�ʴ�ÿ���˶����꿧�ȵ� ÿ�����ȱ�����ɾ�������Ҫ����ʱ��

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

int main()
{
	Machine m0(0, 1), m1(0, 3), m2(0, 4), m3(0, 4), m4(0, 5);
	vector<Machine> ms{ m0,m1,m2 };
	int n = 10;

	for (int i = 0;i < ms.size();i++)
		PrintMachine(ms[i]);

	//����
	cout << "after make_heap:" << endl;
	make_heap(ms.begin(), ms.end(), MachineCompare);

	for (int i = 0;i < ms.size();i++)
		PrintMachine(ms[i]);

	vector<int> drinks;
	
	//�����Ŷӵ����Ž� ��ÿ���˺��꿧�ȵĶ�ʱ��
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