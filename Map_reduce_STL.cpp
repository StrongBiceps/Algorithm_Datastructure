#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

//맵 연산 테스트 함수를 작성한다. 여기서는 f(x)=x^2함수를 사용하여 인자로 넘어온 벡터의 모든 원소를 제곱한다.
void transform_test(vector<int> S);
void reduce_test(vector<int> S);

int main()
{
	vector<int> S{1, 10, 4, 7, 3, 5, 6, 9, 8, 2};

	transform_test(S);
	reduce_test(S);
	return 0;
}

void transform_test(vector<int> S)
{
	vector<int> Tr;
	cout << "[맵 테스트]" << endl;
	cout << "입력 배열,S: ";

	for (const auto& i : S)
	{
		cout << i << " ";
	}
	cout << endl;

	//transform함수 사용
	transform(S.begin(), S.end(), back_inserter(Tr), [](const int& x) {
		return pow(x, 2.0);
		});

	cout << "std::transform(), Tr: ";
	for (auto i : Tr)
	{
		cout << i << " ";
	}
	cout << endl;

	//std::for_each함수 사용
	for_each(S.begin(), S.end(), [](int& x) {
		x = pow(x, 2);
		});

	cout << "std::for_each(), S: ";
	for (auto i : S)
	{
		cout << i << " ";
	}
	cout << endl;
}

void reduce_test(vector<int> S)
{
	cout << endl << "[리듀스 테스트]" << endl;
	cout << "입력 배열, S: ";
	for (const auto& i : S)
	{
		cout << i << " ";
	}
	cout << endl;

	//accumulate함수 사용
	//세 번째 매개변수는 누적합의 초깃값이다.
	auto ans = accumulate(S.begin(), S.end(), 0, [](const int& acc, const int& x) {
		return acc + x;
		});
	cout << "std::accumulate(), ans: " << ans << endl;r
}