#include <iostream>
using namespace std;

//long long���� ���� ������ ������ 100���� ������ �ʴ´�.

//�� ������ ������ ���� �����Һ��� �� ������ �����Ҹ� �߰��ϸ� ������ �����Ѵٴ� ���̴�.

//��, ���� �����ҿ��� ����Ͽ� �������� �� �����Ҹ� �߰��� �� ���� �Ÿ��� ������Ű�� �߰��ϸ�, ������ ������ ���ݿ� ���� �Ÿ���

//���Ѵ�. �׷���, ���� �� �������� �� �� �����Ҹ� ������ �� �ִ�.
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