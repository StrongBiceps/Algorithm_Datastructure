#include <iostream>
using namespace std;

//long long으로 하지 않으면 점수가 100점이 나오지 않는다.

//이 문제의 로직은 현재 주유소보다 싼 가격의 주유소를 발견하면 무조건 경유한다는 점이다.

//즉, 현재 주유소에서 출발하여 다음으로 싼 주유소를 발견할 때 까지 거리를 누적시키고 발견하면, 원래의 주유소 가격에 누적 거리를

//곱한다. 그러면, 가장 싼 가격으로 매 번 주유소를 선택할 수 있다.
int N;
int Dist[100001] = { 0 };
int Value[100001] = { 0 };
long long Result = 0;

int main()
{
	cin >> N;

	for (int i = 0; i < N-1; ++i)
	{
		cin >> Dist[i];
	}

	for (int i = 0; i < N; ++i)
	{
		cin >> Value[i];
	}

	int First = Value[0];
	int Index = 0;
	long long Distance = Dist[0];

	for (int i = 1; i < N; ++i)
	{
		if (i == N-1)
		{
			Result += (long long)(Value[Index] * Distance);
			break;
		}

		if (First > Value[i])
		{
			First = Value[i];
			Result += (long long)(Value[Index] * Distance);
			Distance = (long long)Dist[i];
			Index = i;
		}
		else
		{
			Distance += (long long)Dist[i];
		}
	}

	cout << Result;
}