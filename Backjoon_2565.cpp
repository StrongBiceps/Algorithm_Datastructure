#include <iostream>
#include <algorithm>
using namespace std;

//이 문제의 핵심은 최장 길이 증가하는 부분 수열을 구하는 문제와 다를 것이 없다. 하지만 생각이 그 논리까지 도달하는 것이

//어려웠던 문제이다. 

//일단 전봇대 A의 포인트가 오름차순으로 입력되는 것이 아니라 무작위의 순서로 입력되는 것에 유의해야 한다.

//전봇대 A를 오름차순으로 정렬하여 생각하는 문제이다. 정렬하고 난 후에 전봇대 B의 포인트가 증가하는 수열이 아닌 경우 포인트를

//제외한 경우가 답이 될 것이다. 따라서 전깃줄 개수에서 증가하는 부분 수열의 길이를 빼면 감소하는 수열의 길이가 된다. 

//감소하는 수열이 있으면 반드시 겹치게 된다. 따라서 제거해야만 한다. 결국 겹치지 않게 전깃줄을 제거하는 최소 갯수는

//최장 길이 증가 부분 수열을 뺀 값이 된다.
class Line
{
public:
	int A = 0;
	int B = 0;
};

int N;
int DP[100] = { 0 };
Line line[100] = { 0 };
int Result = 0;

bool Comp(Line& Temp1, Line& Temp2)
{
	return Temp1.A < Temp2.A;
}

int main()
{
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> line[i].A >> line[i].B;
	}

	sort(line, line + N - 1, Comp);

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (line[i].B > line[j].B)
			{
				DP[i] = max(DP[i], DP[j] + 1);
			}
		}

		Result = max(Result, DP[i]);
	}

	cout << Result - N;
}