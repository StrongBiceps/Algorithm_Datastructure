#include <iostream>
#include <climits>
using namespace std;

int W[2001][2001] = { 0 };
int B[2001][2001] = { 0 };
int Result = INT_MAX;

int N, K, M;

//입력된 N,M과 동일한 크기의 멀쩡한 체스판 2 개를 먼저 준비한다.

//그리고 주어진 체스판과 비교해서 같은 색깔이면 0을, 다른 색깔이면 1을 각각의 준비된 멀쩡한 체스판에 다시 기록한다.

//그리고 각 체스판에 적힌 0,1을 더한 각 인덱스의 누적합을 계산하여 다시 2차원 배열을 누적합으로 갱신한다.

//그리고 주어진 크기 K크기의 체스판 만큼 누적합을 비교하면서 가장 작은 누적합을 찾는다.

//멀쩡한 체스판 2개는 각각 (1,1)의 색깔이 검정색,하얀색인 배열이다. 즉 체스판은 처음 색깔이 두 가지 경우로 나뉜다.

//그러면 두 체스판과 색깔이 얼마나 다른지 비교해서, 가장 색깔 차이가 적은 체스판으로 주어진 체스판을 색칠한다면, 가장

//적은 경우의 수로 색칠하여 멀쩡한 체스판을 만드는 경우가 될 것이다.

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
		//열이 짝수이면 다음 행의 첫 번째 열이 같은 색깔로 칠해지므로 한 번 바꿔줘야 한다.
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