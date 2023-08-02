#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

//�� ���� �׽�Ʈ �Լ��� �ۼ��Ѵ�. ���⼭�� f(x)=x^2�Լ��� ����Ͽ� ���ڷ� �Ѿ�� ������ ��� ���Ҹ� �����Ѵ�.
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
	cout << "[�� �׽�Ʈ]" << endl;
	cout << "�Է� �迭,S: ";

	for (const auto& i : S)
	{
		cout << i << " ";
	}
	cout << endl;

	//transform�Լ� ���
	transform(S.begin(), S.end(), back_inserter(Tr), [](const int& x) {
		return pow(x, 2.0);
		});

	cout << "std::transform(), Tr: ";
	for (auto i : Tr)
	{
		cout << i << " ";
	}
	cout << endl;

	//std::for_each�Լ� ���
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
	cout << endl << "[���ེ �׽�Ʈ]" << endl;
	cout << "�Է� �迭, S: ";
	for (const auto& i : S)
	{
		cout << i << " ";
	}
	cout << endl;

	//accumulate�Լ� ���
	//�� ��° �Ű������� �������� �ʱ갪�̴�.
	auto ans = accumulate(S.begin(), S.end(), 0, [](const int& acc, const int& x) {
		return acc + x;
		});
	cout << "std::accumulate(), ans: " << ans << endl;r
}