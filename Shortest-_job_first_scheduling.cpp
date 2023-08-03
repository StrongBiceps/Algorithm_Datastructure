#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

//평균 대기 시간 계산 및 출력 함수를 추가한다.
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
		//만약 size가 5이면 
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

	cout << "-처리 시간: ";
	print_vector<T>(service_times);

	cout << "-대기 시간: ";
	print_vector<T>(waiting_times);

	//초깃값을 0.0으로 줘서 double로 계산되게 한다. 평균 대기 시간은 실수로 출력한다.
	//마지막에 size로 나누어도 double로 확장되어 계산되기 때문에 결과값은 double이다.
	auto ave_waiting_times = accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();

	cout << "-평균 대기 시간: " << ave_waiting_times;

	cout << endl;
}

int main()
{
	vector<int> service_times{8, 1, 2, 4, 9, 2, 3, 5};

	cout << "처음 일 처리시간 & 대기 시간" << endl;

	//일 처리 시간을 오름차순으로 정렬
	sort(service_times.begin(), service_times.end());

	cout << endl;
	cout << "정렬 후 일 처리 시간 & 대기 시간" << endl;
	compute_and_print_waiting_times<int>(service_times);
	return 0;
}