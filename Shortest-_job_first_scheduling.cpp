#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

//��� ��� �ð� ��� �� ��� �Լ��� �߰��Ѵ�.
template<typename T>
auto compute_waiting_times(vector<T>& service_times)
{
	vector<T> W(service_times.size());
	W[0] = 0;

	for (register int i=1; i < service_times.size(); ++i)
	{
		W[i] = W[i - 1] + service_times[i - 1];
		//W[1]= W[0]+service_times[0];
		//W[2]=W[1]+service_times[1];
		//W[3]=W[2]+service_times[2];
		//���� size�� 5�̸� 
		//W[4] = W[3]+service_times[3];
	}

	return W;
}

template<typename T>
void print_vector(vector<T>& V)
{
	for (const auto& i : V)
	{
		cout.width(2);
		cout << i << " ";
	}
	cout << endl;
}

template<typename T>
void compute_and_print_waiting_times(vector<T>& service_times)
{
	auto waiting_times = compute_waiting_times<int>(service_times);

	cout << "-ó�� �ð�: ";
	print_vector<T>(service_times);

	cout << "-��� �ð�: ";
	print_vector<T>(waiting_times);

	//�ʱ갪�� 0.0���� �༭ double�� ���ǰ� �Ѵ�. ��� ��� �ð��� �Ǽ��� ����Ѵ�.
	//�������� size�� ����� double�� Ȯ��Ǿ� ���Ǳ� ������ ������� double�̴�.
	auto ave_waiting_times = accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();

	cout << "-��� ��� �ð�: " << ave_waiting_times;

	cout << endl;
}

int main()
{
	vector<int> service_times{8, 1, 2, 4, 9, 2, 3, 5};

	cout << "ó�� �� ó���ð� & ��� �ð�" << endl;

	//�� ó�� �ð��� ������������ ����
	sort(service_times.begin(), service_times.end());

	cout << endl;
	cout << "���� �� �� ó�� �ð� & ��� �ð�" << endl;
	compute_and_print_waiting_times<int>(service_times);
	return 0;
}