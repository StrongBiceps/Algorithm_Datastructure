#include <iostream>
#include <climits>
using namespace std;

int W[2001][2001] = { 0 };
int B[2001][2001] = { 0 };
int Result = INT_MAX;

int N, K, M;

//�Էµ� N,M�� ������ ũ���� ������ ü���� 2 ���� ���� �غ��Ѵ�.

//�׸��� �־��� ü���ǰ� ���ؼ� ���� �����̸� 0��, �ٸ� �����̸� 1�� ������ �غ�� ������ ü���ǿ� �ٽ� ����Ѵ�.

//�׸��� �� ü���ǿ� ���� 0,1�� ���� �� �ε����� �������� ����Ͽ� �ٽ� 2���� �迭�� ���������� �����Ѵ�.

//�׸��� �־��� ũ�� Kũ���� ü���� ��ŭ �������� ���ϸ鼭 ���� ���� �������� ã�´�.

//������ ü���� 2���� ���� (1,1)�� ������ ������,�Ͼ���� �迭�̴�. �� ü������ ó�� ������ �� ���� ���� ������.

//�׷��� �� ü���ǰ� ������ �󸶳� �ٸ��� ���ؼ�, ���� ���� ���̰� ���� ü�������� �־��� ü������ ��ĥ�Ѵٸ�, ����

//���� ����� ���� ��ĥ�Ͽ� ������ ü������ ����� ��찡 �� ���̴�.

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;

	bool Black = false;
	bool White = true;

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			B[i][j] = Black;
			W[i][j] = White;
			Black = !Black;
			White = !White;
		}
		//���� ¦���̸� ���� ���� ù ��° ���� ���� ����� ĥ�����Ƿ� �� �� �ٲ���� �Ѵ�.
		if (M % 2 == 0)
		{
			Black = !Black;
			White = !White;
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			char Character;
			cin >> Character;

			int Color = 0;

			if (Character == 'B')
			{
				Color = 0;
			}
			else
			{
				Color = 1;
			}

			B[i][j] = Color ^ B[i][j];
			W[i][j] = Color ^ W[i][j];

			B[i][j] = B[i - 1][j] + B[i][j - 1] + B[i][j] - B[i - 1][j - 1];
			W[i][j] = W[i - 1][j] + W[i][j - 1] + W[i][j] - W[i - 1][j - 1];
		}
	}

	pair<int, int> str;
	pair<int, int> end;

	for (int i = 1; i <= N - K + 1; ++i)
	{
		for (int j = 1; j <= M - K + 1; ++j)
		{
			str.first = i;
			str.second = j;
			end.first = i + K - 1;
			end.second = j + K - 1;

			Result = min(Result, B[end.first][end.second]
				- B[str.first - 1][end.second]
				- B[end.first][str.second - 1]
				+ B[str.first - 1][str.second - 1]);
			Result = min(Result, W[end.first][end.second]
				- W[str.first - 1][end.second]
				- W[end.first][str.second - 1]
				+ W[str.first - 1][str.second - 1]);
		}
	}

	cout << Result;
}